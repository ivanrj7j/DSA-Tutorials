#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentNode {
    int number;
    char name[50];
    float total_mark;
    struct StudentNode* next;
};

struct StudentNode* createStudent(int num, const char* name, float mark) {
    struct StudentNode* newNode = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    newNode->number = num;
    strcpy(newNode->name, name);
    newNode->total_mark = mark;
    newNode->next = NULL;
    return newNode;
}

void insertStudent(struct StudentNode** head, int num, const char* name, float mark) {
    struct StudentNode* newStudent = createStudent(num, name, mark);
    newStudent->next = *head;
    *head = newStudent;
    printf("Inserted student %d.\n", num);
}

void deleteStudent(struct StudentNode** head, int num) {
    struct StudentNode *temp = *head, *prev = NULL;

    if (temp != NULL && temp->number == num) {
        *head = temp->next;
        free(temp);
        printf("Deleted student %d.\n", num);
        return;
    }

    while (temp != NULL && temp->number != num) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with number %d not found.\n", num);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Deleted student %d.\n", num);
}

void searchStudent(struct StudentNode* head, int num) {
    struct StudentNode* current = head;
    while (current != NULL) {
        if (current->number == num) {
            printf("Found Student -> Number: %d, Name: %s, Marks: %.2f\n",
                   current->number, current->name, current->total_mark);
            return;
        }
        current = current->next;
    }
    printf("Student with number %d not found.\n", num);
}

void sortList(struct StudentNode* head) {
    if (head == NULL || head->next == NULL) {
        if(head) printf("List sorted or has one element.\n");
        else printf("List is empty, cannot sort.\n");
        return;
    }
    int swapped;
    struct StudentNode *ptr1;
    struct StudentNode *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->number > ptr1->next->number) {
                int tempNum = ptr1->number;
                char tempName[50];
                strcpy(tempName, ptr1->name);
                float tempMark = ptr1->total_mark;

                ptr1->number = ptr1->next->number;
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->total_mark = ptr1->next->total_mark;

                ptr1->next->number = tempNum;
                strcpy(ptr1->next->name, tempName);
                ptr1->next->total_mark = tempMark;
                
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("List sorted by student number.\n");
}

void displayStudents(struct StudentNode* head) {
    if (head == NULL) {
        printf("The student list is empty.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    struct StudentNode* temp = head;
    while (temp != NULL) {
        printf("Number: %-5d | Name: %-20s | Marks: %.2f\n",
               temp->number, temp->name, temp->total_mark);
        temp = temp->next;
    }
    printf("--------------------\n");
}

int main() {
    struct StudentNode* head = NULL;
    int choice, num;
    char name[50];
    float mark;

    while (1) {
        printf("\n--- Student Records Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Sort\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Number: ");
                scanf("%d", &num);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Mark: ");
                scanf("%f", &mark);
                insertStudent(&head, num, name, mark);
                displayStudents(head);
                break;
            case 2:
                printf("Enter Number to Delete: ");
                scanf("%d", &num);
                deleteStudent(&head, num);
                displayStudents(head);
                break;
            case 3:
                printf("Enter Number to Search: ");
                scanf("%d", &num);
                searchStudent(head, num);
                break;
            case 4:
                sortList(head);
                displayStudents(head);
                break;
            case 5:
                displayStudents(head);
                break;
            case 6:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}