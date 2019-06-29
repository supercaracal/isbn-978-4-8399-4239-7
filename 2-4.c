#include <stdlib.h>
#include <stdio.h>

struct node {
  int value;
  struct node *next;
};

static struct node *
build_list(int size, char **values) {
  struct node *n;

  n = (struct node *) malloc(sizeof(struct node));
  sscanf(*values++, "%d", &n->value);
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
    fprintf(stdout, "%d ", n->value);
    print_list(n->next);
  }
}

static void
move_forward_if_less_than(struct node *n, int x) {
  struct node *p1;
  struct node *p2;
  int num;

  p1 = p2 = n;
  while (p2) {
    while (p1 && p1->value < x) p1 = p1->next;
    while (p2 && p2->value >= x) p2 = p2->next;
    if (p1 && p2 && p1 >= p2) break;
    if (p1 && p2) {
      num = p1->value;
      p1->value = p2->value;
      p2->value = num;
    } else {
      if (p2) p2 = p2->next;
    }
  }
}

int
main(int argc, char **argv) {
  struct node *n;
  int x;

  if (argc < 3) {
    fprintf(stderr, "%s\n", "uasge: 2-4 number numbers...");
    exit(1);
  }

  sscanf(argv[1], "%d", &x);
  n = build_list(argc - 2, &argv[2]);
  move_forward_if_less_than(n, x);
  print_list(n);
  free_list(n);
  exit(0);
}
