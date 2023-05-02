#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Player guessing Range
typedef struct {
  int start;
  int end;
} range;

// Outcome from Player's POV
typedef enum { 
  HI,
  LO,
  EQ
} outcome;

// Input validation flags
typedef enum {
  NOT_IN_RNG,
  NOT_A_NUM,
  VALID_NUM
} flag;

bool is_valid(flag f) {
  return f == VALID_NUM;
}

char* flag_to_str(flag f) {
  switch (f) {
    case NOT_A_NUM:  return "Your Number is NOT a Valid Number.";
    case NOT_IN_RNG: return "Your Number DOESN'T lie in the Specified Range.";
    case VALID_NUM:  return "Your Number is a Valid Number";
  }
}

char* outcome_to_str(outcome outcome) {
  switch (outcome) {
    case HI: return "Your Number is High. Retry!"; 
    case LO: return "Your Number is Low. Retry";
    case EQ: return "Congratulations! You guessed it Right.";
  }
}

int get_input() {
  char str[100]; char* rem;
  printf("Enter a Number: ");
  fgets(str, sizeof(str), stdin);
  int num = strtol(str, &rem, 10);
  if (strlen(rem) > 1) return 0; // rem will always contain the \n for pressed enter, hence > 1
  return num;
}

flag validate(int input, range* rng) {
  return input == 0            ? NOT_A_NUM :
         input < rng->start ||
         input > rng->end      ? NOT_IN_RNG
                               : VALID_NUM;
}

outcome compare(int input, int rand) {
  return input > rand ? HI :
         input < rand ? LO 
                      : EQ;
}

bool is_game_over(outcome outcome) {
  return outcome == EQ;
}

int get_random(range* rng) {
  srand((int)time(NULL));
  int rnd = rand();
  rnd %= rng->end;
  rnd += rng->start;
  return rnd;
}

void run_game(range* rng) {
  printf("Welcome to GUESS THE NUMBER Game\n"
         "Enter a value between %d to %d\n\n", 
         rng->start, rng->end);
  
  int rnd = get_random(rng);
  int tries = 0;
  outcome outcome;

  while (!is_game_over(outcome)) {
    int num = get_input();
    tries++;
    flag  flg = validate(num, rng);
    if (!is_valid(flg)) {
      printf("%s\n\n", flag_to_str(flg));
      continue;
    }
    outcome = compare(num, rnd);
    printf("%s\n\n", outcome_to_str(outcome));
  }

  printf("You took %d tries.\n", tries);
}

int main(int argc, char const* argv[]) {
  range rng = { .start = 1, .end = 30 };
  run_game(&rng);
  return 0;
}