#ifndef CONSTANTES_H
#define CONSTANTES_H 				0


#define ID_COMMANDE              	0 // id de la commande reçu
#define MODE                     	1 // donne la type de donnée reçu
#define ACCELERATION             	2 // acceleration du moteur
#define VITESSE                  	3 // vitesse du moteur
#define NOMBRE_DE_PAS_TABLE      	4 // nombre de pas de la table
#define DIRECTION                	5 // sens de rotation du moteur
#define CHOIX_ROTATION           	6 // choix entre rotation en nombre de pas ou rotation en temps
#define NOMBRE_DE_TOUR           	7 // nombre de tour
#define TEMPS_DE_ROTATION        	7 // temps de rotation (en ms)
#define NOMBRE_DE_PHOTOS         	8 // nombre de prises de vues à faire pendant le tour
#define NOMBRE_DE_CAMERAS        	9 // nombre de caméras activées à chaque arret
#define PAUSE_ENTRE_CAMERAS      	10 // temps de pause entre les caméras (en ms)
#define FOCUS_STACKING           	11 // donne le nombre de photos à effectuer avec focus différents à chaque arret et avec chaque caméres
#define NUMERO_CAMERA            	12 // numero de la caméra concernée

#define PULSE_DURATION            	1500 // temps d'activation de la caméra

#define OLED_RESET                	4  
#define MAXIMUM_NUMBER_OF_VALUES  	50 // nombre maximale de données reçues par le bluetooth

#define CAMERA1 					19 // pin de controle de la caméra 1
#define CAMERA2 					32 // pin de controle de la caméra 2
#define CAMERA3 					33 // pin de controle de la caméra 3
#define CAMERA4 					25 // pin de controle de la caméra 4
#define CAMERA5 					26 // pin de controle de la caméra 5
#define CAMERA6 					27 // pin de controle de la caméra 6
#define CAMERA7 					14 // pin de controle de la caméra 7
#define CAMERA8 					12 // pin de controle de la caméra 8
#define CAMERA9 					13 // pin de controle de la caméra 9

static int CAMERA[] = {CAMERA1,CAMERA2,CAMERA3,CAMERA4,CAMERA5,CAMERA6,CAMERA7,CAMERA8,CAMERA9}; // liste des pins de controle des 9 caméras

#define TOUCH7 						4 
#define TOUCH8 						2
#define TOUCH9 						15

#define SDA 						21 // sda i2c
#define SCL 						22 // scl i2c

#define LED 						5 // pin de controle de la led verte

#define RESET 						34 // pin d'interruption pour le reset


#endif
