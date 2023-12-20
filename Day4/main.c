#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

FILE *finput;

/* Day4 global vars */
int total_points = 0;
int total_matchcards = 0;
int *matchcards_stacks;
/* END: Day4 global vars */

/* Day4 functions */
int add_cards(int **cards, int number)
{
  return 0;
}

int day_four_question(char *line)
{
  const char *delim_token = ":|\n";
  const char *delim_subtoken = " ";

  char *str1, *str2, *token, *subtoken;
  char *saveptr1, *saveptr2;

  int *winning_cards = malloc(256 * sizeof(int));
  int n_winning_cards = 0;
  int *my_cards = malloc(256 * sizeof(int));
  int n_my_cards = 0;
  int **cards;
  int *ncards;
  int i, j;
  int card_id;

  if (!matchcards_stacks)
    matchcards_stacks = calloc(256, sizeof(int));

  for (i = 0, str1 = line; ; i++, str1 = NULL) {
    token = strtok_r(str1, delim_token, &saveptr1);
    if (token == NULL)
      break;
    if (i == 0) {
      subtoken = strtok_r(token, delim_subtoken, &saveptr2);
      subtoken = strtok_r(NULL, delim_subtoken, &saveptr2);
      card_id = atoi(subtoken);
    }
    /* printf("Token main: %s\n", token); */
    /* printf("Card ID: %d\n", card_id); */

    if (i == 1) {
      cards = &winning_cards;
      ncards = &n_winning_cards;
    } else {
      cards = &my_cards;
      ncards = &n_my_cards;
    }

    for (j = 0, str2 = token; ; j++, str2 = NULL) {
      subtoken = strtok_r(str2, delim_subtoken, &saveptr2);
      if (subtoken == NULL)
        break;

      (*cards)[j] = atoi(subtoken);
      *ncards = j;
    }

    /* printf("n_winning_cards: %d\n", n_winning_cards); */
    /* printf("n_my_cards: %d\n", n_my_cards); */
  }

  int points = 0;
  int copies = 0;
  for (i = 0; i <= n_my_cards; i++) {
    for (j = 0; j <= n_winning_cards; j++) {
      if (winning_cards[j] == my_cards[i]) {
        copies++;
        if (!points)
          points = 1;
        else
          points *= 2;
      }
    }
  }

  printf("Copies: %d\n", copies);
  matchcards_stacks[card_id - 1] += 1;
  for (i = card_id; copies > 0; copies--)
    matchcards_stacks[i++] += matchcards_stacks[card_id - 1];

  total_points += points;

  free(winning_cards);
  free(my_cards);
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
    day_four_question(*lineptr);
    /* END: specific to Day4 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  read_input(argv[0], "input.txt");

  fclose(finput);

  printf("Matches: ");
  for (int i = 0; i < 256; i++) {
    printf("%d ", matchcards_stacks[i]);
    total_matchcards += matchcards_stacks[i];
  }
  printf("\n");

  printf("Total points: %d\n", total_points);
  printf("Total match cards: %d\n", total_matchcards);

  return 0;
}
