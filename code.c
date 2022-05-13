#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char F_NM[50];
    int qt;
    float price;
    int d;
    struct node *pre;
    struct node *nx;
}FM;

FM *h_c = NULL, *n_n, *t_c = NULL;
FM *h_a = NULL, *t_a = NULL;
FM *h_s;
FM *createmenu(FM *h, int d, char F_NM[25], float price);
FM *createorder(FM *h, int d, int qt);
void displayMenu(FM *h);
void displayOrder(FM *h);
FM *totalsales(int d, int qt);
void calculatetotsales();
FM *delete (int dt, FM *h, FM *tail);
FM *deleteM(int dt, FM *h, FM *tail);
int deleteMenu();
int deleteOrder();
void displaybill();
FM *deleteList(FM *h);
void Manager();
void customer();

int main()
{
    h_a = createmenu(h_a, 101, "Cheese-Pizza", 330);
    h_a = createmenu(h_a, 102, "Special-Pav-Bhaji", 210);
    h_a = createmenu(h_a, 103, "Manchurian-Noodles", 400);
    h_a = createmenu(h_a, 104, "Cheese-Burger", 250);
    h_a = createmenu(h_a, 105, "Cherry-Pineapple", 350);

    FM *demo = h_a;

    FILE *f_p;
    f_p = fopen("Menu.txt", "w");
    if (f_p == NULL)
        printf("\nError");
    else
    {
        while (demo != NULL)
        {
            fprintf(f_p, "%d \t%s \t%f\n", demo->d, demo->F_NM, demo->price);
            demo = demo->nx;
        }
    }
    fclose(f_p);
    int choice;
    do
    {
        printf("\n=========================================================\n");
        printf("           WELCOME TO TAJ HOTEL\n");
        printf("==========================================================\n\n\n");
        printf("          1. MANAGER DESK   \n");
        printf("          2. CUSTOMER DESK \n");
        printf("          3. Exit \n\n");
        printf("          Enter Your Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Manager();
            break;

        case 2:
            customer();
            break;

        case 3:
            printf("          *THANK YOU FOR VISITING*\n");
            break;

        default:
            printf("          Wrong Input, Choose valid option\n");
            break;
        }
    } while (choice != 3);
}

FM *createmenu(FM *h, int d, char F_NM[25], float price)
{

    n_n = (FM *)malloc(sizeof(FM));
    n_n->d = d;
    n_n->price = price;
    n_n->qt = 0;
    strcpy(n_n->F_NM, F_NM);
    n_n->nx = NULL;
    n_n->pre = NULL;

    FM *demo = h_a;

    if (demo == NULL)
        h_a = t_a = n_n;
    else
    {
        while (demo->nx != NULL)
        {
            demo = demo->nx;
        }
        demo->nx = n_n;
        n_n->pre = t_a;
        t_a = n_n;
    }

    return h_a;
}

FM *createorder(FM *h, int d, int qt)
{
    n_n = (FM *)malloc(sizeof(FM));

    FM *demo1 = h_a;
    int flag = 0;
    while (demo1 != NULL)
    {
        if (demo1->d == d)
        {
            flag = 1;
            break;
        }
        demo1 = demo1->nx;
    }

    if (flag == 1)
    {
        n_n->d = d;
        n_n->price = qt * (demo1->price);
        n_n->qt = qt;
        strcpy(n_n->F_NM, demo1->F_NM);
        n_n->nx = NULL;
        n_n->pre = NULL;

        FM *demo = h;

        if (demo == NULL)
            h_c = t_c = n_n;
        else
        {
            while (demo->nx != NULL)
                demo = demo->nx;

            demo->nx = n_n;
            n_n->pre = t_c;
            t_c = n_n;
        }
    }
    else
    {
        printf("          This food item is not available in the menu card!\n");
    }

    return h_c;
}

void displayMenu(FM *h)
{
    int da;
    float price;
    char name[100];
    FILE *f_p;
    f_p = fopen("Menu.txt", "r");
    int n = 0;
    while (!feof(f_p))
    {
        fscanf(f_p, "%d %s %f", &da, name, &price);
        n++;
    }
    rewind(f_p);

    printf("\n");
    printf("        Sr.no.\t    FoodName  \t       Price\n");
    printf("     -----------------------------------------------------\n");
    if (f_p == NULL)
        printf("\nError");
    else
        for (int i = 0; i < n - 1; i++)
        {
            fscanf(f_p, "%d %s %f", &da, name, &price);
            printf("          %d\t%s     \t%0.2f\n", da, name, price);
        }
    fclose(f_p);
}

void displayOrder(FM *h)
{
    FM *demo1 = h;
    if (demo1 == NULL)
    {
        printf("\n          No Order!!\n\n");
    }
    else
    {
        printf("\n");
        printf("        Sr.no.\t    FoodName  \t    Quantity\tPrice\n");
        printf("     -----------------------------------------------------\n");

        while (demo1 != NULL)
        {
            if (demo1->qt == 0)
                printf("          %d\t%s     \t%0.2f\n", demo1->d, demo1->F_NM, demo1->price);
            else
            {
                printf("          %d\t%s     \t%d     \t%0.2f\n", demo1->d, demo1->F_NM, demo1->qt, demo1->price);
            }

            demo1 = demo1->nx;
        }
        printf("\n");
    }
}

FM *totalsales(int d, int qt)
{
    n_n = (FM *)malloc(sizeof(FM));
    int flag = 0;

    FM *demo1 = h_a;
    while (demo1->d != d)
    {
        demo1 = demo1->nx;
    }

    n_n->d = d;
    n_n->price = qt * (demo1->price);
    n_n->qt = qt;
    strcpy(n_n->F_NM, demo1->F_NM);
    n_n->nx = NULL;
    n_n->pre = NULL;

    FM *demo = h_s;

    if (demo == NULL)
        h_s = n_n;
    else
    {
        while (demo->nx != NULL)
        {
            if (demo->d == d)
            {
                flag = 1;
                break;
            }
            demo = demo->nx;
        }

        if (flag == 1)
        {
            demo->qt += n_n->qt;
            demo->price += n_n->price;
        }
        else
        {
            demo->nx = n_n;
        }
    }

    return h_s;
}

void calculatetotsales()
{
    FM *demo = h_c;
    while (demo != NULL)
    {
        h_s = totalsales(demo->d, demo->qt);
        demo = demo->nx;
    }
}

FM *delete (int dt, FM *h, FM *tail)
{
    int a;
    if (h == NULL)
    {
        printf("\n          No order available!!\n");
    }
    else
    {
        FM *demo;
        if (dt == h->d)
        {
            demo = h;
            if (h != NULL && h->qt == 1)
            {
                h = h->nx;
                h->pre = NULL;
                free(demo);
            }
            (h->qt)--;
        }
        else if (dt == tail->d)
        {
            demo = tail;
            if (tail->qt == 1)
            {
                tail = tail->pre;
                tail->nx = NULL;
                free(demo);
            }
            (tail->qt)--;
        }
        else
        {
            demo = h;
            while (dt != demo->d)
            {
                demo = demo->nx;
            }
            if (demo->qt == 1)
            {
                (demo->pre)->nx = demo->nx;
                (demo->nx)->pre = demo->pre;
                free(demo);
            }

            (demo->qt)--;
        }
    }
    return h;
}

FM *deleteM(int dt, FM *h, FM *tail)
{
    int a;
    if (h == NULL)
    {
        printf("\n          No Order Available\n");
    }
    else
    {
        FM *demo;
        if (dt == h->d)
        {
            demo = h;
            h = h->nx;
            if (h != NULL)
            {
                h->pre = NULL;
                free(demo);
            }
        }
        else if (dt == tail->d)
        {
            demo = tail;
            tail = tail->pre;
            tail->nx = NULL;
            free(demo);
        }
        else
        {
            demo = h;
            while (dt != demo->d)
            {
                demo = demo->nx;
            }
            (demo->pre)->nx = demo->nx;
            (demo->nx)->pre = demo->pre;
            free(demo);
        }
    }
    return h;
}

int deleteMenu()
{
    printf("\n          Enter Sr.No. of the food item which you want to delete: ");

    int num;
    int a = 0;
    scanf("%d", &num);
    FM *demo = h_a;
    while (demo != NULL)
    {
        if (demo->d == num)
        {
            h_a = deleteM(num, h_a, t_a);
            a = 1;
            break;
        }
        demo = demo->nx;
    }

    char nm[100];
    int t = 0;
    int dat;
    float p;
    FILE *f_p, *ft;
    f_p = fopen("Menu.txt", "r");
    ft = fopen("data1.txt", "wb+");
    while (!feof(f_p))
    {
        fscanf(f_p, "%d %s %f", &dat, nm, &p);
        t++;
    }
    rewind(f_p);
    for (int i = 0; i < t - 1; i++)
    {
        fscanf(f_p, "%d %s %f", &dat, nm, &p);

        if (dat != num)
        {
            fprintf(ft, "%d\t %s\t %f\n", dat, nm, p);
        }
    }

    fclose(f_p);
    fclose(ft);
    remove("Menu.txt");
    rename("data1.txt", "Menu.txt");

    if (a == 1)
        return 1;
    return 0;
}

int deleteOrder()
{

    int num, Qty;
    printf("\n          Enter Sr.No. of the food item which you want to delete: ");
    scanf("%d", &num);
    printf("\n          Enter qt want to delete: ");
    scanf("%d", &Qty);

    FM *demo = h_c;
    while (demo != NULL)
    {
        if (demo->d == num)
        {
            if (demo->qt == Qty)
            {
                h_c = delete (num, h_c, t_c);
            }
            else
            {
                demo->qt = demo->qt - Qty;
                demo->price = demo->price - (demo->price / Qty);
            }
            return 1;
        }
        demo = demo->nx;
    }
    return 0;
}

void displaybill()
{
    displayOrder(h_c);
    FM *demo = h_c;
    float total_price = 0;
    while (demo != NULL)
    {
        total_price += demo->price;
        demo = demo->nx;
    }

    printf("-----------------------------------------------------------------------\n");
    printf("\n          Price :-\t\t %0.02f       \n", total_price);
    float gst = (((105 * total_price) / 100) - total_price);
    printf("          Additional GST :-\t %.2f\n", gst);
    printf("          -------------------------------\n");
    printf("           Total Price :-\t %.2f\n", gst + total_price);
    printf("          -------------------------------\n");
}

FM *deleteList(FM *h)
{
    if (h == NULL)
    {
        return NULL;
    }
    else
    {
        FM *demo = h;
        while (demo->nx != 0)
        {
            demo = demo->nx;
            free(demo->pre);
        }
        free(demo);
        h = NULL;
    }

    return h;
}

void Manager()
{
    printf("\n----------------------------------------------\n");
    printf("          MANAGER DESK\n");
    printf("----------------------------------------------\n");
    while (1)
    {
        printf("\n        1. View total orders\n");
        printf("          2. Add new food items in the menu card\n");
        printf("          3. Delete food items from the menu card\n");
        printf("          4. Display menu card\n");
        printf("          5. Back To Main Menu \n\n");
        printf("          Enter Your Choice : ");

        int opt;
        scanf("%d", &opt);

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            printf("\n======================= Total Orders =======================\n");

            displayOrder(h_s);
            break;
        case 2:

            printf("\n          Enter Sr.No of the food item: ");
            int num, flag = 0;
            char name[50];
            float price;
            scanf("%d", &num);

            FM *demo = h_a;

            while (demo != NULL)
            {
                if (demo->d == num)
                {
                    printf("\n         This food item already exists in menu card!!\n\n");
                    flag = 1;
                    break;
                }
                demo = demo->nx;
            }

            if (flag == 1)
                break;

            printf("          Enter name of food item: ");
            scanf("%s", name);
            printf("          Enter price: ");
            scanf("%f", &price);
            h_a = createmenu(h_a, num, name, price);

            FILE *f_p;
            f_p = fopen("Menu.txt", "a");
            if (f_p == NULL)
                printf("\nError");
            else
                fprintf(f_p, "%d \t%s \t%f\n", num, name, price);
            printf("\n          New food item has been added to the menu card!!\n\n");
            fclose(f_p);
            break;
        case 3:
            if (deleteMenu())
            {
                printf("\n======================= Updated menu card =======================\n");
                displayMenu(h_a);
            }
            else
                printf("\n          Food item with given Sr.No doesn't available!!\n\n");

            break;
        case 4:
            printf("\n======================== Order menu ========================\n");
            displayMenu(h_a);
            break;

        default:
            printf("\n          Wrong Input !! PLease choose valid option\n");
            break;
        }
    }
}

void customer()
{
    int flag = 0, j = 1;
    char ch, l;
    printf("\n----------------------------------------------\n");
    printf("              CUSTOMER DESK\n");
    printf("----------------------------------------------\n");
    int opt;
    do
    {
        printf("\n          1. Give order\n");
        printf("          2. View ordered food items\n");
        printf("          3. Cancel a food item from order\n");
        printf("          4. Display final bill\n");
        printf("          5. Back To Main Menu \n\n");
        printf("          Enter Your Choice : ");
        scanf("%d", &opt);

        if (opt == 5)
            break;

        switch (opt)
        {
        case 1:
            do
            {
                displayMenu(h_a);
                printf("\n          Enter Sr.No of food item which you want to order: ");
                int n;
                scanf("%d", &n);
                printf("          Enter qt: ");
                int qt;
                scanf("%d", &qt);
                h_c = createorder(h_c, n, qt);
                printf("          Do you want to continue your order (y/n) : ");
                scanf(" %c", &l);
            } while (l != 'n');
            break;
        case 2:
            printf("\n========================== Your Order =========================\n");
            displayOrder(h_c);
            break;
        case 3:
            if (deleteOrder())
            {
                printf("\n====================== Your Updated order ========================\n");
                displayOrder(h_c);
            }
            else
                printf("\n          Food item with given Sr.No doesn't available!!\n");
            break;
        case 4:
            calculatetotsales();
            printf("\n=========================== Final Bill ================================\n");
            displaybill();
            h_c = deleteList(h_c);
            printf("\n          Press any key to return to main menu:");
            fflush(stdin);
            ch = fgetc(stdin);
            flag = 1;
            break;
        case 5:
            break;
        default:
            printf("\n          Wrong Input !! PLease choose valid option\n");
            break;
        }
        if (flag == 1)
            break;
    } while (opt != 5);
}