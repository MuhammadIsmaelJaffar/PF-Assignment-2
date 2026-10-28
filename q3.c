#include <stdio.h>

void inputReadings(int rows, int cols, int arr[100][100])
{
    for (int i = 0; i < rows; i++)
    {
        printf("Enter temperature readings for sensor %d:\n", i);
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void analyzeSensor(int cols, int row_readings[])
{
    int total = 0;
    int highest = row_readings[0];
    int lowest = row_readings[0];
    int critical_count = 0;
    int warning_count = 0;
    int max_streak = 0;
    int current_streak = 0;
    
    for (int j = 0; j < cols; j++)
    {
        int temp = row_readings[j];
        total += temp;
        
        if (temp > highest)
        {
            highest = temp;
        }
        if (temp < lowest)
        {
            lowest = temp;
        }
        
        if (temp >= 40)
        {
            critical_count++;
        }
        else if (temp >= 35 && temp <= 39)
        {
            warning_count++;
        }
        
        if (temp >= 35)
        {
            current_streak++;
            if (current_streak > max_streak)
            {
                max_streak = current_streak;
            }
        }
        else
        {
            current_streak = 0;
        }
    }
    
    float average = (float)total / cols;
    
    printf("Total temperature: %d\n", total);
    printf("Average temperature: %.2f\n", average);
    printf("Highest temperature: %d\n", highest);
    printf("Lowest temperature: %d\n", lowest);
    printf("Critical readings (40C or above): %d\n", critical_count);
    printf("Warning readings (35C to 39C): %d\n", warning_count);
    printf("Longest streak at 35C or above: %d\n", max_streak);
}

int findHighestAverageSensor(int rows, int cols, int arr[100][100], float *highest_avg)
{
    int best_sensor = 0;
    float max_avg = -1;
    
    for (int i = 0; i < rows; i++)
    {
        int sum = 0;
        for (int j = 0; j < cols; j++)
        {
            sum += arr[i][j];
        }
        float avg = (float)sum / cols;
        
        if (i == 0 || avg > max_avg)
        {
            max_avg = avg;
            best_sensor = i;
        }
    }
    
    *highest_avg = max_avg;
    return best_sensor;
}

int main()
{
    int sensors, readings;
    
    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    
    printf("Enter number of hourly readings per sensor: ");
    scanf("%d", &readings);
    
    int data[100][100];
    
    inputReadings(sensors, readings, data);
    
    printf("\nIndividual Sensor Reports:\n");
    for (int i = 0; i < sensors; i++)
    {
        printf("\nReport for Sensor %d:\n", i);
        analyzeSensor(readings, data[i]);
    }
    
    float top_avg = 0;
    int top_sensor = findHighestAverageSensor(sensors, readings, data, &top_avg);
    
    printf("\nFinal Report:\n");
    printf("Sensor with the highest average temperature: Sensor %d with an average of %.2f\n", top_sensor, top_avg);
    
    return 0;
}