#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

#define MAX 255

struct menuList
{
    char name[MAX];
    int price;
} list[MAX];

struct saveOrder
{
    char name[MAX];
    int price;
} saveOrder[MAX];

int comparator(const void *a, const void *b)
{
    struct menuList *listA = (struct menuList *)a;
    struct menuList *listB = (struct menuList *)b;

    return strcmp(listA->name, listB->name);
}

int stringComparator(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

char *strcasestr(const char *str, const char *pattern) {
    size_t i;

    if (!*pattern) return (char*)str;

    for (; *str; str++)
    {
        if (toupper((unsigned char)*str) == toupper((unsigned char)*pattern))
        {
            for (i = 1;; i++)
            {
                if (!pattern[i]) return (char*)str;
                if (toupper((unsigned char)str[i]) != toupper((unsigned char)pattern[i])) break;
            }
        }
    }
    return NULL;
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

int i, j, k; 
int sizeMenu = 0;
int sizeOrder = 0;

void initMenu()
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
    sizeMenu = count;
}

void readMenu()
{
    int page = 1;
    int count = 0;
    char c;

    qsort(list->name, sizeMenu, sizeof(struct menuList), comparator);

    for (i = 0; i < sizeMenu && count < sizeMenu; i++, count++)
    {
        if (i == 0)
        {
            system("cls");
            printf(" _________________________________________\n");
            printf("| %-3s | %-20s | %-10s |\n", "No", "Name", "Price");
            printf("|_____|______________________|____________|\n");
        }
        
        printf("| %-3d | %-20s | %-10d |\n", count + 1, list[count].name, list[count].price);
        
        if (i == 9)
        {
            printf("|_____|______________________|____________|\n\n");
            
            do
            {
                if (count == 9)
                {
                    printf("Press '>' to go to page %d\n", page+1);
                    printf("Press '0' to go back\n");
                    scanf("%c", &c); getchar();
                    if (c == '>')
                    {
                        i = -1;
                        page++;
                        break;
                    }
                    else if (c == '0') break;
                }
                else if (i == 9 && count > 9)
                {
                    char c;
                    printf("Press '<' to go to page %d\n", page-1);
                    printf("Press '>' to go to page %d\n", page+1);
                    printf("Press '0' to go back\n");
                    scanf("%c", &c); getchar();
                    if (c == '>')
                    {
                        i = -1;
                        page++;
                        break;
                    }
                    else if (c == '<')
                    {
                        i = -1;
                        page--;
                        count -= 20;
                        break;
                    }
                    else if (c == '0') break;
                }    
            } while (true);
        }
        if (c == '0') break;
        else if (count+1 == sizeMenu)
        {
            printf("|_____|______________________|____________|\n\n");
            printf("Press '<' to go to page %d\n", page-1);
            printf("Press '0' to go back\n");
            scanf("%c", &c); getchar();
            if (c == '<')
            {
                i = -1;
                page--;
                count -= (10 + sizeMenu % 10);
            }
            else if (c == '0') break;
        }
    }
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
    system("cls");
    int menu = 0;
    welcome();
    printf("\nXYZ Restaurant\n");
    printf("1. Menu\n");
    printf("2. Order\n");
    printf("3. Cart\n");
    printf("4. Exit\n");
    printf(">> ");
    scanf("%d", &menu);
    getchar();

    return menu;
}

int search(char *sub) {
    char str[MAX][MAX];
    char found[MAX][MAX];
    char temp[MAX];
    int count = 0;
    int count2 = 0;
    int i;
    int j;

    system("cls");

    printf("search >> %s", sub);

    printf("\nResults:\n");

    FILE *fr;

    fr = fopen("Menu.txt","r");

    if (!fr)
    {
        printf("ERROR");
        return 1;
    }

    char buff[MAX];
    while (fgets(buff, MAX, fr) != NULL) {
        char *token = strtok(buff, "#");
        
        strcpy(str[count], token);
        count++;
    }

    fclose(fr);

    for (i = 0; i < count; i++)
    {
        if (strcasestr(str[i], sub))
        {
            strcpy(found[count2], str[i]);
            count2++;
        }
    }

    qsort(found, count2, sizeof(found[0]), stringComparator);

    for (i = 0; i < count2 && i < 5; i++)
    {
        printf("%d. %s\n", i+1, found[i]);
    }

    return 0;
}

void order()
{
    system("cls");

    char ch;
    char temp[MAX] = {'\0'};
    search(temp);
    for (i = 0; (ch = getch()) != 13; i++)
    {
        if (ch != 8)
        {
            temp[i] = ch;
        }
        else if (temp[0] != '\0')
        {
            printf("\b \b");
            i--;
            temp[i] = '\0';
            i--;
        }
        else
        {
            i--;
        }
        search(temp);
    }

    for (i = 0; i < sizeMenu; i++)
    {
        if (strncasecmp(temp, list[i].name, strlen(temp)) == 0)
        {
            strcpy(saveOrder[sizeOrder].name, list[i].name);
            saveOrder[sizeOrder].price = list[i].price;
            sizeOrder++;
        }
    }
}

void cart()
{
    int pilihan, jmlhByr;
    int total = 0;
    printf(" _________________________________________\n");
    printf("| %-3s | %-20s | %-10s |\n", "No", "Name", "Price");
    printf("|_____|______________________|____________|\n");

    for (i = 0; i < sizeOrder; i++)
    {
        printf("| %-3d | %-20s | %-10d |\n", i + 1, saveOrder[i].name, saveOrder[i].price);
        total += saveOrder[i].price;
    }


    printf("|_____|______________________|____________|\n");
    printf("| %-26s | %-10d |\n", "Total", total);
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
        if(total > jmlhByr)
            printf("Uang kamu tidak cukup\n");
        else
        {
            printf("Pembayaran berhasil!\n");
            if(jmlhByr > total)
            {
                total = jmlhByr - total;
                printf("Uang kamu sisa: Rp.%d\n", total);
            }
            total = 0;
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
    initMenu();
    int menu;
    do
    {
        switch (mainMenu())
        {
        case 1:
        {
            system("cls");
            readMenu();
            break;
        }

        case 2:
        {
            order();
            break;
        }

        case 3:
        {
            system("cls");
            cart();
            break;
        }

        case 4:
        {
            system("cls");
            printf("Terimakasih sudah berkunjung!");
            getchar();
            menu = 4;
            break;
        }

        case 123:
        {
            adminMenu();
            break;
        }

        default:
        {
            break;
        }
        }
    } while (menu != 4);
    return 0;
}