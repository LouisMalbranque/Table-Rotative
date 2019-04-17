#include "arduino.h"
#include "Peripherique.h"

typedef struct {
  unsigned int id_commande;
  unsigned int id_instruction;
  Peripherique* target;
  String data;
}Instruction;
