#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <locale.h>

FILE *finput;

/* Day4 global vars */
#define ARRAY_LENGTH 21
int total_value = 0;
int total_value_second = 0;
/* END: Day4 global vars */

/* Day4 functions */
int get_value_of_history(int *hist, int reverse)
{
  int val_hist = 0;
  /* int array[] */

  int matroska[ARRAY_LENGTH][ARRAY_LENGTH+1] = { 0 };

  /* ensure all are zero */
  for (int i = 0; i < ARRAY_LENGTH; i++)
    for (int j = 0; j < ARRAY_LENGTH; j++)
      matroska[i][j] = 0;
  
  int i, j;
  int check_all_zero;
  for (i = 0; i < ARRAY_LENGTH; i++) {
    check_all_zero = 1;
    for (j = 0; j < ARRAY_LENGTH - i; j++) {
      if (!i)
        matroska[i][j] = hist[j];
      else {
        matroska[i][j] = matroska[i - 1][j + 1] - matroska[i - 1][j];
      }
      if (matroska[i][j])
        check_all_zero = 0;
      printf("%d ", matroska[i][j]);
    }
    printf("\nCheck: %d\n", check_all_zero);
    if (check_all_zero)
      break;
  }

  for ( j--; i >= 0 ; i--, j++) {
    if (reverse)
      val_hist = matroska[i][0] - val_hist;
    else
      val_hist += matroska[i][j];
  }

  printf("Value: %d\n", val_hist);

  return val_hist;
}

int day_nine(const char *line, int reverse)
{
  /* int val_history = 0; */
  int history[ARRAY_LENGTH];

  /* printf("%s", line); */
  char *str = strdup(line);
  char *token;
  const char *delim_token = " \n";
  int j;
  for (j = 0; ; j++, str = NULL) {
    token = strtok(str, delim_token);
    if (token == NULL)
      break;

    history[j] = atoi(token);
  }

  return get_value_of_history(history, reverse);
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
    total_value += day_nine(*lineptr, 0);
    printf("========================================\n");
    total_value_second += day_nine(*lineptr, 1);
    printf("========================================\n");
    /* END: specific to Day4 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  read_input(argv[0], "input.txt");

  fclose(finput);

  printf("First total value: %d\n", total_value);
  printf("Second total value: %d\n", total_value_second);

  return 0;
}
