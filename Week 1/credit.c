#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool check_card(long);

int main(void)
{
    long card_number;
    const long CARD_MIN = pow(10, 12);
    const long CARD_MAX = pow(10, 16);
    const long SIXTEEN_DIG = pow(10, 15);  // Use for VISA
    const long THIRTEEN_DIG = pow(10, 12); // Use for VISA
    const long FOURTEEN_DIG = pow(10, 13); // Use for AMEX
    const long FIFTEEN_DIG = pow(10, 14);  // Use for MC

    card_number = get_long("Number: ");

    if (check_card(card_number) == true)
    {
        if (card_number < CARD_MIN || card_number > CARD_MAX)
        {
            printf("INVALID\n");
        }
        else
        {
            if (card_number / SIXTEEN_DIG == 4 || card_number / THIRTEEN_DIG == 4)
            {
                printf("VISA\n");
            }
            else if (card_number / FOURTEEN_DIG == 34 || card_number / FOURTEEN_DIG == 37)
            {
                printf("AMEX\n");
            }
            else if (card_number / FIFTEEN_DIG > 50 && card_number / FIFTEEN_DIG < 56)
            {
                printf("MASTERCARD\n");
            }
            else
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

bool check_card(long card_number)
{
    long cc = card_number;
    int index = 1;
    int first_sum = 0;
    int second_sum = 0;
    int check_sum = 0;
    int x;

    while (cc > 0)
    {
        x = cc % 10;
        // printf("x: %i\t", x);
        if (index % 2 == 1)
        {
            check_sum += x;
        }
        else
        {
            x *= 2;
            if (x > 9)
            {
                check_sum += 1 + (x % 10);
            }
            else
            {
                check_sum += x;
            }
        }
        printf("check: %i\n", check_sum);

        cc = cc / 10;
        index++;
    }
    printf("%i\n", check_sum);

    check_sum = first_sum + second_sum;
    if (check_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}