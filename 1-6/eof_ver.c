#include <stdio.h>

int main(int argc, char **argv) {
    FILE *input;
    if(argc > 1){
        input = fopen(argv[1], "r");
    }
    else {
        printf("No arguments given!\n");
        return 1;
    }
    char c = getc(input);
    while(c != EOF) {
        printf("%02x ", c);
        if(c == '\n') {
            printf("\n");
        }
        c = getc(input);
    }
    printf("EOF = %02x\n", c);
    return 0;
}
