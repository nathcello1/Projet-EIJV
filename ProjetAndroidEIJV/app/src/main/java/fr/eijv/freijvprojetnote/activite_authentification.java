package fr.eijv.freijvprojetnote;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

import android.widget.Toast;

public class activite_authentification extends AppCompatActivity {


    private FirebaseAuth mAuth; // Pour l'authentification avec Firebase
    private EditText editTextEmail;
    private EditText editTextPassword;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activite_authentification);

        mAuth = FirebaseAuth.getInstance();
        editTextEmail = findViewById(R.id.ID_editTextEmail);
        editTextPassword = findViewById(R.id.ID_editTextPassword);
    }

    public void seConnecter(View view) {
        String email = editTextEmail.getText().toString();
        String password = editTextPassword.getText().toString();

        mAuth.signInWithEmailAndPassword(email, password).addOnCompleteListener(this, task -> {
                    if (task.isSuccessful()) {
                        Log.d("activity_activite_authentification", "signInWithEmail:success");
                        FirebaseUser user = mAuth.getCurrentUser(); // Compare l'utilisateur et le mot de passe entré avec ceux de Firebase
                        if (user != null) { // Si le user exista dans Firebase
                            Intent intent = new Intent(activite_authentification.this, ActiviteSecondare.class);
                            startActivity(intent); // Affiche "Bienvenue" et lance l'activité "ActiviteSecondare"
                            Toast.makeText(this, "Bienvenue".toString(), Toast.LENGTH_LONG).show();
                            finish();
                        }
                    } else { // Sinon on nettoie les champs et affiche un message d'erreur
                        editTextEmail.getText().clear();
                        editTextPassword.getText().clear();
                        Log.w("activity_activite_authentification", "signInWithEmail:failure", task.getException());
                        Toast.makeText(this, "Email ou mot de passe invalide".toString(), Toast.LENGTH_LONG).show();
                    }
                });
    }
}
