# Projet Barrière Automatix

Ce projet implémente un système de barrière automatique utilisant un robot programmé en **RobotC**. Le programme gère plusieurs modes de fonctionnement, utilise des capteurs pour détecter la présence et exécute des actions comme l’ouverture et la fermeture de la barrière en fonction des signaux captés.

## Table des matières

1. [Description](#description)

2. [Prérequis](#prérequis)

3. [Installation](#installation)

4. [Utilisation](#utilisation)

5. [Structure du code](#structure-du-code)

6. [Tests](#tests)

7. [Auteurs](#auteurs)

8. [Licence](#licence)

## Description

Le projet **Barrière Automatix** vise à automatiser la gestion d'une barrière avec un robot programmable utilisant des capteurs ultrasoniques et sonores. Le programme comporte plusieurs modes :

- **Mode Libre** : La barrière s’ouvre en fonction de la détection des capteurs sans restriction.

- **Mode Protégé** : La barrière s’ouvre uniquement si un code secret est correctement entré par l’utilisateur.

- **Mode Supplémentaire** : Un mode supplémentaire est prévu pour des fonctionnalités futures.

## Prérequis

Pour utiliser et tester ce projet, vous aurez besoin de :

- **RobotC** version 4.x ou supérieure

- Un robot compatible (comme un robot LEGO EV3) avec les capteurs suivants:
  - Capteur ultrasonique (ports S1 et S2)

  - Capteur sonore (port S3)

- **Robot Virtual Worlds** (RVW) pour la simulation (facultatif mais recommandé)

- Un environnement de développement pour **RobotC** installé sur votre ordinateur

## Installation

1. Clonez ce dépôt sur votre machine locale :

   ```bash

   git clone https://github.com/votre-utilisateur/projet-barriere-automatix.git

2. Ouvrez le fichier source barriere_automatix.c dans l’éditeur RobotC.

3. Assurez-vous que votre robot est connecté et que les capteurs sont branchés aux ports corrects (S1, S2 pour les capteurs ultrasoniques, S3 pour le capteur sonore).
   
## Utilisation

1. Lancer la simulation : Si vous utilisez Robot Virtual Worlds, ouvrez le simulateur et choisissez un environnement adapté (ex: parcours de test ou labyrinthe).

2. Exécuter le programme : Appuyez sur "Compile Program" puis "Download" dans l’interface de RobotC.

3. Contrôler le robot :

    - Appuyez sur les boutons du robot pour naviguer entre les modes :

      - Bouton gauche : Mode libre

      - Bouton droit : Mode protégé

      - Bouton haut : Mode supplémentaire (à implémenter)

    - Suivez les instructions affichées sur l’écran du robot pour tester les fonctionnalités (par exemple, entrer le code secret).

## Structure du code

Le code est structuré de la manière suivante :

- song : Une tâche jouant une mélodie de démarrage.

- main : La fonction principale qui gère l'ensemble du programme :

  - Mode 1 : Mode libre (détection des capteurs et ouverture automatique)

  - Mode 2 : Mode protégé (requiert un code secret pour ouvrir la barrière)

  - Mode 3 : Prévu pour de futures fonctionnalités

##Tests

Pour tester le bon fonctionnement du programme :

1. Utilisez Robot Virtual Worlds (RVW) : Le simulateur permet de vérifier si les capteurs et les actions du robot fonctionnent comme prévu.

2. Scénarios de test :

  - Testez le mode libre en approchant un obstacle et vérifiez si la barrière s’ouvre.

  - Testez le mode protégé en entrant le code secret et en observant si la barrière réagit 

  correctement.

  - Essayez de reproduire des scénarios d'erreur (mauvais code, capteurs hors de portée) pour vérifier la robustesse du programme.

## Auteurs

Sanndo BATENGUE - Développeur principal
Bastien FLORENT - Développeur principal
