// Merkins, William
// Chpt7 PA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 10

// Definition of the BST Node
typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Function to create a new BST node
BSTNode* createNode(int key) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Definition of the Binary Search Tree (BST)
typedef struct BST {
    BSTNode* root;
} BST;

// Function to create an empty BST
BST* createBST() {
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

// Get the root of the BST
BSTNode* getRoot(BST* tree) {
    return tree->root;
}

// Recursive search function
BSTNode* searchRecursive(BSTNode* node, int key) {
    if (node == NULL || node->key == key) {
        return node;  // Found or reached the end
    }
    if (key < node->key) {
        return searchRecursive(node->left, key);  // Search in the left subtree
    } else {
        return searchRecursive(node->right, key); // Search in the right subtree
    }
}

// Iterative search function
BSTNode* search(BST* tree, int key) {
    BSTNode* current = tree->root;
    while (current != NULL) {
        if (key == current->key) {
            return current;  // Key found
        }
        current = (key < current->key) ? current->left : current->right;
    }
    return NULL;  // Key not found
}

// Function to check if the tree contains a node with the given key
bool contains(BST* tree, int key) {
    return search(tree, key) != NULL;
}

// Recursive insert function
BSTNode* insertRecursive(BSTNode* parent, BSTNode* nodeToInsert) {
    if (parent == NULL) {
        return nodeToInsert; // Place the new node
    }
    if (nodeToInsert->key < parent->key) {
        parent->left = insertRecursive(parent->left, nodeToInsert);
    } else {
        parent->right = insertRecursive(parent->right, nodeToInsert);
    }
    return parent;
}

// Wrapper function to insert a node
void insertNode(BST* tree, BSTNode* node) {
    if (tree->root == NULL) {
        tree->root = node;
    } else {
        tree->root = insertRecursive(tree->root, node);
    }
}

// Function to insert a key into the BST
bool insertKey(BST* tree, int key) {
    if (contains(tree, key)) {
        return false; // Duplicate keys not allowed
    }
    BSTNode* newNode = createNode(key);
    insertNode(tree, newNode);
    return true;
}

// Print BST in descending order (right-root-left traversal)
void printInReverseOrder(BSTNode* node) {
    if (node == NULL) {
        return;
    }
    printInReverseOrder(node->right);
    printf("%d ", node->key);
    printInReverseOrder(node->left);
}

// Function to print the binary tree in 2D using reverse inorder traversal
void print2DUtil(BSTNode* root, int space) {
    if (root == NULL) {
        return;
    }

    // Increase space for the next level
    space += COUNT;

    // First, process the right child
    print2DUtil(root->right, space);

    // Print the current node after space count
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);

    // Then, process the left child
    print2DUtil(root->left, space);
}

// Wrapper function to print the tree
void print2D(BSTNode* root) {
    print2DUtil(root, 0);
}

// Function to free memory allocated for BST nodes
void freeTree(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main function to execute the BST operations
int main() {
    BST* tree = createBST();

    // Insert the given sequence of keys
    int keys[] = {35, 41, 13, 57, 3, 83, 88, 51, 38, 20, 11, 22, 27, 21, 48, 8};
    int numKeys = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < numKeys; i++) {
        insertKey(tree, keys[i]);
    }

    // Call printInReverseOrder
    printf("---------------------------------------------\n");
    printf("Binary Search Tree After Inserts:\n");
    printInReverseOrder(tree->root);
    printf("\n");

    // Call print2D
    print2D(tree->root);

    // Search for key 27
    if (search(tree, 27) != NULL) {
        printf("\nFound node with key = 27.\n");
    } else {
        printf("\nKey 27 not found.\n");
    }

    // Search for key 89
    if (search(tree, 89) != NULL) {
        printf("Found node with key = 89.\n");
    } else {
        printf("Key 89 not found.\n");
    }

    // Free allocated memory
    freeTree(tree->root);
    free(tree);

    return 0;
}