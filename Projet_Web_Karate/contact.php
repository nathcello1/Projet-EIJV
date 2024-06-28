<?php

use PHPMailer\PHPMailer\PHPMailer;

require './PHPMailer/src/Exception.php';
require './PHPMailer/src/PHPMailer.php';
require './PHPMailer/src/SMTP.php';

$message = '';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (isset($_POST['nom'], $_POST['email'], $_POST['message'])) {
        if (adresseMailValide($_POST['email'])) {
            if (envoie_mail($_POST['nom'], $_POST['email'], $_POST['message'])) {
                $message = 'Votre mail a bien été envoyé';
            } else {
                $message = "Une erreur s'est produite lors de l'envoi du mail";
            }
        } else {
            $message = "L'adresse mail " . htmlspecialchars($_POST['email']) . " n'est pas valide";
        }
    }
}

function envoie_mail($from_name, $from_email, $message)
{
    // Utilisation de strip_tags() pour supprimer les balises HTML
    $from_name = strip_tags($from_name);
    $from_email = strip_tags($from_email);
    $message = htmlspecialchars($message);

    $email_message = "<strong>NOM :</strong> $from_name<br><br>"; // Mettre en gras
    $email_message .= "<strong>EMAIL :</strong> $from_email<br><br>"; // Mettre en gras
    $email_message .= "<strong>MESSAGE :</strong> $message"; // Mettre en gras

    $mail = new PHPMailer();
    $mail->isSMTP();
    $mail->SMTPDebug = 0;
    $mail->SMTPSecure = 'ssl';
    $mail->Host = 'smtp.gmail.com';
    $mail->SMTPAuth = true;
    $mail->Username = ''; // Adresse qui envoie
    $mail->Password = ''; // Mot de passe de l'adresse
    $mail->SMTPSecure = PHPMailer::ENCRYPTION_SMTPS; // Activer le cryptage TLS implicite
    $mail->Port = 465;
    $mail->setFrom($from_email, $from_name);
    $mail->addAddress('', 'karate'); // Adresse qui reçoit
    $mail->isHTML(true);
    $mail->Body = $email_message;
    $mail->setLanguage('fr', '/optional/path/to/language/directory/');
    return $mail->Send();
}

function adresseMailValide($adresse_mail)
{
    $caracteres_autorises_avant_arobase = '[-a-z0-9!#$%&\'*+\\/=?^_`{|}~]'; // Caractères autorisés avant l'arobase
    $caracteres_autorises_apres_arobase = '([a-z0-9]([-a-z0-9]*[a-z0-9]+)?)'; // Caractères autorisés après l'arobase

    $mail_valide = '/^' . $caracteres_autorises_avant_arobase . '+' . '(\.' . $caracteres_autorises_avant_arobase . '+)*' . '@' . '(' . $caracteres_autorises_apres_arobase . '{1,63}\.)+' . $caracteres_autorises_apres_arobase . '{2,63}$/i';
    // On concatène dans $mail_valide les expressions régulières précédentes afin de former une expression régulière permettant de vérifier la validité de l'adresse mail

    return preg_match($mail_valide, $adresse_mail); // On compare l'adresse mail avec l'expression régulière mail_valide
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
    <link
        href="https://fonts.googleapis.com/css?family=Acme:300,400,700%7CTeko:300,400,700%7CMolengo:300,400,700&display=swap"
        rel="stylesheet" />
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
                <a href="programmes.php" class="nav-link">Programmes</a>
                <a href="tarifs.php" class="nav-link">Tarifs</a>
                <a href="actualites.php" class="nav-link">Actualités</a>
                <a href="tchat.php" class="nav-link">Tchat</a>
            </div>
        </div>
    </div>


    <div class="banner_programme">
        <p>
            <span class="contact-info">
                <p class="programme_texte_grand"><strong>CONTACTEZ-NOUS</strong></p>
                <br>
                <p class="programme_texte_petit">
                    Pour toute question ou demande d'information, veuillez remplir le formulaire ci-dessous :
                </p>

            </span>
        </p>
    </div>

    <div class="container">
        <form action="contact.php" method="post" class="contact-form">
            <div class="form-group">
                <label for="nom" class="custom-label">Nom :</label>
                <input type="text" id="nom" name="nom" class="form-control" required>
            </div>

            <div class="form-group">
                <label for="email" class="custom-label">Email :</label>
                <input type="email" id="email" name="email" class="form-control" required>
            </div>
            <br>
            <div class="form-group">
                <label for="message" class="custom-label">Message :</label>
                <textarea id="message" name="message" class="form-control" rows="4" style="height: 200px;"
                    required></textarea>
            </div>

            <button type="submit" class="btn btn-primary">Envoyer</button>
        </form>
        <br>
        <?php if ($message != ''): ?>
            <div class="alert alert-success mt-3" role="alert">
                <?php echo $message; ?>
            </div>
        <?php endif; ?>
    </div>
    <div class="container">
        <div class="box">
            <img src="images/dojo.jpg" alt="Description de l'image">
            <i class="fas fa-map-marker fa-2x"></i>
            <p>Rue du Cheval, 62390 <strong>Auxi-le-Château</strong></p>
            <iframe <iframe
                src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d3049.9723057993465!2d2.1090736959973913!3d50.2312555225775!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x47dd9c09855a6d0b%3A0x736eac492a720a47!2sDojo%2C%20Complexe%20Sportif!5e1!3m2!1sfr!2sfr!4v1717603453153!5m2!1sfr!2sfr"
                width="600" height="300" style="border:0;" allowfullscreen="" loading="lazy"
                referrerpolicy="no-referrer-when-downgrade"></iframe>
        </div>
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

</html>