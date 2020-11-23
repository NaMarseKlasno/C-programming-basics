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
int range_j(int cols2, int offset2, int rows2);

int main() {
    int length = 6+1, cols = 5, offset = 4;
    bool bytes1[7][8] = {
        {0, 1, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1, 0, 1, 1},
        {0, 1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 0, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
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
    // prints:
    // 0 0 0
    // 1 1 1
    // 0 1 1
    // 0 0 0
    // 0 1 1
    // 0 0 1
    // 0 0 1
    // 1 0 1
    //
    // 0 0 0
    // 1 0 0
    // 1 0 0
    // 0 0 0
    // 1 0 0
    // 0 0 0
    // 1 0 0
    // 0 0 0
    
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
    int ii = 0;
    for (int i = 0; i< offset*8; i++) {
        for (int j = 0; j < cols; j++) {
            blocks[i][j] = 0;
        }
    }
    
    int box[offset*8][cols];
    for (int i = 0; i < offset*8; i++) {
        for (int j = 0; j < cols; j++) {
            box[i][j] = 0;
        }
    }
    
    
    int res_int = 0;
    for (int i = 0; i < offset*8; i++) {
        for (int j = 0; j < cols; j++) {
            res_int = range_j(cols, offset, rows);
            if (res_int == 9999) {
                box[i][j] = 0;
            }
            else{
                box[i][j] = bytes[res_int][ii];
            }
        }
        ii++;
        if (ii ==8) {
            ii=0;
        }
    }
    for (int i = 8 * (offset - 1); i < (8*offset); i++) {
        for (int j = rows - 1; j < cols*offset; j++) {
            blocks[i][j] = 0;
        }
    }


    
    for (int i = 0; i< offset*8; i++) {
        for (int j = 0; j < cols; j++) {
            blocks[i][j] = box[i][j];
        }
    }
    int piz = 0;
    
    int cols1 = cols;
    int we = rows;
    while (we - cols1 > 0) {
        we -= cols1;
        piz++;
    }
    //printf("we: %d [%d]\n", we, piz);
    for (int i = 8 * (piz); i < (8*offset); i++) {
        if (i == (8*piz) + 8) {
            we = 0;
        }
        for (int j = we; j < cols; j++) {
            blocks[i][j] = 0;
        }
    }

    //int cols1 = cols;
    //int we = rows;
    //while (we - cols1 > 0) {
    //    we -= cols1;
    //}
    //printf("we-[%d]\n", we);
    
    //for (int i = cols*offset; i < (8*offset); i++) {
    //        for (int j = we; j < cols; j++) {
    //            bytes[i][j] = 0;
    //        }
    // }
    
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
    int in = cols;
    while( n > 1 && offset > 1 ){
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
    //int ww = 100;
    //while (ww > 1) {
    //    printf("----\n");
    //    printf("%d\n", range_j(3, 2));
    //    ww--;
    //}
}

int range_j(int cols2, int offset2, int rows2){
    static int num_n1 = 0;
    static int jj = -1;
    static int off = 1;
    static int count_jj = 0;
    
    jj++;

    if (jj == cols2*off && num_n1 != 8) {
        jj = cols2*off - cols2;
        num_n1++;
    }
    if (num_n1==8) {
        off++;
        jj=cols2*(off-1);
        num_n1=0;
    }

    count_jj++;
    if (count_jj == (8*rows2)+1) {
        return 9999;
    }
    
    return jj;
}

