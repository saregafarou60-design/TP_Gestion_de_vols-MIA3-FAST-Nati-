# Projet : Système de Gestion d'une Agence de Voyage (Cotonou)

## Description
Application console développée en C++ orientée objet (POO) pour la gestion informatisée des vols, des passagers, des paiements et des réservations de billets d'avion pour une agence de voyage à Cotonou.

## Fonctionnalités principales
* Enregistrement et suivi des passagers.
* Création et consultation des vols (avec vérification dynamique des places disponibles).
* Recherche multicritère par destination.
* Réservation de billets sécurisée (contrôle de capacité et interdiction des doublons).
* Gestion automatisée des paiements et des remboursements en cas d'annulation.
* Menu interactif complet avec gestion des erreurs de saisie.

## Instructions de Compilation et d'Exécution
1. Ouvrez un terminal dans le dossier contenant le fichier source (`main.cpp`).
2. Compilez le programme à l'aide de GCC :
   ```bash
   g++ -o agence_voyage main.cpp -std=c++11