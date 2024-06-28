package fr.eijv.freijvprojetnote;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.firestore.FieldValue;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.QueryDocumentSnapshot;
import com.google.firebase.firestore.SetOptions;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ActiviteSecondare extends AppCompatActivity {

    private EditText monTexte;
    private FirebaseFirestore maBD;
    private RecyclerView recyclerView;
    private MessageAdapter messageAdapter;
    private List<Message> messagesList = new ArrayList<>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout_activite_secondaire);

        monTexte = findViewById(R.id.id_saisirLeMessage);
        maBD = FirebaseFirestore.getInstance();

        FirebaseUser user = FirebaseAuth.getInstance().getCurrentUser();
        if (user == null) { // Si une erreur avec le user ce produit alors on renvoie vers l'activité "activite_authentification"
            Intent intent = new Intent(this, activite_authentification.class);
            startActivity(intent);
            finish();
            return;
        }


        recyclerView = findViewById(R.id.id_RecyclerView);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        messageAdapter = new MessageAdapter(messagesList);
        recyclerView.setAdapter(messageAdapter);

        // on trie les champs de la collection "messages" via l'heure d'envoie avec "timestamp"
        maBD.collection("Messagerie").document("chat").collection("messages").orderBy("timestamp").addSnapshotListener((value, error) -> {
                    if (error != null) {
                        Log.e("ActiviteSecondare", "Erreur lors de la récupération des messages", error);
                        return;
                    }
                    // On ajoute a la variable correspondante le champ du message
                    if (value != null && !value.isEmpty()) {
                        messagesList.clear();
                        for (QueryDocumentSnapshot document : value) {
                            String contenu = document.getString("contenu");
                            String userId = document.getString("userId");
                            Object timestampObject = document.get("timestamp");
                            long timestamp;
                            // Permet de faire correspondre les différents timestamp au cas ou l'un des utilisateurs vois l'horloge de son telephone décalé par rapport aux autres
                            if (timestampObject instanceof com.google.firebase.Timestamp) {
                                timestamp = ((com.google.firebase.Timestamp) timestampObject).toDate().getTime();
                            } else if (timestampObject != null) {
                                timestamp = (long) timestampObject;
                            } else {
                                Log.w("ActiviteSecondare", "Timestamp est nul pour le document ID: " + document.getId());
                                continue;
                            }

                            Message message = new Message(userId, contenu, timestamp);
                            // On ajoute a message les différents éléments du message
                            messagesList.add(message);
                        }
                        messageAdapter.notifyDataSetChanged();
                        recyclerView.scrollToPosition(messagesList.size() - 1); // Affiche le dernier message et défile automatiquement vers celui-ci
                    }
                });
    }

    public static class MessageAdapter extends RecyclerView.Adapter<MessageAdapter.MessageViewHolder> { // Permet d'afficher dans le Recyclerview le contenu de messages
        private List<Message> messages;

        public MessageAdapter(List<Message> messages) {
            this.messages = messages;
        }

        @NonNull
        @Override
        public MessageViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_message, parent, false);
            return new MessageViewHolder(view);
        }

        @Override
        public void onBindViewHolder(@NonNull MessageViewHolder holder, int position) {
            Message message = messages.get(position);
            holder.bind(message);

            FirebaseUser currentUser = FirebaseAuth.getInstance().getCurrentUser();
            if (currentUser != null && currentUser.getEmail().equals(message.getUserId())) {
                holder.messageText.setBackgroundResource(R.drawable.message_bg_me);
                holder.messageText.setTextColor(Color.WHITE);
                holder.messageText.setGravity(Gravity.END);
            } else {
                holder.messageText.setBackgroundResource(R.drawable.message_bg_other);
                holder.messageText.setTextColor(Color.BLACK);
                holder.messageText.setGravity(Gravity.START);
            }
        }

        @Override
        public int getItemCount() {
            return messages.size();
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        public class MessageViewHolder extends RecyclerView.ViewHolder {

            private TextView messageText;

            public MessageViewHolder(@NonNull View itemView) {
                super(itemView);
                messageText = itemView.findViewById(R.id.ID_message_text);
            }

            public void bind(Message message) {
                String fullMessage = message.getContenu() + " : " + message.getUserId();
                messageText.setText(fullMessage);
            }
        }
    }

    public void Envoyer(View view) { // Permet d'ajouter un nouveau message a la BDD
        String contenuTexte = monTexte.getText().toString();
        FirebaseUser user = FirebaseAuth.getInstance().getCurrentUser();
        if (user != null) {
            String userId = user.getEmail();
            HashMap<String, Object> messageData = new HashMap<>();
            messageData.put("contenu", contenuTexte);
            messageData.put("userId", userId);
            messageData.put("timestamp", FieldValue.serverTimestamp());

            String messageId = maBD.collection("Messagerie").document().getId();

            maBD.collection("Messagerie").document("chat").collection("messages").document(messageId).set(messageData, SetOptions.merge()).addOnSuccessListener(aVoid -> { // Si l'ajoute dans la collection messages ce fait sans problème
                        // On actualiser la taille du RecyclerView afin de le faire descendre d'un cran
                        int position = messagesList.size() - 1;
                        if (position >= 0) {
                            recyclerView.scrollToPosition(position);
                            monTexte.getText().clear();
                        }
                    }).addOnFailureListener(e -> Log.e("ActiviteSecondare", "Erreur lors de l'envoi du message", e)); // Si le message ne s'ajoute pas correctement on affiche une message d'erreur
        }
    }




    public void Quitter(View view) {
        finish();
    }

    public class Message {
        private String contenu;
        private String userId;
        private long timestamp;

        public Message(String contenu, String userId, long timestamp) {
            this.contenu = contenu;
            this.userId = userId;
            this.timestamp = timestamp;
        }

        public String getContenu() {
            return contenu;
        }

        public String getUserId() {
            return userId;
        }

        public long getTimestamp() {
            return timestamp;
        }
    }

}

