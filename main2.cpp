#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <windows.h>

using namespace std;

vector<int> deleteMultiples(int i, vector<int> primes){
    int num = primes[i];
    int currentnum;
    for(int y = i+1; y<primes.size(); y++){
        currentnum = primes[y];
        if(currentnum%num == 0){
            primes.erase(primes.begin()+y, primes.begin()+y+1);
        }
    }
    return primes;
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
    int z = (int)round((float)input/50.0);
    if(z < 1){
        z = 1;
    }
    vector<int> primes;
    printpercent(0);

    primes.push_back(2);

    for(int y=1; y<input-1; y++){
        y++;
        primes.push_back(y+1);
    }

    auto duration = std::chrono::system_clock::now().time_since_epoch();
    long double ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    while(i < primes.size()){ 

        // printpercent( round(((float)i / (float)primes.size())*50.0) );
        primes = deleteMultiples(i, primes);
        i++;
    }

    duration = std::chrono::system_clock::now().time_since_epoch();
    long double ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();


    int xyz = (int)primes.size();
    // printf("\n\nLast prime is %d.\n", primes[length-1]);
    cout << "\nThat took " << ms2-ms << " milliseconds\nSuccessfully generated " << xyz << " primes.\n\nSave Primes? [y/n]: ";
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
        for(int i=0; i<primes.size(); i++){
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
        fclose(f);
        printf("\nSuccessfully saved prime numbers to %s!\nGoodbye!\n\n", in2);
    }
    return 0;
}