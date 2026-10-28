#include <stdio.h>

int getValidDays()
{
    int days;
    while (1)
    {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days >= 1 && days <= 7)
        {
            return days;
        }
        printf("Invalid value! Please enter a number between 1 and 7.\n");
    }
}

float calculateDailySales(int dayNumber)
{
    int orders;
    printf("\nDay %d - Enter number of orders: ", dayNumber);
    scanf("%d", &orders);
    
    while (orders <= 0)
    {
        printf("Number of orders must be at least 1. Re-enter: ");
        scanf("%d", &orders);
    }
    
    float total_sales = 0;
    float highest_order = 0;
    
    for (int i = 0; i < orders; i++)
    {
        float amount;
        printf("Enter amount for order %d: ", i + 1);
        scanf("%f", &amount);
        
        while (amount <= 0)
        {
            printf("Invalid amount! Amount must be greater than zero. Re-enter amount for order %d: ", i + 1);
            scanf("%f", &amount);
        }
        
        total_sales += amount;
        
        if (i == 0 || amount > highest_order)
        {
            highest_order = amount;
        }
    }
    
    float average_order = total_sales / orders;
    
    printf("\n--- Summary for Day %d ---\n", dayNumber);
    printf("Total sales for Day %d: %.2f\n", dayNumber, total_sales);
    printf("Average order amount: %.2f\n", average_order);
    printf("Highest order amount: %.2f\n", highest_order);
    
    return total_sales;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int best_day = 1;
    float max_sales = dailySales[0];
    
    for (int i = 1; i < numberOfDays; i++)
    {
        if (dailySales[i] > max_sales)
        {
            max_sales = dailySales[i];
            best_day = i + 1;
        }
    }
    
    return best_day;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    printf("\nDaily Sales Bar Chart:\n");
    for (int i = 0; i < numberOfDays; i++)
    {
        printf("Day %d: ", i + 1);
        int asterisks = (int)(dailySales[i] / 100);
        for (int j = 0; j < asterisks; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    int days = getValidDays();
    
    float dailySales[7];
    float total_festival_sales = 0;
    
    for (int i = 0; i < days; i++)
    {
        dailySales[i] = calculateDailySales(i + 1);
        total_festival_sales += dailySales[i];
    }
    
    int best_day = findHighestSalesDay(dailySales, days);
    
    printf("\nFestival Sales Summary:\n");
    printf("Total sales for the entire festival: %.2f\n", total_festival_sales);
    printf("Day with the highest total sales: Day %d\n", best_day);
    
    displayBarChart(dailySales, days);
    
    return 0;
}