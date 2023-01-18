#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

// alias
#define MAX 255

// Menyimpan semua barang yang ada di menu
struct menuList
{
    char name[MAX];
    int price;
} list[MAX];

// menyimpan semua barang yang dipilih saat mengorder
struct saveOrder
{
    char name[MAX];
    int price;
} saveOrder[MAX];

// membuat struct kosong agak dapat mengkosongkan structnya
static const struct saveOrder EmptyStruct;

// comparator untuk qsort struct yang mengsort secara ascending
int comparator(const void *a, const void *b)
{
    struct menuList *listA = (struct menuList *)a;
    struct menuList *listB = (struct menuList *)b;

    // sort descending: -strcmp(listA->name, listB->name)
    return strcmp(listA->name, listB->name);
}

// comparator untuk qsort string yang mengsort secara ascending 
int stringComparator(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

// strstr tetapi tidak case sensitive
// untuk mencari substring dalam string
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

// untuk Welcome
void welcome()
{
    puts(" __          __  _                          _ ");
    puts(" \\ \\        / / | |                        | |");
    puts("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___| |");
    puts("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ |");
    puts("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/_|");
    puts("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___(_)");
}

// global variable
int i, j, k;
int sizeMenu = 0;
int sizeOrder = 0;

// memasukan semua data yang ada di menu ke structnya
void initMenu()
{
    FILE *fp;
    fp = fopen("Menu.txt", "r");

    if (!fp)
    {
        printf("ERROR!");
        return;
    }

    char buff[MAX];
    int count = 0;
    while (fgets(buff, MAX, fp) != NULL)
    {
        char *token = strtok(buff, "#");
        strcpy(list[count].name, token);
        token = strtok(NULL, "\n");
        list[count].price = atoi(token);
        count++;
    }
    fclose(fp);
    sizeMenu = count;
}

// print menu dari file
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

// main menunya
int mainMenu()
{
    system("cls");
    int menu = 0;
    welcome();
    printf("\nPOG Restaurant\n");
    printf("1. Menu\n");
    printf("2. Order\n");
    printf("3. Cart\n");
    printf("4. Exit\n");
    printf(">> ");
    scanf("%d", &menu);
    getchar();

    return menu;
}

// untuk searching dari file yang memiliki substring sama dengan yang dimasukan
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

    FILE *fp;

    fp = fopen("Menu.txt","r");

    if (!fp)
    {
        printf("ERROR");
        return 1;
    }

    char buff[MAX];
    while (fgets(buff, MAX, fp) != NULL) {
        char *token = strtok(buff, "#");
        
        strcpy(str[count], token);
        count++;
    }

    fclose(fp);

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

// setiap kali menulis akan disearch substringnya
void order()
{
    system("cls");

    char ch;
    char temp[MAX] = {'\0'};
    search(temp);
    for (i = 0; (ch = getch()) != '\r'; i++)
    {
        if (ch != '\b')
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
        if (strcasecmp(temp, list[i].name) == 0)
        {
            strcpy(saveOrder[sizeOrder].name, list[i].name);
            saveOrder[sizeOrder].price = list[i].price;
            sizeOrder++;
        }
    }
}

//? alternative order menggunakan binary search
// void order()
// {
//     char order[MAX];
//     printf("Insert food name: ");
//     scanf("%[^\n]", order);
//     getchar();

//     struct menuList key = {order, 0};
//     struct menuList *result = bsearch(order, list->name, sizeMenu, sizeof(struct menuList), comparator);

//     if (result == NULL)
//     {
//         printf("Element not found");
//         getchar();
//     }
//     else
//     {
//         strcpy(saveOrder[sizeOrder].name, result->name);
//         saveOrder[sizeOrder].price = result->price;
//         sizeOrder++;
//         getchar();
//     }
// }
//? end

// mengecek semua barang yang sudah diorder di cart
void cart()
{
    int pilihan;
    int jmlhByr = 0;
    int total = 0;

    if (sizeOrder == 0)
    {
        printf("Empty Cart!"); getchar();
        return;
    }

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
    scanf("%d", &pilihan); getchar();

    if(pilihan == 1)
    {
        printf("\nEnter the amount of money\n");
        printf(">> ");
        scanf("%d", &jmlhByr); getchar();
        if(total > jmlhByr)
        {
            printf("\nYour balance is insufficient!\n");
            getchar();
        }
        else
        {
            printf("\nPayment Successful!\n");
            if(jmlhByr > total)
            {
                total = jmlhByr - total;
                printf("Your change: IDR%d\n", total);

                for (i = 0; i < sizeOrder; i++)
                    saveOrder[i] = EmptyStruct;
                
                sizeOrder = 0;
            }
            getchar();
        }
    }
}

// menambahkan menu ke file
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
    printf("Items added!\n");
    printf("Press ENTER to continue...");
    getchar();
}

// menghapus menu dari file
void removeMenu(char *name)
{
    FILE *fp, *temp;
        
    fp = fopen("Menu.txt","r");
    temp = fopen("temp.txt", "w");
    
    if (!fp)
    {
        printf("ERROR: file not found!"); getchar();
        return;
    }
    
    char buff[MAX];
    char buff2[MAX];
    while (fgets(buff, MAX, fp) != NULL)
    {
        strcpy(buff2, buff);
        char *token = strtok(buff, "#");
        if (strcasecmp(name, token) == 0)
        {
            printf("\nLine Removed!\n"); 
            printf("Press ENTER to continue...");
            getchar();
        }
        else fputs(buff2, temp);
    }
    
    fclose(fp);
    fclose(temp);

    remove("Menu.txt");
    rename("temp.txt", "Menu.txt");
}

// admin panel
void adminMenu()
{
    int menu2;
    do
    {
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
            char name[MAX];
            printf("Menu to remove: ");
            scanf("%[^\n]", name); getchar();
            
            removeMenu(name);
        }

        case 3:
        {
            return;
        }

        default:
        {
            break;
        }
        }
    } while (menu2 != 3);
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
            printf("Thank you for coming!\n"); getchar();
            menu = 4;
            break;
        }

        case 123:
        {
            adminMenu();
            initMenu();
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