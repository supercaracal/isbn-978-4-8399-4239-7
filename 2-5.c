#include <stdlib.h>
#include <stdio.h>

#define CHAR2INT(n) (n - '0')
#define INT2CHAR(c) ('0' + c)

struct node {
  int digit;
  struct node *next;
};

static struct node *
build_list_from_str(char *num) {
  struct node *n;

  n = (struct node *) malloc(sizeof(struct node));
  n->digit = CHAR2INT(*num++);
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
  if (q == 0) return n;

  m = build_list_from_int(q);
  m->next = n;
  return m;
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

static struct node *
add(struct node *a, struct node *b) {
  struct node *m;
  struct node *n;
  struct node *o;

  if (a->next || b->next) {
    m = add(a->next ? a->next : a, b->next ? b->next : b);
  } else {
    m =  NULL;
  }

  n = build_list_from_int(a->digit + b->digit);

  if (m != NULL) {
    if (m->next) {
      if (n->next) {
        n->next->digit += m->digit;
        n->next->next = m->next;
      } else {
        n->digit += m->digit;
        n->next = m->next;
      }
      free(m);
    } else {
      if (n->next) {
        n->next->next = m;
      } else {
        n->next = m;
      }
    }

    if (n->next && n->next->digit > 9) {
      n->digit++;
      n->next->digit -= 10;
    }

    if (n->digit > 9) {
      o = build_list_from_int(n->digit);
      o->next->next = n->next;
      free(n);
      return o;
    }
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
  t = add(a, b);

  fprintf(stdout, "%s + %s = %s\n", to_str(a), to_str(b), to_str(t));

  free_list(a);
  free_list(b);
  free_list(t);

  exit(0);
}
