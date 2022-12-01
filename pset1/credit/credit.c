#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number = get_long("Number: ");
    
    
    //Creates a duplicate to calculate checksum and number of digits
    long num = number;

    int checksum = 0;
    int is_digit_even = false;
    int digits = 0;
    
    while (num > 1)
    {
        if (is_digit_even)
        {
            //checks if checksum value has 2 digits or 1 digit
            if ((num % 10) * 2 < 10)
            {
                checksum += (num % 10) * 2;
            }
            else
            {
                checksum += ((num % 10) * 2) / 10 + ((num % 10) * 2) % 10;
            }
            is_digit_even = false;
        }
        
        else
        {
            checksum += (num % 10);
            is_digit_even = true;
        }
        
        digits++;
        num /= 10;
    }
    checksum %= 10;
    
    
    if (checksum == 0)
    {
        int first_digits;
        switch (digits)
        {
            case 13:
                first_digits = number / 1e12;
                (first_digits == 4) ? printf("VISA\n") : printf("INVALID\n");
                break;
            case 15:
                first_digits = number / 1e13;
                (first_digits == 34 || first_digits == 37) ? printf("AMEX\n") : printf("INVALID\n");
                break;
            case 16:
                first_digits = number / 1e14;
                if (first_digits == 51 || first_digits == 52 || first_digits == 53 || first_digits == 54 || first_digits == 55)
                {
                    printf("MASTERCARD\n");
                    break;
                }
                else if (first_digits / 10 == 4)
                {
                    printf("VISA\n");
                    break;
                }

            default:
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
    
}