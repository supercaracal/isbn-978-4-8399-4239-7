#include <stdlib.h>
#include <stdio.h>

static char *
digits_to_char_array(int n) {
  int i, digits;
  char *ret;

  for (i = 1, digits = 0; i <= n; i *= 10) ++digits;
  ret = (char *) malloc(sizeof(char) * digits + 1);
  if (ret == NULL) return NULL;

  sprintf(ret, "%d", n);
  ret[digits + 1] = '\0';

  return ret;
}

static char *
compress(char *str) {
  char current, next, digit;
  char *tmp;
  char *buf;
  char *buf_tmp;
  char *char_arr;
  char *char_arr_tmp;
  int size, count, after_size;

  size = 0;
  tmp = str;
  while (*tmp++) ++size;

  buf = malloc(size + 1);
  if (buf == NULL) return NULL;

  buf_tmp = buf;
  tmp = str;
  count = 0;
  after_size = 0;
  while (*tmp) {
    current = *tmp++;
    next = *tmp;
    ++count;
    if (current == next) continue;

    *buf_tmp++ = current;
    if (++after_size >= size) return str;
    char_arr = digits_to_char_array(count);
    char_arr_tmp = char_arr;
    while (*char_arr_tmp) {
      digit = *char_arr_tmp++;
      *buf_tmp++ = digit;
      if (++after_size >= size) return str;
    }
    free(char_arr);
    char_arr = NULL;
    count = 0;
  }
  *buf_tmp = '\0';

  return buf;
}

int
main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: 1-5 foobarbaz\n");
    exit(1);
  }

  fprintf(stdout, "%s\n", compress(argv[1]));
  exit(0);
}
