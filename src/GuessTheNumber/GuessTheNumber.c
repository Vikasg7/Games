#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define USAGE "USAGE:\n"\
              "  GuessTheNumber [-s,--start <StartNumber> -e,--end <EndNumber>] <StartNumber> <EndNumber>\n"\
              "OPTIONS:\n"\
              "  -s, --start\t" "Start of the Range as Number\n"\
              "  -e, --end\t"   "End of the Range as Number\n"\
              "  -h, --help\t"  "Prints help\n"\
              "EXAMPLE:\n"\
              "  GuessTheNumber 1 30\n"\
              "  GuessTheNumber -s 1 -e 30\n"\
              "  GuessTheNumber --start 1 --end 30\n"

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
    flag flg = validate(num, rng);
    if (!is_valid(flg)) {
      printf("%s\n\n", flag_to_str(flg));
      continue;
    }
    outcome = compare(num, rnd);
    printf("%s\n\n", outcome_to_str(outcome));
  }

  printf("You took %d tries.\n", tries);
}

void print_help() {
  printf("\n");
  printf("A Simple Guess The Number Game written in C\n");
  printf(USAGE);
}

range parse_range_from_args(int argc, char** argv) {
  range rng = {-1, -1};
  if (argc == 3 && argv[1][0] != '-') {
    rng.start = atoi(argv[1]);
    rng.end = atoi(argv[2]);
    return rng;
  }
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--start") == 0)
      rng.start = atoi(argv[i+1]); else 
    if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--end") == 0)
      rng.end = atoi(argv[i+1]); else 
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      print_help();
      exit(0);
    }
  }
  return rng;
}

#define MAX_ERR_COUNT 3

char** validate_range(range *rng) {
  char** err_msgs = calloc(MAX_ERR_COUNT, sizeof(char *));
  int err_count = 0;

  if (rng->start == -1) 
    err_msgs[err_count++] = "Error: Start number is not provided."; else
  if (rng->start == 0) 
    err_msgs[err_count++] = "Error: Start number must be a valid non-zero number.";
  if (rng->end == -1) 
    err_msgs[err_count++] = "Error: End number is not provided."; else
  if (rng->end == 0) 
    err_msgs[err_count++] = "Error: End number must be a valid non-zero number.";
  if (rng->start != -1 && rng->end !=-1 && rng->end < rng->start) 
    err_msgs[err_count++] = "Error: End number must be greater than start number.";

  if (err_count == 0) {
    free(err_msgs);
    return NULL;
  }

  return err_msgs;
}

void print_err_msgs(char** err_msgs) {
  for (int i = 0; i < MAX_ERR_COUNT; i++) {
    if (err_msgs[i] == NULL) break;
    fprintf(stderr, "%s\n", err_msgs[i]);
  }
  printf("Try `GuessTheNumber --help`\n");
}

int main(int argc, char** argv) {
  range rng = parse_range_from_args(argc, argv);
  char** err_msgs = validate_range(&rng);
  if (err_msgs) {
    print_err_msgs(err_msgs);
    return 1;
  }
  run_game(&rng);
  return 0;
}