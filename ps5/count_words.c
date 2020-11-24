#include <stdio.h>
 
char check_ananas(int x);
char check_ANANAS(int y);
char go_up(char x);

int main(int arg, char* subor[]) {
    FILE *fp;
    fp = fopen(subor[1], "r");
    char cat_boy_kami;
    
    
    // XD
    int Black_Lives_Matter = 0;
    //char res;
    int marder = 0;
    
    while (1){
        cat_boy_kami = fgetc(fp);

        if (cat_boy_kami == EOF){
            break;
        }
        
        if (go_up(cat_boy_kami) == check_ANANAS(0)) {
            marder++;
            if (marder == 6) {
                Black_Lives_Matter++;
            }
        }
        else{
            check_ANANAS(1);
            marder = 0;
        }
    
    }
    //printf("%d\n", Black_Lives_Matter);
    fclose(fp);
    
    FILE *fp2 = fopen(subor[1], "w");
    fputc('0' + Black_Lives_Matter, fp2);
    
    
    fclose(fp2);
    return 0;
}

char go_up(char x){
    if( x <= 'z' && x >= 'a'){
        x += 'A' - 'a';
    }
    return x;
}

char check_ANANAS(int y){
    char ananas2[] = "ANANAS";
    static int intn2 = -1;
    if (y == 1) {
        intn2 = -1;
        return 'q';
    }
    intn2++;
    if (intn2 == 6) {
        intn2 = 0;
    }
    //printf("[%c]", start[intn1]);
    return ananas2[intn2];
}