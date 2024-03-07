#include<stdio.h>
#include<float.h>
#include<math.h>
#include<stdlib.h>

void print_bits ( void* buffer, int bytes, unsigned int mantissa_bits){   

    if(sizeof(char) != 1){

        printf("Rozmiar char'a != 1");
        return;

    }

    int bit_counter = 0;
    unsigned char* ptr = (unsigned char*)buffer;

    for (int i = bytes - 1; i >= 0; i -= 1) {
        
        for (int j = 7; j >= 0; j--) {
            
            printf("%d", (ptr[i] >> j) & 1);
            bit_counter += 1;

            if(bit_counter == 1 || bit_counter == 1 + (bytes * 8) - mantissa_bits) printf(" ");
        }
        
    }
    printf("\n");
}

int float_epsilon() {
    int pow = 0;
    float eps = 1;
    while (eps + 1 != 1) {
        eps /= 2;
        --pow;
    }
    return pow + 1;
}

int float_mantissa(){

    float a = 1;
    float b = 0.5;
    float c = a + b;
    int bits = 1;
    while (c != a) {
        bits = bits + 1;
        b = b / 2;
        c = a + b;
    }

    return bits;
}

int main(){

    printf("---------------float---------------\n");
    printf("Liczba bajtow: %d\n", sizeof(float));
    printf("Liczba bitow: %d\n", sizeof(float) * 8);
    printf("Odczytana mantysa: %d\n", FLT_MANT_DIG);
    printf("Obliczona mantysa: %d\n", float_mantissa());
    printf("Odczytana cecha (wraz ze znakiem): %d\n", (sizeof(float) * 8) - FLT_MANT_DIG);
    printf("Obliczona cecha (wraz ze znakiem): %d\n", (sizeof(float) * 8) - float_mantissa());
    printf("Odczytane epsilon: %g\n", FLT_EPSILON);
    printf("Obliczone epsilon: %g\n", pow(2, float_epsilon()));

    float* float_number = (float*)malloc(sizeof(float));
    *float_number = +0.0f; 
    printf("+0: ");
    print_bits((void*)float_number, sizeof(float), FLT_MANT_DIG);

    printf("-0: ");
    *float_number = -0.0f;   
    print_bits((void*)float_number, sizeof(float), FLT_MANT_DIG);

    printf("Inf: ");
    *float_number = INFINITY;   
    print_bits((void*)float_number, sizeof(float), FLT_MANT_DIG);

    printf("-Inf: ");
    *float_number = -INFINITY;   
    print_bits((void*)float_number, sizeof(float), FLT_MANT_DIG);

    printf("NaN: ");
    *float_number = NAN;   
    print_bits((void*)float_number, sizeof(float), FLT_MANT_DIG);

    free(float_number);

}