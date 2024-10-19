// Nom du fichier: barriere_automatix.c
// Auteur : S. Batengue, B. Florent
// Date de création: Mars 2021
// Version: V1.1
// ----------------------------------------------------------------------------------------------------------------------
// Description : 
// Le programme contrôle une barrière automatique avec deux modes : mode libre et mode protégé.
// - Mode libre : La barrière s'ouvre lorsqu'un véhicule s'approche et se referme lorsqu'il s'éloigne.
// - Mode protégé : La barrière ne s'ouvre que si les capteurs détectent un véhicule et qu'un code secret est entré.
// ----------------------------------------------------------------------------------------------------------------------
// Manuel d'utilisation :
// - Appuyez simultanément sur les boutons gauche et droit pour accéder aux modes.
// - Bouton gauche : Mode libre. La barrière s'ouvre lorsqu'un véhicule est détecté par les capteurs.
// - Bouton droit : Mode protégé. Un code secret est requis pour ouvrir la barrière (séquence : Haut, Droite, Bas).
// - Pour arrêter le programme, appuyez simultanément sur les boutons Haut et Bas.
// ----------------------------------------------------------------------------------------------------------------------

task playSong() {
    // Joue une mélodie lorsque le programme démarre
    playTone(261, 10); sleep(500);
    playTone(329, 10); sleep(700);
    playTone(392, 10); sleep(300);
    playTone(370, 10); sleep(300);
    playTone(329, 10); sleep(1000);
    playTone(496, 10); sleep(500);
    playTone(440, 10); sleep(800);
    playTone(370, 10); sleep(1000);
    playTone(329, 10); sleep(800);
    playTone(392, 10); sleep(300);
    playTone(370, 10); sleep(300);
    playTone(310, 10); sleep(700);
    playTone(348, 10); sleep(500);
    playTone(261, 10); sleep(1000);
}

void configureSensors() {
    // Configure les capteurs pour le mode de détection
    SensorType[S1] = sensorEV3_Ultrasonic;
    SensorType[S2] = sensorEV3_Ultrasonic;
    setSensorMode(S1, modeEV3Ultrasonic_DC_Cm);
    setSensorMode(S2, modeEV3Ultrasonic_DC_Cm);
    SensorType[S3] = sensorSoundDB;
}

void openBarrier() {
    // Ouvre la barrière à 90 degrés
    setMotorTarget(motorA, 90, 25);
    sleep(500);
}

void closeBarrier() {
    // Ferme la barrière à 0 degré
    setMotorTarget(motorA, 0, 25);
    sleep(500);
}

bool isVehicleDetected() {
    // Vérifie si un véhicule est détecté par les capteurs
    int capteur1 = SensorValue[S1];
    int capteur2 = SensorValue[S2];
    int capteur3 = SensorValue[S3];
    return (capteur1 < 15 || capteur2 < 15 || capteur3 > 10);
}

bool isSecretCodeEntered() {
    // Vérifie si le code secret (Haut, Droite, Bas) est entré correctement
    int state = 1;
    while (true) {
        if (state == 1 && getButtonPress(buttonUp)) {
            state = 2; sleep(500);
        } else if (state == 2 && getButtonPress(buttonRight)) {
            state = 3; sleep(500);
        } else if (state == 3 && getButtonPress(buttonDown)) {
            return true;
        } else if (getButtonPress(buttonLeft)) {
            state = 1; // Réinitialise le code si le bouton gauche est appuyé
        }
        sleep(100);
    }
    return false;
}

task main() {
    int mode = 0;
    bool musicPlayed = false;

    configureSensors();

    // Attente de l'activation du programme (boutons gauche et droit simultanés)
    while (!(getButtonPress(buttonLeft) && getButtonPress(buttonRight))) {
        eraseDisplay();
        displayTextLine(1, "Projet Barriere Automatix");
    }

    // Choix du mode : libre ou protégé
    while (!(getButtonPress(buttonUp) && getButtonPress(buttonDown))) {
        eraseDisplay();
        displayTextLine(4, "Mode libre : bouton gauche");
        displayTextLine(8, "Mode protege : bouton droit");

        if (!musicPlayed) {
            startTask(playSong);
            musicPlayed = true;
        }

        if (getButtonPress(buttonLeft)) {
            mode = 1; // Mode libre
        } else if (getButtonPress(buttonRight)) {
            mode = 2; // Mode protégé
        }
        sleep(200);
    }

    // Exécution des actions selon le mode sélectionné
    while (true) {
        eraseDisplay();
        if (mode == 1) {
            // Mode libre
            displayTextLine(4, "Mode acces libre");
            if (isVehicleDetected()) {
                playSound(soundException);
                openBarrier();
                while (isVehicleDetected()) {
                    sleep(200);
                }
                closeBarrier();
            }
        } else if (mode == 2) {
            // Mode protégé
            displayTextLine(4, "Mode acces proteger");
            if (isVehicleDetected()) {
                displayTextLine(6, "Entrez le code secret");
                if (isSecretCodeEntered()) {
                    playSound(soundException);
                    openBarrier();
                    while (isVehicleDetected()) {
                        sleep(200);
                    }
                    closeBarrier();
                } else {
                    displayTextLine(6, "Code incorrect");
                    sleep(1000);
                }
            }
        }

        // Vérification de l'arrêt du programme
        if (getButtonPress(buttonUp) && getButtonPress(buttonDown)) {
            break; // Quitte la boucle principale
        }
        sleep(200);
    }

    // Fin du programme
    eraseDisplay();
    displayTextLine(4, "Fin du programme");
    sleep(2000);
}
