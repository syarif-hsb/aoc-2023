#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day two global vars */
int result_possible = 0;
int result_second_possible = 0;
int max_red = 12;
int max_green = 13;
int max_blue = 14;
/* END: Day two global vars */

/* Day two functions */
int day_two_second_question(char *line)
{
  int id;
  int gball = 0;
  int bball = 0;
  int rball = 0;
  int power = 0;
  const char *delim_token = ":;";
  const char *delim_subtoken = ", \n";

  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int j;
  for (j = 1, str1 = line; ; j++, str1 = NULL) {
    token = strtok_r(str1, delim_token, &saveptr1);
    if (token == NULL)
      break;

    int ball_count = 0;
    for (str2 = token; ; str2 = NULL) {
      subtoken = strtok_r(str2, delim_subtoken, &saveptr2);
      if (subtoken == NULL)
        break;
      if (!strcmp(subtoken, "Game")) {
        id = atoi(strtok_r(NULL, delim_subtoken, &saveptr2));
        continue;
      }
      if (ball_count) {
        if (!(strcmp(subtoken, "green")))
        {
          if (ball_count > gball)
            gball = ball_count;
        }
        if (!(strcmp(subtoken, "blue")))
        {
          if (ball_count > bball)
            bball = ball_count;
        }
        if (!(strcmp(subtoken, "red")))
        {
          if (ball_count > rball)
            rball = ball_count;
        }
      }
      ball_count = atoi(subtoken);
    }
  }

  power = gball * rball * bball;

  return power;
}

int day_two(char *line)
{
  int id;
  const char *delim_token = ":;";
  const char *delim_subtoken = ", \n";

  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int j;
  for (j = 1, str1 = line; ; j++, str1 = NULL) {
    token = strtok_r(str1, delim_token, &saveptr1);
    if (token == NULL)
      break;

    int ball_count = 0;
    for (str2 = token; ; str2 = NULL) {
      subtoken = strtok_r(str2, delim_subtoken, &saveptr2);
      if (subtoken == NULL)
        break;
      if (!strcmp(subtoken, "Game")) {
        id = atoi(strtok_r(NULL, delim_subtoken, &saveptr2));
        continue;
      }
      if (ball_count) {
        if (!(strcmp(subtoken, "green")))
        {
          if (ball_count > max_green)
          {
            printf("Game Id: %d\n", id);
            printf("Green Ball Count is: %d\n", ball_count);
            printf("\n");
            return 0;
          }
        }
        if (!(strcmp(subtoken, "blue")))
        {
          if (ball_count > max_blue)
          {
            printf("Game Id: %d\n", id);
            printf("Blue Ball Count is: %d\n", ball_count);
            printf("\n");
            return 0;
          }
        }
        if (!(strcmp(subtoken, "red")))
        {
          if (ball_count > max_red)
          {
            printf("Game Id: %d\n", id);
            printf("Red Ball Count is: %d\n", ball_count);
            printf("\n");
            return 0;
          }
        }
      }
      ball_count = atoi(subtoken);
    }
  }

  return id;
}
/* END: Day two functions */

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

    /* specific to Day2 */
    char *line_copy = strdup(*lineptr);
    result_possible += day_two(*lineptr);
    result_second_possible += day_two_second_question(line_copy);
    free(line_copy);
  }
  printf("Sum of ID that are possible: %d\n", result_possible);
  printf("Power Accumulation of the balls: %d\n", result_second_possible);
    /* END: specific to Day2 */

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  read_input(argv[0], "input.txt");

  fclose(finput);
  return 0;
}
