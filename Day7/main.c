#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

FILE *finput;

/* Day4 global vars */
struct Hand {
  char *card;
  int value;
};

enum { 
  HighCard, 
  OnePair, 
  TwoPair, 
  ThreeOfAKind, 
  FullHouse, 
  FourOfAKind, 
  FiveOfAKind };

enum {
  Ten = 10,
  Jack,
  Queen,
  King,
  As,
};

struct Hand *hand_collection;
int *hand_values;
int n_hand;
int n_values;
int j_as_joker = 0;
/* END: Day4 global vars */

/* Day4 functions */
static int
card_power(const char c)
{
  switch (c) {
    case 'A':
      return As;
    case 'J':
      if (j_as_joker)
        return 1;
      else
        return Jack;
    case 'Q':
      return Queen;
    case 'K':
      return King;
    case 'T':
      return Ten;
    default:
      return c-48;
  }

  return -1;
}

static int
get_hand_power(const char *hand)
{
  char type1 = '\0';
  char type2 = '\0';
  char type3 = '\0';
  char type4 = '\0';
  int n_type1 = 0;
  int n_type2 = 0;
  int n_type3 = 0;
  int n_type4 = 0;
  int j_cards = 0;

  for (int i = 0; i < 5; i++) {
    if (hand[i] == 'J')
      j_cards++;
    else if (hand[i] == type1)
      n_type1++;
    else if (hand[i] == type2)
      n_type2++;
    else if (hand[i] == type3)
      n_type3++;
    else if (hand[i] == type4)
      n_type4++;
    else if (!type1) {
      type1 = hand[i];
      n_type1++;
    } else if (!type2) {
      type2 = hand[i];
      n_type2++;
    } else if (!type3) {
      type3 = hand[i];
      n_type3++;
    } else if (!type4) {
      type4 = hand[i];
      n_type4++;
    }
  }

  if (j_as_joker) {
    int *max_type;
    max_type = &n_type1;
    if (n_type2 > *max_type)
      max_type = &n_type2;
    if (n_type3 > *max_type)
      max_type = &n_type3;
    if (n_type4 > *max_type)
      max_type = &n_type4;

    *max_type = j_cards + *max_type;
  }

  if (n_type1 == 5)
    return FiveOfAKind;
  else if (n_type1 == 4 || n_type2 == 4)
    return FourOfAKind;
  else if (n_type1 == 3 || n_type2 == 3 || n_type3 == 3)
    if ((n_type1 * n_type2 * n_type3))
      return ThreeOfAKind;
    else
      return FullHouse;
  else if (n_type1 == 2 || n_type2 == 2 || n_type3 == 2)
    if (!n_type4)
      return TwoPair;
    else
      return OnePair;
  else if (n_type1 == 1 || n_type2 == 1 || n_type3 == 1)
    if (n_type4 == 2)
      return OnePair;
    else
      return HighCard;
}

static int
cmp_each_card(const char *s1, const char *s2)
{
  for (int i = 0; i < 5; i++) {
    if (card_power(s1[i]) != card_power(s2[i]))
      return card_power(s1[i]) - card_power(s2[i]);
  }

  return 0;
}

static int
cmp_hand(const void *h1, const void *h2)
{
  char *s1 = (*(struct Hand *)h1).card;
  char *s2 = (*(struct Hand *)h2).card;
  if (get_hand_power(s1) == get_hand_power(s2))
    return cmp_each_card(s1, s2);
  else
    return get_hand_power(s1) - get_hand_power(s2);
}

int read_line(char *line)
{

  int j;
  char *str, *token;
  const char *delim_token = " \n";
  for (j = 0, str = line; ; j++, str = NULL) {
    token = strtok(str, delim_token);
    if (token == NULL)
      break;

    if (!j) {
      hand_collection[n_hand++].card = strdup(token);
    }
    else
      hand_collection[n_values++].value = atoi(token);
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
    /* day_seven(*lineptr); */
    read_line(*lineptr);
    /* END: specific to Day4 */
  }

  free(*lineptr);
  free(lineptr);
}

int main(int argc, char** argv)
{
  hand_collection = malloc(1024 * sizeof(struct Hand));
  hand_values = calloc(1024, sizeof(int));

  read_input(argv[0], "input.txt");

  fclose(finput);

  qsort(hand_collection, n_hand, sizeof(struct Hand), cmp_hand);

  uint64_t total_values = 0;
  for (int i = 0; i < n_values; i++) {
    /* printf("Card: %s. Value: %d. Rank: %d\n", */ 
        /* hand_collection[i].card, hand_collection[i].value, i + 1); */
    total_values += hand_collection[i].value * (i + 1);
  }

  printf("Total Values: %lu\n", total_values);

  j_as_joker = 1;
  qsort(hand_collection, n_hand, sizeof(struct Hand), cmp_hand);

  total_values = 0;
  for (int i = 0; i < n_values; i++) {
    /* printf("Card: %s. Value: %d. Rank: %d\n", */ 
        /* hand_collection[i].card, hand_collection[i].value, i + 1); */
    total_values += hand_collection[i].value * (i + 1);
  }

  printf("Total Values Joker: %lu\n", total_values);
  return 0;
}
