#include <stdio.h>

void displayMenu()
{
    printf("\n--- University Library Management System ---\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    printf("\nEnter member name: ");
    scanf(" %[^\n]", name);
    
    printf("Enter student ID: ");
    scanf("%d", studentID);
    
    printf("Enter membership type (1 for Student, 2 for Faculty): ");
    scanf("%d", memberType);
    
    while (*memberType != 1 && *memberType != 2)
    {
        printf("Invalid choice! Enter 1 for Student or 2 for Faculty: ");
        scanf("%d", memberType);
    }
    
    printf("Member registered successfully!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks)
{
    printf("\n--- Available Books ---\n");
    printf("ID\tTitle\t\t\t\tAvailable Copies\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < totalBooks; i++)
    {
        printf("%d\t%-30s\t%d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType)
{
    if (*borrowedCount >= 3)
    {
        printf("Borrowing limit reached! A member can borrow a maximum of 3 books at a time.\n");
        return;
    }
    
    int id, days;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    
    int bookIndex = -1;
    for (int i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1)
    {
        printf("Invalid book ID!\n");
        return;
    }
    
    if (availableCopies[bookIndex] <= 0)
    {
        printf("Sorry, no copies are available for this book!\n");
        return;
    }
    
    printf("Enter number of days you intend to keep the book: ");
    scanf("%d", &days);
    
    while (days <= 0)
    {
        printf("Days must be positive. Re-enter number of days: ");
        scanf("%d", &days);
    }
    
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[bookIndex]--;
    
    printf("Book borrowed successfully!\n");
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine)
{
    if (*borrowedCount == 0)
    {
        printf("You have not borrowed any books!\n");
        return 0;
    }
    
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    
    int pos = -1;
    for (int i = 0; i < *borrowedCount; i++)
    {
        if (borrowedBookIDs[i] == id)
        {
            pos = i;
            break;
        }
    }
    
    if (pos == -1)
    {
        printf("Error: You have not borrowed this book!\n");
        return 0;
    }
    
    int actualDays;
    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &actualDays);
    
    while (actualDays <= 0)
    {
        printf("Days must be positive. Re-enter days: ");
        scanf("%d", &actualDays);
    }
    
    int allowedDays = (memberType == 1) ? 14 : 30;
    float currentFine = 0;
    
    if (actualDays > allowedDays)
    {
        int extraDays = actualDays - allowedDays;
        float rate = (memberType == 1) ? 20.0 : 10.0;
        currentFine = extraDays * rate;
    }
    
    float payableFine = currentFine;
    if (currentFine > 0)
    {
        char code[20];
        printf("Enter membership code (or type NONE): ");
        scanf("%s", code);
        
        int match = 1;
        char target[] = "LIB2026";
        for (int i = 0; target[i] != '\0' || code[i] != '\0'; i++)
        {
            if (code[i] != target[i])
            {
                match = 0;
                break;
            }
        }
        
        if (match)
        {
            payableFine = currentFine * 0.5;
            printf("Membership code correct! 50%% waiver applied.\n");
        }
        else
        {
            printf("Incorrect code. No waiver applied.\n");
        }
    }
    
    *totalFine += currentFine;
    
    for (int i = 0; i < totalBooks; i++)
    {
        if (bookIDs[i] == id)
        {
            availableCopies[i]++;
            break;
        }
    }
    
    for (int i = pos; i < *borrowedCount - 1; i++)
    {
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    }
    (*borrowedCount)--;
    
    printf("Book returned successfully! Fine for this return: %.2f\n", payableFine);
    return payableFine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver)
{
    printf("\n--- Member Record ---\n");
    printf("Name: %s\n", name);
    printf("Student/Member ID: %d\n", studentID);
    printf("Membership Type: %s\n", (memberType == 1) ? "Student" : "Faculty");
    printf("Currently Borrowed Book IDs: ");
    if (borrowedCount == 0)
    {
        printf("None");
    }
    else
    {
        for (int i = 0; i < borrowedCount; i++)
        {
            printf("%d ", borrowedBookIDs[i]);
        }
    }
    printf("\nTotal Fine Charged (Before Waiver): %.2f\n", totalFine);
    printf("Final Fine Payable (After Waiver): %.2f\n", fineAfterWaiver);
}

int main()
{
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {"C Programming", "Data Structures", "Database Systems", "Operating Systems", "Computer Networks"};
    int availableCopies[5] = {3, 2, 4, 1, 5};
    int totalBooks = 5;
    
    char name[50] = "Not Registered";
    int studentID = 0;
    int memberType = 1;
    
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0;
    float fineAfterWaiver = 0;
    
    int choice;
    do
    {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4:
                {
                    float lastFine = returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                    fineAfterWaiver += lastFine;
                }
                break;
            case 5:
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please select between 1 and 6.\n");
        }
    } while (choice != 6);
    
    return 0;
}