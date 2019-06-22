#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void
reverse(char *str) {
  int i, j;
  char c;

  for (i = 0, j = strlen(str) - 1; i < j; ++i, --j) {
    c = str[i];
    str[i] = str[j];
    str[j] = c;
  }
}

int
main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: 1-2 foobarbaz\n");
    exit(1);
  }

  reverse(argv[1]);

  fprintf(stdout, "%s\n", argv[1]);
  exit(0);
}
