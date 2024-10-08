 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input();
void writefile();
void search();
void output();

struct date {
    int month;
    int day;
    int year;
};

struct account {
    int number;
    char name[100];
    int acct_no;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;
} customer;

int tl, sl, ts;

int main() {
    int i, n;
    char ch;

    while (1) {
        printf("   CUSTOMER BILLING SYSTEM:\n\n");
        printf("===============================\n");
        printf("\n1:    to add account on list\n");
        printf("2:    to search customer account\n");
        printf("3:    exit\n");
        printf("\n================================\n");

        do {
            printf("\nSelect what do you want to do? ");
            ch = getchar();
        } while (ch < '1' || ch > '3');
        getchar(); // To consume newline character

        switch (ch) {
            case '1':
                printf("\nHow many customer accounts? ");
                scanf("%d", &n);
                getchar(); // Consume newline
                for (i = 0; i < n; i++) {
                    input();
                    if (customer.payment > 0)
                        customer.acct_type = (customer.payment < 0.1 * customer.oldbalance) ? 'O' : 'D';
                    else
                        customer.acct_type = (customer.oldbalance > 0) ? 'D' : 'C';

                    customer.newbalance = customer.oldbalance - customer.payment;
                    writefile();
                }
                break;
            case '2':
                printf("Search by what?\n");
                printf("\n1 --- Search by customer number\n");
                printf("2 --- Search by customer name\n");
                search();
                break;
            case '3':
                printf("\nExiting the program.\n");
                exit(0);
        }
    }
    return 0;
}

void input() {
    FILE *fp = fopen("bidur.dat", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    tl = ftell(fp);
    sl = sizeof(customer);
    ts = tl / sl;
    fseek(fp, (ts - 1) * sl, SEEK_SET);
    fread(&customer, sizeof(customer), 1, fp);
    fclose(fp);

    printf("\nCustomer no: %d\n", ++customer.number);
    printf("         Account number: ");
    scanf("%d", &customer.acct_no);
    printf("\n       Name: ");
    scanf("%s", customer.name);
    printf("\n       Mobile no: ");
    scanf("%f", &customer.mobile_no);
    printf("         Street: ");
    scanf("%s", customer.street);
    printf("         City: ");
    scanf("%s", customer.city);
    printf("         Previous balance: ");
    scanf("%f", &customer.oldbalance);
    printf("         Current payment: ");
    scanf("%f", &customer.payment);
    printf("         Payment date(mm/dd/yyyy): ");
    scanf("%d/%d/%d", &customer.lastpayment.month, &customer.lastpayment.day, &customer.lastpayment.year);
}

void writefile() {
    FILE *fp = fopen("bidur.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);
}

void search() {
    char ch;
    char nam[100];
    int n, i, m = 1;
    FILE *fp = fopen("bidur.dat", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    do {
        printf("\nEnter your choice: ");
        ch = getchar();
    } while (ch != '1' && ch != '2');
    getchar(); // Consume newline

    switch (ch) {
        case '1':
            fseek(fp, 0, SEEK_END);
            tl = ftell(fp);
            sl = sizeof(customer);
            ts = tl / sl;
            do {
                printf("\nChoose customer number: ");
                scanf("%d", &n);
                getchar(); // Consume newline
                if (n <= 0 || n > ts)
                    printf("\nEnter correct number\n");
                else {
                    fseek(fp, (n - 1) * sl, SEEK_SET);
                    fread(&customer, sl, 1, fp);
                    output();
                }
                printf("\n\nAgain? (y/n) ");
                ch = getchar();
                getchar(); // Consume newline
            } while (ch == 'y');
            break;
        case '2':
            fseek(fp, 0, SEEK_END);
            tl = ftell(fp);
            sl = sizeof(customer);
            ts = tl / sl;
            fseek(fp, (ts - 1) * sl, SEEK_SET);
            fread(&customer, sizeof(customer), 1, fp);
            n = customer.number;

            do {
                printf("\nEnter the name: ");
                scanf("%s", nam);
                getchar(); // Consume newline
                fseek(fp, 0, SEEK_SET);
                for (i = 1; i <= n; i++) {
                    fread(&customer, sizeof(customer), 1, fp);
                    if (strcmp(customer.name, nam) == 0) {
                        output();
                        m = 0;
                        break;
                    }
                }
                if (m != 0)
                    printf("\n\nDoesn't exist\n");
                printf("\nAnother? (y/n) ");
                ch = getchar();
                getchar(); // Consume newline
            } while (ch == 'y');
            break;
    }
    fclose(fp);
}

void output() {
    printf("\n\n    Customer no    : %d\n", customer.number);
    printf("    Name           : %s\n", customer.name);
    printf("    Mobile no      : %.0f\n", customer.mobile_no);
    printf("    Account number : %d\n", customer.acct_no);
    printf("    Street         : %s\n", customer.street);
    printf("    City           : %s\n", customer.city);
    printf("    Old balance    : %.2f\n", customer.oldbalance);
    printf("    Current payment: %.2f\n", customer.payment);
    printf("    New balance    : %.2f\n", customer.newbalance);
    printf("    Payment date   : %d/%d/%d\n", customer.lastpayment.month, customer.lastpayment.day, customer.lastpayment.year);

    printf("    Account status : ");
    switch (customer.acct_type) {
        case 'C':
            printf("CURRENT\n\n");
            break;
        case 'O':
            printf("OVERDUE\n\n");
            break;
        case 'D':
            printf("DELINQUENT\n\n");
            break;
        default:
            printf("ERROR\n\n");
    }
}
