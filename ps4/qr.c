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
    int length = 4+1, cols = 3, offset = 2;
    bool bytes1[4+1][8] = {
        {0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,0,0},
        {0,1,1,0,1,1,1,1},
        {0,1,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0}
    };
    bool blocks1[offset*8][cols];
    bytes_to_blocks(cols, offset, blocks1, length, bytes1);
    for(int j = 0; j < offset*8; j++){
        for(int i = 0; i < cols; i++){
            printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if(j % 8 == 7){
            printf("\n");
        }
    }
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
    int res[8][rows];
    
    
    //int res2[8][cols];
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < (rows); y++) {
            res[x][y] = bytes[y][x];
        }
    }
    
    
    
    //int jj = 8;
    //printf("res: \n");
    for (int i=0; i < (8); i++) {
        for (int j = 0; j<(cols); j++) {
            blocks[i][j] = res[i][j];
        }
    }
    int ii = 7;
    if(offset >= 2){
        for (int i = 0; i < 8; i++) {
            for (int j = 3; j < (cols*2); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    //printf("ii = %d\n", ii);
    ii = 14;
    if(offset >= 3){
        for (int i = 0; i < 8; i++) {
            for (int j = 6; j < (cols*3); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    //printf("ii = %d\n", ii);
    ii = 21;
    if(offset >= 4){
        for (int i = 0; i < 8; i++) {
            for (int j = 9; j < (cols*4); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = 28;
    if(offset >= 5){
        for (int i = 0; i < 8; i++) {
            for (int j = 12; j < (cols*5); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = 35;
    if(offset >= 6){
        for (int i = 0; i < 8; i++) {
            for (int j = 15; j < (cols*6); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = 42;
    if(offset >= 7){
        for (int i = 0; i < 8; i++) {
            for (int j = 18; j < (cols*7); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = 49;
    if(offset >= 8){
        for (int i = 0; i < 8; i++) {
            for (int j = 21; j < (cols*8); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = 56;
    if(offset >= 9){
        for (int i = 0; i < 8; i++) {
            for (int j = 24; j < (cols*9); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    
    ii = 63;
    int n = 10;
    int k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols*n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    //n = 33 down
    ii = ii - 1;
    n = n + 1;
    k = (n-1)*3;
    if(offset >= n){
        for (int i = 0; i < 8; i++) {
            for (int j = k; j < (cols * n); j++) {
                blocks[ii][j] = res[i][j];
            }
            ii++;
        }
    }
    
    for (int i = 7 * (offset - 1); i < (8*offset); i++) {
        for (int j = rows - 1; j < cols*offset; j++) {
            blocks[i][j] = 0;
        }
    }
}

// task 3 f2
void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]){
    // soon
}


