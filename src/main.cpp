#include <iostream>

int main(){

    int i = 0;

    while (true) {

        if (i % 10000 == 0){
            std::cout << i << std::endl;
        }
        i++;
    }

    return 0;
}