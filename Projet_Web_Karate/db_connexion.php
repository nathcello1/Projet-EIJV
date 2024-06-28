<?php

// Paramètres de connexion à la base de données
$servername = "localhost";
$port = "3307"; // Port utilisé pour la connexion
$username_db = "root";
$password_db = "";
$dbname = "Karate";

try {
    // Connexion à la base de données MySQL avec PDO
    $conn = new PDO("mysql:host=$servername;port=$port;dbname=$dbname", $username_db, $password_db);
    // Définir le mode d'erreur PDO sur exception
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    // En cas d'erreur de connexion à la base de données
    die("Erreur de connexion à la base de données : " . $e->getMessage());
}
?>
