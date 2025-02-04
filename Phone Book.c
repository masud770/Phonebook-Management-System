#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

struct person
{
    char name[40];
    char address[50];
    char father_name[40];
    char mother_name[40];
    long int mble_no;
    char mail[100];
};

void menu();
void got(char *name);
void start();
void back();
void addrecord();
void listrecord();
void modifyrecord();
void deleterecord();
void searchrecord();
void print_header(const char *header);
int isValidEmail(char *email);

int main()
{
    system("color 70");
    start();
    return 0;
}

void print_header(const char *header)
{
    printf("\n\t\t\t=======================================\n");
    printf("\t\t\t\t%s\n", header);
    printf("\t\t\t=======================================\n");
}

void back()
{
    start();
}

void start()
{
    menu();
}

void menu()
{
    system("cls");
    print_header("WELCOME TO THE PHONEBOOK");

    printf("\n\t\t\t1. Add New\n");
    printf("\t\t\t2. List\n");
    printf("\t\t\t3. Exit\n");
    printf("\t\t\t4. Edit\n");
    printf("\t\t\t5. Search\n");
    printf("\t\t\t6. Delete\n");

    printf("\n\t\t\tEnter your choice (1-6): ");
    switch (getch())
    {
    case '1':
        addrecord();
        break;
    case '2':
        listrecord();
        break;
    case '3':
        exit(0);
        break;
    case '4':
        modifyrecord();
        break;
    case '5':
        searchrecord();
        break;
    case '6':
        deleterecord();
        break;
    default:
        system("cls");
        print_header("ERROR: Invalid choice");
        printf("\n\t\t\tPlease choose between 1 and 6.\n");
        getch();
        menu();
    }
}

void toLowerCase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void addrecord()
{
    system("cls");
    FILE *f;
    struct person p;
    f = fopen("phonebook.dat", "ab+");
    if (f == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    print_header("Add New Contact");
    printf("\nEnter Name: ");
    got(p.name);
    printf("\nEnter Address: ");
    got(p.address);
    printf("\nEnter Father's Name: ");
    got(p.father_name);
    printf("\nEnter Mother's Name: ");
    got(p.mother_name);
    int validPhone = 0;
    while (!validPhone)
    {
        printf("\nEnter Phone Number (must start with '0'): ");
        scanf("%ld", &p.mble_no);

        if (p.mble_no > 0 && (p.mble_no / 1000000000) == 0)
        {
            printf("Phone number must start with '0'. Please try again.\n");
        }
        else
        {
            validPhone = 1;
        }
    }

    int validEmail = 0;
    while (!validEmail)
    {
        printf("Enter Email (must be a Gmail address): ");
        got(p.mail);
        toLowerCase(p.mail);
        if (isValidEmail(p.mail))
        {
            validEmail = 1;
        }
        else
        {
            printf("\nPlease input a correct email address.\n");
        }
    }

    fwrite(&p, sizeof(p), 1, f);
    fflush(stdin);

    printf("\n\n\t\t***Record Saved Successfully!***\n");
    fclose(f);
    printf("\n\n**Press any key to return to the menu**");
    getch();
    system("cls");
    menu();
}

int isValidEmail(char *email)
{
    // Check if the email ends with @gmail.com
    int len = strlen(email);
    if (len < 10)
    {
        return 0; // Too short for a valid Gmail address
    }

    // Check if the last 10 characters are "@gmail.com"
    if (strcmp(email + len - 10, "@gmail.com") == 0)
    {
        return 1; // Valid Gmail address
    }

    return 0; // Invalid email
}

void listrecord()
{
    struct person p;
    FILE *f;
    f = fopen("phonebook.dat", "rb");
    if (f == NULL)
    {
        printf("\n\t\t**No records found!**\n");
        getch();
        system("cls");
        menu();
    }

    print_header("Contact List");
    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        printf("\n\nName: %s\n", p.name);
        printf("Address: %s\n", p.address);
        printf("Father's Name: %s\n", p.father_name);
        printf("Mother's Name: %s\n", p.mother_name);
        printf("Phone: %ld\n", p.mble_no);
        printf("Email: %s\n", p.mail);
        printf("----------------------------------------\n");

        getch();
        system("cls");
    }
    fclose(f);
    printf("\n**Press any key to return to the menu**");
    getch();
    system("cls");
    menu();
}

void searchrecord()
{
    struct person p;
    FILE *f;
    char name[100];

    f = fopen("phonebook.dat", "rb");
    if (f == NULL)
    {
        printf("\n\t\t**No records found!**\n");
        getch();
        system("cls");
        menu();
    }

    print_header("Search Contact");
    printf("\nEnter the name of the person to search: ");
    got(name);

    int found = 0;
    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        if (strcmp(p.name, name) == 0)
        {
            printf("\n\t\tDetails of %s:\n", name);
            printf("\nName: %s\n", p.name);
            printf("Address: %s\n", p.address);
            printf("Father's Name: %s\n", p.father_name);
            printf("Mother's Name: %s\n", p.mother_name);
            printf("Phone: %ld\n", p.mble_no);
            printf("Email: %s\n", p.mail);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n\t\t**No contact found with the name: %s**\n", name);
    }

    fclose(f);
    printf("\n**Press any key to return to the menu**");
    getch();
    system("cls");
    menu();
}

void deleterecord()
{
    struct person p;
    FILE *f, *ft;
    int flag = 0;
    char name[100];

    f = fopen("phonebook.dat", "rb");
    if (f == NULL)
    {
        printf("\n\t\t**No records found!**\n");
        getch();
        system("cls");
        menu();
    }

    ft = fopen("temp.dat", "wb+");
    if (ft == NULL)
    {
        printf("\n\t\t**Error opening temp file!**\n");
        exit(1);
    }

    print_header("Delete Contact");
    printf("\nEnter the name of the contact to delete: ");
    got(name);

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        if (strcmp(p.name, name) != 0)
        {
            fwrite(&p, sizeof(p), 1, ft);
        }
        else
        {
            flag = 1;
        }
    }

    fclose(f);
    fclose(ft);

    if (flag != 1)
    {
        printf("\n\t\t**No contact found to delete**\n");
    }
    else
    {
        remove("phonebook.dat");
        rename("temp.dat", "phonebook.dat");
        printf("\n\t\t**Contact deleted successfully!**\n");
    }

    printf("\n**Press any key to return to the menu**");
    getch();
    system("cls");
    menu();
}

void modifyrecord()
{
    struct person p, s;
    FILE *f;
    int flag = 0;
    char name[50];

    f = fopen("phonebook.dat", "rb+");
    if (f == NULL)
    {
        printf("\n\t\t**No records found!**\n");
        getch();
        system("cls");
        menu();
    }

    print_header("Modify Contact");
    printf("\nEnter the name of the contact to modify: ");
    got(name);

    while (fread(&p, sizeof(p), 1, f) == 1)
    {
        if (strcmp(name, p.name) == 0)
        {
            printf("\nEnter new name: ");
            got(s.name);
            printf("\nEnter new address: ");
            got(s.address);
            printf("\nEnter new father's name: ");
            got(s.father_name);
            printf("\nEnter new mother's name: ");
            got(s.mother_name);
            printf("\nEnter new phone number: ");
            scanf("%ld", &s.mble_no);
            printf("\nEnter new email: ");
            got(s.mail);

            fseek(f, -sizeof(p), SEEK_CUR);
            fwrite(&s, sizeof(p), 1, f);
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        printf("\n\t\t**Contact modified successfully!**\n");
    }
    else
    {
        printf("\n\t\t**Contact not found!**\n");
    }

    fclose(f);
    printf("\n**Press any key to return to the menu**");
    getch();
    system("cls");
    menu();
}

void got(char *name)
{
    int i = 0, j;
    char c, ch;
    do
    {
        c = getch();
        if (c != 8 && c != 13)
        {
            *(name + i) = c;
            putch(c);
            i++;
        }
        else if (c == 8 && i > 0)
        {
            i--;
            printf("\b \b");
        }
    }
    while (c != 13);
    *(name + i) = '\0';
}
