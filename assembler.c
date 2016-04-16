#include "opcode.h"
//#include "helper_functions.h"
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
  char str1[60];
  char *token, *memo;
  char regit;
  int opcode, op, address, num=0;

  if(fp1 == NULL) {
    puts("Error opening file1");
    return -1;
  }

  puts(header);
  fputs(header, fp2);
  fputs("\n", fp2);
  address = 00;
  //!feof(fp1)

  while(fgets(str, 60, fp1)) {
		//fgets(str, 60, fp1);
    //if(feof(fp1)) break;
    if(strncmp(str,";",1) == 0 || strncmp(str,"\n",2) == 0) { // if it is a comment line;
      printf("0%d\t\t",address); // print address 00 to screen;
      printf("%s", str); // print results to screen;
      fprintf(fp2, "0%d\t\t\t\t\t", address); // print address 00 to listing file;
      fputs(str, fp2); // print results to listing file;
    }
    else { // if it is not a comment line;
      strcpy(str1,str);
      token = strtok(str, " ,\t\n");
      printf("0%d ", address);
      fprintf(fp2, "0%d ", address);
      while(token!=NULL){
        if(strncmp(token,";",1)==0) break;
        op = getOpcode(token);

        if(strncmp(token,"R",1) == 0){
          regit = token[1];
          printf("%c", regit);
          fprintf(fp2, "%c", regit);
          fprintf(fp3, "%c", regit);
          num++;
          if(num==2) {
            printf(" ");
            fprintf(fp2, " ");
            fprintf(fp3, " ");
            num=0;
          }
        }
        else if(op == -1) {
          memo = token;
          printf("%s", memo);
          fprintf(fp2, "%s", memo);
          fprintf(fp3, "%s", memo);
          num += 2;
          if(num==2) {
            printf(" ");
            fprintf(fp2, " ");
            fprintf(fp3, " ");
            num=0;
          }
        }
        else {
          opcode = op;

          if(opcode==0 || opcode==12) {
            printf("%x0 00", opcode);
            fprintf(fp2, "%x0 00", opcode);
            fprintf(fp3, "%x0 00", opcode);
          }
          else if(opcode>=10) { //change opcode to A,B,C,D, or E;
            printf("%x", opcode);
            fprintf(fp2, "%x", opcode);
            fprintf(fp3, "%x", opcode);
            num++;
          }
          else {
            printf("%d", opcode);
            fprintf(fp2, "%d", opcode);
            fprintf(fp3, "%d", opcode);
            num++;
          }
          if(num==2) {
            printf(" ");
            fprintf(fp2, " ");
            fprintf(fp3, " ");
            num=0;
          }
        }
        token = strtok(NULL, " ,\t\n");
      }
      printf("\t");
      printf("%s", str1);
      fprintf(fp2, "\t\t");
      fprintf(fp2, "%s", str1);
      address += 2;
      str[60] = '0';
    }
  }

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);

  return 0;
}
