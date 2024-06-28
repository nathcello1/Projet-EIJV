<?php
include_once 'db_connexion.php';

try {
    // Récupérer l'ID de la actualité depuis l'URL
    $id = isset($_GET['id']) ? intval($_GET['id']) : 0;

    // Récupérer les détails de la actualité depuis la base de données
    $requete = $conn->prepare("SELECT * FROM actualites WHERE id = :id");
    $requete->bindParam(':id', $id, PDO::PARAM_INT);
    $requete->execute();
    $actu = $requete->fetch(PDO::FETCH_ASSOC);

    if ($actu) {
        $titre = htmlspecialchars($actu['titre']);
        $description = htmlspecialchars($actu['description']);
        $images = json_decode($actu['image']);
    } else {
        $titre = "Actualité non trouvée";
        $description = "";
        $images = [];
    }
} catch (PDOException $e) {
    echo "Erreur : " . $e->getMessage();
    $titre = "Erreur";
    $description = "";
    $images = [];
}

$conn = null;
?>

<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Club de Karaté de Auxi-Le-Château</title>
    <link rel="stylesheet" href="detail.css" />
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css" />
    <link
        href="https://fonts.googleapis.com/css?family=Acme:300,400,700%7CTeko:300,400,700%7CMolengo:300,400,700&display=swap"
        rel="stylesheet" />
    <link href="lightbox2/src/css/lightbox.css" rel="stylesheet" />
</head>

<body>
    <div class="header">
        <?php
        if (session_status() == PHP_SESSION_NONE) {
            session_start();
        }
        if (isset($_SESSION['user']) && $_SESSION['user'] === true) {
            echo '<a href="deconnexion.php" class="login-link">
                  <i class="fa-solid fa-door-open fa-2xl" style="color: #000000;"></i>
                </a>';
        } else {
            echo '<a href="authentification.php" class="login-link">
                  <i class="fa-solid fa-user fa-2xl" style="color: #000000;"></i>
                </a>';
        }
        ?>
        <a href="index.php" class="logo-link">
            <div class="logo-container">
                <img src="images/shotokan.jpg" alt="Logo du Club de Karaté de Auxi-Le-Château" class="logo" />
            </div>
        </a>
        <div class="header-content">
            <h1>Club de Karaté de Auxi-Le-Château</h1>
            <h3></h3>
            <div class="nav-links">
                <a href="index.php" class="nav-link">Accueil</a>
                <a href="contact.php" class="nav-link">Contact</a>
                <a href="programmes.html" class="nav-link">Programmes</a>
                <a href="tarifs.html" class="nav-link">Tarifs</a>
                <a href="actualites.php" class="nav-link">Actualités</a>
                <a href="tchat.php" class="nav-link">Tchat</a>
            </div>
        </div>
    </div>

    <div class="actualites">
        <h2><?php echo $titre; ?></h2>
        <p class="description"><?php echo nl2br($description); ?></p>
        <?php if ($images): ?>
            <div class="actualite">
                <?php foreach ($images as $image): ?>
                    <a href="<?php echo htmlspecialchars($image); ?>" data-lightbox="gallery"
                        data-title="<?php echo $titre; ?>">
                        <img src="<?php echo htmlspecialchars($image); ?>" alt="Image">
                    </a>
                <?php endforeach; ?>
            </div>
        <?php endif; ?>
        <p>Pour revenir aux <a href="actualites.php">actualites</a>.</p>
    </div>
</body>

<footer>
    <div class="container_footer">
        <div class="centered">
            <a href="https://www.facebook.com/people/Karate-club-Auxi-le-Ch%C3%A2teau/100065328918206/"
                class="logo-link">
                <i class="fa-brands fa-facebook fa-2xl" style="color: #000000;"></i>
            </a>
        </div>
        <p class="normal-text">Tous droits réservés &copy; 2024 Club de Karaté Auxi-Le-Château</p>
    </div>
</footer>
<script src="lightbox2/dist/js/lightbox-plus-jquery.js"></script>

</html>