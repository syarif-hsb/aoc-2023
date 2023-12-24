#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

FILE *finput;

/* Day4 global vars */
int time[16] = { 0 };
int dist[16] = { 0 };
uint64_t time_concatenated = 0;
uint64_t dist_concatenated = 0;
char *str_time_concatenated;
char *str_dist_concatenated;
int n_of_time = 0;
int spd_per_chg = 1;
/* END: Day4 global vars */

/* Day4 functions */
int day_six(char *line)
{
  /* printf("%s", line); */
  int *arr = NULL;
  int n = 0;
  char *str_concat = NULL;
  const char *delim_token = ": \n";

  char *str, *token;
  int i, j;
  for (i = 0, str = line; ; i++, str = NULL) {
    token = strtok(str, delim_token);
    if (token == NULL) {
      arr = NULL;
      str_concat = NULL;
      n_of_time = n;
      n = 0;
      break;
    }

    /* printf("%s\n", token); */
    if (!strcmp(token, "Time")) {
      arr = time;
      str_concat = str_time_concatenated;
    } else if (!strcmp(token, "Distance")) {
      arr = dist;
      str_concat = str_dist_concatenated;
    } else {
      arr[n++] = atoi(token);
      strcat(str_concat, token);
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
    day_six(*lineptr);
    /* END: specific to Day4 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  str_time_concatenated = calloc(32, sizeof(char));
  str_dist_concatenated = calloc(32, sizeof(char));
  read_input(argv[0], "input.txt");

  fclose(finput);

  uint64_t dist_achv = 0;
  int pow_poss = 0;
  uint64_t possibilities = 0;
  for (int i = 0; i < n_of_time; i++) {
    printf("Distance: %d\n", dist[i]);
    for (int j = 0; j <= time[i]; j++) {
      dist_achv = (time[i] - j) * (spd_per_chg * j);
      printf("Distance achieved: %d\n", dist_achv);
      if (dist_achv > dist[i])
        possibilities++;
    }
    printf("Possibility: %d\n", possibilities);

    if (!pow_poss)
      pow_poss = possibilities;
    else
      pow_poss *= possibilities;

    possibilities = 0;
  }

  printf("Power of possibilities: %d\n", pow_poss);

  time_concatenated = atoll(str_time_concatenated);
  dist_concatenated = atoll(str_dist_concatenated);
  printf("Str time: %s\n", str_time_concatenated);
  printf("Num time: %lu\n", time_concatenated);
  printf("Str dist: %s\n", str_dist_concatenated);
  printf("Num dist: %lu\n", dist_concatenated);

  uint64_t not_possible = 0;
  for (uint64_t i = 0; i <= time_concatenated; i++) {
    dist_achv = (time_concatenated - i) * (spd_per_chg * i);
    if (dist_achv > dist_concatenated)
    {
      /* printf("Time: %d. Distance achieved: %lu\n", i, dist_achv); */
      possibilities++;
    }
    if (dist_achv > 0xffffffffffffff) {
      /* printf("Time: %d. Distance achieved: %lu. Possibilities: %d\n", i, dist_achv, possibilities); */
      possibilities += (time_concatenated - 2 * i);
      i = time_concatenated - i;
    }
    /* if (i < 50) */
    /* printf("Time: %d. Distance achieved: %lu. Possibilities: %lu\n", i, dist_achv, possibilities); */
  }

  for (uint64_t i = 0; i <= time_concatenated; i++) {
    dist_achv = (time_concatenated - i) * (spd_per_chg * i);
    if (dist_achv > dist_concatenated)
    {
      printf("Time: %d. Distance achieved: %lu\n", i, dist_achv);
      break;
    }
    else
      not_possible++;
  }


  printf("Possibility concatenated: %llu\n", possibilities);
  printf("Possibility concatenated method2: %llu\n", 
      (time_concatenated + 1) - not_possible * 2);

  return 0;
}
