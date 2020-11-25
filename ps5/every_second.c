#include <stdio.h>

char triger_start(int y);

int main(int arg, char* subor[], char* subor2[]) {

    FILE *fp = fopen(subor[1], "r");
    FILE *fp2 = fopen(subor[2], "w");
    
    int n = 0;
    int nn = 0;
    int kost1 = 0;
    //int len_cat = 0;
    //int len_spase = 0;
    
    int parity = 0;
    
    char letter;
    //char cat[30000];
    
    char res;
    
    int ops = 0;
    
    while (1) {
        letter = fgetc(fp);
        if (letter == EOF){
            //cat[len_cat-1]='\0';
            //printf("%d\n", len_cat);
            break;
        }
        
        // check START
        if (kost1 == 0 && letter == triger_start(0)) {
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
                    if (letter == 'S') {
                        res = fgetc(fp);
                        if (res == 'T') {
                            res = fgetc(fp);
                            if (res == 'O') {
                                res = fgetc(fp);
                                if (res == 'P') {
                                    ops = 1;
                                }
                            }
                        }
                    }
                    if (ops == 0) {
                        fputc(letter, fp2);
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

