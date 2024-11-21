#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data);
int pop(struct node **top);
void printStack(struct node *top);

int main() {
    int data;
    struct node *top = NULL;

    while (1) {
        if (scanf("%d", &data) == 1) {
            push(&top, data);
        } else {
            if (feof(stdin) || ferror(stdin)) {
                break;
            } else {
                printStack(top);
                break;
            }
        }
    }

    return 0;
}

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *top;
    int poppedValue = temp->data;
    *top = temp->next;
    free(temp);

    return poppedValue;
}

void printStack(struct node *top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Print stack\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}
