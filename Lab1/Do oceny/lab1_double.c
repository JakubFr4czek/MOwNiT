#include<stdio.h>
#include<float.h>
#include<math.h>
#include<stdlib.h>

//Ta funkcja dziala pod warunkiem, ze char ma dokladnie 1 bajt
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

int double_epsilon() {
    int pow = 0;
    double eps = 1;
    while (eps + 1 != 1) {
        eps /= 2;
        --pow;
    }
    return pow + 1;
}

int double_mantissa(){

    double a = 1;
    double b = 0.5;
    double c = a + b;
    int bits = 1;
    while (c != a) {
        bits = bits + 1;
        b = b / 2;
        c = a + b;
    }

    return bits;

}

int main(){

    printf("\n---------------double---------------\n");
    printf("Liczba bajtow: %d\n", sizeof(double));
    printf("Liczba bitow: %d\n", sizeof(double) * 8);
    printf("Odczytana mantysa: %d\n", DBL_MANT_DIG);
    printf("Obliczona mantysa: %d\n", double_mantissa());
    printf("Odczytana cecha (wraz ze znakiem): %d\n", (sizeof(double) * 8) - DBL_MANT_DIG);
    printf("Obliczona cecha (wraz ze znakiem): %d\n", (sizeof(double) * 8) - double_mantissa());
    printf("Odczytane epsilon: %g\n", DBL_EPSILON);
    printf("Obliczone epsilon: %g\n", pow(2, double_epsilon()));

    double* double_number = (double*)malloc(sizeof(double));
    *double_number = +0.0; 
    printf("+0: ");
    print_bits((void*)double_number, sizeof(double), DBL_MANT_DIG);

    printf("-0: ");
    *double_number = -0.0;   
    print_bits((void*)double_number, sizeof(double), DBL_MANT_DIG);

    printf("Inf: ");
    *double_number = INFINITY;   
    print_bits((void*)double_number, sizeof(double), DBL_MANT_DIG);

    printf("-Inf: ");
    *double_number = -INFINITY;   
    print_bits((void*)double_number, sizeof(double), DBL_MANT_DIG);

    printf("NaN: ");
    *double_number = NAN;   
    print_bits((void*)double_number, sizeof(double), DBL_MANT_DIG);

}