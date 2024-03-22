#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
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
  //  char DOB[10];
    char pass1[20];
    char pass2[20];
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
    while (1)
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
            exit(0);

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
{ int s1;
    struct account u;
    Label:system("cls");
    char pass2[20];
    printf("CREATING NEW ACCOUNT \n");
    divider();
    printf("\nENTER your first name : ");
    scanf("%s", u.first_name);
    for(int i=0;u.first_name[i]!='\0';i++){
    if(!isalpha(u.first_name[i])){
        printf("Invalid enter data ");
        goto Label;
        return;
    }
 }
    printf("Enter last name : ");
    scanf("%s", u.last_name);
    for(int i=0;u.last_name[i]!='\0';i++){
    if(!isalpha(u.last_name[i])){
        printf("Invalid enter data ");
        goto Label;
        return;
    }
 }
    printf("Enter your username : ");
    scanf("%s", u.username);
    printf("Enter your phone number : ");
    scanf("%s", u.phone);
    int d=strlen(u.phone);
    // if(!(d>=10 && d<=12))
    // goto Label;
    for(int i=0;u.phone[i]!='\0';i++){
    if(!(u.phone[i]>='0' && u.phone[i]<='9')){
        printf("Invalid enter data ");
        goto Label;
        return;
    }
 }
    fflush(stdin);
    printf("Enter Gender (M/F): ");
    scanf("%c", &u.gender);
    if(!(u.gender=='M' || u.gender=='m' || u.gender=='F' || u.gender=='f')){
        goto Label;
    }
   // printf("Enter your DOB (dd/mm/yyyy): ");
    //scanf("%s", u.DOB);
   // int dd=(u.DOB[0]-'0')*10+(u.DOB[1]-'0');
    //if(!(dd>=1 && dd<=30)){
      //  goto Label;
    //}
    //int mm=(u.DOB[3]-'0')*10+(u.DOB[4]-'0');
    //if(!(mm>=1 && mm<=12))
   // goto Label;
    //int yy=(u.DOB[6]-'0')*1000+(u.DOB[7]-'0')*100+(u.DOB[8]-'0')*10+(u.DOB[9]-'0');
    //if(!(yy>2023 && yy<1923))
    //goto Label;
    printf("Enter password : ");
    takepassword(u.pass1);

conf_pass:
    printf("\nConfirm password : ");
    takepassword(u.pass2);

    if (strcmp(u.pass1, u.pass2))
    {
        printf("INCORRECT PASSWORD \n\n");
        goto conf_pass;
    }
    else
    {
        printf("\n\nACCOUNT CREATED SUCCESSFULLY\n\n");
        getch();

        FILE *fp = fopen("account.txt", "w");
        fwrite(&u, sizeof(struct account), 1, fp);
        fclose(fp);
    }
}

void login()
{
    system("cls");
    char user[30], log_pass[20];

    struct account u;
    FILE *fp = fopen("account.txt", "r");
    fread(&u, sizeof(struct account), 1, fp);

name:
    printf("enter Username : ");
    scanf("%s", user);
    if (strcmp(u.username, user))
    {
        printf("\nPLEASE ENTER CORRECT USERNAME\n ");
        goto name;
    }

    else
    {
    logpass:
        printf("Enter password : ");
        takepassword(log_pass);
        if (strcmp(u.pass1, log_pass))
        {
            printf("\nINCORRET PASSWORD \n");
            goto logpass;
        }
        else
        {
            system("cls");
            printf("\n****WELCOME %s****\n", u.first_name);
            divider();

            printf("\nYour Details \n");
            divider();
            printf("\nUsername : %s\n", u.username);
            printf("first name : %s\n", u.first_name);
            printf("Last name : %s\n", u.last_name);
            printf("phone number : %s\n", u.phone);
            printf("Gender : %c\n", u.gender);
            printf("Password : %s\n", u.pass1);
        }
        getch();
    }
    fclose(fp);
}



void forgot()
{
    system("cls");
    struct account u;
    int choice;
    char username[20], password[20], phone[20];
    FILE *fp = fopen("Account.txt", "r");
    fread(&u, sizeof(struct account), 1, fp);

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
        if (strcmp(username, u.username))
        {
            printf("USERNAME NOT FOUND !!");
            getch();
        }
        else
        {
            printf("ACCOUNT FOUND!\n");
            divider();
            printf("\nUsername : %s \n", u.username);
            printf("First name : %s \n", u.first_name);
            printf("Last name : %s \n", u.last_name);
            printf("Phone no. : %s \n", u.phone);
            printf("Password : %s \n", u.pass1);
            getch();
        }

        break;

    case 2:
        printf("Enter your Passowrd : ");
        scanf("%s", password);
        if (strcmp(password, u.pass1))
        {
            printf("ACCOUNT NOT FOUND !!");
            getch();
        }
        else
        {
            printf("ACCOUNT FOUND!\n");
            divider();
            printf("\nUsername : %s \n", u.username);
            printf("First name : %s \n", u.first_name);
            printf("Last name : %s \n", u.last_name);
            printf("Phone no. : %s \n", u.phone);
            printf("Password : %s \n", u.pass1);
            getch();
        }

        break;

    case 3:
        printf("Enter your Phone no. : ");
        scanf("%s", phone);
        if (strcmp(phone, u.phone))
        {
            printf("\nACCOUNT NOT FOUND !!");
            getch();
        }
        else
        {
            printf("ACCOUNT FOUND!\n");
            divider();

            printf("\nUsername : %s \n", u.username);
            printf("First name : %s \n", u.first_name);
            printf("Last name : %s \n", u.last_name);
            printf("Phone no. : %s \n", u.phone);
            printf("Password : %s \n", u.pass1);
            getch();
        }

        break;
    case 4:
        return;

    default:
        printf("INVALID CHOICE\n");
        break;
    }

    fclose(fp);
}

void change_password()
{
    system("cls");

    int num1, num2;
    srand(time(0));

number:
    num1 = rand();
    printf("\nThe random number is %d\n", num1);

    printf("Enter the above number : ");
    scanf("%d", &num2);
    if (num1 == num2)
    {
        struct account u;
        char pass2[20];

        FILE *fp = fopen("Account.txt", "r");
        fread(&u, sizeof(u), 1, fp);

        printf("Enter new password : ");
        takepassword(u.pass1);
    pas:
        printf("\nConfirm new password :");
        scanf("%s", pass2);
        if (strcmp(u.pass1, pass2))
        {
            printf("*INCORRECT PASSWORD**\nPlease try again.....\n");
            goto pas;
        }
        else
        {
            fp = fopen("Account.txt", "w");
            fwrite(&u, sizeof(u), 1, fp);
            printf("***PASSWORD CHANGE SUCCESSFULLY***");
            getch();
        }
        fclose(fp);
    }

    else
    {
        printf("Please input the correct number\n");
        goto number;
    }
}

void delete_account()
{

    FILE *fp = fopen("account.txt", "r");

    printf("ARE YOU SURE[Y/N] : ");
    char ch = getche();
    if (ch == 'Y' || ch == 'y')
    {
        fp = fopen("account.txt", "w");
        fprintf(fp, " ");
        printf("\nACCOUNT DELETED SUCCESSFULLY\n");
        getch();
    }

    else if (ch == 'N' || ch == 'n')
    {
        printf("\nACCOUNT DELETION STOPPED\n");
        getch();
    }
}