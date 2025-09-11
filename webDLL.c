#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WebPage {
    char url[100];
    struct WebPage *prev, *next;
};

struct WebPage* currentPage = NULL;

void visitPage(const char* url) {
    struct WebPage* newPage = (struct WebPage*)malloc(sizeof(struct WebPage));
    if(!newPage){
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newPage->url, url);
    newPage->prev = currentPage;
    newPage->next = NULL;

    if (currentPage != NULL) {
        struct WebPage* temp = currentPage->next;
        while (temp != NULL) {
            struct WebPage* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        currentPage->next = newPage;
    }
    currentPage = newPage;
    printf("Visited: %s\n", currentPage->url);
}

void goBack() {
    if (currentPage != NULL && currentPage->prev != NULL) {
        currentPage = currentPage->prev;
        printf("<- Back to: %s\n", currentPage->url);
    } else {
        printf("Cannot go back. No previous page.\n");
    }
}

void goForward() {
    if (currentPage != NULL && currentPage->next != NULL) {
        currentPage = currentPage->next;
        printf("-> Forward to: %s\n", currentPage->url);
    } else {
        printf("Cannot go forward. No next page.\n");
    }
}

void showCurrentPage() {
    if (currentPage != NULL) {
        printf("Currently on page: %s\n", currentPage->url);
    } else {
        printf("Browser history is empty.\n");
    }
}

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\n--- Browser Navigation Menu ---\n");
        printf("1. Visit a page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show Current Page\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%99s", url);
                visitPage(url);
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrentPage();
                break;
            case 5:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}