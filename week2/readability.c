#include <cs50.h>
#include <stdio.h>
#include <string.h>

void printArrayDebug(char *arr[], int len, string label) {
  printf("%s: ", label);
  for (int i = 0; i < len; i++) {
    printf("%s ", arr[i]);
  }
  printf("\n");
}

int main(void) {
  string paragraph = get_string("Text: ");

  int len = strlen(paragraph);
  printf("String length: %d\n", len);
  char *words[len];
  int sentences = 0;

  int i = 0;
  // Tokenize the first word with strtok
  char *word = strtok(paragraph, " ");
  // We need an actual number lower number to rely on or too many
  // iterations shit the bed
  while (word != NULL && i < len / 4) {
    if (strchr(word, '.') != NULL || strchr(word, '!') != NULL ||
        strchr(word, '?') != NULL) {
      sentences++;
    }
    words[i] = word;
    i++;
    // The following call to strtok starts with null and picks up where the last
    // call left off
    word = strtok(NULL, " ");
  }

  // The number of iterations is the number of words
  int total_words = i;
  printf("Total words: %d\n", total_words);
  printf("Total sentences: %d\n", sentences);
  // printArrayDebug(words, i, "Words");

  int total_letters = 0;
  for (int j = 0; j < total_words; j++) {
    if (strchr(words[j], '.') != NULL || strchr(words[j], '!') != NULL ||
        strchr(words[j], '?') != NULL) {
      total_letters -= 1;
    }
    total_letters += strlen(words[j]);
  }
  printf("Total letters: %d\n", total_letters);

  double avg_letters = ((double)total_letters / total_words) * 100;
  double avg_sentences = ((double)sentences / total_words) * 100;
  printf("Avg letter: %f\n", avg_letters);
  printf("Avg sentences: %f\n", avg_sentences);

  double index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;
  printf("Index: %f\n", index);

  return 0;
}
