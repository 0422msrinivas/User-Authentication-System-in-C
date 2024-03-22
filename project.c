#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int menu();
void signup();
void login();
void forgot();
void change_password();
void delete_account();

struct account
{
    char first_name[20];
    char last_name[20];
    char username[30];
    char phone[15];
    char gender;
    char pass1[20];
};

void divider()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
}

int main()
{
    int isRunning = 1; // Variable to control the loop

    while (isRunning)
    {
        system("cls");
        switch (menu())
        {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;
        case 3:
            forgot();
            break;
        case 4:
            change_password();
            break;
        case 5:
            delete_account();
            break;
        case 6:
            isRunning = 0; // Set isRunning to false to exit the loop
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}

int menu()
{
    int c;
    printf("\n******MAIN MENU******\n");
    divider();
    printf("\n1.SIGNUP\n");
    printf("2.LOGIN\n");
    printf("3.FORGOT PASSOWRD OR USERNAME\n");
    printf("4.CHANGE PASSWORD\n");
    printf("5.DELETE ACCOUNT\n");
    printf("6.EXIT\n");
    divider();
    printf("\nEnter your choice : ");
    scanf("%d", &c);
    return c;
}

void takepassword(char pass[20])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            pass[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 9 || ch == 32)
        {
            continue;
        }
        else
        {
            pass[i++] = ch;
            printf("*");
        }
    }
}

void signup()
{
    system("cls");
    struct account u;
    char pass2[20];

    printf("CREATING NEW ACCOUNT \n");
    divider();
    printf("\nEnter your first name : ");
    scanf("%s", u.first_name);
    for (int i = 0; u.first_name[i] != '\0'; i++)
    {
        if (!isalpha(u.first_name[i]))
        {
            printf("Invalid enter data ");
            return;
        }
    }
    printf("Enter last name : ");
    scanf("%s", u.last_name);
    for (int i = 0; u.last_name[i] != '\0'; i++)
    {
        if (!isalpha(u.last_name[i]))
        {
            printf("Invalid enter data ");
            return;
        }
    }
    printf("Enter your username : ");
    scanf("%s", u.username);
    printf("Enter your phone number : ");
    scanf("%s", u.phone);
    int d = strlen(u.phone);
    for (int i = 0; u.phone[i] != '\0'; i++)
    {
        if (!(u.phone[i] >= '0' && u.phone[i] <= '9'))
        {
            printf("Invalid enter data ");
            return;
        }
    }
    fflush(stdin);
    printf("Enter Gender (M/F): ");
    scanf("%c", &u.gender);
    if (!(u.gender == 'M' || u.gender == 'm' || u.gender == 'F' || u.gender == 'f'))
    {
        printf("Invalid gender input ");
        return;
    }
    printf("Enter password : ");
    takepassword(u.pass1);

    printf("\nConfirm password : ");
    takepassword(pass2);

    if (strcmp(u.pass1, pass2))
    {
        printf("Passwords do not match\n\n");
        return;
    }
    else
    {
        FILE *fp = fopen("account.txt", "a"); // Open file in append mode
        if (fp == NULL)
        {
            printf("Error opening file.\n");
            return;
        }
        fwrite(&u, sizeof(struct account), 1, fp); // Write account information to file
        fclose(fp);                                // Close file
        printf("\n\nACCOUNT CREATED SUCCESSFULLY\n\n");
        getch();
    }
}

void login()
{
    system("cls");
    char user[30], log_pass[20];
    struct account u;
    FILE *fp = fopen("account.txt", "r");

    printf("Enter Username : ");
    scanf("%s", user);
    printf("Enter Password : ");
    takepassword(log_pass);

    while (fread(&u, sizeof(struct account), 1, fp))
    {
        if (strcmp(user, u.username) == 0 && strcmp(log_pass, u.pass1) == 0)
        {
            printf("\n****WELCOME %s****\n", u.first_name);
            divider();
            printf("\nYour Details \n");
            divider();
            printf("\nUsername : %s\n", u.username);
            printf("First name : %s\n", u.first_name);
            printf("Last name : %s\n", u.last_name);
            printf("Phone number : %s\n", u.phone);
            printf("Gender : %c\n", u.gender);
            fclose(fp);
            getch();
            return;
        }
    }
    fclose(fp);
    printf("\nLOGIN FAILED! Please check your username and password.\n");
    getch();
}

void forgot()
{
    system("cls");
    struct account u;
    int choice;
    char username[30], password[20], phone[20];
    FILE *fp = fopen("account.txt", "r");

    printf("\n1.Search by Username\n");
    printf("2.Search by password\n");
    printf("3.Search by Phone no.\n");
    printf("4.MAIN MENU\n");
    divider();
    printf("\nEnter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Enter your Username : ");
        scanf("%s", username);
        break;

    case 2:
        printf("Enter your Password : ");
        scanf("%s", password);
        break;

    case 3:
        printf("Enter your Phone no. : ");
        scanf("%s", phone);
        break;

    case 4:
        return;

    default:
        printf("INVALID CHOICE\n");
        break;
    }

    printf("\nAccount Details\n");
    divider();

    while (fread(&u, sizeof(struct account), 1, fp))
    {
        if ((choice == 1 && strcmp(username, u.username) == 0) ||
            (choice == 2 && strcmp(password, u.pass1) == 0) ||
            (choice == 3 && strcmp(phone, u.phone) == 0))
        {
            printf("\nUsername : %s\n", u.username);
            printf("First name : %s\n", u.first_name);
            printf("Last name : %s\n", u.last_name);
            printf("Phone no. : %s\n", u.phone);
            printf("Gender : %c\n", u.gender);
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    printf("\nNo matching account found!\n");
    getch();
}

void change_password()
{
    system("cls");
    char user[30], log_pass[20], pass2[20];
    struct account u;
    FILE *fp = fopen("account.txt", "r+");

    printf("Enter Username : ");
    scanf("%s", user);
    printf("Enter Current Password : ");
    takepassword(log_pass);

    int found = 0;
    while (fread(&u, sizeof(struct account), 1, fp))
    {
        if (strcmp(user, u.username) == 0 && strcmp(log_pass, u.pass1) == 0)
        {
            printf("\nEnter new password : ");
            takepassword(u.pass1);

            printf("\nConfirm new password : ");
            takepassword(pass2);

            if (strcmp(u.pass1, pass2) != 0)
            {
                printf("Passwords do not match.\n");
            }
            else
            {
                fseek(fp, -sizeof(struct account), SEEK_CUR);
                fwrite(&u, sizeof(struct account), 1, fp);
                printf("\nPassword changed successfully!\n");
            }
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nUser not found or invalid password!\n");
    }
    fclose(fp);
    getch();
}

void delete_account()
{
    system("cls");
    char user[30], log_pass[20];
    struct account u;
    FILE *fp = fopen("account.txt", "r");

    printf("Enter Username : ");
    scanf("%s", user);
    printf("Enter Password : ");
    takepassword(log_pass);

    FILE *temp = fopen("temp.txt", "w");
    int found = 0;
    while (fread(&u, sizeof(struct account), 1, fp))
    {
        if (strcmp(user, u.username) == 0 && strcmp(log_pass, u.pass1) == 0)
        {
            found = 1;
            continue;
        }
        fwrite(&u, sizeof(struct account), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove("account.txt");
    rename("temp.txt", "account.txt");

    if (found)
    {
        printf("\nAccount deleted successfully!\n");
    }
    else
    {
        printf("\nUser not found or invalid password!\n");
    }
    getch();
}
