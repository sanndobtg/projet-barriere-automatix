
// Nom du fichier: barrière automatix
// Auteur : S.Batengue B.Florent
// Date de création: Mars 2021
// Version: V2
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Description :
// Le programme comporte deux modes: le mode libre et le mode protege.
// On accede au mode libre en suivant les instructions qui s'affichent sur l'ecrant.
// En choisissant le mode libre, la barriere s'ouvre des qu'une voiture
// s'aproche de la bariere.
// Et se referme l'orsque la voiture s'en eloigne.
// En choisissant le mode proteger, la barriere ne
// s'ouvre que quand les capteurs ultrasons detectent
// la presence d'un vehicule, un code secret est alors
// demander au conducteur.
// Si le code est correct, la bariere s'ouvre sinon la barrier reste fermee.
// ----------------------------------------------------------------------------------------------------------------------
// Manuel d'utilisation :
// -Appuyer sur les boutons droit et gauche de nouvelles instructions vont  apparaitre à l'ecran.
// -Le choix du bouton gauche donne acces au mode libre.
//     * En mode libre, le programme marche normalement sans aucune restriction.
//     * Il suffit d'approcher un objet de la barierre et celle-ci s'ouvre
//       et ne se ferme qu'une fois que si l'ojet s'en eloigne.
// -Le choix du bouton droit donne acces au mode protege.
//     * Se mode permet une utilisation plus securisee de la barriere.
//     * Pour y acceder, un code secret qui correspond à une conbinaison de touche à entrer.
//     * Voici le code secret: Touche haut, Touche droite,Touche bas, Touche gauche.
// -Si le mot de passe est bon la barriere s'ouvre, au cas contraire il vous est proposer de recuperer puis de reesayer.
// -Si vous vous voulez arreter le programme pour une raison ou pour une autre,
//     * vous devez rentrer la conbinaison de touche suivante: Touche haut et Touche bas simultanement.
//========================================================================================================================

/**
 * La fonction song représente la chanson au lancement du programme.
 */
task song() {
    playTone(261, 10);
    sleep(500);
    playSound(soundFastUpwardTones);
    playTone(261, 10);
    sleep(500);
}

task main() {
    // Déclaration des variables
    int capteur, capteur2, capteur3, mode, music, sound_1, sound_2, sound_mode1, sound_mode2;
    int etat = 1;
    mode = 0;
    music = 1;
    sound_1 = 1;
    sound_2 = 1;
    sound_mode1 = 1;
    sound_mode2 = 1;

    // Configuration des capteurs
    SensorType[S1] = sensorEV3_Ultrasonic;
    SensorType[S2] = sensorEV3_Ultrasonic;
    SensorType[S3] = sensorSoundDB;
    setSensorMode(S1, modeEV3Ultrasonic_DC_Cm);
    setSensorMode(S2, modeEV3Ultrasonic_DC_Cm);
    

    // Attente de l'activation du programme
    while (!(getButtonPress(buttonLeft) && getButtonPress(buttonRight))) {
        eraseDisplay();
        displayTextLine(1, "Projet Barriere Automatix");
    }

    // Boucle principale du programme
    while (!(getButtonPress(buttonUp) && getButtonPress(buttonDown))) {
        sleep(2000);
        eraseDisplay();
        displayTextLine(4, "Mode libre: bouton gauche");
        displayTextLine(8, "Mode proteger: bouton droit");

        // Lancement de la musique au démarrage
        if (music == 1) {
            startTask(song);
            music = 0;
        }

        // Choix du mode en fonction des boutons pressés
        if (getButtonPress(buttonLeft)) {
            mode = 1;  // Mode libre
        }
        if (getButtonPress(buttonRight)) {
            mode = 2;  // Mode protéger
        }
        if (getButtonPress(buttonUp)) {
            mode = 3;  // Mode supplémentaire (à définir)
        }

        // Exécution des modes
        if (mode == 1) {
            eraseDisplay();
            displayTextLine(4, "Mode acces libre");

            // Lecture des valeurs des capteurs
            capteur = SensorValue[S1];
            capteur2 = SensorValue[S2];
            capteur3 = SensorValue[S3];

            // Sons d'alerte
            if (sound_mode1 == 1) {
                playSound(soundFastUpwardTones);
                sound_mode1 = 0;
                sleep(500);
            }

            // Ouverture de la barrière si conditions remplies
            while (capteur < 15 || capteur2 < 15 || capteur3 > 10) {
                if (sound_1 == 1) {
                    playSound(soundException);
                    sound_1 = 0;
                    sleep(500);
                }
                setMotorTarget(motorA, 90, 25);
                sleep(500);

                // Mise à jour des capteurs
                capteur = SensorValue[S1];
                capteur2 = SensorValue[S2];
                capteur3 = SensorValue[S3];
            }

            setMotorTarget(motorA, 0, 25);
            sleep(500);
            sound_1 = 1;
            sound_mode2 = 1;
        }

        if (mode == 2) {
            eraseDisplay();
            displayTextLine(4, "Mode acces proteger");

            capteur = SensorValue[S1];
            capteur2 = SensorValue[S2];

            if (sound_mode2 == 1) {
                playSound(soundFastUpwardTones);
                sound_mode2 = 0;
                sleep(500);
            }

            // Vérification du code secret
            while (capteur < 15 || capteur2 < 15) {
                displayTextLine(4, "Entrez le code secret");

                if (etat == 1 && getButtonPress(buttonUp)) {
                    etat = 2;
                    displayTextLine(4, "Touche haut");
                    sleep(500);
                }
                if (etat == 2 && getButtonPress(buttonRight)) {
                    etat = 3;
                    displayTextLine(4, "Touche droite");
                    sleep(500);
                }
                if (etat == 3 && getButtonPress(buttonDown)) {
                    etat = 4;
                    displayTextLine(4, "Touche bas");
                    sleep(500);
                }
                if (etat == 4 && getButtonPress(buttonLeft)) {
                    displayTextLine(4, "Touche gauche");
                    etat = 5;
                    sleep(500);
                }

                if (etat == 5) {
                    if (sound_2 == 1) {
                        playSound(soundException);
                        sound_2 = 0;
                        sleep(500);
                    }
                    displayTextLine(4, "Barriere ouverte");
                    setMotorTarget(motorA, 90, 25);
                    sleep(500);
                    capteur = SensorValue[S1];
                    capteur2 = SensorValue[S2];
                }

                if (etat != 5 && getButtonPress(ANY_BUTTON)) {
                    etat = 6;
                }

                if (etat == 6) {
                    displayTextLine(4, "Code incorrect, reculez !");
                }
            }

            setMotorTarget(motorA, 0, 25);
            sleep(500);
            etat = 1;
            sound_2 = 1;
            sound_mode1 = 1;
        }

        if (mode == 3) {
            // Implémentation du mode 3 en cours de developpement...
        }
    }

    // Fin du programme
    eraseDisplay();
    displayTextLine(4, "Fin du programme");
    sleep(2000);
}
// -----------------------------------------------------------------------------------------------
