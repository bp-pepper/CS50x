#include <cs50.h>
#include <stdio.h>

int pop_growth(int);

int main(void)
{
    int years = 0;
    int pop, target;

    // TODO: Prompt for start size
    do
    {
        pop = get_int("Start size: ");
    } while (pop < 9);

    // TODO: Prompt for end size
    do
    {
        target = get_int("End size: ");
    } while (target <= pop);

    // TODO: Calculate number of years until we reach threshold
    while (pop < target)
    {
        pop = pop_growth(pop);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}

int pop_growth(int p)
{
    p += (p / 3) - (p / 4);
    return p;
}
