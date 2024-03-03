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

int long_double_epsilon() {
    int pow = 0;
    long double eps = 1;
    while (eps + 1 != 1) {
        eps /= 2;
        --pow;
    }
    return pow + 1;
}

int long_double_mantissa(){

    long double a = 1;
    long double b = 0.5;
    long double c = a + b;
    int bits = 1;
    while (c != a) {
        bits = bits + 1;
        b = b / 2;
        c = a + b;
    }

    return bits;

}

int main(){

    printf("\n---------------long double---------------\n");
    printf("Sizeof zwraca: %d\n", sizeof(long double));
    printf("Liczba bajtow: %d\n", sizeof(long double));
    printf("Liczba bitow: %d\n", sizeof(long double) * 8);
    printf("Odczytana mantysa: %d\n", LDBL_MANT_DIG);
    printf("Obliczona mantysa: %d\n", long_double_mantissa());
    printf("Odczytana cecha (wraz ze znakiem): %d\n", (sizeof(long double) * 8) - LDBL_MANT_DIG);
    printf("Obliczona cecha (wraz ze znakiem): %d\n", (sizeof(long double) * 8) - long_double_mantissa());
    printf("Odczytane epsilon: %Le\n", LDBL_EPSILON);
    printf("Obliczone epsilon: %g\n", pow(2, long_double_epsilon()));
    
    long double* long_double_number = (long double*)malloc(sizeof(long double));
    *long_double_number = +0.0l; 

    printf("+0: ");
    print_bits((void*)long_double_number, sizeof(long double), long_double_mantissa());

    printf("-0: ");
    *long_double_number = -0.0l;   
    print_bits((void*)long_double_number, sizeof(long double), long_double_mantissa());

    printf("Inf: ");
    *long_double_number = INFINITY;   
    print_bits((void*)long_double_number, sizeof(long double), long_double_mantissa());

    printf("-Inf: ");
    *long_double_number = -INFINITY;   
    print_bits((void*)long_double_number, sizeof(long double), long_double_mantissa());

    printf("NaN: ");
    *long_double_number = NAN;   
    print_bits((void*)long_double_number, sizeof(long double), long_double_mantissa());
    
    free(long_double_number);

    float x = LDBL_EPSILON;

    printf("%.30f\n", 1 + x);

}