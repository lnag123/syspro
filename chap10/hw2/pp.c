#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode) {
        perror("Memory Error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*tail) {
        (*tail)->next = newNode;
    } else {
        *head = newNode;
    }
    *tail = newNode;
}

int delete(struct node **head, struct node **tail) {
    if (!*head) {
        printf("Queue is empty\n");
        return -1;
    }

    struct node *temp = *head;
    int data = temp->data;
    *head = temp->next;
    if (!*head) {
        *tail = NULL;
    }
    free(temp);
    return data;
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int input;

    while (scanf("%d", &input) == 1) {
		if (input < 0) {
            break;
        }
        addq(&head, &tail, input);
    }
	printf("Print queue\n");
    while (head) {
        printf("%d\n", delete(&head, &tail));
    }
    return 0;
}

