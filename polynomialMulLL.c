#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coeff;
    int exp;
    struct Term* next;
};

void insertTerm(struct Term** poly, int c, int e) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coeff = c;
    newTerm->exp = e;
    newTerm->next = NULL;

    if (*poly == NULL || (*poly)->exp < e) {
        newTerm->next = *poly;
        *poly = newTerm;
        return;
    }

    struct Term* temp = *poly;
    while (temp->next != NULL && temp->next->exp >= e) {
        temp = temp->next;
    }

    if (temp->exp == e) {
        temp->coeff += c;
    } else {
        newTerm->next = temp->next;
        temp->next = newTerm;
    }
}

void display(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    while (poly != NULL) {
        if(poly->coeff != 0) {
            printf("%dx^%d", poly->coeff, poly->exp);
            if (poly->next != NULL && poly->next->coeff != 0) {
                printf(" + ");
            }
        }
        poly = poly->next;
    }
    printf("\n");
}

struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term *p1 = poly1, *p2 = poly2;
    while (p1 != NULL) {
        insertTerm(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        insertTerm(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }
    return result;
}

struct Term* multiplyPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term *p1 = poly1, *p2;

    if (!poly1 || !poly2) return NULL;

    while (p1 != NULL) {
        p2 = poly2;
        while (p2 != NULL) {
            insertTerm(&result, p1->coeff * p2->coeff, p1->exp + p2->exp);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return result;
}

void freePoly(struct Term** poly) {
    struct Term* current = *poly;
    struct Term* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *poly = NULL;
}

int main() {
    struct Term *poly1 = NULL, *poly2 = NULL;
    int n, i, c, e;

    printf("--- Polynomial 1 ---\n");
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter coeff and exp for term %d: ", i + 1);
        scanf("%d %d", &c, &e);
        insertTerm(&poly1, c, e);
    }

    printf("\n--- Polynomial 2 ---\n");
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter coeff and exp for term %d: ", i + 1);
        scanf("%d %d", &c, &e);
        insertTerm(&poly2, c, e);
    }

    printf("\nPolynomial 1: ");
    display(poly1);
    printf("Polynomial 2: ");
    display(poly2);

    int choice;
    printf("\n--- Operations ---\n");
    printf("1. Addition\n");
    printf("2. Multiplication\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        struct Term* sum = addPolynomials(poly1, poly2);
        printf("\nSum: ");
        display(sum);
        freePoly(&sum);
    } else if (choice == 2) {
        struct Term* product = multiplyPolynomials(poly1, poly2);
        printf("\nProduct: ");
        display(product);
        freePoly(&product);
    } else {
        printf("Invalid choice.\n");
    }

    freePoly(&poly1);
    freePoly(&poly2);

    return 0;
}
