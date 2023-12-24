#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <locale.h>

FILE *finput;

/* Day4 global vars */
struct Node {
  char *name;
  char *dst_left;
  char *dst_right;
  struct Node *left;
  struct Node *right;
};

struct Node *map;
char *direction;
int n_map = 0;
int direction_is_obtained = 0;
/* END: Day4 global vars */

/* Day4 functions */
void handling_sigint(int sig)
{

}

uint64_t calculate_steps_second_method()
{
  uint64_t steps = 0;
  char *cur_dir = direction;
  struct Node *pos[256] = { NULL };
  int n_pos;

  for (int i = 0; i < n_map; i++) {
    if ((map[i].name)[2] == 'A') {
      pos[n_pos++] = &map[i];
      printf("%s\n", map[i].name);
    }
  }

  while (1) {
    for (int i = 0; i < n_pos; i++) {
      if (*cur_dir == 'L')
        pos[i] = pos[i]->left;
      if (*cur_dir == 'R')
        pos[i] = pos[i]->right;
    }

    steps++;
    printf("Step: %'lu\n", steps);

    int sync_test = 1;
    for (int i = 0; i < n_pos; i++) {
      if (!(sync_test *= ((pos[i]->name)[2] == 'Z')))
        break;
    }
    if (sync_test)
      return steps;
    if (!*++cur_dir)
      cur_dir = direction;
  }
}

uint64_t calculate_steps(const char *s)
{
  uint64_t steps = 0;
  char *cur_dir = direction;
  struct Node *cur_pos = map;
  while (cur_pos++) {
    if (!strcmp(cur_pos->name, s))
      break;
  }
  while (1) {
    if (*cur_dir == 'L')
      cur_pos = cur_pos->left;
    if (*cur_dir == 'R')
      cur_pos = cur_pos->right;

    steps++;

    /* printf("Steps: %lu. Current node: %s\n", steps, cur_pos->name); */
    if (!strcmp(cur_pos->name, "ZZZ"))
    /* if ((cur_pos->name)[2] == 'Z') */
      break;
    if (!*++cur_dir)
      cur_dir = direction;
  }

  return steps;
}

void arrange_map()
{
  for (int i = 0; i < n_map; i++) {
    for (int j = 0; j < n_map || !map[i].left || !map[i].right; j++) {
      if (!strcmp(map[i].dst_left, map[j].name))
        map[i].left = &map[j];
      if (!strcmp(map[i].dst_right, map[j].name))
        map[i].right = &map[j];
    }
  }
}

int read_line(char *line)
{
  /* printf("%s", line); */
  if (!(strcmp(line, "\n")))
    return 0;

  char *str, *token;
  const char *delim_token = " (),=\n";
  int j;
  for (j = 0, str = line; ; j++, str = NULL) {
    token = strtok(str, delim_token);
    if (token == NULL)
      break;

    if (!direction_is_obtained) {
      direction = strdup(token);
      direction_is_obtained = 1;
      break;
    }

    if (j == 0) 
      map[n_map].name = strdup(token);
    else if (j == 1)
      map[n_map].dst_left = strdup(token);
    else
      map[n_map++].dst_right = strdup(token);
  }

  return 0;
}
/* END: Day4 functions */

void read_input(const char *prog_name, const char *filename)
{
  finput = fopen(filename, "r");
  if (!finput) {
    fprintf(stderr, "Error: %s \'%s\'\n", strerror(errno), prog_name);
    exit(EXIT_FAILURE);
  }

  /* lineptr is the pointer to the line read */
  /* required as an argument for getline() */
  char **lineptr = malloc(sizeof(char**));
  size_t *n = malloc(sizeof(size_t*));

  while (1) {
    ssize_t st;
    st = getline(lineptr, n, finput);
    if (st == -1)
      break;

    /* specific to Day4 */
    read_line(*lineptr);
    /* END: specific to Day4 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  map = malloc(1024 * sizeof(struct Node));

  read_input(argv[0], "input.txt");

  fclose(finput);

  arrange_map();

  setlocale( LC_ALL, "en_US.UTF-8" );
  printf("Steps: %lu\n", calculate_steps("AAA"));
  printf("Steps: %lu\n", calculate_steps_second_method());
  return 0;
}
