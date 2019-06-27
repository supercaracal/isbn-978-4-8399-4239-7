#include <stdlib.h>
#include <stdio.h>

static int
is_substring(char *a, char *b) {
  char c, d;
  int i, j;

  for (i = j = 0; a[i]; ++i) {
    c = a[i];
    d = b[j];
    if (c == d) {
      ++j;
    } else {
      j = 0;
    }
    if (!b[j]) return 1;
  }

  return 0;
}

static int
is_same_string_within_ring(char *a, char *b) {
  int size_a, size_b, i, j;
  char *tmp;
  char *buf;

  tmp = a;
  size_a = size_b = 0;
  while (*tmp++) ++size_a;
  tmp = b;
  while (*tmp++) ++size_b;
  if (size_a != size_b) return 0;

  buf = (char *) malloc(size_a * 2 + 1);
  tmp = buf;;
  for (i = 0; i < 2; ++i) {
    for (j = 0; j < size_a; ++j) {
      *tmp++ = a[j];
    }
  }
  *tmp = '\0';

  return is_substring(buf, b);
}

int
main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "%s\n", "uasge: 1-8 foo bar");
    exit(1);
  }

  fprintf(stdout, "%s\n", is_same_string_within_ring(argv[1], argv[2]) ? "yes" : "no");
  exit(0);
}
