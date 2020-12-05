#include <stdio.h>
#include <string.h>

int main(){
    FILE *testfile;
    testfile = fopen("testfile.txt", "r");
    int lines_count = 0;
    char chr;
    chr = fgetc(testfile);
    while (chr != EOF) {
        if (chr == '\n')
            lines_count++;
        chr = fgetc(testfile);
    }
    fseek(testfile, 0, SEEK_SET);

    int question_count = lines_count / 5;
    int correct_answers = 0;
    for (int i = 0; i < question_count; i++) {
        char buffer[256];
        fgets(buffer, 256, testfile);
        printf("%s", buffer);

        int correct_answer = 0;
        for (int j = 1; j <= 4; j++) {
            char buffer[256];
            fgets(buffer, 256, testfile);
            char *s;
            if (buffer[0] == '*') {
                s = buffer + 1;
                correct_answer = j;
            }
            else
                s = buffer;
            printf("%d. %s", j, s);
        }

        int answer;
        do {
            printf("Enter answer number (1-4): ");
            //fflush(stdin);
            scanf("%d", &answer);
        } while ((answer < 1) || (answer > 4));

        if (answer == correct_answer)
            correct_answers++;
    }

    printf("\nCorrect answers: %d / %d (%.2f %%)",
           correct_answers, question_count, (float) correct_answers / question_count * 100);

    fclose(testfile);
    return 0;
}
