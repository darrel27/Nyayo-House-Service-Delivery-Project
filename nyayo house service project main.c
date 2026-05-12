#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define AVG_SERVICE_TIME 5   // average minutes per customer

// ---------------- CUSTOMER STRUCT ----------------
typedef struct {
    char name[50];
    int priorityCategory;   // 0=Normal, 1=Emergency, 2=VIP, 3=PWD, 4=Elderly, 5=Expectant
    time_t joinTime;
} Customer;

// ---------------- QUEUE STRUCT ----------------
typedef struct {
    Customer data[MAX];
    int front, rear;
} Queue;

// ---------------- QUEUE FUNCTIONS ----------------
void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, Customer c) {
    if (isFull(q)) {
        printf("\nQueue is FULL. Cannot add more customers.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->data[q->rear] = c;
}

Customer dequeue(Queue *q) {
    Customer temp = {"EMPTY", 0, 0};
    if (isEmpty(q)) return temp;

    temp = q->data[q->front];

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return temp;
}

// ---------------- DISPLAY QUEUE ----------------
void displayQueue(Queue *q, char label[]) {
    printf("\n--- %s ---\n", label);

    if (isEmpty(q)) {
        printf("[EMPTY]\n");
        return;
    }

    for (int i = q->front; i <= q->rear; i++) {
        printf("%d) %s | Joined: %s",
            i - q->front + 1,
            q->data[i].name,
            ctime(&q->data[i].joinTime)
        );
    }
}

// ---------------- SEARCH CUSTOMER ----------------
int searchQueue(Queue *q, char name[]) {
    if (isEmpty(q)) return -1;

    for (int i = q->front; i <= q->rear; i++) {
        if (strcmp(q->data[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// ---------------- REMOVE CUSTOMER ----------------
void removeFromQueue(Queue *q, char name[]) {
    if (isEmpty(q)) {
        printf("\nQueue is empty.\n");
        return;
    }

    int index = searchQueue(q, name);
    if (index == -1) {
        printf("\nCustomer NOT found.\n");
        return;
    }

    for (int i = index; i < q->rear; i++) {
        q->data[i] = q->data[i + 1];
    }
    q->rear--;

    if (q->rear < q->front) {
        q->front = q->rear = -1;
    }

    printf("\nCustomer '%s' removed successfully.\n", name);
}

// ---------------- ESTIMATED WAIT TIME ----------------
int estimateWait(Queue *q) {
    if (isEmpty(q)) return 0;

    int size = q->rear - q->front + 1;
    return size * AVG_SERVICE_TIME;
}

// ---------------- SERVE NEXT CUSTOMER ----------------
Customer serveNext(Queue *emQ, Queue *vipQ, Queue *pwdQ, Queue *eldQ, Queue *exQ, Queue *normalQ) {

    if (!isEmpty(emQ)) return dequeue(emQ);
    if (!isEmpty(vipQ)) return dequeue(vipQ);
    if (!isEmpty(pwdQ)) return dequeue(pwdQ);
    if (!isEmpty(eldQ)) return dequeue(eldQ);
    if (!isEmpty(exQ)) return dequeue(exQ);
    if (!isEmpty(normalQ)) return dequeue(normalQ);

    Customer none = {"EMPTY", 0, 0};
    return none;
}

// ---------------- MAIN PROGRAM ----------------
int main() {
    Queue emergencyQ, vipQ, pwdQ, elderlyQ, expectantQ, normalQ;

    initQueue(&emergencyQ);
    initQueue(&vipQ);
    initQueue(&pwdQ);
    initQueue(&elderlyQ);
    initQueue(&expectantQ);
    initQueue(&normalQ);

    int choice;
    int totalServed = 0;

    while (1) {
        printf("\n=============== NYAYO HOUSE SERVICE SYSTEM ===============\n");
        printf("1. Add Normal Customer\n");
        printf("2. Add Priority Customer\n");
        printf("3. Display All Queues\n");
        printf("4. Serve Next Customer\n");
        printf("5. Search Customer\n");
        printf("6. Remove Customer\n");
        printf("7. Show Statistics\n");
        printf("8. Exit\n");
        printf("===========================================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            Customer c;
            printf("Enter name: ");
            fgets(c.name, 50, stdin);
            c.name[strcspn(c.name, "\n")] = 0;
            c.priorityCategory = 0;
            c.joinTime = time(NULL);

            enqueue(&normalQ, c);
            printf("\nAdded to NORMAL queue.\n");

        } else if (choice == 2) {
            Customer c;
            int cat;

            printf("Enter name: ");
            fgets(c.name, 50, stdin);
            c.name[strcspn(c.name, "\n")] = 0;

            printf("\nChoose Priority Category:\n");
            printf("1. Emergency / Medical\n");
            printf("2. Diplomatic / VIP\n");
            printf("3. Persons with Disabilities (PWD)\n");
            printf("4. Elderly (60+)\n");
            printf("5. Expectant Mothers\n");
            printf("Enter category: ");
            scanf("%d", &cat);
            getchar();

            c.priorityCategory = cat;
            c.joinTime = time(NULL);

            switch (cat) {
                case 1: enqueue(&emergencyQ, c); break;
                case 2: enqueue(&vipQ, c); break;
                case 3: enqueue(&pwdQ, c); break;
                case 4: enqueue(&elderlyQ, c); break;
                case 5: enqueue(&expectantQ, c); break;
                default: printf("Invalid category!\n");
            }

            printf("\nPriority customer added.\n");

        } else if (choice == 3) {
            displayQueue(&emergencyQ, "Emergency Queue");
            displayQueue(&vipQ, "VIP Queue");
            displayQueue(&pwdQ, "PWD Queue");
            displayQueue(&elderlyQ, "Elderly Queue");
            displayQueue(&expectantQ, "Expectant Mothers Queue");
            displayQueue(&normalQ, "Normal Queue");

        } else if (choice == 4) {
            Customer served = serveNext(&emergencyQ, &vipQ, &pwdQ, &elderlyQ, &expectantQ, &normalQ);

            if (strcmp(served.name, "EMPTY") == 0) {
                printf("\nNo customers in queue.\n");
            } else {
                time_t now = time(NULL);
                int waited = (int) difftime(now, served.joinTime) / 60;

                printf("\nServing: %s\n", served.name);
                printf("Wait Time: %d minutes\n", waited);

                totalServed++;
            }

        } else if (choice == 5) {
            char name[50];
            printf("Enter name to search: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;

            int found = 0;

            if (searchQueue(&emergencyQ, name) != -1) { printf("Found in Emergency Queue\n"); found = 1; }
            if (searchQueue(&vipQ, name) != -1) { printf("Found in VIP Queue\n"); found = 1; }
            if (searchQueue(&pwdQ, name) != -1) { printf("Found in PWD Queue\n"); found = 1; }
            if (searchQueue(&elderlyQ, name) != -1) { printf("Found in Elderly Queue\n"); found = 1; }
            if (searchQueue(&expectantQ, name) != -1) { printf("Found in Expectant Mothers Queue\n"); found = 1; }
            if (searchQueue(&normalQ, name) != -1) { printf("Found in Normal Queue\n"); found = 1; }

            if (!found) printf("Customer NOT found.\n");

        } else if (choice == 6) {
            char name[50];
            printf("Enter name to remove: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;

            removeFromQueue(&emergencyQ, name);
            removeFromQueue(&vipQ, name);
            removeFromQueue(&pwdQ, name);
            removeFromQueue(&elderlyQ, name);
            removeFromQueue(&expectantQ, name);
            removeFromQueue(&normalQ, name);

        } else if (choice == 7) {
            printf("\n------- SYSTEM STATISTICS -------\n");
            printf("Total Customers Served: %d\n", totalServed);
            printf("Current Queue Sizes:\n");
            printf("Emergency: %d\n", emergencyQ.rear - emergencyQ.front + 1);
            printf("VIP: %d\n", vipQ.rear - vipQ.front + 1);
            printf("PWD: %d\n", pwdQ.rear - pwdQ.front + 1);
            printf("Elderly: %d\n", elderlyQ.rear - elderlyQ.front + 1);
            printf("Expectant: %d\n", expectantQ.rear - expectantQ.front + 1);
            printf("Normal: %d\n", normalQ.rear - normalQ.front + 1);

        } else if (choice == 8) {
            printf("\nExiting system. Goodbye.\n");
            break;

        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
