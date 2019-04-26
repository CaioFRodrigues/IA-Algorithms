#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Inform the algorithm:\n");
        printf("-bfs -idfs -astar -idastar -gbfs\n");
        return 1;
    }

    char const* const fileName = "8puzzle_instances.txt"; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[38];

    char programName[BUFSIZ];
    strcpy(programName, "..\\main.exe ");
    strcat(programName, argv[1]);
    strcat(programName, " ");

    while (fgets(line, sizeof(line), file)) {
        char call[50];
        strcpy(call, programName);
        strcat(call, line);
        if (strlen(call) > 21) {
            puts(call);
            system(call);
        }
    }
    fclose(file);
    return 0;
}
