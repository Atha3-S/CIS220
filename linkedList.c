//Merkins, William
//Chpt4 PA

#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a structure for the list itself
typedef struct List {
    Node* head;
    Node* tail;
} List;

// Function to allocate memory for a new node and initialize it with data
Node* allocateNewNode(int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty list
void initList(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Function to append a node to the list, pseudocode found in PA 4.2.6
void ListAppendNode(List* list, Node* newNode) {
	// If list is empty, new head and tail node
    if (list->head == NULL) {  
        list->head = newNode;
        list->tail = newNode;
	// list not empty, new tail node	
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Function to append an item to the list, pseudocode found in PA 4.2.6
void ListAppend(List* list, int item) {
	// Create node to add
    Node* newNode = allocateNewNode(item);
    ListAppendNode(list, newNode);
}

// Function to prepend a node to the list, pseudocode found in PA 4.2.9
void ListPrependNode(List* list, Node* newNode) {
	// If list is empty, new head and tail node
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
		// list not empty, new head node
        newNode->next = list->head;
        list->head = newNode;
    }
}

// Function to prepend an item to the list, pseudocode found in PA 4.2.9
void ListPrepend(List* list, int item) {
	// Create node to add
    Node* newNode = allocateNewNode(item);
    ListPrependNode(list, newNode);
}

// Function searches for a node with a specific data value, pseudocode found in PA 4.3.1 
Node* ListSearch(List *list, int key) {
    Node *curNode = list->head;
    while (curNode != NULL) {
        if (curNode->data == key) {
            return curNode;
        }
        curNode = curNode->next;
    }
    return NULL;
}

// Function to insert a node after a specific node in the list, pseudocode found in PA 4.3.4
void ListInsertNodeAfter(List* list, Node* currentNode, Node* newNode) {
    // If list is empy, new head and tail node
	if (list->head == NULL) {  
        list->head = newNode;
        list->tail = newNode;
	// Inserting after list's tail node, new tail node
    } else if (currentNode == list->tail) {
        list->tail->next = newNode;
        list->tail = newNode;
	// Inserting in middle of list
    } else {
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
}

// Function to insert a new item after a specific item, pseudocode found in Figure 4.3.1
int ListInsertAfter(List *list, int currentItem, int newItem) {
	// Search for the node to insert after
    Node *currentNode = ListSearch(list, currentItem);    
    if (currentNode != NULL) {
        Node *newNode = allocateNewNode(newItem);
		// Call ListInsertNodeAfter method
        ListInsertNodeAfter(list, currentNode, newNode);
		// Success
        return 1; 
    }
	// Failure
    return 0; 
}

// Function to remove a node after a specific node in the list, pseudocode found in PA 4.4.1
void ListRemoveNodeAfter(List* list, Node* curNode) {
    Node* sucNode;
	// Special case, remove head
    if (curNode == NULL) {  // Special case, remove head
        sucNode = list->head->next;
        list->head = sucNode;
		// Removed last item
        if (sucNode == NULL) {  
            list->tail = NULL;
        }
	// Node exists after curNode
    } else if (curNode->next != NULL) {
        sucNode = curNode->next->next;
        curNode->next = sucNode;
		// Removed tail, set tail to curNode
        if (sucNode == NULL) {  
            list->tail = curNode;
        }
    }
}

// Function to remove a node with a specific data value, pseudocode found in Figure 4.4.1
int ListRemove(List *list, int itemToRemove) {
    Node *previous = NULL;
    Node *current = list->head;    
    while (current != NULL) {
        if (current->data == itemToRemove) {
			// Call ListRemoveNodeAfter method
            ListRemoveNodeAfter(list, previous);
            // Success
			return 1; 
        }
        previous = current;
        current = current->next;
    }
    // Not found
    return 0; 
}

// Function to traverse and print the list, pseudocode found in PA 4.8.1
void ListTraverse(List* list) {
	// Start at head
    Node* curNode = list->head;  
    while (curNode != NULL) {
		// Prints the node's data
        printf("%d -> ", curNode->data); 
        // Traverse to next node in the list		
        curNode = curNode->next;
    }
    printf("NULL\n");
}

// Function to find the insertion position for a data value, pseudocode found in figure 4.9.1 
Node* ListFindInsertionPosition(List* list, int dataValue) {
	// curNodeA keeps track of the node before the insertion position
    Node* curNodeA = NULL;
	// curNodeB starts at the head and traverses the list list
    Node* curNodeB = list->head;
	// Traverse the list until we find the correct insertion position
	// Stop when curNodeB is null (end of list) or dataValue is small than or equal to curNode
    while (curNodeB != NULL && dataValue > curNodeB->data) {
		// Move curNodeA to curNodeB (keeping track of previous node)
        curNodeA = curNodeB;
		// Move curNodeB to the next node
        curNodeB = curNodeB->next;
    }
	// Return curNodeA, which is the node after which the new value should be inserted
	// If curNodeA is null, it means the new value should be inserted at the head
    return curNodeA;
}

// Function to perform insertion sort on the list, pseudocode found in PA 4.9.1
void ListInsertionSortSinglyLinked(List* list) {
	// Initalize beforeCurrent to the head of the list
    Node* beforeCurrent = list->head;
	// Start curNode from the second node (if head is not null)
    Node* curNode = list->head ? list->head->next : NULL;
	// Traverse through the linked list
    while (curNode != NULL) {
		// Store the next node before manipulating curNode
        Node* next = curNode->next;
		// Find the correct position for curNode in the sorted portion of the list
        Node* position = ListFindInsertionPosition(list, curNode->data);
		// If curNode is already in the correct position, move beforeCurrent foward
        if (position == beforeCurrent) {
            beforeCurrent = curNode;
        } else {
			// Removes the curNode from its current position
            ListRemoveNodeAfter(list, beforeCurrent);
			// If position is null, curNode should be inserted at the beginning
            if (position == NULL) {
                ListPrependNode(list, curNode);
            } else {
				// Insert curNode after the found position
                ListInsertNodeAfter(list, position, curNode);
            }
        }
		// Move to the next node in the original list
        curNode = next;
    }
}

// Function to sum the data values of all nodes in the list
int sumDataValues(List* list) {
    int sum = 0;
    Node* curNode = list->head;
    while (curNode != NULL) {
        sum += curNode->data;
        curNode = curNode->next;
    }
    return sum;
}

// main function
int main() {
    // Initialize the list
    List myList;
    initList(&myList);

    // Display the list
    printf("Initial list: ");
    ListTraverse(&myList);

    // Sum and display the sum of the node values
    int sum = sumDataValues(&myList);
    printf("Sum of node values: %d\n", sum);

    // Append nodes with data values 10 and 20
    ListAppend(&myList, 10);
    ListAppend(&myList, 20);

    // Prepend a node with data value 30
    ListPrepend(&myList, 30);

    // Insert a node with data value 40 after the head node
    ListInsertAfter(&myList, myList.head->data, 40);

    // Insert a node with data value 50 at the end of the list
    ListAppend(&myList, 50);

    // Insert a node with data value 60 after the node with data value 10
    ListInsertAfter(&myList, 10, 60);

    // Insert a node with data value 70 after the node with data value 40
    ListInsertAfter(&myList, 40, 70);

    // Display the list
    printf("List after insertions: ");
    ListTraverse(&myList);

    // Remove the head node
    ListRemoveNodeAfter(&myList, NULL);

    // Remove the node after the node with data value 70
    Node* node70 = ListSearch(&myList, 70);
    if (node70 != NULL) {
        ListRemoveNodeAfter(&myList, node70);
    }

    // Display the list
    printf("List after removals: ");
    ListTraverse(&myList);

    // Search for the node with data value 50
    Node* node50 = ListSearch(&myList, 50);
    if (node50 != NULL) {
        printf("Node with data value 50 found.\n");
    } else {
        printf("Node with data value 50 not found.\n");
    }

    // Search for the node with data value 15
    Node* node15 = ListSearch(&myList, 15);
    if (node15 != NULL) {
        printf("Node with data value 15 found.\n");
    } else {
        printf("Node with data value 15 not found.\n");
    }

    // Sort and display the list
    ListInsertionSortSinglyLinked(&myList);
    printf("Sorted list: ");
    ListTraverse(&myList);

    // Sum and display the sum of the node values
    sum = sumDataValues(&myList);
    printf("Sum of node values after sorting: %d\n", sum);

    return 0;
}
