//
// Created by Nathan Seymour on 29/12/20.
//

int pcpow(int base, unsigned int exponent)
{
    int number = base;

    if(exponent == 0)
    {
        return 1;
    }

    for(; exponent > 1; exponent--)
    {
        number *= base;
    }

    return number;
}