#include "opcode.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
  FILE *fp1;
  FILE *fp2;
  char str[60];
  char *token;

  fp1 = fopen("ADD1.ASM","r+");
  fp2 = fopen("ADD2.ASM","w+");

  if(fp1 == NULL) {
  	puts("Error opening file1");
  	return -1;
  }

  while(!feof(fp1)) {
  	fgets(str, 60, fp1);
  	puts(str);
  	fputs(str, fp2);
  }
  fclose(fp1);
  fp1 = fopen("ADD1.ASM","r+");

  while(!feof(fp1)) {
    fgets(str, 60, fp1);
    token = strtok(str, " ,");
    while(token != NULL) {
      int opcode = getOpcode(token);
      printf("%s: %d\n", token, opcode);
      token = strtok(NULL, " ,");
    }
  }

  fclose(fp2);
  return 0;
}
