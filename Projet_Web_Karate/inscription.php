<?php
// Inclure le fichier de connexion à la base de données
include_once 'db_connexion.php';

// Démarrer la session si ce n'est pas déjà fait
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}

// Vérifier si l'utilisateur est déjà connecté, si oui, le rediriger vers une autre page
if (isset($_SESSION['user']) && $_SESSION['user'] === true) {
    header("Location: index.php");
    exit();
}

// Déclarer des variables pour stocker les messages d'erreur
$usernameErr = $emailErr = $passwordErr = $confirmPasswordErr = $inscriptionSucc = "";
$errorClass = "error";

// Vérifier si le formulaire a été soumis
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Récupérer les données du formulaire
    $username = $_POST["username"];
    $email = $_POST["email"];
    $password = $_POST["password"];
    $confirmPassword = $_POST["confirm-password"];

    // Vérifier que le nom d'utilisateur n'est pas vide
    if (empty($username)) {
        $_SESSION['usernameErr'] = "Le nom d'utilisateur est requis.";
    } elseif (!preg_match("/^[a-zA-Z0-9]*$/", $username)) {
        $_SESSION['usernameErr'] = "Le nom d'utilisateur ne peut contenir que des lettres et des chiffres.";
    }

    // Vérifier la validité de l'adresse e-mail
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $_SESSION['emailErr'] = "L'adresse e-mail n'est pas valide.";
    }

    // Vérifier que le mot de passe répond à des critères de sécurité minimum
    if (strlen($password) < 8 || !preg_match("/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$/", $password)) {
        $_SESSION['passwordErr'] = "Le mot de passe doit comporter au moins 8 caractères et inclure au moins une lettre majuscule, une lettre minuscule, un chiffre et un caractère spécial.";
    }

    // Vérifier que le champ "Confirmer le mot de passe" correspond au champ "Mot de passe"
    if ($password !== $confirmPassword) {
        $_SESSION['confirmPasswordErr'] = "Les mots de passe ne correspondent pas.";
    }

    // Vérifier si le nom d'utilisateur n'est pas déjà utilisé
    $stmt = $conn->prepare("SELECT * FROM utilisateurs WHERE username = :username");
    $stmt->bindParam(':username', $username);
    $stmt->execute();
    if ($stmt->rowCount() > 0) {
        $_SESSION['usernameErr'] = "Ce nom d'utilisateur est déjà utilisé.";
    }

    // Vérifier si l'adresse e-mail n'est pas déjà utilisée
    $stmt = $conn->prepare("SELECT * FROM utilisateurs WHERE email = :email");
    $stmt->bindParam(':email', $email);
    $stmt->execute();
    if ($stmt->rowCount() > 0) {
        $_SESSION['emailErr'] = "Cette adresse e-mail est déjà utilisée.";
    }

    // Si aucune erreur n'est détectée, vous pouvez continuer avec le traitement des données du formulaire
    if (empty($_SESSION['usernameErr']) && empty($_SESSION['emailErr']) && empty($_SESSION['passwordErr']) && empty($_SESSION['confirmPasswordErr'])) {
        // Hasher le mot de passe
        $hashed_password = password_hash($password, PASSWORD_DEFAULT);

        // Préparer la requête SQL pour l'insertion des données
        $sql = "INSERT INTO utilisateurs (username, email, password, type) VALUES (:username, :email, :password, 'visiteur')";
        $stmt = $conn->prepare($sql);

        // Liaison des paramètres
        $stmt->bindParam(':username', $username);
        $stmt->bindParam(':email', $email);
        $stmt->bindParam(':password', $hashed_password); // Utiliser le mot de passe haché

        // Exécution de la requête
        $stmt->execute();

        // Définir un message de succès
        $_SESSION['inscriptionSucc'] = "L'inscription a bien été effectuée.";
    }
}

// Supprimer les messages d'erreur de la session après les avoir affichés
$usernameErr = isset($_SESSION['usernameErr']) ? $_SESSION['usernameErr'] : "";
$emailErr = isset($_SESSION['emailErr']) ? $_SESSION['emailErr'] : "";
$passwordErr = isset($_SESSION['passwordErr']) ? $_SESSION['passwordErr'] : "";
$confirmPasswordErr = isset($_SESSION['confirmPasswordErr']) ? $_SESSION['confirmPasswordErr'] : "";

unset($_SESSION['usernameErr']);
unset($_SESSION['emailErr']);
unset($_SESSION['passwordErr']);
unset($_SESSION['confirmPasswordErr']);
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

    <!-- Formulaire d'inscription -->
    <div class="signup-container">
        <h2>Inscription</h2>
        <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
            <div class="input-group">
                <label for="username">Nom d'utilisateur</label>
                <input type="text" id="username" name="username" />
                <span class="error-message"><?php echo $usernameErr; ?></span>
            </div>

            <div class="input-group">
                <label for="email">Email</label>
                <input type="email" id="email" name="email" />
                <span class="error-message"><?php echo $emailErr; ?></span>
            </div>

            <div class="input-group">
                <label for="password">Mot de passe</label>
                <input type="password" id="password" name="password" />
                <span class="error-message"><?php echo $passwordErr; ?></span>
            </div>

            <div class="input-group">
                <label for="confirm-password">Confirmer le mot de passe</label>
                <input type="password" id="confirm-password" name="confirm-password" />
                <span class="error-message"><?php echo $confirmPasswordErr; ?></span>
            </div>
            <?php
            if (isset($_SESSION['inscriptionSucc'])) {
                echo "<p class='error-message'>" . $_SESSION['inscriptionSucc'] . "</p>";
                // Une fois affiché,supprimer le message de la session
                unset($_SESSION['inscriptionSucc']);
            }
            ?>
            <button type="submit" class="btn">S'inscrire</button>
        </form>
        <div class="signup-link">
            <a href="authentification.php">Déjà inscrit ? Se connecter ici.</a>
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
