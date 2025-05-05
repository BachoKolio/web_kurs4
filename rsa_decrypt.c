#include <stdio.h>
#include <stdlib.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#define MAXN 4096
#define KEYFILE "private.pem"

RSA* load_private_key(const char* filename){
    FILE* fp = fopen(filename, "rb");
    RSA* rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
    fclose(fp);
    return rsa;
}

int hex_to_bin(const char* hex, unsigned char* bin)
{
    int len = 0;
    for(int i = 0; hex[i] != '\0' && hex[i+1] != '\0'; i+=2){
        sscanf(&hex[i],"%2hhx", &bin[len]);
        len++; 
    }
    return len;
}

int decrypt_rsa(RSA* rsa, const unsigned char* encrypt,
    int encryptlen, unsigned char* decrypt){
    return RSA_private_decrypt(encryptlen, encrypt, decrypt, 
        rsa, RSA_PKCS1_OAEP_PADDING);
}

int main(){
    RSA* rsa = load_private_key(KEYFILE);
    char hex[MAXN];
    scanf("%s", hex);
    unsigned char encrypt[MAXN];
    int encryptLen = hex_to_bin(hex, encrypt);
    unsigned char decrypt[MAXN];
    int decryptedLen = decrypt_rsa(rsa, encrypt, encryptLen, decrypt);
    printf("%.*s\n", decryptedLen, decrypt);
    return EXIT_SUCCESS;
}
