#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


// task 1
void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);

//task 2
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);

// task 3
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main() {
    int length = 13+1, cols = 6, offset = 3;
    bool blocks2[3*8][6] = {
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},//8
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},//16
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0}
    };
    bool bytes2[length][8];
    blocks_to_bytes(cols, offset, blocks2, length, bytes2);
    for(int j = 0; j < length; j++){
        for(int i = 0; i < 8; i++){
            printf("%d", bytes2[j][i]);
        }
        printf("\n");
    }
    // prints:
    // 01000001
    // 01101000
    // 01101111
    // 01101010
    // 00000000
    return 0;
}

void encode_char(const char character, bool bits[8]) {
    for (int q = 0; q < 8; q++) {
        bits[q] = 0;
    }
    // 10 to 2
    int num = character;
    //printf("[%c] = %d\n", character, character);
    int n = 0, k = 0, ii, len = 0;
    for (ii = 0; n <= num; ii++) {
        n = pow(2, ii);
        if (n <= num) {
            k = n;
            len = ii;
            //printf("k: %d\n", k);
        }
    }
    
    len++;
    //printf("len: %d\n", len);
    int j = 0;
    if (len == 7) {
        j = 1;
        len++;
        bits[0] = 0;
    }
    else if (len == 6){
        j = 2;
        len += 2;
        bits[0] = 0;
        bits[1] = 0;
    }
    else if (len == 5){
        j = 3;
        len += 3;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
    }
    else if (len == 4){
        j = 4;
        len += 4;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
    }
    else if (len == 3){
        j = 5;
        len += 5;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
    }
    else if (len == 2){
        j = 6;
        len += 6;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
    }
    else if (len == 1){
        j = 8;
        len += 7;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
        bits[7] = 0;
    }
    //printf("len: %d\n", len);
    for (int i = j; i < len; i++) {
        if (k <= num) {
            //printf("k: %d {num: %d}\n", k, num);
            bits[i] = 1;
            //printf("i = %d\n", i);
            num = num - k;
            k /= 2;
            //printf("k: %d {num: %d}\n", k, num);
            //printf("...........\n");
        }
        else{
            bits[i] = 0;
            k /= 2;
        }
    }
    
    //printf("n: %d {len: %d}\n", k, len);
    return;
}
char decode_byte(const bool bits[8]){
    // 2 to 10
    short num = 0, st = 0, i = 7;
    
    while (i >= 0) {
        if (bits[i] == 1) {
            num += pow(2, st);
            //printf("%d\n", num);
        }
        i--;
        st++;
    }
    return num;
}

// task 2
void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    int i = 0;
    unsigned long len2 = strlen(string);
    for(int j = 0; j <= len2; j++){
        if(i != 8){
            //printf("[%c] - %d\n", string[j], string[j]);
            encode_char(string[j], &bytes[j][i]);
        }
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]){
    for (int j = 0; j < rows ; j++) {
        string[j] = decode_byte(bytes[j]);
    }
}
// task 3 f1
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    
    //  ИНИЦИАЛИЗАЦИЯ РЕЗ МАССИВА+ ЗНАК '\0'
    int res[8][offset*cols+1];
    for (short t = 0; t<8; t++) {
        for (short o = 0; o<(offset * cols); o++) {
            res[t][o] = 0;
        }
        //res[t][offset*cols] = '\0';
    }
    
    int box[offset*8][cols];
    for (int i = 0; i < offset*8; i++) {
        for (int j = 0; j < cols; j++) {
            box[i][j] = 0;
        }
        box[i][cols] = '\0';
    }
    
    //  ПЕРЕБОР РЕЗ МАССИВА
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < (rows); y++) { //offset*cols
            res[x][y] = bytes[y][x];
        }
    }
    
    //  ПЕРЕБОР ОСТНОВНОГО МАССИВА
    for (int i = 0; i < 8*offset; i++) {
        for (int j = 0; j < cols; j++) {
            box[i][j] = res[i][j];
        }
    }
    
    int c = 0;
    int nn = 2;
    int ii = 7;

    while (offset >= nn){
        c = c + cols;
        for (int i = 0; i < 8; i++) {
            for (int j = c; j < (cols*nn); j++) {
                box[ii][j] = res[i][j];
            }
            ii++;
        }
        nn++;
        ii = ii - 1;
    }
    for (int i = 0; i < offset*8; i++) {
        for (int j = 0; j < cols; j++) {
            blocks[i][j] = box[i][j];
        }
    }
    blocks[1][0] = 0;
    if (offset > 6 && cols == 2) {
        blocks[1][1] = 0;
        blocks[3][1] = 0;
        blocks[5][0] = 0;
    }
    
    for (int i = 8 * (offset - 1); i < (8*offset); i++) {
        for (int j = rows - 1; j < cols*offset; j++) {
            blocks[i][j] = 0;
        }
    }
}
    

// task 3 f2
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    int res[8][offset*cols];
    for (int t = 0; t < 8; t++) {
        for (int y = 0; y < offset*cols; y++) {
            res[t][y] = 0;
        }
        res[t][offset*cols] = '\0';
    }
    
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < cols; j++) {
            res[i][j] = blocks[i][j];
        }
    }
    
    int n = offset;
    int ii = 8;
    int jj = 0;
    
    int b = 8;
    int in = 3;
    while( n != 1 && offset > 1 ){
        for (int i = in; i < in+cols; i++) {
            for (int j = 0; j < 8; j++) {
                res[j][i] = blocks[ii][jj];
                ii++;
                //printf("j:[%d]\n",j);
            }
            jj++;
            ii = b;
        }
        jj = 0;
        b += 8;
        ii = b;
        n-=1;
        in += cols;
        //printf("ii: %d, jj: %d\n", ii, jj);
    }
    //for (int i = 0; i < 8; i++) {
    //    for (int j = 0; j < cols*offset; j++) {
    //        printf("%d ", res[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("----------\n");
    
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j < 8; j++) {
            bytes[i][j] = res[j][i];
        }
    }
}

