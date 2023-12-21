#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day4 global vars */
int seeds[256] = {0};
int *categories[3] = { NULL, NULL, NULL };
int seed_cat[256] = { 0 };
int fertilizer_cat[256] = { 0 };
int water_cat[256] = { 0 };
int light_cat[256] = { 0 };
int temperature_cat[256] = { 0 };
int humidity_cat[256] = { 0 };
int location_cat[256] = { 0 };

int seedFlag = 0;
/* END: Day4 global vars */

/* Day4 functions */
int parse_numbers(char *s, int *cat1, int *cat2)
{
  int dest_start, source_start;
  int range;

  const char *delim_token = " \n";
  char *str, *token;
  int i;
  for (i = 0, str = s; ; i++, str = NULL) {
    token = strtok(str, delim_token);
    if (token == NULL)
      break;

    switch(i) {
      case 0:
        dest_start = atoi(token);
        break;
      case 1:
        source_start = atoi(token);
        break;
      case 2:
        range = atoi(token);
        break;
    }
    printf("%#2d ", atoi(token));
  }
  printf("\n");

  return 0;
}

int day_five(char *line)
{
  if (!strcmp(line, "\n")) {
    categories[0] = NULL;
    categories[1] = NULL;
    return 0;
  }
  
  if (categories[0] && categories[2])
    parse_numbers(line, categories[0], categories[2]);

  const char *delim_token = ":";
  const char *delim_subtoken = "- \n";

  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;
  int i, j;
  for (i = 0, str1 = line; ; i++, str1 = NULL) {
    token = strtok_r(str1, delim_token, &saveptr1);
    if (token == NULL)
      break;

    if (!strcmp(token, "seeds")) {
      seedFlag = 1;
      continue;
    }
    else {
    }

    for (j = 0, str2 = token; ; j++, str2 = NULL) {
      subtoken = strtok_r(str2, delim_subtoken, &saveptr2);
      if (subtoken == NULL) {
        if (seedFlag)
          seedFlag = 0;
        break;
      }

      if (seedFlag) {
        seeds[j] = atoi(subtoken);
        continue;
      }

      if (!strcmp(subtoken, "seed"))
        categories[j] = seed_cat;
      else if (!strcmp(subtoken, "fertilizer"))
        categories[j] = fertilizer_cat;
      else if (!strcmp(subtoken, "water"))
        categories[j] = water_cat;
      else if (!strcmp(subtoken, "light"))
        categories[j] = light_cat;
      else if (!strcmp(subtoken, "temperature"))
        categories[j] = temperature_cat;
      else if (!strcmp(subtoken, "humidity"))
        categories[j] = humidity_cat;
      else if (!strcmp(subtoken, "location"))
        categories[j] = location_cat;
    }
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
    day_five(*lineptr);
    /* END: specific to Day4 */
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
