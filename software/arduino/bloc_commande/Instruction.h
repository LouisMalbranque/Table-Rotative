#include "arduino.h"
#include "Peripherique.h"

typedef struct {
  Peripherique* target;
  String data;
}Instruction;
