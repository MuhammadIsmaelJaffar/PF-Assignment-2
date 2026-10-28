#include <stdio.h>

int main()
{
    int rows, cols;
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    
    printf("Enter number of seats per row: ");
    scanf("%d", &cols);
    
    int seats[100][100];
    
    printf("Enter seating status (0 for available, 1 for booked):\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("Seating Status for seat %d in row %d: ", j, i);
            scanf("%d", &seats[i][j]);
        }
    }
    
    printf("\nSeating Arrangement:\n");
    printf("  ");
    for (int j = 0; j < cols; j++)
    {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < rows; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("X ");
            }
        }
        printf("\n");
    }
    
    printf("\nSeat Availability Report:\n");
    int total_available = 0;
    for (int i = 0; i < rows; i++)
    {
        int row_available = 0;
        for (int j = 0; j < cols; j++)
        {
            if (seats[i][j] == 0)
            {
                row_available++;
            }
        }
        printf("Row %d: %d available seats\n", i, row_available);
        total_available += row_available;
    }
    printf("Total available seats in hall: %d\n", total_available);
    
    int k;
    printf("\nEnter number of customers who want to sit together (k): ");
    scanf("%d", &k);
    
    if (k <= 0 || k > cols)
    {
        printf("Invalid group size!\n");
        return 0;
    }
    
    int mid_row = rows / 2;
    int found = 0;
    int allocated_row = -1;
    int start_seat = -1;
    
    for (int d = 0; d < rows; d++)
    {
        int row_indices[2];
        int count = 0;
        
        int r1 = mid_row - d;
        int r2 = mid_row + d;
        
        if (d == 0)
        {
            if (r1 >= 0 && r1 < rows)
            {
                row_indices[count++] = r1;
            }
        }
        else
        {
            if (r1 >= 0 && r1 < rows)
            {
                row_indices[count++] = r1;
            }
            if (r2 >= 0 && r2 < rows && r2 != r1)
            {
                row_indices[count++] = r2;
            }
        }
        
        for (int idx = 0; idx < count; idx++)
        {
            int r = row_indices[idx];
            int consecutive = 0;
            
            for (int j = 0; j < cols; j++)
            {
                if (seats[r][j] == 0)
                {
                    consecutive++;
                    if (consecutive == k)
                    {
                        allocated_row = r;
                        start_seat = j - k + 1;
                        found = 1;
                        break;
                    }
                }
                else
                {
                    consecutive = 0;
                }
            }
            
            if (found)
            {
                break;
            }
        }
        
        if (found)
        {
            break;
        }
    }
    
    if (found)
    {
        printf("\nBooking successful!\n");
        printf("Allocated Row: %d\n", allocated_row);
        printf("Allocated Seats: ");
        for (int j = start_seat; j < start_seat + k; j++)
        {
            seats[allocated_row][j] = 1;
            printf("%d ", j);
        }
        printf("\n");
        
        printf("\nUpdated Seating Arrangement:\n");
        printf("  ");
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", j);
        }
        printf("\n");
        
        int remaining_available = 0;
        for (int i = 0; i < rows; i++)
        {
            printf("%d ", i);
            for (int j = 0; j < cols; j++)
            {
                if (seats[i][j] == 0)
                {
                    printf("_ ");
                    remaining_available++;
                }
                else
                {
                    printf("X ");
                }
            }
            printf("\n");
        }
        
        printf("Remaining available seats in hall: %d\n", remaining_available);
    }
    else
    {
        printf("\nNo suitable block of %d consecutive available seats found. Seating plan remains unchanged.\n", k);
    }
    
    return 0;
}