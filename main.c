#include <stdio.h>
#include <string.h>

struct Account {
    int id;
    char name[50];
    double balance;
};

struct Account accounts[100];
int accountCount = 0;
void loadAccounts() {
    FILE *file = fopen("accounts.txt", "r");
    if(file == NULL) return;

    while(fscanf(file, "%d %s %lf", 
                 &accounts[accountCount].id,
                 accounts[accountCount].name,
                 &accounts[accountCount].balance) == 3) {
        accountCount++;
    }

    fclose(file);
}
void saveAccounts() {
    FILE *file = fopen("accounts.txt", "w");
    for(int i = 0; i < accountCount; i++) {
        fprintf(file, "%d %s %.2lf\n", 
                accounts[i].id,
                accounts[i].name,
                accounts[i].balance);
    }
    fclose(file);
}
void createAccount() {
    printf("Enter account ID: ");
    scanf("%d", &accounts[accountCount].id);

    printf("Enter name: ");
    scanf("%s", accounts[accountCount].name);

    printf("Enter initial balance: ");
    scanf("%lf", &accounts[accountCount].balance);

    accountCount++;
    saveAccounts();
    printf("Account created!\n");
}
void showAccounts() {
    if(accountCount == 0) {
        printf("No accounts found.\n");
        return;
    }

    for(int i = 0; i < accountCount; i++) {
        printf("\nID: %d\n", accounts[i].id);
        printf("Name: %s\n", accounts[i].name);
        printf("Balance: %.2lf\n", accounts[i].balance);
    }
}
void deposit() {
    int id;
    double amount;
    printf("Enter account ID: ");
    scanf("%d", &id);

    for(int i = 0; i < accountCount; i++) {
        if(accounts[i].id == id) {
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);
            accounts[i].balance += amount;
            saveAccounts();
            printf("Deposit successful!\n");
            return;
        }
    }
    printf("Account not found!\n");
}
void withdraw() {
    int id;
    double amount;
    printf("Enter account ID: ");
    scanf("%d", &id);

    for(int i = 0; i < accountCount; i++) {
        if(accounts[i].id == id) {
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);
            if(amount > accounts[i].balance) {
                printf("Insufficient balance!\n");
            } else {
                accounts[i].balance -= amount;
                saveAccounts();
                printf("Withdrawal successful!\n");
            }
            return;
        }
    }
    printf("Account not found!\n");
}
void menu() {
    int choice;
    while(1) {
        printf("\n--- Mini Banking System ---\n");
        printf("1. Create account\n");
        printf("2. Show all accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if(choice == 1) createAccount();
        else if(choice == 2) showAccounts();
        else if(choice == 3) deposit();
        else if(choice == 4) withdraw();
        else if(choice == 5) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice! Try again.\n");
        }
    }
}
int main() {
    printf("Welcome to Mini Banking System!\n");
    loadAccounts(); // charger les comptes existants
    menu();
    return 0;
}
