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

static int
equal(char *a, char *b) {
  while (*a && *b) {
    if (*a++ != *b++) return 0;
  }
  return !*a && !*b;
}

static void
delete_next(struct node *n) {
  struct node *next;

  if (!n || !n->next) return;

  next = n->next->next;
  free(n->next);
  n->next = next;
}

static void
unique_list(struct node *n) {
  struct node *tmp;

  tmp = n;
  while (tmp && tmp->next) {
    if (equal(n->value, tmp->next->value)) {
      delete_next(tmp);
    } else {
      tmp = tmp->next;
    }
  }

  if (n) unique_list(n->next);
}

int
main(int argc, char **argv) {
  struct node *n;

  if (argc < 2) {
    fprintf(stderr, "%s\n", "uasge: 2-1 foo bar baz");
    exit(1);
  }

  n = build_list(argc - 1, &argv[1]);
  unique_list(n);
  print_list(n);
  free_list(n);
  exit(0);
}
