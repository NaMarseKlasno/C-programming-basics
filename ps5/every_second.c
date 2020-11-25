#include <stdio.h>

char triger_start(int y);
char triger_stop(int y);
char go_up(char x);

int main(int arg, char* subor[], char* subor2[]) {

    FILE *fp = fopen(subor[1], "r");
    FILE *fp2 = fopen(subor[2], "w");
    
    int n = 0;
    int n2 = 0;
    int nn = 0;
    int kost1 = 0;
    //int len_cat = 0;
    //int len_spase = 0;
    
    int parity = 0;
    
    char letter;
    int ops = 0;
    
    char tie[10000];
    int c = 0;
    
    while (1) {
        letter = fgetc(fp);
        if (letter == EOF){
            //cat[len_cat-1]='\0';
            //printf("%d\n", len_cat);
            break;
        }
        
        // check START
        if (kost1 == 0 && go_up(letter) == triger_start(0)) {
            n++;
            if (n==5) {
                kost1 = 1;
                n=0;
            }
        }
        else{
            triger_start(1);
            n=0;
        }
        //printf("%c", letter);
         
        if (kost1==1) {
            if (nn != 0) {
                
                if(parity%2 == 0 && nn != 1){
                    if (go_up(letter) == triger_stop(0)) {
                        n2++;
                        if (n2==4) {
                            ops = 1;
                            n2=0;
                        }
                    }
                    else{
                        triger_stop(1);
                        n2=0;
                    }
                    
                    if (ops == 0) {
                        //fputc(letter, fp2);
                        tie[c] = letter;
                        c++;
                    }
                }
                if (letter == ' ') {
                    //len_spase++;
                    parity++;
                }
            }
            nn++;
        }
    }
    if (go_up(tie[c-1]) == 'O') {
        if (go_up(tie[c-2]) == 'T') {
            if (go_up(tie[c-3]) == 'S') {
                c -= 4;
                //printf("dd\n");
            }
        }
    }
    else{
        c-=1;
    }
    
    for (int i = 0; i < c; i++) {
        fputc(tie[i], fp2);
    }
    
    fclose(fp);
    fclose(fp2);
    return 0;
}
    
char triger_start(int y){
    char start[] = "START";
    static int intn1 = -1;
    if (y == 1) {
        intn1 = -1;
        return 0;
    }
    intn1++;
    if (intn1 == 5) {
        intn1 = 0;
    }
    //printf("[%c]", start[intn1]);
    return start[intn1];
}

char triger_stop(int y){
    char start[] = "STOP";
    static int intn1 = -1;
    if (y == 1) {
        intn1 = -1;
        return 0;
    }
    intn1++;
    if (intn1 == 4) {
        intn1 = 0;
    }
    //printf("[%c]", start[intn1]);
    return start[intn1];
}

char go_up(char x){
    if( x <= 'z' && x >= 'a'){
        x += 'A' - 'a';
    }
    return x;
}
