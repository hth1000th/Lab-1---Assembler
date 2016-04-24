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
