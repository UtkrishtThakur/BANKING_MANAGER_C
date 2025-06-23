#include <stdio.h>
#include <string.h>
#include <windows.h>
void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void wait_animation();

typedef struct
{
    char name[50];
    int acc_no;
    float balance;
} account;

int main()
{
    int choice;
    while (1)
    {
        printf("\n\n\n ***Bank management system*** \n");
        printf("1. Create account \n");
        printf("2. Deposit money \n");
        printf("3. Withdraw money \n");
        printf("4. Check balance  \n");
        printf("5. Exit \n");
        printf("State your choice \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("Exiting system....\n");
            return 0;
            break;

        default:
            printf("Invalid choice");
            break;
        }
    }
}
// ...existing code...
void create_account()
{
    FILE *file = fopen("account.dat", "ab+");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }

    account acc;
    printf("\n\n Enter your name: ");
    fflush(stdin); // Add this line to clear the input buffer (Windows-specific)
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';
    printf("\n Enter your acc number: ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0.0;
    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    wait_animation();
    printf("\n");
    printf("\n Account created successfully \n");
}
// ...existing code...
void deposit_money()
{
   FILE *file =fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }
    int acc_no;
    account acc_read;
    printf("\n Enter your account number: ");
    scanf("%d", &acc_no);
     wait_animation();
    
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_no == acc_read.acc_no)
        {
            float deposit_amount;
            printf("\n Enter the amount to deposit: ");
            scanf("%f", &deposit_amount);
            acc_read.balance += deposit_amount;
            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
           
            printf("\n\n Deposit successful! New balance: %.2f\n", acc_read.balance);
            return;
        }
    }
    
    printf("\n Account not found \n");
    fclose(file);
}



void withdraw_money()
{
    FILE *file = fopen("account.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }
    int acc_no;
    account acc_read;
    printf("\n Enter your account number: ");
    scanf("%d", &acc_no);
    
    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_no == acc_read.acc_no)
        {
            float withdraw_amount;
            printf("\n Enter the amount to withdraw: ");
           
            scanf("%f", &withdraw_amount);
             wait_animation();
            if (withdraw_amount > acc_read.balance)
            {
                printf("\n Insufficient balance \n");
                fclose(file);
                return;
            }
            acc_read.balance -= withdraw_amount;
            fseek(file, -sizeof(acc_read), SEEK_CUR);
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);

            printf("\n Withdrawal successful! New balance: %.2f\n", acc_read.balance);
            return;
        }
    }
    
    printf("\n Account not found \n");
    fclose(file);
}
void check_balance()
{
    FILE *file = fopen("account.dat", "rb");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }
    int acc_no;
    account acc_read;
    printf(" \n Enter your account number: ");
    scanf("%d", &acc_no);
    wait_animation();

    while (fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if (acc_no == acc_read.acc_no)
        {
            printf("\n Your account was found your balance is : %0.2f", acc_read.balance);
            fclose(file);
            return;
        }
        
    }
    printf("\n Account not found \n");
    fclose(file);
    return;
    
   
}


void wait_animation()
{
    printf("\n Wait, It will only take a few seconds");
    for (int i = 0; i < 5; i++)
    {
       printf(".");
       Sleep(1000);
    }
    
}