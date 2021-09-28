/* Page 24
 * Exercise 1-13
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define IN_WORD 1
#define OUT_WORD 0

#define UC_LO 65
#define UC_HI 90
#define LC_LO 97
#define LC_HI 122
#define ALPH_L 25
#define NUM_LO 48
#define NUM_HI 57

#define BUCKET_LEN 20
int buckets[BUCKET_LEN];

#define BAR_CHAR '#'//(char)176
#define MAX_HEIGHT 30

int find_max(int arr[], int len) {
    int result = (1 << (sizeof(int)*8 - 1));
    for(int i = 0; i < len; i++) {
        if(result < arr[i]){
            result = arr[i];
        }
    }
    return result;
}


int main(int argc, char **argv) {
    for(int i = 0; i < BUCKET_LEN; i++) {
        buckets[i] = 0;
    }
    
    FILE *input;
    if(argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        return 1;
    }
    uint8_t word_state = OUT_WORD;
    int word_len = 0;
    char cursor;
    while(cursor != EOF) {
        cursor = getc(input);
        if((cursor >= UC_LO) && (cursor <= UC_HI)){
            if(!word_state) {
                word_state = IN_WORD;
            }
            word_len++;
        } 
        else if((cursor >= LC_LO) && (cursor <= LC_HI)) {
            if(!word_state) {
                word_state = IN_WORD;
            }
            word_len++;
        } 
        else if((cursor >= NUM_LO) && (cursor <= NUM_HI)) {
            //add word to bucket
            if(word_state){
                word_state = OUT_WORD;
                buckets[word_len - 1]++;
                word_len = 0;
            }
        }
        else {
            //add word to bucket
            if(word_state){
                word_state = OUT_WORD;
                buckets[word_len - 1]++;
                word_len = 0;
            } 
        } 
    }

    int total = 0;
    for(int i = 0; i < BUCKET_LEN; i++) {
        total += buckets[i];
    }

    int max = find_max(buckets, BUCKET_LEN);
    int fraction[BUCKET_LEN];
    for(int i = 0; i < BUCKET_LEN; i++) {
        if(buckets[i] > 0) {
            fraction[i] = ((float)buckets[i] * MAX_HEIGHT)/ max;
        } else { 
            fraction[i] = 0;
        }
    }
    printf("\n");

    for(int i = MAX_HEIGHT; i > 0; i--) {
        for(int j = 0; j < BUCKET_LEN; j++) {
            char fill = ' ';
            if(fraction[j] >= i) {
                fill = BAR_CHAR;
            } 
            for(int k = 0; k < 3; k++) {
                printf("%c", fill);
            }
            printf("\t");
        }
        printf("\n");
    }
    printf("\n");
    
    for(int i = 0; i < BUCKET_LEN; i++) {
        if(buckets[i] > 0) {
            printf("%d\t", buckets[i]);
        }
    }
    printf("\n");
    
    float percent;
    for(int i = 0; i < BUCKET_LEN; i++) {
        if(buckets[i] > 0) {
            percent = (float)buckets[i] / total; 
            printf("%.2f%c\t", percent*100, '%');
        }
    }
    printf("\n");

    for(int i = 0; i < BUCKET_LEN; i++) {
        if(buckets[i] > 0) {
            printf("%d\t", i+1);
        }
    }

    fclose(input);
    return 0;
}
