#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day3 global vars */
#define TABLE_WIDTH  140
#define TABLE_LENGTH 140
int part_bombs[TABLE_LENGTH][TABLE_WIDTH] = { 0 };
int gear_bombs[TABLE_LENGTH][TABLE_WIDTH] = { 0 };
char engine_visu[TABLE_LENGTH][TABLE_WIDTH + 1] = { '\0' };
/* char **engine_visu; */
/* uint_32t **part_bombs; */

/* to keep track of the position */
/* m: index to width */
/* n: index to length */
int mb = 0;
int nb = 0;
int gear_index = 0;
int gear_last_index = 0;
/* END: Day3 global vars */

/* Day3 functions */
int calc_part_number()
{
  int total_part_number = 0;
  int total_gear_number = 0;

  int new_number_found = 0;
  int new_number = 0;
  int bomb_found = 0;
  /* int gear_first_component = 0; */
  int gear_collection[1024] = { 0 };
  int gear_first_component[1024] = { 0 };
  int gear_found = 0;
  int gear_found_index = 0;

  for (int i = 0; i < TABLE_LENGTH; i++) {
    for (int j = 0; j < TABLE_WIDTH + 1; j++) {
      /* printf("%s\n", *engine_visu+(i * (TABLE_WIDTH + 1) + j)); */
      if (engine_visu[i][j] != '\0') {
        if (!new_number_found) {
          new_number_found = 1;
          new_number = atoi(*engine_visu+
              (i * (TABLE_WIDTH + 1) + j));
        }
        if (part_bombs[i][j] == 1)
          bomb_found = 1;
        if (gear_bombs[i][j]) {
          gear_found = gear_bombs[i][j];
        }
      } else {
        if (new_number_found) {
          new_number_found = 0;
          if (bomb_found) {
            total_part_number += new_number;
          }
          if (gear_found) {
            gear_collection[gear_found_index] = gear_found;
            gear_first_component[gear_found_index++] = new_number;
            printf("Gear found: %d\t%d\n", gear_found, new_number);
            for (int x = 0; x < 1024; x++) {
              if (gear_collection[x] == gear_found && 
                  x != gear_found_index - 1) {
                total_gear_number += gear_first_component[x] * 
                  new_number;
                printf("Gear complete: %d. Total: %d\n",
                    new_number * gear_first_component[x], 
                    total_gear_number);
                break;
              }
            }
            /* gear_first_component = 0; */
          }
          else {
            /* gear_first_component = new_number; */
            gear_last_index = gear_found;
          }
        }
        new_number = 0;
        bomb_found = 0;
        gear_found = 0;
      }
    }
  }

  return total_gear_number;
}

void set_bombs(int isGear, int i, int j)
{
  for (int ic = i - 1; ic <= i + 1; ic++) {

    if (ic < 0 || ic > TABLE_LENGTH - 1)
      continue;

    for (int jc = j - 1; jc <= j + 1; jc++) {

      if (jc < 0 || jc > TABLE_WIDTH - 1)
        continue;

      part_bombs[ic][jc] = 1;
      gear_bombs[ic][jc] = isGear;
    }
  }

  return;
}

int day_three(char *line)
{
  char ch;
  for (mb = 0; (ch = *line) != '\n'; mb++, *line++) {
    if ((ch-48) > 9 || (ch-48) < 0) {
      if (ch != '.') { /* Anything not '.' and not number are symbols */
        if (ch == '*') {
          gear_index++;
          set_bombs(gear_index, nb, mb);
        }
        else
          set_bombs(0, nb, mb);
      }
    } else { /* In case of number */
      engine_visu[nb][mb] = ch;
    }
  }

  return 0;
}
/* END: Day3 functions */

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
    if (st == -1) {
      break;

      /* specific to Day3 */
      mb = 0;
      /* END: specific to Day3 */
    }

    /* specific to Day3 */
    day_three(*lineptr);
    nb++;
    /* END: specific to Day3 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  read_input(argv[0], "input.txt");

  fclose(finput);

  /* for (int i = 0; i < TABLE_LENGTH; i++) { */
  /*   for (int j = 0; j < TABLE_LENGTH; j++) { */
  /*     printf("%d", part_bombs[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  /* printf("\n"); */
  /* for (int i = 0; i < TABLE_LENGTH; i++) { */
  /*   for (int j = 0; j < TABLE_LENGTH; j++) { */
  /*     if (engine_visu[i][j] != '\0') */
  /*       printf("%c", engine_visu[i][j]); */
  /*     else */
  /*       printf("."); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  /* for (int i = 0; i < TABLE_LENGTH; i++) { */
  /*   for (int j = 0; j < TABLE_LENGTH; j++) { */
  /*     printf("%d", gear_bombs[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /*   for (int j = 0; j < TABLE_LENGTH; j++) { */
  /*     if (engine_visu[i][j] != '\0') */
  /*       printf("%c", engine_visu[i][j]); */
  /*     else */
  /*       printf("."); */
  /*   } */
  /*   printf("\n"); */
  /*   printf("--\n"); */
  /* } */
  /* for (int i = 0; i < TABLE_LENGTH; i++) { */
  /*   for (int j = 0; j < TABLE_LENGTH; j++) { */
  /*     if (engine_visu[i][j] != '\0') */
  /*       printf("%c", engine_visu[i][j]); */
  /*     else */
  /*       printf("."); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  printf("The total is: %d\n", calc_part_number());
  return 0;
}
