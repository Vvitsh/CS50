#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int sumWordValue(char word[]) {
  char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                  1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int sum = 0;
  int word_len = strlen(word);
  int letters_len = sizeof(letters) / sizeof(letters[0]);
  for (int i = 0; i < word_len; i++) {
    char letter = tolower(word[i]);
    for (int j = 0; j < letters_len; j++) {
      if (letter == letters[j]) {
        sum += values[j];
      }
    }
  }
  return sum;
}
int sumWordValue2(char word[]) {
  int values[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                  1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  int sum = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    char letter = tolower(word[i]);
    // Using the ascii values so whatever letter we use minus 'a' will give us
    // the value index eg. 'c' - 'a' = 2 (99 - 97 = 2)
    if (letter >= 'a' && letter <= 'z') {
      sum += values[letter - 'a'];
    }
  }
  return sum;
}

int main(void) {
  string word1 = get_string("Player 1: ");
  string word2 = get_string("Player 2: ");

  int score1 = sumWordValue(word1);
  int score2 = sumWordValue(word2);
  // printf("Score 1: %d\n", score1);
  // printf("Score 2: %d\n", score2);

  if (score1 > score2) {
    printf("Player 1 wins!\n");
  } else if (score2 > score1) {
    printf("Player 2 wins!\n");
  } else {
    printf("Tie!");
  }

  return 0;
}
