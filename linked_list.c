#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
void createList(struct Node** head);
void insertAtPosition(struct Node** head, int data, int position);
void insertAfterNode(struct Node* head, int data, int after);
void insertBeforeNode(struct Node** head, int data, int before);
void deleteAtPosition(struct Node** head, int position);
void displayList(struct Node* head);
void searchList(struct Node* head, int data);
int getLength(struct Node* head);

int main() {
    struct Node* head = NULL;
    int choice, data, position, key;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create the list\n");
        printf("2. Insert an element at any position\n");
        printf("3. Insert after a node\n");
        printf("4. Insert before a node\n");
        printf("5. Delete an element from any position\n");
        printf("6. Display the list\n");
        printf("7. Search for an element\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createList(&head);
                break;
            case 2:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                printf("Enter the position to insert: ");
                scanf("%d", &position);
                insertAtPosition(&head, data, position);
                break;
            case 3:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                printf("Enter the data of the node to insert after: ");
                scanf("%d", &key);
                insertAfterNode(head, data, key);
                break;
            case 4:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                printf("Enter the data of the node to insert before: ");
                scanf("%d", &key);
                insertBeforeNode(&head, data, key);
                break;
            case 5:
                printf("Enter the position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;
            case 6:
                displayList(head);
                break;
            case 7:
                printf("Enter the data to search: ");
                scanf("%d", &data);
                searchList(head, data);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void createList(struct Node** head) {
    int n, data;
    struct Node *newNode, *temp;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);

        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
        } else {
            temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}

void insertAtPosition(struct Node** head, int data, int position) {
    struct Node *newNode, *temp;
    int len = getLength(*head);

    if (position < 1 || position > len + 1) {
        printf("Invalid position!\n");
        return;
    }

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
    } else {
        temp = *head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void insertAfterNode(struct Node* head, int data, int after) {
    struct Node *newNode, *temp;

    temp = head;
    while (temp != NULL && temp->data != after) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node with data %d not found!\n", after);
        return;
    }

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertBeforeNode(struct Node** head, int data, int before) {
    struct Node *newNode, *temp, *prev = NULL;

    temp = *head;
    while (temp != NULL && temp->data != before) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node with data %d not found!\n", before);
        return;
    }

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = temp;

    if (prev == NULL) {
        *head = newNode;
    } else {
        prev->next = newNode;
    }
}

void deleteAtPosition(struct Node** head, int position) {
    struct Node *temp, *prev;
    int len = getLength(*head);

    if (position < 1 || position > len) {
        printf("Invalid position!\n");
        return;
    }

    temp = *head;

    if (position == 1) {
        *head = temp->next;
        free(temp);
    } else {
        for (int i = 1; i < position; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        free(temp);
    }
}

void displayList(struct Node* head) {
    struct Node* temp = head;

    if (temp == NULL) {
        printf("List is empty!\n");
        return;
    }

    printf("List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void searchList(struct Node* head, int data) {
    struct Node* temp = head;
    int position = 1;

    while (temp != NULL) {
        if (temp->data == data) {
            printf("Element %d found at position %d\n", data, position);
            return;
        }
        temp = temp->next;
        position++;
    }

    printf("Element %d not found in the list\n", data);
}

int getLength(struct Node* head) {
    struct Node* temp = head;
    int length = 0;

    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    return length;
}