package fr.eijv.freijvprojetnote;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.google.firebase.firestore.FirebaseFirestore;

import java.util.Objects;

public class MainActivity extends AppCompatActivity {


    private FirebaseFirestore maBd;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void ConnexionBDD(View view) {
        this.maBd = FirebaseFirestore.getInstance(); // Se connecte a la Base De Donnée Firebase

        Toast.makeText(MainActivity.this, Objects.toString(Objects.nonNull(maBd)),Toast.LENGTH_SHORT).show(); // Si la connexion reussi affiche le message "true"
        Intent monIntent= new Intent(this, activite_authentification.class);
        startActivity(monIntent); // Lance l'activité "activite_authentification"
    }

    public void Quitter(View view) {
        finish(); // Quitte l'activité
    }
}

