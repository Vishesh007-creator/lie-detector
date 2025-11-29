#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_ANS 1000
#define NUM_QUESTIONS 3

int count_words(char *str) {
    int count = 0, in_word = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i]) && !in_word) {
            in_word = 1;
            count++;
        } else if (isspace((unsigned char)str[i])) {
            in_word = 0;
        }
    }
    return count;
}

void to_lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int count_hesitation(char *answer) {
    char temp[MAX_ANS];
    strcpy(temp, answer);
    to_lowercase(temp);

    int count = 0;
    if (strstr(temp, "maybe")) count++;
    if (strstr(temp, "i think")) count++;
    if (strstr(temp, "not sure")) count++;
    if (strstr(temp, "i don't know")) count++;
    if (strstr(temp, "idk")) count++;
    if (strstr(temp, "shayad")) count++;
    if (strstr(temp, "kya pata")) count++;

    return count;
}

int main() {
    char *questions[NUM_QUESTIONS] = {
        "Have you ever lied to your best friend?",
        "Are you hiding something important right now?",
        "Would you tell the whole truth if nobody could catch you?"
    };

    char answer[MAX_ANS];
    double total_score = 0.0;

    printf("=============================================\n");
    printf("           LIE DETECTOR (FUN APP)           \n");
    printf("=============================================\n");
    printf("Note: This is NOT a real polygraph.\n\n");

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nQ%d: %s\n", i + 1, questions[i]);
        printf("Your answer: ");
        fflush(stdout);

        clock_t start = clock();
        if (fgets(answer, sizeof(answer), stdin) == NULL) {
            printf("Input error.\n");
            return 1;
        }
        clock_t end = clock();

        size_t len = strlen(answer);
        if (len > 0 && answer[len - 1] == '\n') {
            answer[len - 1] = '\0';
        }

        double time_taken_sec = (double)(end - start) / CLOCKS_PER_SEC;
        int word_count = count_words(answer);
        int hesitation_count = count_hesitation(answer);

        if (time_taken_sec < 0.1) time_taken_sec = 0.1;

        double wpm = (word_count / time_taken_sec) * 60.0;
        double q_score = 0.0;

        if (time_taken_sec > 12)      q_score += 25;
        else if (time_taken_sec > 8)  q_score += 15;
        else if (time_taken_sec > 5)  q_score += 8;

        if (word_count <= 3)          q_score += 15;
        else if (word_count > 25)     q_score += 10;

        q_score += hesitation_count * 15;
        total_score += q_score;

        printf("\n--- Analysis for Question %d ---\n", i + 1);
        printf("Time taken      : %.2f sec\n", time_taken_sec);
        printf("Words typed     : %d\n", word_count);
        printf("Typing speed    : %.2f WPM\n", wpm);
        printf("Hesitations     : %d\n", hesitation_count);
        printf("Question score  : %.2f\n", q_score);
        printf("---------------------------------\n");
    }

    double avg_score = total_score / NUM_QUESTIONS;

    printf("\n=============================================\n");
    printf("               FINAL VERDICT\n");
    printf("Average Stress Score: %.2f\n", avg_score);

    if (avg_score < 15) {
        printf("RESULT: Likely TRUTHFUL ✅\n");
    } else if (avg_score < 35) {
        printf("RESULT: UNCERTAIN 😶\n");
    } else {
        printf("RESULT: POSSIBLY LYING ❌\n");
    }

    printf("=============================================\n");
    printf("Disclaimer: Just for fun, not real lie detection.\n");
    printf("=============================================\n");

    return 0;
}
