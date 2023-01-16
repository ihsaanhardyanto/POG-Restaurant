#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 256

struct menuList
{
    char name[MAX];
    int price;
} list[MAX];

struct saveOrder
{
    char name[MAX];
    int price;
    int total;
} saveOrder[MAX];

int comparator(const void *a, const void *b)
{
    struct menuList *listA = (struct menuList *)a;
    struct menuList *listB = (struct menuList *)b;

    return strcmp(listA->name, listB->name);
}

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
    while (fgets(buff, MAX, fr) != NULL)
    {
        char *token = strtok(buff, "#");
        strcpy(list[count].name, token);
        token = strtok(NULL, "\n");
        list[count].price = atoi(token);
        count++;
    }
    fclose(fr);

    qsort(list->name, count, sizeof(struct menuList), comparator);

    int count2 = 0;
    printf(" _________________________________________\n");
    printf("| %-3s | %-20s | %-10s |\n", "No", "Name", "Price");
    printf("|_____|______________________|____________|\n");
    while (count > 0)
    {
        printf("| %-3d | %-20s | %-10d |\n", count2 + 1, list[count2].name, list[count2].price);
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
    printf("Press ENTER to continue...");
    getchar();
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
    scanf("%d", &menu);
    getchar();

    return menu;
}

void order()
{
    int pilihan;
    int count2 = 0;
    readMenu();
    printf("Type your order(1-8)\n");
    printf("press '0' to go back\n");
    printf(">> ");
    /* Ini salah, tinggal pindahin saveOrder yang dipilih */
    while (pilihan != 0)
    {
        scanf("%d", &pilihan);
        getchar();
        if (pilihan == 1)
        {
            strcpy(saveOrder[0].name, list[0].name);
            saveOrder->total += 10000;
        }
        if (pilihan == 2)
        {
            saveOrder->total += 15000;
        }
        if (pilihan == 3)
        {
            saveOrder->total += 18000;
        }
        if (pilihan == 4)
        {
            saveOrder->total += 13000;
        }
        if (pilihan == 5)
        {
            saveOrder->total += 10000;
        }
        if (pilihan == 6)
        {
            saveOrder->total += 12000;
        }
        if (pilihan == 7)
        {
            saveOrder->total += 20000;
        }
        if (pilihan == 8)
        {
            saveOrder->total += 18000;
        }
    }
}

void readOrder()
{
    // Kosong
}

void cart()
{
    int count = 0;
    int pilihan, jmlhByr;
    int count2 = 0;
    readOrder();
    printf(" _________________________________________\n");
    printf("| %-3s | %-20s | %-10s |\n", "No", "Name", "Price");
    printf("|_____|______________________|____________|\n");

    /* Line 172 - 179 belum selesai */
    while (count > 0)
    {
        printf("| %-3s | %-20s | %-10d |\n", count2 + 1, saveOrder[count2].name, saveOrder[count2].price);
        count--;
        count2++;
    }

    printf("|_____|______________________|____________|\n");
    printf("| %11s %16s %-10d |\n", "Total", "|", saveOrder->total);
    printf("|____________________________|____________|\n");
    printf("1. Pay\n");
    printf("2. Back\n");
    printf(">> ");
    scanf("%d", &pilihan);
    getchar();
    if(pilihan == 1)
    {
        printf("\nMasukan jumlah uang\n");
        printf(">> ");
        scanf("%d", &jmlhByr);
        if(saveOrder->total > jmlhByr)
            printf("Uang kamu tidak cukup\n");
        else
        {
            printf("Pembayaran berhasil!\n");
            if(jmlhByr > saveOrder->total)
            {
                saveOrder->total = jmlhByr - saveOrder->total;
                printf("Uang kamu sisa: Rp.%d\n", saveOrder->total);
            }
            saveOrder->total = 0;
        }
    }
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
    scanf("%d", &menu2);
    getchar();
    switch (menu2)
    {
    case 1:
    {
        //! Write this in separate function
        char name[MAX];
        char price[MAX];
        system("cls");
        printf("Menu Name: ");
        scanf("%[^\n]", name);
        getchar();
        printf("Menu Price: ");
        scanf("%s", price);
        getchar();
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
            cart();
            // TODO: Check ordered food and total price
            break;
        }

        case 3:
        {
            system("cls");
            // TODO: Add patorjk.com ascii text
            printf("Terimakasih sudah berkunjung!");
            getchar();
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