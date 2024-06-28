<?php
session_start();

// Vérifier si l'utilisateur est connecté
if (!isset($_SESSION['user']) || $_SESSION['user'] !== true) {
  // Définir un message d'avertissement
  $_SESSION['warning_message'] = "Vous devez être connecté pour accéder à ce contenu.";
  // Rediriger vers la page d'authentification
  header("Location: authentification.php");
  exit;
}

include_once 'db_connexion.php';

// Récupérer l'ID de l'utilisateur connecté depuis la session
$user_id = $_SESSION['user_id'];

// Traitement du formulaire d'envoi de message
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['message'])) {
  // Récupérer le message depuis le formulaire
  $message_content = htmlspecialchars($_POST['message'], ENT_QUOTES, 'UTF-8');

  // Vérifier si le message n'est pas vide et ne dépasse pas la limite de 250 caractères
  if (!empty($message_content) && strlen($message_content) <= 250) {
    try {
      // Récupérer le pseudo de l'utilisateur à partir de son ID
      $stmt = $conn->prepare("SELECT username FROM utilisateurs WHERE id = :user_id");
      $stmt->bindParam(':user_id', $user_id);
      $stmt->execute();
      $user = $stmt->fetch(PDO::FETCH_ASSOC);

      if ($user) {
        $username = $user['username'];

        // Préparer la requête d'insertion du message dans la base de données
        $stmt = $conn->prepare("INSERT INTO chat_messages (username, user_id, message_content, message_time) VALUES (:username, :user_id, :message_content, NOW())");

        // Liaison des paramètres
        $stmt->bindParam(':username', $username);
        $stmt->bindParam(':user_id', $user_id);
        $stmt->bindParam(':message_content', $message_content);

        // Exécution de la requête
        $stmt->execute();
      }
    } catch (PDOException $e) {
      // Gérer les erreurs éventuelles
      echo "Erreur : " . $e->getMessage();
    }
  } 
}

// Suppression d'un message si le formulaire de suppression est soumis
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['delete_message'])) {
  $message_id = $_POST['message_id'];

  try {
    // Vérifier si l'utilisateur est l'auteur du message
    $stmt = $conn->prepare("SELECT user_id FROM chat_messages WHERE id = :message_id");
    $stmt->bindParam(':message_id', $message_id);
    $stmt->execute();
    $message = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($message && $message['user_id'] == $user_id) {
      // Supprimer le message de la base de données
      $stmt = $conn->prepare("DELETE FROM chat_messages WHERE id = :message_id");
      $stmt->bindParam(':message_id', $message_id);
      $stmt->execute();
    }
  } catch (PDOException $e) {
    // Gérer les erreurs éventuelles
    echo "Erreur : " . $e->getMessage();
  }
}

// Récupérer les messages du chat depuis la base de données
$stmt = $conn->query("SELECT * FROM chat_messages ORDER BY message_time DESC");
$messages = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>

<!DOCTYPE html>
<html lang="fr">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Club de Karaté de Auxi-Le-Château</title>
  <link rel="stylesheet" href="site.css">
  <link rel="stylesheet" href="chat.css">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css" />
  <link href="https://fonts.googleapis.com/css?family=Acme:300,400,700%7CTeko:300,400,700%7CMolengo:300,400,700&display=swap" rel="stylesheet" />
</head>

<body>
  <div class="header">
    <?php
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
    <div>
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
          <p class="programme_texte_grand"><strong>TCHAT</strong></p>
          <br />
          <p class="programme_texte_petit">
            Venez rejoindre des miliers d'adeptes de ce sport de combat afin de discuter de sujet divers et variés autour du karaté !
          </p>
        </span>
      </p>
    </div>

  <div class="chat-container">
    <div class="chat-messages">
    <?php foreach ($messages as $message) : ?>
  <div class="message <?php echo ($message['user_id'] == $user_id) ? 'own-message' : ''; ?>">
    <span class="username"><?php echo $message['username']; ?>:</span>
    <span class="message-content"><?php echo $message['message_content']; ?></span>
    <span class="date-time"><?php echo $message['message_time']; ?></span>
    <?php if (isset($_SESSION['type']) && $_SESSION['type'] === 'admin') : ?>
      <!-- Formulaire de suppression de message pour les administrateurs -->
      <form action="" method="post" class="delete-form">
        <input type="hidden" name="message_id" value="<?php echo $message['id']; ?>">
        <button type="submit" name="delete_message" class="delete-button">Supprimer</button>
      </form>
    <?php elseif ($message['user_id'] == $user_id) : ?>
      <!-- Formulaire de suppression de message pour les utilisateurs normaux -->
      <form action="" method="post" class="delete-form">
        <input type="hidden" name="message_id" value="<?php echo $message['id']; ?>">
        <button type="submit" name="delete_message" class="delete-button">Supprimer</button>
      </form>
    <?php endif; ?>
  </div>
<?php endforeach; ?>
    </div>
    <form action="" method="post" class="message-form">
      <textarea id="message" name="message" placeholder="Écrivez votre message ici" maxlength="250" oninput="verifCaractere(this)"></textarea>
      <button type="submit"><i class="fas fa-arrow-alt-circle-right fa-3x"></i></button>
        </form>
    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['message']) && empty($_POST['message'])) {
      echo "<p class=\"error-message\">Le message est vide.</p>";    
    }
    ?>
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
  <script>
    //Script JS pour faire une verif de taille max de caractère à 250
    function verifCaractere(textarea) {
      if (textarea.value.length > 250) {
        textarea.value = textarea.value.substring(0, 250);
        textarea.setAttribute("readonly", "readonly");
      } else {
        textarea.removeAttribute("readonly");
      }
    }
  </script>
</body>

</html>
