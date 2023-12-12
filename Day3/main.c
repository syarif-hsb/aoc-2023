#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day3 global vars */
int *prev_numbers = NULL;
int *prev_numbers_pos = NULL;
int n_prev_numbers = 0;
/* END: Day3 global vars */

/* Day3 functions */
int day_three(char *line)
{
  if (prev_numbers == NULL) {
    int *prev_numbers = malloc(256 * sizeof(int));
  }
  if (prev_numbers_pos == NULL) {
    int *prev_numbers_pos = malloc(256 * sizeof(int));
  }

  int n_digits = 0;
  char *digits = malloc(256 * sizeof(char));
  memset(digits, 0, 256);
  while ((ch = *line++) != '\n') {
    if ((ch-48) > 9 || (ch-48) < 0) {
      if (ch != '.') { /* Anything not '.' and not number are symbols */
      }
    } else { /* In case of number */
      digits[n_digits] = ch;
      n_digits++;
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
    }

    /* specific to Day3 */
    day_three(*lineptr);
    /* END: specific to Day3 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  read_input(argv[0], "input.txt");

  fclose(finput);
  return 0;
}
