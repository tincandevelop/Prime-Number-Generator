#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>



using namespace std;

vector<int> primes;

int isPrime(int i, int lengthofprimes){
    int currentprime;
    for(unsigned int y=0; y<lengthofprimes && primes[y] < ceil(sqrt(i)); y++){
        currentprime = primes[y];
        if(i%currentprime == 0){
            return 0;
        }
    }
    return 1;
}

void printpercent(int percent, int amount, int total){
    printf("\r[");
    for(int i=0; i<percent; i++){
        printf("#");
    }
    for(int i=0; i<50-percent; i++){
        printf(" ");
    }
    printf("] %d%% completed (%d/%d)", percent*2, amount, total);
    fflush(stdout); 
}

int main(){
    printf("Welcome to Prime Number Generator!\nV 0.0.1\n\nWould you like generate a finite or infinite amount of primes: ");
    char inputx[256];
    cin >> inputx;

    bool infinite = false;

    cout << "\n\"" << inputx << "\"\n";

    if( strcmp(inputx, "Infinite") == 0 || strcmp(inputx, "infinite") == 0){
        infinite = true;
    }

    primes.push_back(2);

    vector<long double> times;

    auto duration = std::chrono::system_clock::now().time_since_epoch();
    long double ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    long double last = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    if(infinite == false){
        int input;
        cout << "How many primes would you like to generate: ";
        cin >> input;
        printf("\n\nGenerating %d primes...\n", input);
        printpercent(0,0,input);
        int i=1;
        int x=3;
        duration = std::chrono::system_clock::now().time_since_epoch();
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        while(i < input){ 
            if(isPrime(x, i) == 1){
                primes.push_back(x);
                i++;
                if(i%10000 == 0){
                    printpercent( round(((float)i / (float)input)*50.0), i, input );
                }
            }
            x++;
            x++;
        }
    }else{
        printf("\n\nGenerating infinite primes...\n");
        int i=1;
        int x=3;
        duration = std::chrono::system_clock::now().time_since_epoch();
        long double last = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        long double ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        long double pps;
        bool quit = false;
        while(i < INFINITY && !quit){ 
            if(isPrime(x, i) == 1){
                primes.push_back(x);
                i++;
                if(i%100000 == 0){
                    duration = std::chrono::system_clock::now().time_since_epoch();
                    ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
                    pps = 100000.0/((ms3-last)/1000.0);
                    last = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
                    cout << "\r" << i << " primes generated. " << setprecision(17) << pps << "PPS";
                }
            }
            x++;
            x++;
            if(GetAsyncKeyState(VK_SPACE)){
                char isquit[256];
                cout << "\n\nDo you want to continue? [Y/N]: ";
                cin >> isquit;
                if(strcmp(isquit,"N") == 0 || strcmp(isquit,"n") == 0){
                    quit = true;
                    break;
                }else{
                    cout << "\n";
                }
            }
        }
    }

    cout << "\n\n\n";

    for(int i=0; i<times.size(); i++){
        cout << times[i] << ", ";
    }

    cout << "\n\n\n";

    duration = std::chrono::system_clock::now().time_since_epoch();
    long double ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    int xyz = primes.size();
    std::cout << "\n\nThat took " << std::setprecision (15) << (ms2-ms)/1000.0 << " seconds";
    printf("\nLast prime is %d.\n", primes[primes.size()-1]);
    printf("Successfully generated %i primes.\n\nSave Primes? [y/n]: ", xyz);
    char in[256];
    scanf("%256s", in);

    if(strcmp(in, "Y") == 0 || strcmp(in, "y") == 0){
        printf("\n\nFile name: ");
        char in2[256];
        cin >> in2;

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
    // system("pause");
    return 0;
}