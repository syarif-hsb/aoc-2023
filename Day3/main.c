#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day3 global vars */
/* END: Day3 global vars */

/* Day3 functions */
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
