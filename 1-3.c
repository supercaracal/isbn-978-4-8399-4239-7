#include <stdlib.h>
#include <stdio.h>

static int
is_anagram(char *a, char *b) {
  unsigned int count;

  count = 0;
  while(*a) count += (unsigned int) *a++;
  while(*b) count -= (unsigned int) *b++;

  return count == 0;
}

int
main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: 1-3 foo bar\n");
    exit(1);
  }

  fprintf(stdout, "%s\n", is_anagram(argv[1], argv[2]) ? "yes" : "no");
  exit(0);
}
