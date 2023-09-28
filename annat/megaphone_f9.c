#include <stdio.h>

int main(void)
{
        int res;
        while ((res = getchar()) != EOF)
        {
                if (res >= 'a' && res <= 'z')
                {
                        res -= ' '; //mellanslag motsvara exakt det avstådent mellan en stor och liten bokstav, ascii för ' ' är 32
                putchar(res);
                }
        }
        return 0;
}