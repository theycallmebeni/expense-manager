//done bt behnam zarei 
//ELECTRICAL ENGINEERING AT IUT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define initial_capacity 10

struct Expense {
    char date[11] ;
    char desc[1200] ;
    float amount ;
    char category [20];

};

struct Expense *expenses =NULL ;
int expense_count = 0 ;
int capacity = 0 ;


void load_expenses(){
    FILE *file ;
    file = fopen("expense.txt" , "r") ;
    if (file ==NULL ) {
        printf("there's no file to be found ad the name of EXPENSE \n ");
        return ;

    }

    while (fscanf(file, "%s %f %s %[^\n]\n",
                  expenses[expense_count].date,
                  &expenses[expense_count].amount,
                  expenses[expense_count].category,
                  expenses[expense_count].desc) == 4) {
        expense_count++;
        if (expense_count >= capacity) {
            capacity = capacity ? capacity * 2 : initial_capacity;
            expenses = realloc(expenses, capacity * sizeof(struct Expense));
            if (!expenses) {
                printf("Error: Memory allocation failed.\n");
                exit(1);
            }
        }
    }
fclose(file) ;

}
void save_expenses(){
    FILE *file = fopen("expense.txt", "w");
    if (!file) {
        printf("Error: Cannot save expenses to file.\n");
        return;
    }

    for (int i = 0; i < expense_count; i++) {
        fprintf(file, "%s %.2f %s %s\n",
                expenses[i].date,
                expenses[i].amount,
                expenses[i].category,
                expenses[i].desc);
    }

    fclose(file);
}



void add_expense(){
    if (expense_count >= capacity) {
        capacity = capacity ? capacity * 2 : initial_capacity;
        expenses = realloc(expenses, capacity * sizeof(struct Expense));
        if (!expenses) {
            printf("Error: Memory allocation failed.\n");
            exit(1);
        }
    }

    struct Expense *exp = &expenses[expense_count];
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", exp->date);
    printf("Enter amount: ");
    scanf("%f", &exp->amount);
    printf("Enter category (e.g., Food, Transport): ");
    scanf("%s", exp->category);
    printf("Enter description: ");
    getchar(); // Clear newline
    fgets(exp->desc, 50, stdin);
    exp->desc[strcspn(exp->desc, "\n")] = 0; // Remove newline

    expense_count++;
    save_expenses();
    printf("Expense added successfully.\n");


}

void display_expenses() {
    if (expense_count == 0 )  {
    printf("NO EXPENSES HAS RECORDED \n") ;
    return ;

    }
    printf("EXPENSES\n") ;
    printf("date\t|amount\t|category\t|discription\n") ;
    printf("----------------------------------------\n") ;
    for (int i = 0; i < expense_count; i++) {
        printf("%s | %.2f | %s | %s\n",
               expenses[i].date,
               expenses[i].amount,
               expenses[i].category,
               expenses[i].desc);
    }

}



void summarize_by_category() {
    if (expense_count == 0) {
        printf("No expenses to summarize.\n");
        return;
    }

    char categories[20][20];
    float totals[20] = {0};
    int cat_count = 0;

    for (int i = 0; i < expense_count; i++) {
        int found = 0;
        for (int j = 0; j < cat_count; j++) {
            if (strcmp(expenses[i].category, categories[j]) == 0) {
                totals[j] += expenses[i].amount;
                found = 1;
                break;
            }
        }
        if (!found && cat_count < 20) {
            strcpy(categories[cat_count], expenses[i].category);
            totals[cat_count] = expenses[i].amount;
            cat_count++;
        }
    }

    printf("\nSummary by Category:\n");
    printf("Category | Total\n");
    printf("------------------\n");
    for (int i = 0; i < cat_count; i++) {
        printf("%s | %.2f\n", categories[i], totals[i]);
    }
}

void find_largest_expense() {
    if (expense_count == 0) {
        printf("No expenses to analyze.\n");
        return;
    }

    int max_index = 0;
    for (int i = 1; i < expense_count; i++) {
        if (expenses[i].amount > expenses[max_index].amount) {
            max_index = i;
        }
    }

    printf("\nLargest Expense:\n");
    printf("Date: %s\n", expenses[max_index].date);
    printf("Amount: %.2f\n", expenses[max_index].amount);
    printf("Category: %s\n", expenses[max_index].category);
    printf("Description: %s\n", expenses[max_index].desc);
}

int main (){
load_expenses() ;
int choice ;

while(1){
    printf("EXPENSES\n") ;
    printf("1.ADD EXPENSE\n2.VIEW EXPENSES\n3.SUMMARIZE BY CATEGORY\n4.EXIT\n") ;
    scanf("%d" , &choice ) ;

    switch(choice){
        case 1 :
            add_expense() ; break ;
        case 2 :
            display_expenses();
            break ;
        case 3 :
            summarize_by_category() ; break ;
        case 4 :
            find_largest_expense();
            free(expenses); // Free dynamically allocated memory
            printf("Exiting...\n");
            break ;
        default:
            printf("VALUE OF CHOICE HAS TO BE SOMETHING BETWEEN 1 AND 4 !!\n ") ;


    }

}


    return 0 ;

}