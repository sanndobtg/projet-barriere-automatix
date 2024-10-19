// Nom du fichier: barriere_automatix.c
// Auteur : S. Batengue, B. Florent
// Date de cr�ation: Mars 2021
// Version: V1.1
// ----------------------------------------------------------------------------------------------------------------------
// Description : 
// Le programme contr�le une barri�re automatique avec deux modes : mode libre et mode prot�g�.
// - Mode libre : La barri�re s'ouvre lorsqu'un v�hicule s'approche et se referme lorsqu'il s'�loigne.
// - Mode prot�g� : La barri�re ne s'ouvre que si les capteurs d�tectent un v�hicule et qu'un code secret est entr�.
// ----------------------------------------------------------------------------------------------------------------------
// Manuel d'utilisation :
// - Appuyez simultan�ment sur les boutons gauche et droit pour acc�der aux modes.
// - Bouton gauche : Mode libre. La barri�re s'ouvre lorsqu'un v�hicule est d�tect� par les capteurs.
// - Bouton droit : Mode prot�g�. Un code secret est requis pour ouvrir la barri�re (s�quence : Haut, Droite, Bas).
// - Pour arr�ter le programme, appuyez simultan�ment sur les boutons Haut et Bas.
// ----------------------------------------------------------------------------------------------------------------------

task playSong() {
    // Joue une m�lodie lorsque le programme d�marre
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
    // Configure les capteurs pour le mode de d�tection
    SensorType[S1] = sensorEV3_Ultrasonic;
    SensorType[S2] = sensorEV3_Ultrasonic;
    setSensorMode(S1, modeEV3Ultrasonic_DC_Cm);
    setSensorMode(S2, modeEV3Ultrasonic_DC_Cm);
    SensorType[S3] = sensorSoundDB;
}

void openBarrier() {
    // Ouvre la barri�re � 90 degr�s
    setMotorTarget(motorA, 90, 25);
    sleep(500);
}

void closeBarrier() {
    // Ferme la barri�re � 0 degr�
    setMotorTarget(motorA, 0, 25);
    sleep(500);
}

bool isVehicleDetected() {
    // V�rifie si un v�hicule est d�tect� par les capteurs
    int capteur1 = SensorValue[S1];
    int capteur2 = SensorValue[S2];
    int capteur3 = SensorValue[S3];
    return (capteur1 < 15 || capteur2 < 15 || capteur3 > 10);
}

bool isSecretCodeEntered() {
    // V�rifie si le code secret (Haut, Droite, Bas) est entr� correctement
    int state = 1;
    while (true) {
        if (state == 1 && getButtonPress(buttonUp)) {
            state = 2; sleep(500);
        } else if (state == 2 && getButtonPress(buttonRight)) {
            state = 3; sleep(500);
        } else if (state == 3 && getButtonPress(buttonDown)) {
            return true;
        } else if (getButtonPress(buttonLeft)) {
            state = 1; // R�initialise le code si le bouton gauche est appuy�
        }
        sleep(100);
    }
    return false;
}

task main() {
    int mode = 0;
    bool musicPlayed = false;

    configureSensors();

    // Attente de l'activation du programme (boutons gauche et droit simultan�s)
    while (!(getButtonPress(buttonLeft) && getButtonPress(buttonRight))) {
        eraseDisplay();
        displayTextLine(1, "Projet Barriere Automatix");
    }

    // Choix du mode : libre ou prot�g�
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
            mode = 2; // Mode prot�g�
        }
        sleep(200);
    }

    // Ex�cution des actions selon le mode s�lectionn�
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
            // Mode prot�g�
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

        // V�rification de l'arr�t du programme
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
