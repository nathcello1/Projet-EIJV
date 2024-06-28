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
  <body class="container_programme">
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
    <div class="container">
      <div class="additional-content">
        <div class="left-column">
          <p class="large-text">Qui sommes-nous ?</p>
          <p class="petit-text">
            Le Karaté club d'Auxi-Le-Château, initialement Maizicourt, est un
            club qui comptabilise à ce jour plus de 20 adhérents. Créé par son
            fondateur en 2010, l'objectif étant de promouvoir l'enseignement du
            Karaté Shotokan dans la ville de Maizicourt et ses alentours.
            <strong>Laurent Deboffle</strong>, ceinture noire 3ème Dan, est le
            fondateur du club Shotokan.
          </p>
        </div>
        <div class="right-column">
          <div class="hero-image"></div>
        </div>
      </div>
    </div>

    <div class="banner_programme">
      <p>
        <span class="contact-info">
          <p class="programme_texte_grand"><strong>PROGRAMMES</strong></p>
          <br />
          <p class="programme_texte_petit">
            Retrouvez les différents programmes proposés par le club Karate en
            fonction des niveaux de chacun. Les cours sont proposés sur
            plusieurs plages horaires afin de convenir aux disponibilités de
            chacun. Pour rappel, il est possible de participer à 2 séances
            gratuites pour découvrir le module sur lequel vous êtes intéressés.
            Pour plus d'informations, n'hésitez pas à contacter le club. Nous
            vous répondrons dans les meilleurs délais.
          </p>
        </span>
      </p>
    </div>
    <div class="programme-image">
      <img src="images/programme.png" alt="Programme du Club de Karaté" />
    </div>
    <br />
    <br />
    <br />
    <div class="container_programme">
      <div class="additional-content_programme">
        <div class="left-column_programme">
          <ol class="programme_explain">
            <li><strong>Renforcement musculaire</strong> de 15 minutes,</li>
            <br />
            <li>
              <strong>Entraînement aux katas</strong> / exercices de
              <strong>mise en situation</strong> avec du matériel (couteaux en
              plastique, etc) durant 30 minutes.
            </li>
            <br />
            <li>
              La séance se conclut avec 15 minutes de <strong>combats.</strong>
            </li>
          </ol>
        </div>
        <div class="right-column_programme">
          <img src="images/combat.jpeg" alt="ia" class="ia" width="750px" />
        </div>
      </div>
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
