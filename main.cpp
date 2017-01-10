#include <vector>
#include <iostream>
#include <windows.h>
#include <random>

using namespace std;

vector<int> primes = {};

bool isPrime(int i){
    for(auto x : primes){
        if(i % x == 0){
            return false;
        }
    }
    return true;
}

int main(){
    int i = 2;

    while(true){
        if(isPrime(i)){
            primes.push_back(i);
            cout << i << "\t";
        }
        i++;
         //Sleep(rand() % 1000);
    }
    system("pause");
    return 0;
}