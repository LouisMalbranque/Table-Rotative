#include "arduino.h"
#include "Peripherique.h"
#include "constantes.h"
#include <pthread.h>

class CameraThread: public Peripherique
{
  private:
    // thread qui controle les cameras 
    pthread_t thread;
    

  public:
    int nb_camera; // nombre de caméras à activer

  
    using Peripherique::Peripherique; // utilise le constructeur par défaut de Peripherique
    
    void begin(); // démarre le thread
    String read(); // lis la donnée partagée et renvoie sa valeur
    void write(String d); // écrit dans la variable partagée

    String createDatagramme(int* values); // crée le datagramme à envoyer en fonctions des valeurs envoyées en bluetooth
    void setCameras(int nb_camera, int* cameras); // indique les caméras connectées et le nombre de caméras connectées
};
