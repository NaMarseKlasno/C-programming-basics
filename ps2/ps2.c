#include <stdio.h>
#include <math.h>

float lift_a_car(const int stick_length, const int human_weight, const int car_weight);

float unit_price(const float pack_price, const int rolls_count, const int pieces_count);

int collatz(const int number);

int opposite_number(const int n, const int number);

void counter(const int input_array[], const int array_size, int result_array[2]);

unsigned long sum_squared(const int line);

int array_min(const int input_array[], const int array_size);
int array_max(const int input_array[], const int array_size);

unsigned long special_counter(const int input_array[], const int array_size);

int special_numbers(const int input_array[], const int array_size, int result_array[]);

int main(){
    int input_array[] = {16,17,4,3,5,2};
    int result_array[6];
    int count = special_numbers(input_array, 6, result_array);
    for(int i = 0; i < count; i++){
        printf("%d ", result_array[i]);
    }
    printf("\n");
    return 0;
}

// task 1
float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
    float b = human_weight + car_weight;
    float res = stick_length * human_weight / b;
    res = roundf(res * pow(10, 2)) / pow(10, 2);
    //res = roundValue(res, 2);
    return res;
}

// task 2
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    float a2 = pieces_count * 11.7 / 100;
    a2 = a2 * rolls_count;
    float res2 = 11.7 * pack_price / a2;
    res2 = roundf(res2 * pow(10, 2)) / pow(10, 2);
    return res2;
}

// task 3
int collatz(const int number){
    int num3 = number;
    int count_num3 = 1;
    while (num3 != 1) {
        if (num3%2 == 0) {
            num3 = num3 / 2;
        }
        else{
            num3 = 3 * num3 + 1;
        }
        count_num3 += 1;
    }
    return count_num3;
}

// task 4
int opposite_number(const int n, const int number){
    int num4 = n / 2;
    int arr4[2*n];
    int n4 = 0;
    int n4_2 = 0;
    int res4;
    while (n4 != n) {
        arr4[n4] = n4;
        n4 += 1;
    }
    while( n4 != 2 * n){
        arr4[n4] = n4_2;
        n4 += 1;
        n4_2 += 1;
    }
    res4 = arr4[number + num4];
    return res4;
}

// task 5
void counter(const int input_array[], const int array_size, int result_array[2]){
    int tn5 = 0;
    int res5_0 = 0;
    int res5_1 = 0;
    while (tn5 != array_size) {
        if (tn5 % 2 == 0) {
            res5_0 += input_array[tn5];
        }
        else{
            res5_1 += input_array[tn5];
        }
        tn5 += 1;
    }
    result_array[0] = res5_0;
    result_array[1] = res5_1;
}

// task 6
unsigned long sum_squared(const int line){
    unsigned long arr_rez[100];
    unsigned long arr6[100];
    
    unsigned long res6 = 0;
    
    int trad = 0;
    int srad = 1;
    int rar_line = 3;
    int for_rez = 0;
    
    while (trad <= line) {
        if (trad == 0) {
            arr6[0] = 1;
            arr6[1] = 0;
        }
        else if (trad == 1){
            arr6[0] = 1;
            arr6[1] = 1;
            arr6[2] = 0;
        }
        else{
            while (srad <= rar_line) {
                if (srad - 1 == 0) {
                    arr6[srad - 1] = 1;
                    arr6[srad] = 0;
                }
                else if (srad == rar_line){
                    arr6[srad - 1] = 1;
                    arr6[srad] = 0;
                }
                else{
                    arr6[srad - 1] = arr_rez[srad - 2] + arr_rez[srad - 1];
                }
                srad += 1;
            }
            srad = 1;
            rar_line += 1;
        }
        while (arr6[for_rez] != 0) {
            arr_rez[for_rez] = arr6[for_rez];
            for_rez += 1;
            if (arr6[for_rez] == 0) {
                arr_rez[for_rez] = arr6[for_rez];
                break;
            }
        }
        for_rez = 0;
        
        int test_rez6 = 0;
        
        
        if (trad == line) {
            while (arr_rez[test_rez6] != 0) {
                res6 = res6 + arr_rez[test_rez6] * arr_rez[test_rez6];
                test_rez6 += 1;
            }
        }
        trad += 1;
    }
    return res6;
}

// task 7 min / max
int array_min(const int input_array[], const int array_size){
    int res_min = 0;
    if (input_array == NULL) {
        res_min = -1;
        return res_min;
    }
    int test7_array[array_size];
    
    
    int tarr = 0;
    while (tarr != array_size) {
        test7_array[tarr] = input_array[tarr];
        //printf("%d  ", test7_array[tarr]);
        tarr += 1;
    }
    
    int i_min;
    int j_min;
    int q_min;
    
    for (i_min = 0; i_min < array_size - 1; i_min += 1) {
        for (j_min = 0; j_min < array_size - i_min - 1; j_min += 1) {
            if (test7_array[j_min] > test7_array[j_min + 1] ) {
                q_min = test7_array[j_min];
                test7_array[j_min] = test7_array[j_min + 1];
                test7_array[j_min + 1] = q_min;
            }
        }
    }
    res_min = test7_array[0];
    return res_min;
}

int array_max(const int input_array[], const int array_size){
    int res_max = 0;
    if (input_array == NULL) {
        res_max = -1;
        return res_max;
    }
    
    int max_array[array_size];
    
    int tarrm = 0;
    while (tarrm != array_size) {
        max_array[tarrm] = input_array[tarrm];
        tarrm += 1;
    }
    
    int i_max;
    int j_max;
    int q_max;
    
    for (i_max = 0; i_max < array_size - 1; i_max += 1) {
        for (j_max = 0; j_max < array_size - i_max - 1; j_max += 1) {
            if (max_array[j_max] > max_array[j_max + 1] ) {
                q_max = max_array[j_max];
                max_array[j_max] = max_array[j_max + 1];
                max_array[j_max + 1] = q_max;
            }
        }
    }
    res_max = max_array[array_size - 1];
    return res_max;
}

// task 8
unsigned long special_counter(const int input_array[], const int array_size){
    int num8 = 0;
    int res8 = 0;
    while (num8 != array_size) {
        if (num8%2 == 0) {
            res8 = res8 + input_array[num8];
        }
        else{
            res8 = res8 + pow(input_array[num8], 2);
        }
        num8 += 1;
    }
    return res8;
}

// task 9
int special_numbers(const int input_array[], const int array_size, int result_array[]){
    int num9 = 0;
    int arr9[array_size];

    while (num9 != array_size) {
        arr9[num9] = input_array[num9];
        num9 += 1;
    }
    num9 = 0;
    int nums = 0;
    int save9 = 0;
    int sum_right = 0;
    
    int n_res9 = 0;
    
    while (num9 != array_size) {
        save9 = arr9[num9];
        nums = num9 + 1;
        sum_right = 0;
        while(nums != array_size){
            sum_right = sum_right + arr9[nums];
            nums += 1;
        }
        if (save9 > sum_right) {
            result_array[n_res9] = save9;
            n_res9 += 1;
        }
        num9 += 1;
    }
    return n_res9;
}
