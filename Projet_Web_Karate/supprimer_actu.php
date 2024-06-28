<?php
// Vérifier si l'ID à supprimer a été envoyé
if (isset($_POST['id_actu'])) {
    include_once 'db_connexion.php';

    try {
        // Récupérer les noms des images à supprimer
        $requete_images = $conn->prepare("SELECT image FROM actualites WHERE id = :id_actu");
        $requete_images->bindParam(':id_actu', $_POST['id_actu']);
        $requete_images->execute();
        $resultat_images = $requete_images->fetch(PDO::FETCH_ASSOC);

        // Supprimer chaque image du dossier "uploads"
        $images = json_decode($resultat_images['image']);
        foreach ($images as $image) {
            // Construire le chemin complet du fichier à supprimer
            $chemin_image = "uploads/" . $image;
            // Supprimer le fichier
            if (file_exists($chemin_image)) {
                unlink($chemin_image);
            } else {
                echo "Le fichier $chemin_image n'existe pas.";
            }
        }

        // Préparer la requête de suppression dans la base de données
        $requete_suppression = $conn->prepare("DELETE FROM actualites WHERE id = :id_actu");
        $requete_suppression->bindParam(':id_actu', $_POST['id_actu']);

        // Exécuter la requête de suppression
        $requete_suppression->execute();

        // Redirection vers une page de confirmation ou une autre page après la suppression
        header("Location: actualites.php");
        exit();
    } catch (PDOException $e) {
        echo "Erreur : " . $e->getMessage();
    }

    $conn = null;
} else {
    // Redirection si l'ID  n'a pas été fourni
    header("Location: actualites.php");
    exit();
}
?>
