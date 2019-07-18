#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 64

struct set_of_stacks {
  char ***stacks;
  int stack_size;
  int stack_idx;
  int set_size;
  int set_idx;
};

static char *
extract_value(char *cmd) {
  char *tmp1;
  char *tmp2;

  tmp1 = &cmd[4];
  while (*tmp1++ != ' ') {}
  tmp2 = tmp1;
  while (*tmp2 != '\n') ++tmp2;
  *tmp2 = '\0';

  return tmp1;
}

static struct set_of_stacks *
init_stack(int stack_size) {
  struct set_of_stacks *stk;

  stk = (struct set_of_stacks *) malloc(sizeof(struct set_of_stacks));
  stk->stacks = (char ***) malloc(sizeof(char **) * 1);
  stk->stacks[0] = (char **) malloc(sizeof(char *) * stack_size);

  stk->stack_size = stack_size;
  stk->stack_idx = 0;
  stk->set_size = 1;
  stk->set_idx = 0;

  return stk;
}

static void
free_stack(struct set_of_stacks *stk) {
  int i, j, size;

  for (i = 0; i < stk->set_size; ++i) {
    size = i == stk->set_idx ? stk->stack_idx : stk->stack_size;
    for (j = 0; j < size; ++j) {
      free(stk->stacks[i][j]);
    }
    free(stk->stacks[i]);
  }

  free(stk->stacks);
  free(stk);
  stk = NULL;
}

static void
print_stack(struct set_of_stacks *stk) {
  int i, j, size;

  fprintf(stdout, "[");
  for (i = 0; i <= stk->set_idx; ++i) {
    size = i == stk->set_idx ? stk->stack_idx : stk->stack_size;
    for (j = 0; j < size; ++j) {
      if (i != 0 || j != 0) fprintf(stdout, ", ");
      fprintf(stdout, "%s", stk->stacks[i][j]);
    }
  }
  fprintf(stdout, "]\n");
}

static void
push(struct set_of_stacks *stk, char *val) {
  char ***tmp;

  stk->stacks[stk->set_idx][stk->stack_idx] = val;
  stk->stack_idx++;
  if (stk->stack_idx == stk->stack_size) {
    stk->set_idx++;
    if (stk->set_idx == stk->set_size) {
      tmp = (char ***) realloc(stk->stacks, sizeof(char **) * (stk->set_size + 1));
      if (tmp == NULL) return;
      stk->stacks = tmp;
      stk->set_size++;
      stk->stacks[stk->set_idx] = (char **) malloc(sizeof(char *) * stk->stack_size);
    }
    stk->stack_idx = 0;
  }
}

static char *
pop(struct set_of_stacks *stk) {
  char *val;

  stk->stack_idx--;
  if (stk->stack_idx < 0) {
    stk->stack_idx = stk->stack_size - 1;
    stk->set_idx--;
  }
  if (stk->set_idx < 0) {
    stk->stack_idx = 0;
    stk->set_idx = 0;
    return NULL;
  }
  val = stk->stacks[stk->set_idx][stk->stack_idx];
  stk->stacks[stk->set_idx][stk->stack_idx] = NULL;
  return val;
}

int
main(int argc, char **argv) {
  char *buf;
  int stack_size;
  struct set_of_stacks *stk;

  if (argc != 2) {
    fprintf(stderr, "%s\n", "uasge: 3-3 size-of-stack");
    exit(1);
  }

  sscanf(argv[1], "%d", &stack_size);
  if (stack_size < 1) exit(1);
  stk = init_stack(stack_size);

  while (1) {
    fprintf(stdout, "> ");
    buf = (char *) calloc(1, BUF_SIZE);
    buf = fgets(buf, BUF_SIZE, stdin);
    if (buf == NULL) continue;

    if (strncmp(buf, "push", 4) == 0) {
      push(stk, extract_value(buf));
    } else if (strncmp(buf, "pop", 3) == 0) {
      fprintf(stdout, "%s\n", pop(stk));
      free(buf);
      buf = NULL;
    } else if (strncmp(buf, "list", 4) == 0) {
      print_stack(stk);
      free(buf);
      buf = NULL;
    } else if (strncmp(buf, "quit", 4) == 0) {
      free(buf);
      buf = NULL;
      break;
    } else if (strncmp(buf, "\n", 1) == 0) {
      free(buf);
      buf = NULL;
    } else {
      fprintf(stderr, "Unknown command\n");
      free(buf);
      buf = NULL;
    }
  }

  free_stack(stk);
  exit(0);
}
