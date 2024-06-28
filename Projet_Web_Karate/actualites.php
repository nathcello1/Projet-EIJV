<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Club de Karaté de Auxi-Le-Château</title>
  <link rel="stylesheet" href="site.css">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
  <link href="https://fonts.googleapis.com/css?family=Acme:300,400,700%7CTeko:300,400,700%7CMolengo:300,400,700&display=swap" rel="stylesheet">
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
        <img src="images/shotokan.jpg" alt="Logo du Club de Karaté de Auxi-Le-Château" class="logo">
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
          <p class="programme_texte_grand"><strong>ACTUALITÉS</strong></p>
          <br />
          <p class="programme_texte_petit">
            Retrouvez les dernières actualités du club ci-dessous
          </p>
        </span>
      </p>
    </div>
  <div class="container">
    
    <!-- Formulaire pour ajouter une actualité -->
    <?php
    // Vérifier si l'utilisateur est un administrateur
    if (isset($_SESSION['type']) && $_SESSION['type'] === 'admin') {
      echo '<form action="ajout_actu.php" method="post" enctype="multipart/form-data">
            <label for="titre de l\'actualité">Titre :</label><br>
            <textarea id="titre" name="titre" rows="2" cols="20"></textarea><br>
            <label for="description">Description :</label><br>
            <textarea id="description" name="description" rows="4" cols="50"></textarea><br>
            <label for="image">Image :</label><br>
            <input type="file" id="images" name="images[]" multiple accept="image/*" required><br>
            <br>
            <input type="submit" value="Ajouter">
          </form>';
    }
    ?>
    <br>
    <!-- Affichage des actualités à partir du fichier affichage_actu.php -->
    <div class="actualites">
      <?php include 'affichage_actu.php'; ?>
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