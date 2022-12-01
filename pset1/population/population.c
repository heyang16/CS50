#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Requests user to enter starting size
    int size;
    do
    {
        size = get_int("Start size: ");
    }
    while (size < 9);

    //Requests user to enter ending size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < size);

    //Calculates number of years required
    int years = 0;
    while (size < end_size)
    {
        int births = size / 3;
        int deaths = size / 4;
        size += births - deaths;
        years++;
    }

    printf("Years: %i", years);
}