#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>
#define MAXN 1000
#define KEY_SIZE 8

int main()
{
    unsigned char key[KEY_SIZE] = "banichka";
    unsigned char input[MAXN];
    scanf("%s", input);
    unsigned int input_length = strlen(input);

    int padded_length = ((input_length + 7) / 8) * 8;
    unsigned char padded_input[padded_length];
    unsigned char output[padded_length];
    memcpy(padded_input, input, input_length);
    memset (padded_input + input_length,
            padded_length - input_length,
            padded_length - input_length
    );
    DES_key_schedule key_schedule;
    DES_set_key((DES_cblock*) key, &key_schedule);
    for(int i = 0; i < padded_length; i += 8){
        DES_ecb_encrypt((DES_cblock*)(padded_input + 1),
    (DES_cblock*)(output + i),
        &key_schedule, DES_ENCRYPT);
    }
    for(int i = 0; i < padded_length; i++){
        printf("%02x", output[i]);
    }
    return EXIT_SUCCESS;
}