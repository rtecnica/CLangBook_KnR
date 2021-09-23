/* Page 31 
 * Exercise 1-19
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 256

char *rev_str(char *input) { 
    int length;
    for(length = 0; input[length] != '\0'; length++);
    char c;
    for(int i = 0; i < ((length+1)/2); i++) {
        c = input[length - 1 - i];
        input[length - 1 - i] = input[i];
        input[i] = c;

    }
    return input;
}

int main(int argc, char **argv) {
    FILE *input;
    if(argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        return 1;
    }
    char *giganto_buf = malloc(LINE_SIZE);
    giganto_buf = fgets(giganto_buf, LINE_SIZE, input);
    while(giganto_buf != NULL) {
        printf("%s", rev_str(giganto_buf));
        giganto_buf = fgets(giganto_buf, LINE_SIZE, input);
    }
    return 0;
}

