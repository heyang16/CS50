#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int calculate_index(string text);

int main(void)
{
    //Prompts user for text
    string word = get_string("Text: ");
    
    //Calculates index
    int index = calculate_index(word);
    
    //Prints index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", calculate_index(word));
    }
}

int calculate_index(string text)
{
    //Initialize number of words, letters and sentences
    int words = 0;
    int letters = 0;
    int sentences = 0;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char character = text[i];
        
        //Checks if character is alphabetical
        if (isalpha(character))
        {
            letters++;
        }
        
        //Checks if character is '!' or '?' or '.'
        if (character == 33 || character == 46 || character == 63)
        {
            sentences++;
        }
        
        //Checks if character is a whitespace
        if (isspace(character))
        {
            words++;
        }
    }
    
    //Add final word of the sentence
    words++;
    
    //Calculates and returns index
    float L = (float) letters * 100 / (words);
    float S = (float) sentences * 100 / (words);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}