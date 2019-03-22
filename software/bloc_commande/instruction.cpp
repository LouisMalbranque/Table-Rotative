#include "instruction.h"

Instruction::Instruction( void (*runnable) (void) ){
  this->runnable = runnable;
}

Instruction::Instruction(){
}

void Instruction::run(){
  (*runnable)();
}
