#include <stdio.h>
#include <stdlib.h>

struct PolyNode {
    int coeff;
    int exp_x;
    int exp_y;
    struct PolyNode* next;
};

// Inserts a term into the polynomial. If a term with the same exponents
// exists, their coefficients are added. Otherwise, a new term is appended.
void insertTerm(struct PolyNode** poly, int coeff, int exp_x, int exp_y) {
    if (coeff == 0) return;

    struct PolyNode* current = *poly;
    struct PolyNode* last = NULL;

    while (current != NULL) {
        if (current->exp_x == exp_x && current->exp_y == exp_y) {
            current->coeff += coeff;
            return;
        }
        last = current;
        current = current->next;
    }
    
    struct PolyNode* newTerm = (struct PolyNode*)malloc(sizeof(struct PolyNode));
    newTerm->coeff = coeff;
    newTerm->exp_x = exp_x;
    newTerm->exp_y = exp_y;
    newTerm->next = NULL;

    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        last->next = newTerm;
    }
}

// Displays the polynomial, skipping any terms with a zero coefficient.
void displayPoly(struct PolyNode* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    struct PolyNode* temp = poly;
    int first_term = 1;

    while (temp != NULL) {
        if(temp->coeff != 0) {
            if (!first_term && temp->coeff > 0) {
                 printf(" + ");
            } else if (!first_term && temp->coeff < 0) {
                 printf(" - ");
            }
            
            int c = temp->coeff > 0 ? temp->coeff : -temp->coeff;
            if (first_term && temp->coeff < 0) printf("-");

            printf("%dx^%dy^%d", c, temp->exp_x, temp->exp_y);
            first_term = 0;
        }
        temp = temp->next;
    }

    if (first_term) {
        printf("0");
    }
    printf("\n");
}

// Adds two polynomials by creating a new result polynomial.
struct PolyNode* addPolynomials(struct PolyNode* poly1, struct PolyNode* poly2) {
    struct PolyNode* result = NULL;
    struct PolyNode *p1 = poly1, *p2 = poly2;

    while (p1 != NULL) {
        insertTerm(&result, p1->coeff, p1->exp_x, p1->exp_y);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertTerm(&result, p2->coeff, p2->exp_x, p2->exp_y);
        p2 = p2->next;
    }
    
    return result;
}

void freePoly(struct PolyNode** poly) {
    struct PolyNode* current = *poly;
    struct PolyNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *poly = NULL;
}

int main() {
    struct PolyNode *poly1 = NULL, *poly2 = NULL, *sum = NULL;
    int n, i, c, ex, ey;

    printf("--- Polynomial 1 ---\n");
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter coeff, exp_x, exp_y for term %d: ", i + 1);
        scanf("%d %d %d", &c, &ex, &ey);
        insertTerm(&poly1, c, ex, ey);
    }

    printf("\n--- Polynomial 2 ---\n");
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter coeff, exp_x, exp_y for term %d: ", i + 1);
        scanf("%d %d %d", &c, &ex, &ey);
        insertTerm(&poly2, c, ex, ey);
    }

    printf("\nPolynomial 1: ");
    displayPoly(poly1);
    printf("Polynomial 2: ");
    displayPoly(poly2);

    sum = addPolynomials(poly1, poly2);

    printf("\nSum: ");
    displayPoly(sum);

    freePoly(&poly1);
    freePoly(&poly2);
    freePoly(&sum);

    return 0;
}