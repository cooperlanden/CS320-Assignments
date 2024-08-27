#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Struct to keep info
typedef struct {
    char letter;
    int count;
} LetterCount;

// Initialize the array of LetterCount structs
void initializeCounts(LetterCount counts[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        counts[i].letter = 'a' + i;
        counts[i].count = 0;
    }
}

// Update the counts
void updateCounts(LetterCount counts[], char c) {
    if (isalpha(c)) {
        c = tolower(c);
        counts[c - 'a'].count++;
    }
}

int main() {
    FILE *file;
    char filename[100];
    char c;
    LetterCount counts[ALPHABET_SIZE];

    // Initialize the counts array
    initializeCounts(counts);

    // Prompt user for the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // Read file and update counts
    while ((c = fgetc(file)) != EOF) {
        updateCounts(counts, c);
    }

    // Close file
    fclose(file);

    // Print result
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", counts[i].letter, counts[i].count);
    }

    return 0;
}
