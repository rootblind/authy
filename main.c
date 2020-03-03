#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char user[1000],pass[1000];

void anticracker()
{
    system("cls");
    while(1)
    {
        printf("TOO MANY ATTEMPTS, CLOSE THE APPLICATION AND TRY AGAIN!\n");
        Sleep(1000);
    }
}

// crypting function
void enc()
{
    char text_dec[100000] = "";
    int i = 0;
    for(i = 0; i < strlen(pass); i++)
        if(pass[i] >= 'A' && pass[i] <= 'Z')
            text_dec[i] = 'Z' - pass[i] + 'A';
        else if(pass[i] >= 'a' && pass[i] <= 'z')
            text_dec[i] = 'z' - pass[i] + 'a';
            else if(pass[i] >= '0' && pass[i] <= '9')
                    text_dec[i] = '9' - pass[i] + '0';
    text_dec[i] = NULL;
    strcpy(pass,text_dec);
}

void login()
{
    system("cls");
    printf("============================ LOGIN ============================\n");
    printf("If you fail to login in 4 attempts, the application will break!\n\n");

    char true_user[1000],true_pass[1000];
    unsigned wrongpass,attempts = 4,wronguser;

    do//if the user exists
    {
        wronguser = 1;
        unsigned illegal_c;
        do//if the text has illegal characters
        {
            illegal_c = 0;
            do//if the text has at least 6 characters
            {
                printf("Username: ");scanf("%s",&user);
                if(strlen(user) < 6)
                    printf("Too few characters!\n");

            }while(strlen(user) < 6);

             for(int i = 0; i < strlen(user) && !illegal_c; i++)//se cauta caractere nepermise
                if((user[i] < 'a' || user[i] > 'z') && (user[i] < 'A' || user[i] > 'Z') && (user[i] < '0' || user[i] > '9'))
                    {
                        printf("You must use only letters A - z or digits 0 - 9!\n");
                        illegal_c = 1;
                    }
        }while(illegal_c);

        FILE *acclistusers = fopen("acc\\acclist","r");
        while(fgets(true_user,999,acclistusers) && wronguser)
        {
            true_user[strlen(true_user) - 1] = NULL;
            if(strcmp(user,true_user) == 0)
                wronguser = 0;
        }
        fclose(acclistusers);

        if(wronguser)
        {
            attempts--;
            printf("The username is incorrect!\n");
        }
    }while(wronguser && attempts);

    if(!attempts)
        anticracker();

    do//if the pass is right
    {
        wrongpass = 1;
        unsigned illegal_c;
        do
        {
            illegal_c = 0;
            do
            {
                printf("Password: ");scanf("%s",&pass);
                if(strlen(pass) < 6)
                    printf("Too few characters!\n");

            }while(strlen(pass) < 6);

            for(int i = 0; i < strlen(pass) && !illegal_c; i++)//se cauta caractere nepermise
            if((pass[i] < 'a' || pass[i] > 'z') && (pass[i] < 'A' || pass[i] > 'Z') && (pass[i] < '0' || pass[i] > '9'))
                {
                    printf("You must use only letters A - z or digits 0 - 9!\n");
                    illegal_c = 1;
                }

        }while(illegal_c);

        char pathing_to_pass[100];
        strcpy(pathing_to_pass,"acc\\");
        strcat(pathing_to_pass,user);
        FILE *accpasswordcheck = fopen(pathing_to_pass,"r");
        enc();
        while(fgets(true_pass,999,accpasswordcheck) && wrongpass)
        {
            true_pass[strlen(true_pass) - 1] = NULL;
            if(strcmp(pass,true_pass) == 0)
                wrongpass = 0;
        }
        fclose(accpasswordcheck);

        if(wrongpass)
        {
            printf("The password is incorrect!\n");
            attempts--;
        }

    }while(wrongpass && attempts);

    if(!attempts)
        anticracker();
}

void sign_in()
{
    system("cls");
    printf("============================ SIGN IN ============================\n");
    printf("Only digits and letters!\nAt least 6 characters!\n\n");
    unsigned exists;//determins if the username already exists
    do{//USERNAME
        unsigned illegal_c;//determins if the text has illegal characters

        exists  = 0;
        do{
            illegal_c = 0;
            do{
                printf("Username: ");scanf("%s",&user);
                if(strlen(user) < 6)
                    printf("Too few characters!\n");
            }while(strlen(user) < 6);//minimum lenght is 6 characters

            for(int i = 0; i < strlen(user) && !illegal_c; i++)//searching for illegal characters
                if((user[i] < 'a' || user[i] > 'z') && (user[i] < 'A' || user[i] > 'Z') && (user[i] < '0' || user[i] > '9'))
                    {
                        printf("You must use only letters A - z or digits 0 - 9!\n");
                        illegal_c = 1;
                    }

        }while(illegal_c);
        //searching if this username exists
        FILE *acclist = fopen("acc\\acclist","r");
        char reading_user[1000];
        while(fgets(reading_user,999,acclist) != NULL && !exists)
        {
            reading_user[strlen(reading_user) - 1] = NULL;
            if(strcmp(reading_user,user) == 0)
            {
                exists = 1;
                printf("The username is already in use!\n");
            }
        }
        fclose(acclist);

    }while(exists);


    unsigned illegal_c;
    do{
        illegal_c = 0;
        do{
            printf("Password: ");scanf("%s",&pass);
            if(strlen(pass) < 6)
                printf("Too few characters!\n");
        }while(strlen(pass) < 6);

        for(int i = 0; i < strlen(pass) && !illegal_c; i++)
            if((pass[i] < 'a' || pass[i] > 'z') && (pass[i] < 'A' || pass[i] > 'Z') && (pass[i] < '0' || pass[i] > '9'))
                {
                    printf("You must use only letters A - z or digits 0 - 9!\n");
                    illegal_c = 1;
                }

    }while(illegal_c);

    FILE *acclist = fopen("acc\\acclist","a");
    fprintf(acclist,"%s\n",user);
    fclose(acclist);
    //creating the pathing
    char path_to_pass[1000];
    strcpy(path_to_pass,"acc\\");
    strcat(path_to_pass,user);
    FILE *newacc = fopen(path_to_pass,"a");
    enc();
    fprintf(newacc,"%s\n",pass);
    fclose(newacc);

    login();

}

int main()
{
    system("color c");
    DIR* dir = opendir("acc");
    if (!dir)
        system("mkdir acc");
    unsigned select;
    do{
        system("cls");
        printf("============================ Protected by  A U T H Y ============================\n");
        printf("This application requires an account!\n\n\n");
        printf("[1] LOGIN\n");
        printf("[2] NEW USER\n");
        printf("Choose: ");scanf("%u",&select);
    }while(select != 1 && select != 2);
    switch(select)
    {
    case 1:
        login();
        break;
    case 2:
        sign_in();
        break;
    }


    return 0;
}
