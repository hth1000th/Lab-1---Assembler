#include <stdio.h>
#include <assert.h>

#include <opcode.h>
#include <test.h>

int main(void) {

  test_getOpcode();

  puts("testing complete");
  return 0;
}

void test_getOpcode() {
  puts("testing int getOpcode(char * command)");
  assert(getOpcode("LDD") == 1);
  assert(getOpcode("CAT") == -1);
  assert(getOpcode("STO") == 3);
}
