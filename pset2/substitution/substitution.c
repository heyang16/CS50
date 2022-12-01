#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Checks number of arguments
    if (argc != 2)
    {
        printf("Please enter a single key");
        return 1;
    }
    
    string key = argv[1];
    //Checks if key has 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    
    //Checks if key is alphabetical
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must be alphabetical");
            return 1;
        }
        //Checks for repeated characters
        for (int j = i + 1; j < 26; j++)
        {
            if (key[j] == key[i])
            {
                printf("Key must not contain repeated characters");
                return 1;
            }
        }
    }
    
    //Prompts user for plaintext
    string plaintext = get_string("plaintext: ");
    
    int n = strlen(plaintext);
    
    //Converts plaintext to ciphertext using key
    for (int i = 0; i < n; i++)
    {
        if isalpha(plaintext[i])
        {
            if isupper(plaintext[i])
            {
                plaintext[i] = toupper(key[plaintext[i] - 65]);
            }
            if islower(plaintext[i])
            {
                plaintext[i] = tolower(key[plaintext[i] - 97]);
            }
        }
    }
    
    printf("ciphertext: %s\n", plaintext);
    return 0;
}