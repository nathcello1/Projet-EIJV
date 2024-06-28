<?php
include_once 'db_connexion.php';

// Démarrer la session si ce n'est pas déjà fait
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}

// Vérifier si un message d'avertissement existe
if (isset($_SESSION['warning_message'])) {
    $warning_message = $_SESSION['warning_message'];
    // Effacer la variable de session après l'avoir affichée
    unset($_SESSION['warning_message']);
} else {
    $warning_message = "";
}

// Vérifier si l'utilisateur est déjà connecté, si oui, le rediriger vers une autre page
if (isset($_SESSION['user']) && $_SESSION['user'] === true) {
    header("Location: index.php");
    exit();
}

// Vérifier si le formulaire a été soumis
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Récupérer les valeurs du formulaire
    $username = $_POST["username"];
    $password = $_POST["password"];
    

    try {
        // Requête SQL pour vérifier les informations d'identification de l'utilisateur
        $query = "SELECT id, username, password, type FROM utilisateurs WHERE username = :username";       
        $statement = $conn->prepare($query);

        // Liaison des paramètres
        $statement->bindParam(':username', $username);

        // Exécution de la requête
        $statement->execute();

        $user = $statement->fetch(PDO::FETCH_ASSOC);

        if ($user) {
            // Vérifier si le mot de passe fourni correspond au mot de passe haché stocké dans la base de données
            if (password_verify($password, $user['password'])) {
                $_SESSION['user'] = true;
                $_SESSION['type'] = $user['type']; // Ajout du type d'utilisateur récupéré de la base de données
                $_SESSION['username'] = $user['username']; // Ajout du nom d'utilisateur récupéré de la base de données
                $_SESSION['user_id'] = $user['id']; // Ajout de l'ID de l'utilisateur récupéré de la base de données

                header("Location: index.php");
                exit();
            } else {
                // Identifiants invalides
                $_SESSION['error_message'] = "Nom d'utilisateur ou mot de passe incorrect.";
            }
        } else {
            // Identifiants invalides
            $_SESSION['error_message'] = "Nom d'utilisateur ou mot de passe incorrect.";
        }
    } catch (PDOException $e) {
        // En cas d'erreur de connexion à la base de données
        $_SESSION['error_message'] = "Erreur de connexion à la base de données : " . $e->getMessage();
    }
}

// Supprimer le message d'erreur de la session après l'avoir affiché
if(isset($_SESSION['error_message'])) {
    $error_message = $_SESSION['error_message'];
    unset($_SESSION['error_message']);
}
?>

<!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Club de Karaté de Auxi-Le-Château</title>
    <link rel="stylesheet" href="site.css" />
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css" />
    <link href="https://fonts.googleapis.com/css?family=Acme:300,400,700%7CTeko:300,400,700%7CMolengo:300,400,700&display=swap" rel="stylesheet" />
</head>

<body>
    <div class="header">
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
                <a href="programmes.php" class="nav-link">Programmes</a>
                <a href="tarifs.php" class="nav-link">Tarifs</a>
                <a href="actualites.php" class="nav-link">Actualités</a>
                <a href="tchat.php" class="nav-link">Tchat</a>
            </div>
        </div>
    </div>
    <div class="auth-container">
        <?php if (!empty($warning_message)) : ?>
            <div class="warning-message"><?php echo $warning_message; ?></div>
        <?php endif; ?>
        <h2>Authentification</h2>
        <form method="post" action="authentification.php">
            <div class="input-group">
                <label for="username">Nom d'utilisateur</label>
                <input type="text" id="username" name="username" />
            </div>
            <div class="input-group">
                <label for="password">Mot de passe</label>
                <input type="password" id="password" name="password" />
            </div>
            <?php if(isset($error_message)): ?>
                <p class="error-message"><?php echo $error_message; ?></p>
            <?php endif; ?>
            <button type="submit" class="btn">Se connecter</button>
        </form>
        <div class="signup-link">
            <a href="inscription.php">Pas encore inscrit ? Inscrivez-vous ici.</a>
        </div>
    </div>

    <footer>
        <div class="container_footer">
            <div class="centered">
                <a href="https://www.facebook.com/people/Karate-club-Auxi-le-Ch%C3%A2teau/100065328918206/" class="logo-link">
                    <i class="fa-brands fa-facebook fa-2xl" style="color: #000000;"></i>
                </a>
            </div>
            <p class="normal-text">Tous droits réservés &copy; 2024 Club de Karaté Auxi-Le-Château</p>
        </div>
    </footer>
</body>

</html>