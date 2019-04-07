/* pseudo code bloc moteur

ce pseudo code doit permettre au moteur de supporter une gestion de la pause, et la modification de ses paramètres en temps réel pendant tu tache en cours
l'idée est de créer plusieurs états possible dans lesquels le moteur peut se trouver, dépendant de ses carac bluetooth

*/
bool pause = false;

loop(){
	
	switch ( bluetooth.read() ){
		case "0", "1", "2":
//			il n'y a rien à faire
		case "3":
//			le bloc de commande fait un pause/continue, il faut changer l'état de "pause"
			pause = !pause;	
			if (pause == true){
//				si une pause est déclanchée, il faut mémoriser le temps restant et la distance restante pour reprendre plus tard
				temps_restant = motor.timeLeft();
				distance_restant = motor.distanceLeft();
			}
			else{
//				la pause est terminée, il faut recharger les paramètres de temps et distance
				motor.setRotationTime( temps_restant );
				motor.setRotationDistance( distance_restant );
				motor.setCurrentPosition(0);
			}



		default:
//			un datagramme est reçu, il faut le décoder et changer les variables
//			il faut également notifier le bloc de commande que la data est reçue
			bluetooth.write("1");

			values = bluetooth.decode();
			motor.setAcceleration(values[ACCELERATION]);
			motor.setSpeed(values[SPEED]);
//			...				
			motor.setCurrentPosition(0);
	}


	if (motor.distanceLeft() == 0 or motor.timeLeft() == 0){
//		le moteur a fini sa rotation
//		timeLeft() renvoie le temps restant jusqu'à la fin de la rotation, si la rotation est en temps, false sinon
//		distanceLeft(), même principe pour le nombre de pas
		bluetooth.write("2");		
	}

// 	si on est pas en pause, on run le moteur
	if (!pause) motor.run();


}