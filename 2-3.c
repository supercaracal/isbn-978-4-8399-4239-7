#include <stdlib.h>
#include <stdio.h>

struct node {
  char *value;
  struct node *next;
};

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

static void
print_list(struct node *n) {
  if (n == NULL) {
    fprintf(stdout, "\n");
  } else {
    fprintf(stdout, "%s ", n->value);
    print_list(n->next);
  }
}

static struct node *
take_center(struct node *n, int size) {
  int i, max;
  struct node *p;

  for (i = 0, max = size / 2; i <= max; ++i) p = n->next;
  return p;
}

static void
delete(struct node *n) {
  struct node *tmp;

  if (!n || !n->next) return;
  tmp = n->next;
  n->value = n->next->value;
  n->next = n->next->next;
  free(tmp);
}

int
main(int argc, char **argv) {
  struct node *n;

  if (argc < 4) {
    fprintf(stderr, "%s\n", "uasge: 2-3 foo bar baz (size >= 3)");
    exit(1);
  }

  if (argc % 2) {
    fprintf(stderr, "The size of list must be odd.\n");
    exit(1);
  }

  n = build_list(argc - 1, &argv[1]);
  delete(take_center(n, argc - 1));
  print_list(n);
  free_list(n);
  exit(0);
}
