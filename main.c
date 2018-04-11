#include <stdio.h>
#include <string.h>
#include "boyer_moore.h"

int main(void) {
  char linha[] = "This eBook is for the use of anyone anywhere at no cost and with";
  char search[] = "eBook";
  printf("%d\n", (int) strlen(linha));
  printf("%d\n", (int) strlen(search));
  printf("%s\n", boyer_moore((uint8_t*) linha, strlen(linha), (uint8_t*) search, strlen(search)));

  return 0;
}
