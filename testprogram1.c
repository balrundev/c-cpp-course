#include <stdio.h>
#include <stdlib.h>

char *readline(FILE *testfile){
    char *buffer;
    int buffer_size = 0;
    buffer = malloc(buffer_size + 1);
    char chr;
    while ((chr = fgetc(testfile)) != '\n') {
        buffer_size++;
        buffer = realloc(buffer, buffer_size + 1);
        buffer[buffer_size - 1] = chr;
        buffer[buffer_size] = '\0';
    }
    return buffer;
}

int main(){
    FILE *testfile;
    testfile = fopen("testfile.txt", "r");
    int lines_count = 0;
    char chr;
    while ((chr = fgetc(testfile)) != EOF) {
        if (chr == '\n')
            lines_count++;
    }
    fseek(testfile, 0, SEEK_SET);

    int question_count = lines_count / 5;
    int correct_answers = 0;

    for (int i = 0; i < question_count; i++) {
        char *buffer = readline(testfile);
        printf("%s\n", buffer);
        int correct_answer = 0;
        for (int j = 1; j <= 4; j++) {
            char *answer_text = readline(testfile);
            if (answer_text[0] == '*') {
                correct_answer = j;
                answer_text = answer_text + 1;
            }
            printf("%d. %s\n", j, answer_text);
        }

        int answer;
        do {
            printf("Enter answer number (1-4): ");
            scanf("%d", &answer);
            fflush(stdin);
        } while (answer < 1 || answer > 4);

        if (answer == correct_answer)
            correct_answers++;
    }

    printf("\nCorrect answers: %d / %d (%.2f %%)",
           correct_answers, question_count, (float) correct_answers / question_count * 100);

    fclose(testfile);
    return 0;
}
