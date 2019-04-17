#ifndef CONSTANTES_H
#define CONSTANTES_H 0


#define ID_COMMANDE              0
#define MODE                     1
#define ACCELERATION             2
#define VITESSE                  3
#define NOMBRE_DE_PAS_TABLE      4
#define DIRECTION                5
#define CHOIX_ROTATION           6
#define NOMBRE_DE_TOUR           7
#define TEMPS_DE_ROTATION        7
#define NOMBRE_DE_PHOTOS         8
#define NOMBRE_DE_CAMERAS        9
#define PAUSE_ENTRE_CAMERAS      10
#define FOCUS_STACKING           11

//id commande, mode, acceleration, vitesse, nombre de pas de la table, direction, choix rotation, nombre de tour, temps de rotation, nombre de photos, nombre de caméras, pause entre caméras, focus stacking activé. 

#define PULSE_DURATION            1500

#define OLED_RESET                4
#define MAXIMUM_NUMBER_OF_VALUES  10

#define CAMERA1 35
#define CAMERA2 32
#define CAMERA3 33
#define CAMERA4 25
#define CAMERA5 26
#define CAMERA6 27
#define CAMERA7 14
#define CAMERA8 12
#define CAMERA9 13

static int CAMERA[] = {CAMERA1,CAMERA2,CAMERA3,CAMERA4,CAMERA5,CAMERA6,CAMERA7,CAMERA8,CAMERA9};

#define TOUCH7 4
#define TOUCH8 2
#define TOUCH9 15

#define SDA 21
#define SCL 22

#define LED 5

#define RESET 34


#endif
