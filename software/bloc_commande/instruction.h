#include "arduino.h"

class Instruction
{
  private:
    void (*runnable) (void);
  public:
    Instruction();
    Instruction(void (*runnable) (void));
    void run();
};
