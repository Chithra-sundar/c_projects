#include <stdio.h>

struct Customer {
    char name[100];
    int customerID;
    float totalAmount;
};

struct Product {
    char productName[100];
    float price;
    int quantity;
};

float calculateTotal(struct Product products[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += products[i].price * products[i].quantity;
    }
    return total;
}

int main() {
    struct Customer customer;
    int n;
    printf("Enter Customer ID: ");
    scanf("%d", &customer.customerID);

    printf("Enter Customer Name (without spaces): ");
    scanf("%s", customer.name);

    printf("Enter number of products purchased: ");
    scanf("%d", &n);

    struct Product products[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for product %d\n", i + 1);
        printf("Enter product name: ");
        scanf("%s", products[i].productName);

        printf("Enter price of %s: ", products[i].productName);
        scanf("%f", &products[i].price);

        printf("Enter quantity of %s: ", products[i].productName);
        scanf("%d", &products[i].quantity);
    }

    float totalAmount = calculateTotal(products, n);
    customer.totalAmount = totalAmount;

    float discount = 0;
    if (totalAmount > 500) {
        discount = totalAmount * 0.1;
        totalAmount -= discount;
    }

    float tax = totalAmount * 0.18;
    totalAmount += tax;

    printf("\n\n--------- CUSTOMER BILL ---------\n");
    printf("Customer ID: %d\n", customer.customerID);
    printf("Customer Name: %s\n", customer.name);
    printf("Purchased Products:\n");

    for (int i = 0; i < n; i++) {
        printf("%s - $%.2f x %d = $%.2f\n", products[i].productName, products[i].price, products[i].quantity, products[i].price * products[i].quantity);
    }

    printf("\nSubtotal: $%.2f\n", customer.totalAmount);
    if (discount > 0) {
        printf("Discount: -$%.2f\n", discount);
    }
    printf("Tax (18%%): $%.2f\n", tax);
    printf("Total Amount: $%.2f\n", totalAmount);

    printf("\n--------------------------------\n");

    return 0;
}
