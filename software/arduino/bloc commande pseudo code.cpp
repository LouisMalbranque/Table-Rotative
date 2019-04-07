/*algo boitier de commande:


les périphériques bluetooth (comme le bloc moteur ou le module de focus stacking, et idéalement les appareils photo) sont des objects de classes différentes mais qui décendent tous de
"PeriphériqueBluetooth"

on a donc qqch comme :

MoteurBluetooth moteur;
FocusBluetooth focus;
idéalement ControleCameraBluetooth cameras;

on garde une liste des périphs
PériphériqueBluetooth listePériphériques[] = {moteur, focus, camera}



avec MoteurBluetooth, FocusBluetooth et ControleCameraBluetooth qui décendent de PeripheriqueBluetooth

PériphériqueBluetooth implémente les fonction de read, write et de connect (...), mais pas la fonction createDatagramme, qui doit être implémentées dans les classes filles
la methode createDatagramme doit être capable de créer le string à envoyer à partir de la liste de parametres envoyés par le bluetooth



à coté de ça, on a une classe ou une structure Instruction, qui comporte 2 attributs, 
un PeripheriqueBluetooth target, et un String datagramme contenant la chaine à envoyer





ceci est un proto du loop qui pourait tourner dans le boitier de commande


*/
loop(){

//	la première étape est toujours de réceptionner les données du téléphone
//	si un nouvelle trame est reçu, on la décode

	if (telephoneBluetooth.receive()){
		int * values = telephoneBluetooth.decode();


			switch values[0]:
				case MODE_PROGRAMME: (0) 
//					on est en mode programme donc on peut génerer la liste de taches à effectuer (et surtout la liste de messages à envoyer aux périphériques)
//					on ajoute donc à une pile d'actions à effectuer pileActions

					Instruction nouvelleAction (moteur, moteur.createDatagramme(values));
					pileActions.add(nouvelleAction);

					Instruction nouvelleAction (cameras, cameras.createDatagramme(values));
					pileActions.add(nouvelleAction);

//					là c'est pour une seule rotation et une seule photo mais l'idée est là	

				case MODE_TEMPS_REEL: (1)
//					pareil ici mais par exemple ça donnerait qqch comme:

					Instruction nouvelleAction (moteur, moteur.createDatagramme(values));
					pileActions.add(nouvelleInstruction)

				case PAUSE:
//					là c'est différentp pcq il faut généré un code de pause pour tous les périphériques et les mettre en haut de la pile
					for i = 0 ...{
						Instruction nouvelleAction ( listePériphériques[i], listePériphériques[i].createDatagramme() );
//						ajouter nouvelleAction à la pile mais en 1e
					}
	}// fin du bloc de réception téléphone


//	chaque périph se met à 1 si il a une tache en cours, et à 2 si il a fini. il est remis à 0 (disponible) par le bloc de commande quand il valide la fin de la tache.
//	un périphérique n'a pas le droit de se remettre à 0 tant que le bloc ne l'a pas fait lui même pour valider la fin de tache


	if (action == NULL)
	{
//		aka si aucune action n'est en cours on récupère la prochaine action à executer dans la pile.
	 	action = pileActions.pop();
	}

	else
	{

//		aka une action est en cours, il faut vérifier que le périphérique en question a bien recu le message, et n'a pas fini sa tache


		if action.target.isAvailable()   	<=>		action.target.read() == "0" 
		{
//			dans ce cas la cible de l'instruction est disponible, ça veut dire qu'elle n'a pas reçu l'ordre, donc il faut lui écrire:

			action.target.write(action.datagramme);
		}
		
		if action.target.isWorking()     	<=> 	action.target.read() == "1"
		{
//			dans ce cas l'action est en cours, on a rien besoin de faire, à part attendre
		}

		if action.target.isDone()			<=> 	action.target.read() == "2"
		{
//			la cible annonce qu'elle a terminé sa tache, il faut libérer la cible, et supprimer l'action en cours pour prendre la prochaine.

			action.target.write("0");
			action = NULL;
		}

	}


}
