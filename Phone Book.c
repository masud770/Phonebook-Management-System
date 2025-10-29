#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>


int isValidEmail(char email[]) {
    int i, atPos = -1, dotPos = -1;
    int len = strlen(email);

    if (len < 5 || email[0] == '@')
        return 0;

    for (i = 0; i < len; i++) {
        char c = email[i];

        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '@' || c == '.' || c == '_'))
            return 0;

        if (c >= 'A' && c <= 'Z')
            return 0;

        if (c == '@') {
            if (atPos != -1) return 0;
            atPos = i;
        } else if (c == '.') {
            dotPos = i;
        }
    }

    if (atPos == -1 || dotPos == -1 || dotPos < atPos)
        return 0;

    if (len - dotPos < 3)
        return 0;

    return 1;
}


    struct person
    {
        char name[40];
        char address[50];
        char father_name[40];
        char mother_name[40];
        long int mble_no;
        char mail[100];
    };

// Function declarations
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

// Main function
    int main()
    {
        system("color 70");
        start();
        return 0;
    }

// Print header with a title
    void print_header(const char *header)
    {
        printf("\n\t\t\t=======================================\n");
        printf("\t\t\t\t%s\n", header);
        printf("\t\t\t=======================================\n");
    }

// Go back to menu
    void back()
    {
        start();
    }

// Start the program
    void start()
    {
        menu();
    }

// Main menu
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
            system("cls");
            print_header("Exiting...");
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
            printf("\n\t\tInvalid choice!");
            getch();
            menu();
        }
    }

// Add new record
    void addrecord()
    {
        FILE *f;
        struct person p;
        f = fopen("phonebook.dat", "ab+");
        if (f == NULL)
        {
            printf("\nError opening file!");
            exit(1);
        }

        system("cls");
        print_header("Add New Contact");

        printf("\nEnter name: ");
        got(p.name);
        printf("\nEnter address: ");
        got(p.address);
        printf("\nEnter father's name: ");
        got(p.father_name);
        printf("\nEnter mother's name: ");
        got(p.mother_name);
        printf("\nEnter phone number: ");
        scanf("%ld", &p.mble_no);
        fflush(stdin);

        do
        {
            printf("\nEnter e-mail: ");
            got(p.mail);
            if (!isValidEmail(p.mail))
                printf("\nInvalid email format! Please try again.\n");
        }  while (!isValidEmail(p.mail));


        fwrite(&p, sizeof(p), 1, f);
        fclose(f);

        printf("\n\nRecord added successfully!");
        printf("\nPress any key to return to menu...");
        getch();
        menu();
    }

// List all records
    void listrecord()
    {
        struct person p;
        FILE *f;
        f = fopen("phonebook.dat", "rb");
        if (f == NULL)
        {
            printf("\nNo records found!");
            getch();
            menu();
        }

        system("cls");
        print_header("All Contacts");

        while (fread(&p, sizeof(p), 1, f) == 1)
        {
            printf("\nName: %s", p.name);
            printf("\nAddress: %s", p.address);
            printf("\nFather's Name: %s", p.father_name);
            printf("\nMother's Name: %s", p.mother_name);
            printf("\nMobile No: %ld", p.mble_no);
            printf("\nE-mail: %s\n", p.mail);
            printf("---------------------------------------\n");
        }
        fclose(f);
        printf("\nPress any key to return to menu...");
        getch();
        menu();
    }

// Modify record
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
            menu();
        }

        system("cls");
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
                fflush(stdin);


                do
                    {
                        printf("\nEnter new email: ");
                        got(s.mail);
                        if (!isValidEmail(s.mail))
                            printf("\nInvalid email format! Please try again.\n");
                    } while (!isValidEmail(s.mail));


                fseek(f, -sizeof(p), SEEK_CUR);
                fwrite(&s, sizeof(p), 1, f);
                flag = 1;
                break;
            }
        }

        fclose(f);

        if (flag == 1)
            printf("\n\t\t**Contact modified successfully!**\n");
        else
            printf("\n\t\t**Contact not found!**\n");

        printf("\nPress any key to return to menu...");
        getch();
        menu();
    }

// Delete record
    void deleterecord()
    {
        struct person p;
        FILE *f, *ft;
        int flag = 0;
        char name[50];

        f = fopen("phonebook.dat", "rb");
        if (f == NULL)
        {
            printf("\n\t\t**No records found!**\n");
            getch();
            menu();
            return;
        }

        ft = fopen("temp.dat", "wb");
        if (ft == NULL)
        {
            printf("\n\t\t**Temporary file could not be created!**\n");
            fclose(f);
            getch();
            menu();
            return;
        }

        system("cls");
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

        if (flag == 1)
        {
            remove("phonebook.dat");
            rename("temp.dat", "phonebook.dat");
            printf("\n\t\t**Contact deleted successfully!**\n");
        }
        else
        {
            printf("\n\t\t**No contact found with that name!**\n");
        }

        printf("\nPress any key to return to menu...");
        getch();
        menu();
    }

// Search record
    void searchrecord()
    {
        struct person p;
        FILE *f;
        char name[50];
        int flag = 0;

        f = fopen("phonebook.dat", "rb");
        if (f == NULL)
        {
            printf("\n\t\t**No records found!**\n");
            getch();
            menu();
            return;
        }

        system("cls");
        print_header("Search Contact");
        printf("\nEnter name to search: ");
        got(name);

        while (fread(&p, sizeof(p), 1, f) == 1)
        {
            if (strcmp(p.name, name) == 0)
            {
                printf("\nName: %s", p.name);
                printf("\nAddress: %s", p.address);
                printf("\nFather's Name: %s", p.father_name);
                printf("\nMother's Name: %s", p.mother_name);
                printf("\nMobile No: %ld", p.mble_no);
                printf("\nE-mail: %s\n", p.mail);
                flag = 1;
                break;
            }
        }

        if (flag == 0)
            printf("\n\t\t**Contact not found!**\n");

        fclose(f);
        printf("\nPress any key to return to menu...");
        getch();
        menu();
    }

// Safe input function (with backspace support)
    void got(char *name)
    {
        int i = 0;
        char c;
        do
        {
            c = getchar();
            if (c != '\n' && c != '\r')
            {
                name[i++] = c;
            }

        }
        while (c != '\n' && c != '\r');
        name[i] = '\0';
    }
