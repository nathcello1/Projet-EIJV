<?php
include_once 'db_connexion.php';

try {
    // Récupérer les actualités de la base de données
    $requete = $conn->query("SELECT * FROM actualites ORDER BY date_creation DESC");
    $actualites = $requete->fetchAll(PDO::FETCH_ASSOC);

    echo "<div class='actualite'>"; // Début du conteneur de la galerie

    foreach ($actualites as $actu) {
        // Décoder le JSON des images et les afficher
        $images = json_decode($actu['image']);
        if ($images) {
            foreach ($images as $image) {
                echo "<div class='actu'>";
                echo "<a href='detail_actu.php?id=" . $actu['id'] . "'>"; // Vérifiez ce lien
                echo "<img src='" . htmlspecialchars($image) . "' alt='Image' class='actualite-img'>";
                echo "</a>";
                
                // Afficher le bouton de suppression uniquement pour les administrateurs
                if (isset($_SESSION['type']) && $_SESSION['type'] === 'admin') {
                    echo "<form method='post' action='supprimer_actu.php'>";
                    echo "<input type='hidden' name='id_actu' value='" . $actu['id'] . "'>";
                    echo "<input type='submit' value='Supprimer' class='supprimer-btn'>";
                    echo "</form>";
                }
                echo "</div>";
                // Sortir de la boucle après l'affichage de la première image
                break;
            }
        }
    }

    echo "</div>"; // Fin du conteneur de la galerie
} catch (PDOException $e) {
    echo "Erreur : " . $e->getMessage();
}

// Fermer la connexion
$conn = null;
?>
