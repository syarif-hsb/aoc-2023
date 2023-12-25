#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

FILE *finput;

/* Day4 global vars */
/* The worst AOC so far XD */
#define MAZE_LENGTH 140
#define MAZE_WIDTH  140
int32_t dist_table[MAZE_LENGTH][MAZE_WIDTH];
char direction_map[MAZE_LENGTH][MAZE_WIDTH];
size_t n_row = 0;
int cur_pos[2]; /* i, j */
int init_pos[2]; /* i, j */
int steps;
int right_is_outside = 0;
int left_is_outside = 0;

enum {
  Initial,
  Top,
  Bottom,
  Right,
  Left
};

enum {
  init,
  nw,
  ne,
  se,
  sw,
  ns,
  we,
};
/* END: Day4 global vars */

/* Day4 functions */
int check_surrounding(int m, int n)
{
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i == 0 && j == 0)
        continue;
      if (dist_table[m + i][n + j] < -1)
        return -2;
    }
  }

  return -1;
}

void numbering_table()
{
  if (direction_map[cur_pos[0]][cur_pos[1]] == 'S') {
    dist_table[cur_pos[0]][cur_pos[1]] = 0;
  } else if (dist_table[cur_pos[0]][cur_pos[1]] > 0) {
    if (dist_table[cur_pos[0]][cur_pos[1]] > steps)
      dist_table[cur_pos[0]][cur_pos[1]] = ++steps;
  } else {
    dist_table[cur_pos[0]][cur_pos[1]] = ++steps;
  }
}

int dir_table(char c)
{
  switch (c) {
    case 'L':
      return ne;
    case 'J':
      return nw;
    case 'F':
      return se;
    case '7':
      return sw;
    case '-':
      return we;
    case '|':
      return ns;
    case 'S':
      return init;
  }

  return -1;
}

void mark_left_right(int right, int i, int j)
{
  if (i < 0 || i > MAZE_LENGTH - 1 || j < 0 || j > MAZE_WIDTH - 1)
    return;

  if (!right_is_outside && !left_is_outside) {
    if (dist_table[i][j] == -2) {
      if (right) {
        right_is_outside = 1;
      } else {
        left_is_outside = 1;
      }
    }
  } else {
    if (dist_table[i][j] != -1)
      return;

    if (right)
      dist_table[i][j] -= right_is_outside;
    else
      dist_table[i][j] -= left_is_outside;
  }

  return;
}

int move_one_tile(int dir, int numbering)
{
  int tile_type;
  switch (dir) {
    case Top:
      cur_pos[0]--;
      tile_type = dir_table(direction_map[cur_pos[0]][cur_pos[1]]);
      if (numbering)
        numbering_table();
      if (tile_type == sw) {
        if (!numbering) {
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0]    , cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1]    );
        }
        return Left;
      } else if (tile_type == se) {
        if (!numbering) {
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0]    , cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] + 1);
        }
        return Right;
      } else if (tile_type == ns) {
        if (!numbering) {
          /* I have no idea any other way */
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0]    , cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0]    , cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] + 1);
        }
        return Top;
      }
      break;
    case Bottom:
      cur_pos[0]++;
      tile_type = dir_table(direction_map[cur_pos[0]][cur_pos[1]]);
      if (numbering)
        numbering_table();
      if (tile_type == nw) {
        if (!numbering) {
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0]    , cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] - 1);
        }
        return Left;
      } else if (tile_type == ne) {
        if (!numbering) {
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0]    , cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] + 1);
        }
        return Right;
      } else if (tile_type == ns) {
        if (!numbering) {
          /* I have no idea any other way */
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 0, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 0, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] + 1);
        }
        return Bottom;
      }
      break;
    case Left:
      cur_pos[1]--;
      tile_type = dir_table(direction_map[cur_pos[0]][cur_pos[1]]);
      if (numbering)
        numbering_table();
      if (tile_type == ne) {
        if (!numbering) {
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0]    , cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] + 1);
        }
        return Top;
      } else if (tile_type == se) {
        if (!numbering) {
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0]    , cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] + 1);
        }
        return Bottom;
      } else if (tile_type == we) {
        if (!numbering) {
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1]    );
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] + 1);
        }
        return Left;
      }
      break;
    case Right:
      cur_pos[1]++;
      tile_type = dir_table(direction_map[cur_pos[0]][cur_pos[1]]);
      if (numbering)
        numbering_table();
      if (tile_type == nw) {
        if (!numbering) {
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0]    , cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] - 1);
        }
        return Top;
      } else if (tile_type == sw) {
        if (!numbering) {
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0]    , cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] + 1, cur_pos[1] + 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1]    );
        }
        return Bottom;
      } else if (tile_type == we) {
        if (!numbering) {
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] - 1);
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1]    );
          mark_left_right(0, cur_pos[0] - 1, cur_pos[1] + 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] - 1);
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1]    );
          mark_left_right(1, cur_pos[0] + 1, cur_pos[1] + 1);
        }
        return Right;
      }
      break;
      /* case init */
  }

  if (tile_type == init)
    return Initial;

  printf("Error: Wrong direction detected\n");
  exit(EXIT_FAILURE);
}

int analyze_value(int dir)
{
  int possible = 0;
  int tile_type;
  switch (dir) {
    case Top:
      tile_type = dir_table(
          direction_map[cur_pos[0] - 1][cur_pos[1] + 0]);
      switch (tile_type) {
        case sw:
        case se:
        case ns:
          possible = 1;
          break;
        default:
          break;
      }
      break;
    case Bottom:
      tile_type = dir_table(
          direction_map[cur_pos[0] + 1][cur_pos[1] + 0]);
      switch (tile_type) {
        case nw:
        case ne:
        case ns:
          possible = 1;
          break;
        default:
          break;
      }
      break;
    case Left:
      tile_type = dir_table(
          direction_map[cur_pos[0] + 0][cur_pos[1] - 1]);
      switch (tile_type) {
        case ne:
        case se:
        case we:
          possible = 1;
          break;
        default:
          break;
      }
      break;
    case Right:
      tile_type = dir_table(
          direction_map[cur_pos[0] + 0][cur_pos[1] + 1]);
      switch (tile_type) {
        case nw:
        case sw:
        case we:
          possible = 1;
          break;
        default:
          break;
      }
      break;
  }
  return possible;
}

void walk_the_maze()
{
  int dir;
  int tile;
  /* Initialize */
  for (int i = 0; i < 4; i++) {
    if (analyze_value(Top + i)) {
      dir = Top + i;
      steps = 0;
      numbering_table();
      dir = move_one_tile(dir, 1);
    }
    while (direction_map[cur_pos[0]][cur_pos[1]] != 'S') {
      dir = move_one_tile(dir, 1);
    }
  }

  return;
}

void create_maze(const char *line)
{
  char ch;
  int i = 0;
  while ((direction_map[n_row][i] = *line++) != '\n')
    i++;

  n_row++;

  return;
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
    create_maze(*lineptr);
    /* END: specific to Day4 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  read_input(argv[0], "input.txt");

  fclose(finput);

  for (int i = 0; i < MAZE_LENGTH; i++)
    for (int j = 0; j < MAZE_WIDTH; j++)
      dist_table[i][j] = -1;

  int i, j;
  for (i = 0; i < MAZE_LENGTH; i++)
    for (j = 0; j < MAZE_WIDTH; j++)
      if (direction_map[i][j] == 'S')
        goto S_found;

S_found:
  cur_pos[0] = init_pos[0] = i;
  cur_pos[1] = init_pos[1] = j;

  walk_the_maze();

  int result = 0;
  for (int i = 0; i < MAZE_LENGTH; i++) {
    for (int j = 0; j < MAZE_WIDTH; j++) {
      if (result < dist_table[i][j])
        result = dist_table[i][j];
    }
  }

  printf("The longest steps is: %d\n", result);

  for (int i = 0; i < MAZE_LENGTH; i++) {
    if (dist_table[i][0] < 0)
      dist_table[i][0] -= 1;
    if (dist_table[i][MAZE_WIDTH - 1] < 0)
      dist_table[i][MAZE_WIDTH - 1] -= 1;
  }

  for (int j = 0; j < MAZE_WIDTH; j++) {
    if (dist_table[0][j] < 0)
      dist_table[0][j] -= 1;
    if (dist_table[MAZE_LENGTH - 1][j] < 0)
      dist_table[MAZE_LENGTH - 1][j] -= 1;
  }

  for (int i = 1; i < MAZE_LENGTH - 1; i++) {
    for (int j = 1; j < MAZE_WIDTH - 1; j++) {
      if (dist_table[i][j] == -1)
        dist_table[i][j] = check_surrounding(i, j);
    }
  }

  for (int i = MAZE_LENGTH - 2; i > 0; i--) {
    for (int j = MAZE_WIDTH - 2; j > 0; j--) {
      if (dist_table[i][j] == -1)
        dist_table[i][j] = check_surrounding(i, j);
    }
  }
  dist_table[0][0] += 1;
  dist_table[MAZE_LENGTH - 1][0] += 1;
  dist_table[0][MAZE_WIDTH - 1] += 1;
  dist_table[MAZE_LENGTH - 1][MAZE_WIDTH - 1] += 1;

  int dir;
  cur_pos[0] = init_pos[0];
  cur_pos[1] = init_pos[1];
  for (int i = 0; i < 4; i++) {
    if (analyze_value(Top + i)) {
      dir = Top + i;
      steps = 0;
      numbering_table();
      dir = move_one_tile(dir, 0);
      i = 4;
    }
    printf("Debug. i: %d\n", Top + i);
    while (direction_map[cur_pos[0]][cur_pos[1]] != 'S') {
      dir = move_one_tile(dir, 0);
      if (right_is_outside || left_is_outside)
        goto Outside_found;
    }
  }

Outside_found:

  cur_pos[0] = init_pos[0];
  cur_pos[1] = init_pos[1];
  for (int i = 0; i < 4; i++) {
    if (analyze_value(Top + i)) {
      dir = Top + i;
      steps = 0;
      numbering_table();
      dir = move_one_tile(dir, 0);
      i = 4;
    }
    printf("Debug. i: %d\n", Top + i);
    while (direction_map[cur_pos[0]][cur_pos[1]] != 'S') {
      dir = move_one_tile(dir, 0);
    }
  }

  int result2 = 0;
  for (int i = 0; i < MAZE_LENGTH; i++) {
    for (int j = 0; j < MAZE_WIDTH; j++) {
      if (dist_table[i][j] == -1)
        result2++;
    }
  }

  printf("Enclosed number of cells: %d\n", result2);

  return 0;
}
