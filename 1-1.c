#include <stdlib.h>
#include <stdio.h>

#define CHAR_FOUND(ascii, bits) \
  do {\
    if (ascii & bits) return 0;\
    ascii |= (bits);\
  } while(0)

static int
is_unique(const char *word) {
  int i;
  char c;
  unsigned int ascii1;
  unsigned int ascii2;
  unsigned int ascii3;
  unsigned int ascii4;
  unsigned int bits;

  ascii1 = ascii2 = ascii3 = ascii4 = 0;

  for (i = 0; word[i] != '\0'; ++i) {
    c = word[i];
    bits = 1 << (c % 32);
    if (c < 32) {
      CHAR_FOUND(ascii1, bits);
    } else if (c < 64) {
      CHAR_FOUND(ascii2, bits);
    } else if (c < 96) {
      CHAR_FOUND(ascii3, bits);
    } else {
      CHAR_FOUND(ascii4, bits);
    }
  }

  return 1;
}

int
main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stdout, "usage: 1-1 foobarbaz\n");
    exit(1);
  }

  fprintf(stdout, "%s\n", is_unique(argv[1]) ? "unique" : "not unique");
  exit(0);
}
