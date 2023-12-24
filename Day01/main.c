#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day one global vars */
int result = 0;
int match_array = 0;
int letter_index = 0;
char digit_in_word[10][6] = {
  {'z', 'e', 'r', 'o', '\0'},
  {'o', 'n', 'e', '\0'},
  {'t', 'w', 'o', '\0'},
  {'t', 'h', 'r', 'e', 'e', '\0'},
  {'f', 'o', 'u', 'r', '\0'},
  {'f', 'i', 'v', 'e', '\0'},
  {'s', 'i', 'x', '\0'},
  {'s', 'e', 'v', 'e', 'n', '\0'},
  {'e', 'i', 'g', 'h', 't', '\0'},
  {'n', 'i', 'n', 'e', '\0'},
};
/* END: Day one global vars */

int get_digit_from_word(char c)
{
  if (match_array) {
    if (c == digit_in_word[match_array - 1][letter_index]) {
      letter_index++;
      if ((digit_in_word[match_array - 1][letter_index]) == '\0') {
        int temp_return = match_array - 1;
        match_array = 0;
        letter_index = 0;
        return temp_return;
      }
      else {
        return 0;
      }
    } else if (letter_index == 1 &&
        (match_array == 3 || match_array == 5 || match_array == 7) &&
        c == digit_in_word[match_array][letter_index]) {
      match_array++;
      letter_index++;
      return 0;
    } else {
      match_array = 0;
      letter_index = 0;
    }
  }

  for (int i = 0; i < 10; i++) {
    if (c == digit_in_word[i][letter_index]) {
      match_array = i + 1;
      letter_index++;
      return 0;
    }
  }

  return 0;
}

int day_one(char *line)
{
  char ch;
  int digit1 = 0;
  int digit2 = 0;
  int dgt;
  int first_digit = 1;

  while ((ch = *line++) != '\0') {
    if ((ch-48) > 9 || (ch-48) < 0) {
      if (!(dgt = get_digit_from_word(ch))) {
        continue;
      }
      ch = dgt + 48;
    }

    ch -= 48;
    digit2 = ch;
    digit1 = digit1 + first_digit * ch;
    first_digit = 0;
  }

  result = result + digit1 * 10 + digit2;
  printf("digit1: %d\t", digit1);
  printf("digit2: %d\t", digit2);
  printf("result: %d\n", result);

  return 0;
}

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

    /* specific to Day1 */
    day_one(*lineptr);
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
