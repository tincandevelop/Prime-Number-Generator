#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int length = 0;
int len = 0;

int* deleteFromArray(int i, int *array){
    for(int z=i; z<length; z++){
        array[z] = array[z+1];
    }
    return array;
}

void deleteMultiples(int i, int *primes){
    int num = primes[i];
    int currentnum;
    for(int y=i+1; y<len; y++){
        currentnum = primes[y];
        if(currentnum != -1 && currentnum%num == 0){
            // deleteFromArray(y, primes);
            primes[y] = -1;
            length += -1;
        }
    }
}

void printpercent(int percent){
    printf("\r[");
    for(int i=0; i<percent; i++){
        printf("#");
    }
    for(int i=0; i<50-percent; i++){
        printf(" ");
    }
    printf("] %d%% completed", percent*2);
    fflush(stdout); 
}

int main(){
    printf("Welcome to Prime Number Generator!\nV 0.0.1\n\nHow many primes woulld you like to generate: ");
    int input;
    scanf("%d", &input);
    printf("\n\nGenerating primes up to %d...\n", input);
    int i=0;
    length = input-1;
    len = length;
    int z = (int)round((float)input/50.0);
    if(z < 1){
        z = 1;
    }
    int* primes = malloc(sizeof(int)*input);
    printpercent(0);

    for(int y=1; y<input-1; y++){
        primes[y-1] = y+1;
    }

    while(i < input-1){ 

        printpercent( round(((float)i / (float)length)*50.0) );

        if(primes[i] != -1){
            deleteMultiples(i, primes);
        }
        i++;
    }


    int xyz = (int)length;
    // printf("\n\nLast prime is %d.\n", primes[length-1]);
    printf("Successfully generated %i primes.\n\nSave Primes? [y/n]: ", xyz);
    char in[256];
    scanf("%256s", in);

    if(strcmp(in, "Y") == 0 || strcmp(in, "y") == 0){
        printf("\n\nFile name: ");
        char in2[256];
        scanf("%256s", in2);

        FILE *f = fopen(in2, "w");
        if (f == NULL)
        {
            printf("\n\nError opening file!\n");
            exit(1);
        }
        int x =0;
        for(int i=0; i<input-1; i++){
            if(primes[i] != -1){
                if(x == 5){
                    fprintf(f, "\n");
                    x = 0;
                    if(i % 100 == 0){
                        fprintf(f, "\n\t[%d] Primes\n\n", i);
                    }
                }
                fprintf(f, "%d\t", primes[i]);
                x++;
            }
        }
        fclose(f);
        printf("\nSuccessfully saved prime numbers to %s!\nGoodbye!\n\n", in2);
    }
    // // system("pause");
    free(primes);
    return 0;
}