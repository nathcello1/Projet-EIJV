<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Club de Karaté de Auxi-Le-Château</title>
    <link rel="stylesheet" href="site.css" />
    <link
      rel="stylesheet"
      href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css"
    />
    <link
      href="https://fonts.googleapis.com/css?family=Acme:300,400,700%7CTeko:300,400,700%7CMolengo:300,400,700&display=swap"
      rel="stylesheet"
    />
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
          <img
            src="images/shotokan.jpg"
            alt="Logo du Club de Karaté de Auxi-Le-Château"
            class="logo"
          />
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
          <p class="programme_texte_grand"><strong>TARIFS</strong></p>
          <br>
          <p class="programme_texte_petit">
            Le club propose un tarif unique pour tous. Que vous soyez d'un niveau plus avancé, ou bien même débutant, le tarif sera le même ! 
          </p>
        </span>
      </p>
    </div>
    <div class="tarif-card">
      <h2>120 € ANNUEL</h2>
      <ul>
        <li>   Nombre de cours : 2 / semaines</li>
        <li>   Payable en plusieurs fois : x4</li>
      </ul>
    </div>
  </body>
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
</html>
