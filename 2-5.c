#include <stdlib.h>
#include <stdio.h>

#define CHAR2INT(n) (n - '0')
#define INT2CHAR(c) ('0' + c)
#define FIRST_CALL 1

struct node {
  int digit;
  int carry;
  struct node *next;
};

static struct node *
build_list_from_str(char *num) {
  struct node *n;

  n = (struct node *) malloc(sizeof(struct node));
  n->digit = CHAR2INT(*num++);
  n->carry = 0;
  n->next = *num ? build_list_from_str(num) : NULL;
  return n;
}

static struct node *
build_list_from_int(int num) {
  struct node *m;
  struct node *n;
  int q, r;

  q = num / 10;
  r = num % 10;

  n = (struct node *) malloc(sizeof(struct node));
  n->digit = r;
  n->next = NULL;
  if (q < 10) {
    n->carry = q;
    return n;
  } else {
    m = build_list_from_int(q);
    m->next = n;
    return m;
  }
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
to_str(struct node *n) {
  int size, i;
  char *str;
  struct node *tmp;

  if (n == NULL) return NULL;
  for (tmp = n, size = 0; tmp; tmp = tmp->next) ++size;
  str = (char *) malloc(size + 1);
  for (tmp = n, i = 0; tmp; tmp = tmp->next, ++i) str[i] = INT2CHAR(tmp->digit);
  str[i] = '\0';
  return str;
}

static int
length(struct node *n) {
  int size;
  for (size = 0; n; n = n->next) ++size;
  return size;
}

static struct node *
pad_left_zero(struct node *n, int size) {
  struct node *z;

  if (size == 0) return n;
  z = (struct node *) malloc(sizeof(struct node));
  z->digit = 0;
  z->next = n;
  return pad_left_zero(z, --size);
}

static struct node *
add(struct node *a, struct node *b, int first_call) {
  struct node *m;
  struct node *n;
  int size_a, size_b;

  if (!a && !b) return NULL;

  size_a = length(a);
  size_b = length(b);
  if (size_a > size_b) {
    b = pad_left_zero(b, size_a - size_b);
  } else if (size_a < size_b) {
    a = pad_left_zero(a, size_b - size_a);
  }

  if (a->next || b->next) {
    m = add(a->next ? a->next : NULL, b->next ? b->next : NULL, 0);
  } else {
    m =  NULL;
  }

  n = build_list_from_int(a->digit + b->digit);

  if (m != NULL) {
    n->digit += m->carry;
    m->carry = 0;
    n->next = m;

    if (n->digit > 9) {
      n->carry = n->digit / 10;
      n->digit = n->digit % 10;
    }
  }

  if (first_call && n->carry) {
    m = build_list_from_int(n->carry);
    n->digit = n->digit % 10;
    n->carry = 0;
    m->next = n;
    n = m;
  }

  return n;
}

int
main(int argc, char **argv) {
  struct node *a;
  struct node *b;
  struct node *t;

  if (argc != 3) {
    fprintf(stderr, "%s\n", "uasge: 2-5 number number");
    exit(1);
  }

  a = build_list_from_str(argv[1]);
  b = build_list_from_str(argv[2]);
  t = add(a, b, FIRST_CALL);

  fprintf(stdout, "%s + %s = %s\n", to_str(a), to_str(b), to_str(t));

  free_list(a);
  free_list(b);
  free_list(t);

  exit(0);
}
