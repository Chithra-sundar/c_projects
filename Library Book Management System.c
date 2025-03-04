#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[50];
    char author[50];
    int pages;
    float price;
} Book;

void addBook();
void displayBooks();
void searchBook();
void modifyBook();
void deleteBook();

int main() {
    int choice;
    while (1) {
        printf("\n========= Book Management System =========\n");
        printf("1. Add a Book\n2. Display All Books\n3. Search for a Book\n4. Modify a Book\n5. Delete a Book\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: modifyBook(); break;
            case 5: deleteBook(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void addBook() {
    FILE *fp = fopen("books.dat", "ab");
    if (!fp) { perror("Error opening file"); return; }

    Book b;
    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    printf("Enter Number of Pages: ");
    scanf("%d", &b.pages);
    printf("Enter Price: ");
    scanf("%f", &b.price);
    getchar();

    fwrite(&b, sizeof(Book), 1, fp);
    fclose(fp);
    printf("Book added successfully!\n");
}

void displayBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) { printf("No books found!\n"); return; }

    Book b;
    printf("\n========= Book List =========\n");
    while (fread(&b, sizeof(Book), 1, fp)) {
        printf("\nTitle: %s\nAuthor: %s\nPages: %d\nPrice: $%.2f\n", b.title, b.author, b.pages, b.price);
    }
    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) { printf("No books found!\n"); return; }

    char searchTitle[50];
    printf("Enter Book Title to Search: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (strcmp(b.title, searchTitle) == 0) {
            printf("\nBook Found!\nTitle: %s\nAuthor: %s\nPages: %d\nPrice: $%.2f\n", b.title, b.author, b.pages, b.price);
            found = 1;
            break;
        }
    }
    if (!found) printf("Book not found!\n");
    fclose(fp);
}

void modifyBook() {
    FILE *fp = fopen("books.dat", "rb+");
    if (!fp) { printf("No books found!\n"); return; }

    char searchTitle[50];
    printf("Enter Book Title to Modify: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    Book b;
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (strcmp(b.title, searchTitle) == 0) {
            printf("Enter New Author Name: ");
            fgets(b.author, sizeof(b.author), stdin);
            b.author[strcspn(b.author, "\n")] = 0;
            printf("Enter New Number of Pages: ");
            scanf("%d", &b.pages);
            printf("Enter New Price: ");
            scanf("%f", &b.price);
            getchar();

            fseek(fp, -sizeof(Book), SEEK_CUR);
            fwrite(&b, sizeof(Book), 1, fp);
            printf("Book modified successfully!\n");
            fclose(fp);
            return;
        }
    }
    printf("Book not found!\n");
    fclose(fp);
}

void deleteBook() {
    FILE *fp = fopen("books.dat", "rb");
    if (!fp) { printf("No books found!\n"); return; }

    FILE *temp = fopen("temp.dat", "wb");
    char searchTitle[50];
    printf("Enter Book Title to Delete: ");
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;

    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (strcmp(b.title, searchTitle) != 0) fwrite(&b, sizeof(Book), 1, temp);
        else found = 1;
    }
    fclose(fp); fclose(temp);
    remove("books.dat"); rename("temp.dat", "books.dat");
    printf(found ? "Book deleted!\n" : "Book not found!\n");
}
