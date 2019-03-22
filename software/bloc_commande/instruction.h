#include "arduino.h"
#include "constantes.h"

class Instruction
{
  private:
    void (*runnable) (void);
  public:
    Instruction();
    Instruction(void (*runnable) (void));
    void run();
};
