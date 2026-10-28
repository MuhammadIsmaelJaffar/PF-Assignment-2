#include <stdio.h>

int sumOfProperDivisors(int num)
{
    int sum = 0;
    for (int i = 1; i <= num / 2; i++)
    {
        if (num % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}

int main()
{
    int n;
    
    printf("Enter n: ");
    scanf("%d", &n);
    
    int pairs_found = 0;
    
    printf("\nAmicable pairs up to %d:\n", n);
    for (int a = 1; a <= n; a++)
    {
        int b = sumOfProperDivisors(a);
        
        if (b > a && b <= n)
        {
            if (sumOfProperDivisors(b) == a && a != b)
            {
                printf("(%d, %d)\n", a, b);
                pairs_found++;
            }
        }
    }
    
    if (pairs_found == 0)
    {
        printf("No amicable pairs found up to %d.\n", n);
    }
    else
    {
        printf("Total amicable pairs found: %d\n", pairs_found);
    }
    
    return 0;
}