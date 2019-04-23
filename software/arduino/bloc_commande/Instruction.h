#include "arduino.h"
#include "Peripherique.h"

typedef struct {
  int id_commande;
  int id_instruction;
  Peripherique* target;
  String data;
}Instruction;
