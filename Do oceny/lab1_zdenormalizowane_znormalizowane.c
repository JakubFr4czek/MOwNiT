#include<stdio.h>
#include<float.h>

//Ta funkcja dziala pod warunkiem, ze char ma dokladnie 1 bajt
void print_bits ( void* buffer, int bytes, unsigned int mantissa_bits){   

    if(sizeof(char) != 1){

        printf("Char size != 1");
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


int main(){

    float number1 = 3.9;
    print_bits(&number1, sizeof(float), FLT_MANT_DIG);

    float number2 = 1e-39;
    print_bits(&number2, sizeof(float), FLT_MANT_DIG);

}