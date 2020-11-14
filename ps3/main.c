#include "hangman.h"
#include <stdlib.h>
#include <time.h>



int main(){
    srand(time(NULL));
    char secret[30];
    get_word(secret);
    hangman(secret);
    
    return 0;
}