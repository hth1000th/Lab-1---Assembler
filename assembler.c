#include "opcode.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
		FILE *fp1 = fopen("ADD1.ASM","r+"); // Open the assembly input file;
  	FILE *fp2 = fopen("ADD1.LST","w+"); // Open the listing output file;
  	FILE *fp3 = fopen("ADD1.OBJ","w+"); // Open the object output file;
  	char header[] = "Mem Opcode\tSource"; // the header line;
  	char str[60];
  	char *token, *memo;
		char regit;
		int i, opcode, op, address;

  	if(fp1 == NULL) {
  		puts("Error opening file1");
  		return -1;
  	}

  	puts(header);
		fputs(header, fp2);
		fputs("\n", fp2);
		address = 00;

		while(!feof(fp1)) {
      fgets(str, 60, fp1);
			if(strncmp(str,";",1) == 0 || strncmp(str,"\n",1) == 0) {
        printf("0%d\t\t",address);
				fprintf(fp2, "0%d\t\t\t\t\t", address);
	  		puts(str);
	  		fputs(str, fp2);
      }
      else {
        token = strtok(str, " ,=+\t\n");
			  while(token!=NULL){
          if(strncmp(token,";",1) == 0) {
            break;
					}
					op = getOpcode(token);

			    if(strncmp(token,"R",1) == 0){
            regit = token[1];
					}
					else if(op == -1) {
						memo = token;
					}
					else {
						opcode = op;
					}
					token = strtok(NULL, " ,=+\t\n");
				}
				printf("0%d %d%c %s\n", i, opcode, regit, memo);
				str[60] = '0';
			}
		}

    fclose(fp1);
  	fclose(fp2);
  	fclose(fp3);

  	return 0;
}
