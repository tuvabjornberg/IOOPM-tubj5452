#include <stdio.h>

int factorial_tail_recursive(int n, int result)
{
    if (n == 0 || n == 1)
    {
        return result; 
    }
    else 
    {
    return factorial_tail_recursive(n - 1, n * result); 
    }
}

int main() {
    printf("Tail-recursive: %d\n", factorial_tail_recursive(5, 1)); 
}