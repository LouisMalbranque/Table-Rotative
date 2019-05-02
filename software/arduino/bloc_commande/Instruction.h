#include "arduino.h"
#include "Peripherique.h"

// structure d'instructions
typedef struct {
  int id_commande;     	// id de la commande à laquelle l'instruction est attachée
  int id_instruction; 	// id d'instruction
  Peripherique* target; // périphérique cible de la commande
  String data;			// chaine de caractère à envoyer au périphérique pour qu'il réalise son action
}Instruction;
