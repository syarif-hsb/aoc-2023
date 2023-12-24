#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

FILE *finput;

/* Day4 global vars */
uint *map = NULL;
uint seeds[256] = { 0 };
uint seed_soil_map[256] = { 0 };
uint soil_fertilizer_map[256] = { 0 };
uint fertilizer_water_map[256] = { 0 };
uint water_light_map[256] = { 0 };
uint light_temperature_map[256] = { 0 };
uint temperature_humidity_map[256] = { 0 };
uint humidity_location_map[256] = { 0 };

int seedFlag = 0;
/* END: Day4 global vars */

/* Day4 functions */
int trace_map(int seed, uint *map)
{
    for (int j = 0; j < 250; j++) {
      if (!map[j * 3 + 1] && !map[j * 3 + 2]) {
        return seed;
      }
      if (seed >= map[j * 3 + 1] && 
          seed <= map[j * 3 + 1] + map[j * 3 + 2] - 1) {
        return map[j * 3] + (seed - map[j * 3 + 1]);
      }
    }
}

int n_parse = 0;
int parse_numbers(char *s, uint *map)
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

    map[n_parse] = atoi(token);
    printf("%#2u ", map[n_parse]);
    n_parse++;
  }
  printf("\n");

  return 0;
}

int day_five(char *line)
{
  if (!strcmp(line, "\n")) {
    map = NULL;
    n_parse = 0;
    return 0;
  }
  
  if (map)
    parse_numbers(line, map);

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

      /* printf("Debug\n"); */
      if (!strcmp(subtoken, "seed"))
        map = seed_soil_map;
      else if (!strcmp(subtoken, "soil"))
        map = soil_fertilizer_map;
      else if (!strcmp(subtoken, "fertilizer"))
        map = fertilizer_water_map;
      else if (!strcmp(subtoken, "water"))
        map = water_light_map;
      else if (!strcmp(subtoken, "light"))
        map = light_temperature_map;
      else if (!strcmp(subtoken, "temperature"))
        map = temperature_humidity_map;
      else if (!strcmp(subtoken, "humidity"))
        map = humidity_location_map;

      if (map)
        return 0;
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

  uint lowest_location = 0;
  for (int i = 0; seeds[i] != 0; i++) {
    uint temp;
    uint temp2;

    printf("Seed: %lu\n", seeds[i]);
    printf("Soil: %lu, ", temp2 = trace_map(seeds[i], seed_soil_map));
    printf("fertilizer: %lu, ", temp2 = trace_map(temp2, soil_fertilizer_map));
    printf("water: %lu, ", temp2 = trace_map(temp2, fertilizer_water_map));
    printf("light: %lu, ", temp2 = trace_map(temp2, water_light_map));
    printf("temperature: %lu, ", temp2 = trace_map(temp2, light_temperature_map));
    printf("humidity: %lu, ", temp2 = trace_map(temp2, temperature_humidity_map));
    printf("location: %lu\n", temp2 = trace_map(temp2, humidity_location_map));

    if (lowest_location == 0 || lowest_location > temp2)
      lowest_location = temp2;
  }
  printf("Lowest 1: %lu\n", lowest_location);
  lowest_location = 0;

  for (uint i = 0; seeds[i] != 0; i += 2) {
    printf("Head seed: %lu\n", seeds[i]);
    for (uint j = 0; j < seeds[i + 1]; j++) {
      uint temp;
      uint temp2;

      /* printf("Seed: %lu\n", seeds[i] + j); */
      /* printf("Soil: %lu, ", temp2 = trace_map(seeds[i] + j, seed_soil_map)); */
      /* printf("fertilizer: %lu, ", temp2 = trace_map(temp2, soil_fertilizer_map)); */
      /* printf("water: %lu, ", temp2 = trace_map(temp2, fertilizer_water_map)); */
      /* printf("light: %lu, ", temp2 = trace_map(temp2, water_light_map)); */
      /* printf("temperature: %lu, ", temp2 = trace_map(temp2, light_temperature_map)); */
      /* printf("humidity: %lu, ", temp2 = trace_map(temp2, temperature_humidity_map)); */
      /* printf("location: %lu\n", temp2 = trace_map(temp2, humidity_location_map)); */

      /* printf("Seed: %lu. ", seeds[i] + j); */
      temp2 = trace_map(seeds[i] + j, seed_soil_map);
      temp2 = trace_map(temp2, soil_fertilizer_map);
      temp2 = trace_map(temp2, fertilizer_water_map);
      temp2 = trace_map(temp2, water_light_map);
      temp2 = trace_map(temp2, light_temperature_map);
      temp2 = trace_map(temp2, temperature_humidity_map);
      temp2 = trace_map(temp2, humidity_location_map);

      if (lowest_location == 0 || lowest_location > temp2)
        lowest_location = temp2;
      /* printf("Current lowest: %lu\n", lowest_location); */
    }
  }

  printf("Lowest 2: %lu\n", lowest_location);

  return 0;
}
