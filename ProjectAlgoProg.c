#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 256

struct menuList
{
    int no;
    char name[MAX];
    int price;
} list[MAX];

void welcome()
{
    puts(" __          __  _                          _ ");
    puts(" \\ \\        / / | |                        | |");
    puts("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| |");
    puts("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ |");
    puts("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/_|");
    puts("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___(_)");
}

void readMenu()
{
    FILE *fr;
    fr = fopen("Menu.txt", "r");

    if (!fr)
    {
        printf("ERROR!");
        return;
    }

    char buff[MAX];
    int count = 0;
    while (fgets(buff, MAX, fr) != NULL) {
        list[count].no = count+1;
        char * token = strtok(buff, "#");
        strcpy(list[count].name, token);
        token = strtok(NULL, "\n");
        list[count].price = atoi(token);
        count++;
    }
    fclose(fr);

    int count2 = 0;
    printf(" _________________________________________\n");
    printf("| %-3s | %-20s | %-10s |\n", "No", "Name", "Price");
    printf("|_____|______________________|____________|\n");
    while (count > 0)
    {
        printf("| %-3d | %-20s | %-10d |\n", list[count2].no, list[count2].name, list[count2].price);
        count--;
        count2++;
    }
    printf("|_____|______________________|____________|\n\n");
}

void writeMenu(char *name, char *price)
{
    FILE *fp;
    fp = fopen("Menu.txt", "a");

    if (!fp)
    {
        printf("ERROR!");
        return;
    }
    
    fprintf(fp, "%s#%s\n", name, price);
    fclose(fp);
    printf("Menu has been added\n");
    printf("Press ENTER to continue..."); getchar();
}

int mainMenu()
{
    int menu = 0;
    welcome();
    printf("\nXYZ Restaurant\n");
    printf("1. Menu\n");
    printf("2. Cart\n");
    printf("3. Exit\n");
    printf(">> ");
    scanf("%d", &menu); getchar();

    return menu;
}

void order()
{
    readMenu();
    printf("Type your order(1-8)\n");
    printf("press '0' to go back\n");
    printf(">> ");
    getchar();
}

void adminMenu()
{
    int menu2;
    system("cls");
    printf("Admin Menu\n");
    printf("1. Add Menu\n");
    printf("2. Remove Menu\n");
    printf("3. Exit\n");
    printf(">> ");
    scanf("%d", &menu2); getchar();
    switch (menu2)
    {
        case 1:
        {
            //! Write this in separate function
            char name[MAX];
            char price[MAX];
            system("cls");
            printf("Menu Name: ");
            scanf("%[^\n]", name); getchar();
            printf("Menu Price: ");
            scanf("%s", price); getchar();
            writeMenu(name, price);
            break;
        }
        
        case 2:
        {
            // TODO: Add option to remove menu
        }

        case 3:
        {
            // TODO: Go back to the main menu
        }

        default:
        {
            break;
        }
    }
}

int main()
{
    int menu;
    do
    {
        switch (mainMenu())
        {
            case 1:
            {
                system("cls");
                order();
                break;
            }
            
            case 2:
            {
                system("cls");
                // TODO: Check ordered food and total price
                break;
            }

            case 3:
            {
                system("cls");
                // TODO: Add patorjk.com ascii text
                printf("Terimakasih sudah berkunjung!"); getchar();
                break;
            }

            case 123:
            {
                adminMenu();
                break;
            }

            default:
            {
                //! Admin Menu is not finished, check the function
                break;
            }
        }
    } while (menu != 3);   
    return 0;
}