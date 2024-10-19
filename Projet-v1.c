// Nom du fichier: barrière automatix
// Auteur : S.Batengue B.Florent
// Date de création: Mars 2021
// Version: V1
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
// -Appuyer sur les boutons droite et gauche simultanement jusqu'a apparition. De nouvelles instruction a l'ecrant.
// -Le choix du bouton droit donne acces au mode libre. 
//     *En mode libre, le programme marche normalement sans aucune restriction. 
//     * Il suffit d'approcher un objet de la barierre et celle-ci s'ouvre 
//      et ne se ferme qu'une fois que si l'ojet s'en eloigne. 
// -Le choix du bouton gauche donne acces au mode protege.
//      * Ce mode permet une utilisation plus securiser de la bariere.
//      * Pour y acceder, un code secret qui correspond a une conbinaison de touche a entrer.
//      *Voici le code secret: Touche haut, Touche droite,Touche bas. 
// -Si vous vous voulez arreter le programme pour une raison ou pour une autre,
//  vous devez rentrer la conbinaison de touche suivante: Touche haut et Touche bas simultanement. 
//========================================================================================================================
task song()
{
playTone(261, 10);
sleep(500);
playTone(329, 10);
sleep(700);
playTone(392, 10);
sleep(300);
playTone(370, 10);
sleep(300);
playTone(329, 10);
sleep(1000);
playTone(496, 10);
sleep(500);
playTone(440, 10);
sleep(800);
playTone(370, 10);
sleep(1000);
playTone(329, 10);
sleep(800);
playTone(392, 10);
sleep(300);
playTone(370, 10);
sleep(300);
playTone(310, 10);
sleep(700);
playTone(348, 10);
sleep(500);
playTone(261, 10);
sleep(1000);
}

task main()
{
	int capteur,capteur2,capteur3,mode,music,sound_1,sound_2;
	int etat = 1;
	mode=0;
	music=1;
	sound_1=1;
	sound_2=1;
	SensorType[S1] = sensorEV3_Ultrasonic;
	SensorType[S2] = sensorEV3_Ultrasonic;
	setSensorMode(S1,modeEV3Ultrasonic_DC_Cm);
	setSensorMode(S2,modeEV3Ultrasonic_DC_Cm);
	SensorType[S3] = sensorSoundDB;
	while (!(getButtonPress(buttonLeft) == 1 && getButtonPress(buttonRight) == 1))
	{
	    eraseDisplay();
	    displayTextLine (1, "Projet Barriere Automatix ");
	}
	while(!(getButtonPress(buttonUp) == 1 && getButtonPress(buttonDown) == 1 ))
	{
		sleep(2000);
	  eraseDisplay();
	  displayTextLine (4, "Mode libre bouton gauche");
	  displayTextLine (8, "Mode proteger bouton droit");
		if(music==1)
		{
			startTask(song);
			music=0;
		}
	  if(getButtonPress(buttonLeft)==true)
		{
			mode=1;
		}
		if(getButtonPress(buttonRight)==true)
		{
			mode=2;
		}
		if (mode==1)
		{
			eraseDisplay();
			displayTextLine(4,"Mode acces libre ");
			capteur = SensorValue[S1];
			capteur2 = SensorValue[S2];
			capteur3 = SensorValue[S3];
			while (capteur<15 || capteur2<15 || capteur3>10)
			     {
			       	if(sound_1==1)
			       	{
			       		playSound(soundException);
			      		sound_1=0;
			      		sleep(500);
			     		}
	  					setMotorTarget(motorA,90,25);
	  					sleep(500);
	  					capteur = SensorValue[S1];
	  					capteur2 = SensorValue[S2];
	  					capteur3 = SensorValue[S3]; 
			     }
					setMotorTarget(motorA,0,25);
    	    sleep(500);
    	    sound_1=1;
	 	}	 
		if(mode==2)
		{
			eraseDisplay();
			displayTextLine(4,"mode acces proteger");
			capteur = SensorValue[S1];
			capteur2 = SensorValue[S2];	
			while (capteur<15 || capteur2<15)
			    {
						displayTextLine(4,"donnez moi le code secret");
						if(etat==1 && getButtonPress(buttonUp)==1)
							{
								etat=2; 
								displayTextLine(4,"Touche haut");
								sleep(500);
							}
						if(etat==2 && getButtonPress(buttonRight)==1)
							{
								etat=3;
								displayTextLine(4,"Touche droite");
								sleep(500);
							}
						if(etat==3 && getButtonPress(buttonDown)==1)	
							{	
								etat=4;
								displayTextLine(4,"Touche bas");
								sleep(500);
							}	
						if(etat==4 && getButtonPress(buttonLeft)==1)
							{
								displayTextLine(4,"Touche gauche");
	  						etat=5;
	  						sleep(500);
							}
						if(etat==5)
							{
								if(sound_2==1)
			       		{
			       			playSound(soundException);
			      			sound_2=0;
			      			sleep(500);
			     			}
								displayTextLine(4,"barriere ouverte");
								setMotorTarget(motorA,90,25);
	  						sleep(500);
		  					capteur = SensorValue[S1];
	 	 						capteur2 = SensorValue[S2];
							}
		     }	
 		     setMotorTarget(motorA,0,25);
    	   sleep(500);
      	 etat=1;
      	 sound_2=1;
		}	
	}
	eraseDisplay();
	displayTextLine (4,"Fin programme");
	sleep(2000);
}
// ---------------------------------------------------------------------------------