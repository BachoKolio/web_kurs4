#include <stdio.h>
#include <stdlib.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#define MAXN 4096
#define KEYFILE "public.pem"

RSA* load_public_key(const char* filename){
    FILE* fp = fopen(filename, "rb");
    RSA* rsa = PEM_read_RSAPublicKey(fp, NULL, NULL, NULL);
    fclose(fp);
    return rsa;
}

int encrypt_message(RSA* rsa, const unsigned char* plaintext, unsigned char* cipher)
{
    int length = strlen(plaintext) + 1;
    int encrypted_length = RSA_public_encrypt(length, plaintext ,cipher, rsa, 
    RSA_PKCS1_OAEP_PADDING);
    return encrypted_length;
}

int main(){
    unsigned char plaintext[MAXN];
    scanf("%s", plaintext);
    unsigned char cipher[MAXN];
    RSA* rsa = load_public_key(KEYFILE);
    int encrypted_length = encrypt_message(rsa, plaintext, cipher);
    for(int i = 0; i < encrypted_length; i++){
        printf("%02x", cipher[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
