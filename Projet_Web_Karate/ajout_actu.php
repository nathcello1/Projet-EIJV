<?php
include_once 'db_connexion.php';

try {
    // Récupérer les données du formulaire
    $titre = $_POST['titre'] ?? '';
    $description = $_POST['description'] ?? '';

    // Vérifier si des fichiers ont été correctement téléchargés
    if (!empty($_FILES['images']['tmp_name'][0])) {
        // Chemin où stocker les images téléchargées
        $upload_directory = "uploads/";
        $images = [];

        // Parcourir chaque fichier téléchargé
        foreach ($_FILES['images']['tmp_name'] as $index => $tmp_name) {
            if ($index >= 10)
                break; // Limiter à 10 images

            // Nom de l'image sur le serveur
            $image_name = $_FILES['images']['name'][$index];

            // Chemin complet où enregistrer l'image sur le serveur
            $image_path = $upload_directory . $image_name;

            // Déplacer l'image téléchargée vers le dossier d'uploads
            if (move_uploaded_file($tmp_name, $image_path)) {
                $images[] = $image_path; // Ajouter le chemin de l'image au tableau
            }
        }

        // Convertir le tableau d'images en chaîne JSON pour stockage
        $images_json = json_encode($images);

        // Préparer la requête d'insertion
        $requete = $conn->prepare("INSERT INTO actualites (titre, description, date_creation, image) VALUES (:titre, :description, NOW(), :images)");

        // Liaison des paramètres
        $requete->bindParam(':titre', $titre);
        $requete->bindParam(':description', $description);
        $requete->bindParam(':images', $images_json);

        $requete->execute();

        // Redirection vers la page d'actualités après l'ajout réussi
        header("Location: actualites.php");
        exit();
    } else {
        echo "Veuillez sélectionner au moins une image.";
    }
} catch (PDOException $e) {
    // En cas d'erreur de connexion, afficher l'erreur
    echo "Erreur : " . $e->getMessage();
}

$conn = null;
?>
