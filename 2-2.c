#include <stdlib.h>
#include <stdio.h>

#define LIST_SIZE (argc - 2)

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

static char *
reverse_get(struct node *n, int k) {
  struct node *p1;
  struct node *p2;

  for (p1 = p2 = n; k > 1; --k) p2 = p2->next;

  while (p2->next) {
    p1 = p1->next;
    p2 = p2->next;
  }

  return p1->value;
}

int
main(int argc, char **argv) {
  struct node *n;
  int k;

  if (argc < 3) {
    fprintf(stderr, "%s\n", "uasge: 2-2 index elements...");
    exit(1);
  }

  sscanf(argv[1], "%d", &k);
  if (k < 1) {
    fprintf(stderr, "The number of index must be positive. (> %d)\n", 0);
    exit(1);
  }
  if (k > LIST_SIZE) {
    fprintf(stderr, "The number of index must be in range of list size. (%d <= index <= %d)\n", 1, LIST_SIZE);
    exit(1);
  }

  n = build_list(LIST_SIZE, &argv[2]);
  fprintf(stdout, "%s\n", reverse_get(n, k));
  free_list(n);
  exit(0);
}
