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

static void
free_list(int size, struct node *n) {
  struct node *next;

  if (size == 0 || !n) return;
  next = n->next;
  free(n);
  if (next) free_list(--size, next);
}

static struct node *
build_list(int size, char **values) {
  int i, j;
  struct node *n0;
  struct node *n1;
  struct node *n2;
  struct node *n3;

  for (i = 0, j = size - 1, n0 = n1 = n2 = n3 = NULL; i < j; ++i, n1 = n2) {
    n2 = (struct node *) malloc(sizeof(struct node));
    n2->value = values[i];
    if (n1) {
      n1->next = n2;
    } else {
      n0 = n2;
    }
    if (equal(values[i], values[j])) {
      n3 = (struct node *) malloc(sizeof(struct node));
      n3->value = values[j];
      n3->next = n2;
    }
  }

  if (n3 == NULL) {
    free_list(size, n0);
    return NULL;
  }

  n2->next = n3;

  return n0;
}

static struct node *
find_first_circulated_node(struct node *n) {
  struct node *rabbit;
  struct node *tortoise;

  if (!n) return n;

  rabbit = tortoise = n;
  do {
    if (rabbit->next) rabbit = rabbit->next;
    if (rabbit->next) rabbit = rabbit->next;
    if (tortoise->next) tortoise = tortoise->next;
  } while (rabbit != tortoise);

  rabbit = n;
  do {
    if (rabbit->next) rabbit = rabbit->next;
    if (tortoise->next) tortoise = tortoise->next;
  } while (rabbit != tortoise);

  return rabbit;
}

int
main(int argc, char **argv) {
  struct node *n;
  int size;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "uasge: 2-6 a b c d e c");
    exit(1);
  }

  size = argc - 1;

  n = build_list(size, &argv[1]);

  if (n == NULL) {
    fprintf(stderr, "%s\n", "Please specify circulated list using last element.");
    exit(1);
  }

  fprintf(stdout, "%s\n", find_first_circulated_node(n)->value);
  free_list(size, n);
  exit(0);
}
