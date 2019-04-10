#include "arduino.h"
#include "Peripherique.h"
#include "constantes.h"
#include <pthread.h>

class CameraThread: public Peripherique
{
  private:

    pthread_t thread;


  public:
    using Peripherique::Peripherique;
    void begin();
    String read();
    void write(String d);

    String createDatagramme(int* values);
};
