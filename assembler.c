#include "opcode.h"
#include "helper_functions.h"
#include <stdio.h>
#include <string.h> // strtok()
#include <ctype.h>

int main(void)
{
  FILE *fp1 = fopen("ADD1.ASM","r+"); // Open the assembly input file;
  FILE *fp2 = fopen("ADD1.LST","w+"); // Open the listing output file;
  FILE *fp3 = fopen("ADD1.OBJ","w+"); // Open the object output file;
  char header[] = "Mem Opcode\tSource";
  char str[60], str1[60];
  char *token;
  char memo[3];
  char current_line[15];
  int opcode;
  int address[2] = {0,0}; // set address to zero

  if(fp1 == NULL) {
    puts("Error opening file1");
    return -1;
  }
  puts(header); // print the header line to screen;
  fprintf(fp2, "%s\n", header); // print the header line to listing file;

  while(fgets(str, 60, fp1)) { // while there are input lines to read;
    if(is_comment(str) || is_blank(str)) {  // if it is a comment line;
      printf("%X%X\t\t%s", address[0], address[1], str);
      fprintf(fp2, "%X%X\t\t\t\t\t%s", address[0], address[1], str);
    }
    else {  // if it is an executable line;
      strcpy(str1, str);
      token = strtok(str, " ,\t\n"); // get first token;
      opcode = getOpcode(token); // get the opcode for the token;
      if(opcode == -1) {
        printf("Invalid opcode!\n");
        continue;
      }
      select_commands(opcode, memo); // select groups for appropriate opcode
      sprintf(current_line, "%X%X %X%c %c%c", address[0], address[1],
              opcode, memo[0], memo[1], memo[2]); // assemble final line
      printf("%s\t%s", current_line, str1);
      fprintf(fp2, "%s\t\t%s", current_line, str1);
      fprintf(fp3, "%X%c %c%c ", opcode, memo[0], memo[1], memo[2]);
      increment_address(address); // increment address by 2;
    }
  }
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);

  return 0;
}
