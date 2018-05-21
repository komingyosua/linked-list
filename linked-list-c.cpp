#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define ff fflush(stdin)

struct Motorcycle{
    char name[100];
    int qty;
    char status[100];
    int priority;
    Motorcycle *next, *prev;
}*head, *tail, *curr;

void menu(){
    printf("BLUE MOTORCYCLE PARTS\n");
    printf(".....................\n\n");
    printf("1. View Order List\n");
    printf("2. Add New Order\n");
    printf("3. Take Order\n");
    printf("4. Search\n");
    printf("5. Exit\n");
    printf(">> Input choice : ");
}

void print(){
    int id = 1;
    printf("--- ORDER LIST ---\n\n");
    printf("-------+--------------------------------+-----------\n");
    printf("| No.  | Name of Parts                  | Quantity |  Status |\n");
    printf("-------+--------------------------------+-----------\n");

    if(head == NULL){
        puts("");
    }else{
        curr = head;
        while(curr){
            printf("|   %d. | %s                          |       %d | %s |\n", id, curr->name, curr->qty, curr->status);
            id++;
            curr = curr->next;

        }
    }

    printf("-------+--------------------------------+-----------\n");
}


void pushHead(int qty, char name[], char status[]){
    curr = (Motorcycle*) malloc(sizeof(Motorcycle));
    strcpy(curr->name, name);
    curr->qty = qty;
    strcpy(curr->status, status);

    curr->next = curr->prev = NULL;

    if(head == NULL){
        head = tail = curr;
    }else{
        curr->next = head;
        head->prev = curr;
        curr = head;
    }
}

void pushTail(int qty, char name[], char status[]){
    curr = (Motorcycle*) malloc(sizeof(Motorcycle));
    strcpy(curr->name, name);
    curr->qty = qty;
    strcpy(curr->status, status);

    curr->next = curr->prev = NULL;

    if(head == NULL){
        head = tail = curr;
    }else{
        tail->next = curr;
        curr->prev = tail;
        curr = tail;
    }
}

void pushMid(int qty, char name[], char status[]){
    if(head == NULL){
        pushHead(qty, name, status);
    }else if(name < head->name){
        pushHead(qty, name, status);
    }else if(name > tail->name){
        pushTail(qty, name, status);
    }else{
        curr = (Motorcycle*) malloc(sizeof(Motorcycle));
        strcpy(curr->name, name);
        curr->qty = qty;
        strcpy(curr->status, status);

        curr->next = curr->prev = NULL;

        Motorcycle *temp = head;

        while(temp != NULL && temp->name < curr->name){
            temp = temp->next;
        }

        curr->prev = temp->prev;
        curr->next = temp;

        temp->prev->next = curr;
        temp->prev = curr;
    }
}

void priority(int qty, char name[], char status[]){
    curr = (Motorcycle*) malloc(sizeof(Motorcycle));
    strcpy(curr->name, name);
    curr->qty = qty;
    strcpy(curr->status, status);

    if(strcmp(curr->status, "High") == 0){
        curr->priority = 3;
    }else if(strcmp(curr->status, "Medium") == 0){
        curr->priority = 2;
    }else if(strcmp(curr->status, "Low") == 0){
        curr->priority = 1;
    }

    curr->next = curr->prev = NULL;
    if(head == NULL){
        head = tail = curr;
    }else{
        Motorcycle *temp = head;

        while(temp != NULL){
            if(curr->priority > temp->priority){
                if(temp == head){
                    pushHead(qty, name, status);
                }else{
                    curr->prev = temp->prev;
                    curr->next = temp;

                    temp->prev->next = curr;
                    temp->prev = curr;
                }
                break;
            }
            temp = temp->next;
        }

        if(temp == NULL){
            pushTail(qty, name, status);
        }
    }
}


void popHead(){
    if(head == NULL){
        printf("No data to delete");
    }else if(head == tail){
        curr = head;
        head = tail = NULL;
        free(curr);
    }else{
        curr = head;
        head = head->next;
        free(curr);
        head->prev = NULL;
    }
}

void popAll(){
    curr = head;
    while(curr != NULL){
        popHead();
    }
}

void popTail(){
    if(head == NULL){
        printf("No data to delete");
    }else if(head == tail){
        curr = tail;
        head = tail = NULL;
        free(curr);
    }else{
        curr = tail;
        tail = tail->prev;
        free(curr);
        tail->next = NULL;
    }
}

void popMid(int no){
	int temu = 0;

	if(head == NULL){
		printf("No Data\n");
	}else{
		curr = head;
		for(int i = 0; i < no; i++){
            temu = 1;
            break;
			curr = curr->next;
		}

		if(temu == 1){
			if(curr == head){
				popHead();
			}else if(curr == tail){
				popTail();
			}else{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(curr);
			}
		}else{
			printf("Data Not Found\n");
		}
	}
}

void searchData(char name[]){
    int i = 1, key = 0;
    curr = head;

    while(curr != NULL){
        if(strcmp(curr->name , name) == 0){
            key = 1;
            printf("%d %s %d %s", i, curr->name, curr->qty, curr->status);
        }
        i++;
        curr = curr->next;
    }

    if(key != 1){
        printf("Not Found");
    }

}

int main(){
    int choice;

    do{
        system("cls");
        menu();
        scanf("%d", &choice);ff;

        switch(choice){
        case 1:
            system("cls");
            print();
            getchar();
            break;
        case 2:
            char name[100];
            char status[100];
            int qty;

            printf("Input Name of Motorcycle's Part [3..30]: ");
            scanf("%[^\n]", &name);ff;

            printf("Input Quantity of The Motorcycle's Part [1..20]: ");
            scanf("%d", &qty);ff;

            printf("Input Priority [High, Medium, Low]: ");
            scanf("%s", &status);ff;

            priority(qty, name, status);
            getchar();
            break;
        case 3:
            int no;

            print();

            printf("Input Number of The Order [1..1]: ");
            scanf("%d", &no);

            popMid(no);
            getchar();
            break;

        case 4:
            printf("Input Name of Motorcycle's Part [3..30]: ");
            scanf("%[^\n]", &name);ff;

            searchData(name);
            getchar();
            break;
        }
    }while(choice != 5);



    getchar();
    return 0;
}
