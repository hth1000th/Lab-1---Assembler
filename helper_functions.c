#include "helper_functions.h"
#include <stdio.h>
#include <string.h> // strtok()
#include <ctype.h>

// to check if each line str is a comment line;
int is_comment(char * str)
{
  return str[0] == ';';
}

// to check if each line str is a blank line;
int is_blank(char * str)
{
  return str[0] == '\n';
}

// to check if each token is a register;
int is_register(char * token)
{
  return token[0] == 'R';
}

// to increase address by 2;
void increment_address(int address[])
{
  if(address[1] >= 14) {
    address[0] += 1;
    address[1] = 0;
  }
  else {
    address[1] += 2;
  }
}

// Group 1: process command
void command_group1(char memo[])
{
  sprintf(memo, "%c%c%c", '0','0','0');
}

void get_two_tokens(char *token[])
{
  int i;
  for(i=0; i<2; i++) {
    token[i] = strtok(NULL, " ,\t\n");
  }
}

// Group 3: process command register register
void command_group3(char memo[])
{
  char *token[2];
  get_two_tokens(token);
  sprintf(memo, "%c%c0", token[0][1], token[1][1]);
}

// Group 2: process command register number;
// Group 4: process command register register register
void command_group24(char memo[]) // Group 2, 4;
{
  char *token[3];
  get_two_tokens(token);
  if(is_register(token[1])){ // Group 4;
    token[2] = strtok(NULL, " ,\t\n");
    sprintf(memo, "%c%c%c", token[0][1], token[1][1], token[2][1]);
  }
  else {                     // Group 2;
    sprintf(memo, "%c%c%c", token[0][1], token[1][0], token[1][1]);
  }
}

void select_commands(int opcode, char memo[])
{
  switch(opcode) {
    case 0:
    case 12:
      command_group1(memo); // Group 1;
      break;
    case 4:
    case 13:
    case 14:                // Group 3;
      command_group3(memo);
      break;
    default:                // Groups 2, 4;
      command_group24(memo);
      break;
  }
}
