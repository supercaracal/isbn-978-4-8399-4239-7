#include <stdlib.h>
#include <stdio.h>

#define APPEND_CHAR(buf, c) \
  do {\
    buf->str[buf->idx++] = c;\
  } while(0)

struct str_buf {
  char *str;
  int size;
  int idx;
};

static int
str_size(char *str) {
  int size;

  size = 0;
  while(*str++) ++size;
  return size;
}

static struct str_buf *
alloc_str_buf(struct str_buf *buf, int default_size) {
  char *tmp;
  int size;

  if (buf == NULL) {
    buf = (struct str_buf *) malloc(sizeof(struct str_buf));
    buf->str = (char *) malloc(default_size);
    buf->size = default_size;
    buf->idx = 0;
  } else if (buf->idx >= buf->size) {
    size = buf->size * 2;
    tmp = realloc(buf->str, size);
    if (tmp != NULL) {
      buf->str = tmp;
      buf->size = size;
    }
  }

  return buf;
}

static void
free_str_buf(struct str_buf *buf) {
  free(buf->str);
  buf->str = NULL;
  free(buf);
  buf = NULL;
}

static char *
escape_space(char *str, int size, struct str_buf *buf) {
  int i;

  for (i = 0; i < size; ++i) {
    buf = alloc_str_buf(buf, size);
    if (str[i] == ' ') {
      APPEND_CHAR(buf, '%');
      APPEND_CHAR(buf, '2');
      APPEND_CHAR(buf, '0');
    } else {
      APPEND_CHAR(buf, str[i]);
    }
  }
  APPEND_CHAR(buf, '\0');

  return buf->str;
}

int
main(int argc, char **argv) {
  struct str_buf *buf;
  int size;

  if (argc != 2) {
    fprintf(stderr, "usage: 1-4 \"foo bar baz\"\n");
    exit(1);
  }

  buf = NULL;
  size = str_size(argv[1]);
  buf = alloc_str_buf(buf, size);
  fprintf(stdout, "%s\n", escape_space(argv[1], size, buf));
  free_str_buf(buf);
  exit(0);
}
