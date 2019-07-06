#include <stdlib.h>
#include <stdio.h>

struct node {
  char *value;
  struct node *next;
};

static int
equal(char *a, char *b) {
  while (*a && *b) {
    if (*a++ != *b++) return 0;
  }
  return !*a && !*b;
}

static struct node *
build_list(int size, char **values) {
  struct node *n;

  n = (struct node *) malloc(sizeof(struct node));
  n->value = *values++;
  n->next = --size > 0 ? build_list(size, values) : NULL;
  return n;
}

static void
free_list(struct node *n) {
  struct node *next;

  if (!n) return;
  next = n->next;
  free(n);
  if (next) free_list(next);
}

static struct node *
dig(struct node *f, struct node *b) {
  struct node *n;

  n = NULL;

  if (f->next == NULL) {
    if (equal(f->value, b->value)) n = b->next ? b->next : b;
  } else {
    n = dig(f->next, b);
    if (n && (f == b || equal(f->value, n->value))) {
      n = n->next ? n->next : n;
    } else {
      n = NULL;
    }
  }

  return n;
}

static int
is_palindrome(struct node *n) {
  return dig(n, n) ? 1 : 0;;
}

int
main(int argc, char **argv) {
  struct node *n;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "uasge: 2-7 a b c b a");
    exit(1);
  }

  n = build_list(argc - 1, &argv[1]);
  fprintf(stdout, "%s\n", is_palindrome(n) ? "yes" : "no");
  free_list(n);
  exit(0);
}
