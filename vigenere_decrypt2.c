#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1024

char* vigenere_decrypt(char* cipher, char* key)
{
    int text_length = strlen(cipher);
    int key_length = strlen(key);
    char* plaintext = (char*) malloc(sizeof(char) * (text_length + 1));
    memset(plaintext, '\0', sizeof(char) * (text_length + 1));

    for(int i = 0; i < text_length; i++)
    {
        if(isalpha(cipher[i]))
        {
            int shift = tolower(key[i % key_length]) - 'a';
            if(islower(cipher[i]))
            {
                plaintext[i] = (cipher[i] - 'a' - shift + 26) % 26 + 'a';
            }
            else
            {
                plaintext[i] = (cipher[i] - 'A' - shift + 26) % 26 + 'A';
            }
        }
        else
        {
            plaintext[i] = cipher[i];
        }
    }
    plaintext[text_length] = '\0';
    return plaintext;
}

int read_cipher(char* filename, char* cipher)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("The file does not exist.");
        return EXIT_FAILURE;
    }

    if(fgets(cipher, MAXN, fp) == NULL)
    {
        printf("Error reading from file.");
        return EXIT_FAILURE;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

void write_text(char* filename, char* text)
{
    FILE* fp = fopen(filename, "wb");
    fprintf(fp, "%s", text);
    fclose(fp);
}

int main()
{
    char cipher[MAXN];
    char key[MAXN];
    char filename[MAXN];
    scanf("%s", filename);
    read_cipher(filename, cipher);
    scanf("%s", filename);
    read_cipher(filename, key);
    char* plaintext = vigenere_decrypt(cipher, key);
    printf("%s", plaintext);
    write_text("text1.txt", plaintext);
    free(plaintext);
    return EXIT_SUCCESS;
}
