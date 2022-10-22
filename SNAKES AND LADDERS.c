#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Creating a node
struct node {
    int value;
    int type;
    struct node* destination;
    struct node* next; 
};

// Creating a shorter way to type struct node to save time
typedef struct node node;

// printing the linked list
void printList(node* head) {
    node* temp = head;

    while(temp != NULL) {
        printf("%d %d - ", temp->value, temp->type);
        temp = temp -> next;
    }
}

// Creating a new node
node* create_new_node(int value) {
    node* result = malloc(sizeof(node));
    result -> type = 0;
    result -> value = value;
    result -> next = NULL;
    return result;
}

// finding a speciffic node in the list
node* find_node(node *head, int value){
    node* tmp = head;
    while (tmp != NULL) {
        if (tmp ->value == value ) return tmp;
        tmp = tmp -> next;
    }
    return NULL;
}

//-------------------------------------------------------------------------------------------------------------

// Generating a random dice roll
int dice() {
    return (rand() % 6 + 1);
}

// generating a random number between 1 and 10
int random_number() {
    return 1 + (rand() % 10);
}

// Generating the size of the board
int sizeOfBoard() {
    return 32 + (rand() % 33);
}


int main(){
    int seed = time(NULL);
    srand(seed); // Problem seed: 1651435308
    printf("Seed: %d\n", seed);

    // Opening the connection to a file
    FILE *game_summary = fopen("GameSummary.txt", "w");
    if (game_summary == NULL) {
        printf("Error ");
    }
    node *head = create_new_node(1);
    node *tmp;
    node* player;
    int ladders = 0;
    int snakes = 0;



    // Storing and printing the size of the board.
    int boardSize = sizeOfBoard();
    printf("The size of the board ---> %d\n", boardSize);
    


    // Getting the user input on how many snakes are needted
    printf("How many snakes   ---> ");
    scanf("%d", &snakes);



    // Getting the user input on how many ladders are needed
    printf("How many laddders ---> ");
    scanf("%d", &ladders);

    // Creates the board for the game
    node* curNode = head;
    for (int i = 2; i <= boardSize; i++) {
        curNode->next = create_new_node(i);
        curNode = curNode->next;
    }

    
    // Setting the head of snakes to value 1;
    for (int i = 0; i < snakes; i++) {
        int random_number = 2 + (rand() % (boardSize - 2));
        node* found_node = find_node(head, random_number);
        if (found_node != NULL) {
            found_node->type = 1;
        }
    }

    // Setting the head of the ladders value to 2
    for (int i = 0; i<= ladders; i++) {
        int random_number = 2 + (rand() % (boardSize - 2));
        node* found_node = find_node(head, random_number);
        if (found_node != NULL && found_node->type != 1) {
            found_node->type = 2;
        }
    }

    
    // Putting the snakes and ladders on the board
    for (int j = 1; j <= boardSize; j++) {
        node* found_node = find_node(head, j);
        // Inserting the snakes on the board
        if (found_node->type == 1) {
            int dest = found_node-> value - random_number(); 
            if (dest < 1) {
                dest = 1;
            }
            node* n = find_node(head, dest);
            found_node->destination = n;
            
        }
        // inserting the ladders onto the board
        else if (found_node->type == 2) {
            int dest = found_node->value + random_number(); 
            if (dest > boardSize) {
                dest = boardSize;
            }
            node* n = find_node(head, dest);
            found_node->destination = n;
            
        }
    }

    player = head;
    // printing the boardsize, number of snakes, number of ladders
    fprintf(game_summary, "Board Size ---> %d\n", boardSize);
    fprintf(game_summary, "Number of Snakes ---> %d\n", snakes);
    fprintf(game_summary, "Number of Ladders ---> %d\n", ladders);
     do {
         int diceRoll = dice();
         // printing the dice roll
         fprintf(game_summary, "Rolled a %d: ", diceRoll);
         
         // printing where the player moved to
         fprintf(game_summary, "Moved %d ---> ", player->value);
         for (int i = 0; i < diceRoll; i++) {
             if (player->next == NULL) { break; }
             player = player->next;
         }
         fprintf(game_summary, "%d, ", player->value);

         // Checking if the player landed on a snake
         if (player->type == 1) {
             fprintf(game_summary, "Landed on a snake: %d ---> %d", player->value, player->destination->value);
             player = player->destination;
         }
         // Checking if the player landed on a ladder
         else if (player->type == 2) {
             fprintf(game_summary, "Landed on a ladder: %d ---> %d", player->value, player->destination->value);
             player = player->destination;
         }
         fprintf(game_summary, "\n");
     } while(player->value != boardSize);

     // Closing the connection to the file
    fclose(game_summary);

     // Printing the list
    printList(head);

    
}