#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    //Obtains height from user
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);
    
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}