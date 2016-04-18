#include "opcode.h"
#include <string.h>

int getOpcode(char * command)
{
	char *commands[15] = {
		"NOP", "LDD", "LDI",
		"STO", "MOV", "ADI",
		"ADF", "OR", "AND",
		"XOR", "ROR", "JMP",
		"HLT", "LDX", "STX"};
  int i;
  int j = -1;

  for(i=0; i<15; i++) {
    if(strcasecmp(command, commands[i]) == 0) {
      j = i;
      break;
    }
  }
  return j;
}
