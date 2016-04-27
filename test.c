#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <opcode.h>
#include <helper_functions.h>
#include <test.h>

int main(void) {

  test_getOpcode();
  test_is_comment();
  test_is_blank();
  test_is_register();
  test_increment_address();
  test_command_group1();
  test_get_two_tokens();
  test_command_group3();
  test_command_group24();
  test_select_commands();

  puts("testing complete");
  return 0;
}

void test_getOpcode() {
  puts("testing int getOpcode(char * command)");
  assert(getOpcode("LDD") == 1);
  assert(getOpcode("CAT") == -1);
  assert(getOpcode("STO") == 3);
  assert(getOpcode("NOP") == 0);
  assert(getOpcode("STX") == 14);
}
void test_is_comment() {
  puts("testing int is_comment(char * str)");
  assert(is_comment(";Hello") == 1);
  assert(is_comment("testing") == 0);
  assert(is_comment(" ") == 0);
}
void test_is_blank() {
  puts("testing int is_blank(char * str)");
  assert(is_blank("\n") == 1);
  assert(is_blank(" ") == 0);
  assert(is_blank("\nLDD") == 1);
}
void test_is_register() {
  puts("testing int is_register(char * token)");
  assert(is_register("R0") == 1);
  assert(is_register("r1") == 0);
  assert(is_register("12") == 0);
}

void test_increment_address() {
  int address[] = {0,0};
  puts("testing void increment_address(int address[])");
  increment_address(address);
  assert(address[0] == 0 && address[1] == 2);
  address[0] = 5;
  address[1] = 12;
  increment_address(address);
  assert(address[0] == 5 && address[1] == 14);
  address[0] = 3;
  address[1] = 14;
  increment_address(address);
  assert(address[0] == 4 && address[1] == 0);
  address[0] = 7;
  address[1] = 16;
  increment_address(address);
  assert(address[0] == 8 && address[1] == 0);
}

void test_command_group1() {
  char memo[3];
  puts("testing void command_group1(char memo[])");
  command_group1(memo);
  assert(strcmp(memo, "000")==0);
}

void test_get_two_tokens() {
  char *token[2];
  char str[] = "MOV RC, R7";
  puts("testing void get_two_tokens(char *token[])");
  strtok(str, " ,\t\n");
  get_two_tokens(token);
  assert(strcmp(token[0], "RC")==0 && strcmp(token[1], "R7")==0);
  strcpy(str, "OR R4, R2, RB");
  strtok(str, " ,\t\n");
  get_two_tokens(token);
  assert(strcmp(token[0], "R4")==0 && strcmp(token[1], "R2")==0);
  strcpy(str, "ROR RC, 2");
  strtok(str, " ,\t\n");
  get_two_tokens(token);
  assert(strcmp(token[0], "RC")==0 && strcmp(token[1], "2")==0);
}

void test_command_group3() {
  char memo[3];
  char str[] = "LDX R5, RC";
  puts("testing void command_group3(char memo[])");
  strtok(str, " ,\t\n");
  command_group3(memo);
  assert(strcmp(memo, "5C0")==0);
  strcpy(str, "MOV RC, R7");
  strtok(str, " ,\t\n");
  command_group3(memo);
  assert(strcmp(memo, "C70")==0);
}

void test_command_group24() {
  char memo[3];
  char str[] = "ADI RC, R3, RF";
  puts("testing void command_group24(char memo[])");
  strtok(str, " ,\t\n");
  command_group24(memo);
  assert(strcmp(memo, "C3F")==0);
  strcpy(str, "STO RC, D2");
  strtok(str, " ,\t\n");
  command_group24(memo);
  assert(strcmp(memo, "CD2")==0);
}

void test_select_commands() {
  char memo[3];
  char str[] = "STX R5, RC";
  puts("testing void select_commands(int opcode, char memo[])");
  select_commands(0, memo);
  assert(strcmp(memo, "000")==0);
  strtok(str, " ,\t\n");
  select_commands(14, memo);
  assert(strcmp(memo, "5C0")==0);
  strcpy(str, "XOR RC, R3, RF");
  strtok(str, " ,\t\n");
  select_commands(9, memo);
  assert(strcmp(memo, "C3F")==0);
}
