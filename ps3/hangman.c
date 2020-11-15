#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    
    int i;
    int j;
    int guess = 0;
    
    //printf("%d\n", is_word_guessed("hello", "aeiou"));
    //printf("%lu len lett\n", strlen(letters_guessed));
    
    char letters2[strlen(letters_guessed)];
    int n_lett = 0;
    
    while (n_lett < strlen(letters_guessed)) {
        letters2[n_lett] = letters_guessed[n_lett];
        n_lett ++;
        //printf("%d\n", is_word_guessed("hhhhh", "eiouh"));
    }
    
    n_lett = 0;
    //int nj = 0;
    int c_guess = guess;

    
    for (i = 0; i < strlen(secret); i += 1) {
        c_guess = guess;
        for (j = 0; j < strlen(letters_guessed); j += 1) {
            if (secret[i] == letters2[j] && c_guess == guess){
                guess += 1;
                //printf("str   %c %d %d\n", letters2[j], i, j);
                //unsigned long size_l = strlen(letters2);
                //nj = j;
            
                //for (int ii = nj; ii < size_l - 1; ii++) {
                //    letters2[ii] = letters2[ii + 1];
                //}
                //letters2[strlen(letters2)-1] = 'A';
            }

        }
    }
    //printf("guess   %d\n", guess);
    if (guess == strlen(secret)) {
        return 1;
    }
    return 0;
}

// char guess my func
bool is_char_guessed(const char secret[], char letter[]){
    
    int i;
    int guess = 0;
        
    int c_guess = guess;

    for (i = 0; i < strlen(secret); i += 1) {
        c_guess = guess;
        for (int j = 0; j < strlen(letter); j++) {
            if (secret[i] == letter[j] && c_guess == guess){
                guess = 1;
                return true;
            }
        }
    }
    return false;
}


//get_guessed_word("container", "arpstxgoieyu", result);
// result = "_o_tai_er"

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    int guess = 0;
    int c_guess = guess;
    int i = 0;
    int j = 0;
    if (strlen(letters_guessed) == 0) {
        for (short m = 0; m<strlen(secret); m++) {
            guessed_word[m] = '_';
        }
    }
    
    for (i = 0; i < strlen(secret); i += 1) {
        c_guess = guess;
        for (j = 0; j < strlen(letters_guessed); j += 1) {
            if (secret[i] == letters_guessed[j] && c_guess == guess){
                guess += 1;
                guessed_word[i] = letters_guessed[j];
                //printf("%c %d\n", letters_guessed[j], j);
            }
            else if (secret[i] != letters_guessed[j] && c_guess == guess){
                guessed_word[i] = '_';
            }
        }
    }
    guessed_word[strlen(secret)] = '\0';
    //printf("[%lu]\n", strlen(letters_guessed));
}

//a b c d e f g h i j k l m n o p q r s t u v w x y z

//char result[30];
//get_available_letters("arpstxgoieyu", result);
// result = "bcdfhjklmnqvwz"

void get_available_letters(const char letters_guessed[], char available_letters[]){
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int guess = 0;
    int c_guess = guess;

    int nj = 0;
    
    for (int i = 0; i < strlen(letters_guessed); i += 1) {
        c_guess = guess;
        for (int j = 0; j < strlen(alphabet); j += 1) {
            if (letters_guessed[i] == alphabet[j] && c_guess == guess){
                guess += 1;
                //printf("str   %c %d %d\n", letters2[j], i, j);
                unsigned long size_l = strlen(alphabet);
                nj = j;
            
                for (nj = j; nj < size_l - 1; nj++) {
                    alphabet[nj] = alphabet[nj + 1];
                }
            }

        }
    }
    alphabet[strlen(alphabet)] = '\0';
    
    unsigned long n = strlen(letters_guessed);
    if(n == 26){
        alphabet[0] = '\0';
    }
    
    //printf("%lu  is - n\n", n); 
    //unsigned long n = n - strlen(letters_guessed);
    for (int i = 0; i < 26 - n; i += 1) {
        available_letters[i] = alphabet[i];
        available_letters[i+1] = '\0';
        //printf("%s  [%d]\n", available_letters, i);
    }
    //available_letters[strlen(available_letters)] = '\0';
    //printf("len  %lu\n", strlen(available_letters));

    //printf("avar lett  %s  %lu\n", available_letters, strlen(available_letters));
}

void hangman(const char secret[]){
    //secret = "addressees";
    printf("[%s]\n", secret);
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %lu letters long.\n", strlen(secret));
    //test arena
  

    bool stop_while = true;
    int guesses = 8;
    
    char letters_guessed[30] = {""};
    char letone[30];
    char result2[30];  //strlen(secret) + 1
    int n = 0;
    
    int ii = 0;
    
    int m = 0;
    short tupo = 0;
    
    while ( (stop_while) || (guesses > 0) ) {
        if(guesses == 0){
            stop_while = false;
            printf("-------------\n");
            printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
            break;
        }
        printf("-------------\n");
        printf("You have %d guesses left.\n", guesses);
        
        char result1[26-strlen(letters_guessed)];
        //printf("lett g = [%s]\n", letters_guessed);
        //printf("%lu - right n\n", strlen(letters_guessed));
	get_available_letters(letters_guessed, result1);

        printf("Available letters: %s\n", result1);
        char letter[15];
        printf("Please guess a letter: ");
        scanf("%s", letter);
	tupo += 1;	

        // 'A' to 'a'..
        unsigned long length = strlen(letter);
        for (unsigned long i = 0; i < length || letter[i] != '\0'; i += 1){
            if(letter[i] != '\0'){
                letter[i] = tolower(letter[i]);
            }
        }
        
        // @...?
        int flag = 0;
        char alphabet2[] = "abcdefghijklmnopqrstuvwxyz";
        for (int a = 0; a < strlen(letter); a++) {
            for (int a2 =0; a2 < 26; a2++) {
                if (letter[a] == alphabet2[a2]) {
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            //printf("%s  lett \n", letters_guessed);
            char result2r[strlen(result2)+1];
            //printf("%s  res2\n", result2);
        
            //printf("%s 2r\n", result2r);
            int a = 0;
            for (short a2 = 0; a2 < (strlen(result2)*2) - 1; a2+=2) {
                //printf("%c\n", result2r[a]);
                result2r[a2] = result2[a];
                if(result2[a+1] != '\0'){
                    result2r[a2+1] = ' ';
                    a++;
                }
                else{
                    result2r[a2+1] = '\0';
                }
                //a++;
            }
            printf("Oops! '%s' is not a valid letter: %s\n", letter, result2r);
            continue;
        }
        
        // the end ...))
        n += 1;
        
        // //Was already used// OR Bad Guess
        
        
        if (strlen(letter) == strlen(secret)) {
            if (is_word_guessed(secret, letter) == 1) {
                printf("Congratulations, you won!\n");
                break;
            }
            else if(is_word_guessed(secret, letter) == 0){
                printf("Sorry, bad guess. The word was %s.\n", secret);
                break;
            }
        }
        
        char letter_rez[strlen(letter)];
        if (1){
            for (int l = 0; l < strlen(letter); l++) {
                letter_rez[l] = letter[l];
            }
            unsigned long q = strlen(letter_rez);
            for (int i = 0; i < q; i++) {
                for (int j = i + 1; j < q; j++) {
                    if (letter_rez[i] == letter_rez[j]) {
                        for (int d = j; d < q; d++) {
                            letter_rez[d] = letter_rez[d+1];
                        }
                        j -= 1;
                        q -= 1;
                    }
                }
                
            }
            
            for (int i = 0; i < strlen(letter); i++) {
                if (is_char_guessed(letone, letter) == false) {
                    letters_guessed[m] = letter_rez[i];
                    m++;
                }
            }
            
            get_guessed_word(secret, letters_guessed, result2);
            if (is_char_guessed(letone, letter)) {
                if(n > 1 && strlen(letter) == 1){
                    //printf("%s  lett \n", letters_guessed);
                    char result2r[strlen(result2)+1];
                    //printf("%s  res2\n", result2);
                
                    //printf("%s 2r\n", result2r);
                    int a = 0;
                    for (short a2 = 0; a2 < (strlen(result2)*2) - 1; a2+=2) {
                        //printf("%c\n", result2r[a]);
                        result2r[a2] = result2[a];
                        if(result2[a+1] != '\0'){
                            result2r[a2+1] = ' ';
                            a++;
                        }
                        else{
                            result2r[a2+1] = '\0';
                        }
                        //a++;
                    }
                    printf("Oops! You've already guessed that letter: %s\n", result2r);
                    continue;
                }
            }
            for (int i2 = 0; i2 < strlen(letter); i2 += 1) {
                letone[ii] = letter[i2];
                ii += 1;
            }
            if (is_char_guessed(secret, letter) == false){
                //printf("%s  lett \n", letters_guessed);
                char result2r[strlen(result2)+1];
                //printf("%s  res2\n", result2);
            
                //printf("%s 2r\n", result2r);
                int a = 0;
                for (short a2 = 0; a2 < (strlen(result2)*2) - 1; a2+=2) {
                    //printf("%c\n", result2r[a]);
                    result2r[a2] = result2[a];
                    if(result2[a+1] != '\0'){
                        result2r[a2+1] = ' ';
                        a++;
                    }
                    else{
                        result2r[a2+1] = '\0';
                    }
                    //a++;
                }

                printf("Oops! That letter is not in my word: %s\n", result2r);
                guesses -= 1;
                continue;
            }
            
        }
        //printf("letter  =  %d\n", is_char_guessed(secret, letter));
        //printf("letter  =  %s  [%lu]\n", letter, strlen(letter));
        
        //printf("num = %d\n", num);

        //printf("[%s]\n", letters_guessed);
        get_guessed_word(secret, letters_guessed, result2);
        //result2[(strlen(result2r)*2) - 1] = '\0';
        //printf("%s 2\n", result2);
        if (is_word_guessed(secret, letters_guessed) == 1 ) {
            stop_while = false;
            char result2r[strlen(result2)+1];
            int a = 0;
            for (short a2 = 0; a2 < (strlen(result2)*2) - 1; a2+=2) {
                //printf("%c\n", result2r[a]);
                result2r[a2] = result2[a];
                if(result2[a+1] != '\0'){
                    result2r[a2+1] = ' ';
                    a++;
                }
                else{
                    result2r[a2+1] = '\0';
                }
                //a++;
            }
            printf("Good guess: %s\n", result2r);
            printf("-------------\n");
            printf("Congratulations, you won!\n");
            break;
        }
        else if (is_char_guessed(secret, letter)){
            //printf("%s  lett \n", letters_guessed);
            char result2r[strlen(result2)+1];
            //printf("%s  res2\n", result2);
        
            //printf("%s 2r\n", result2r);
            int a = 0;
            for (short a2 = 0; a2 < (strlen(result2)*2) - 1; a2+=2) {
                //printf("%c\n", result2r[a]);
                result2r[a2] = result2[a];
                if(result2[a+1] != '\0'){
                    result2r[a2+1] = ' ';
                    a++;
                }
                else{
                    result2r[a2+1] = '\0';
                }
                //a++;
            }
            printf("Good guess: %s\n", result2r);
            //printf("-------------\n");
        }
    }
}