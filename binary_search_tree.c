/**
 * file: binary_search_tree.c
 * author: thomas Wood (thomas@wgapl.com)
 * description: an ANSI C implementation of a binary search tree
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
    struct node* parent;
} node;


// void insert_bst(node*, int);
void insert_bst(node*, int);
int search_bst(node*, int);
void delete_bst(node*, int);
node* min_bst(node*);

int main() {
    int n = 10;
    int values_to_insert[10] = {8, 34, -10, 82, 43, 4, 9, 2, 77, 12};

    node* root = (node*)malloc(sizeof(node));
    root->value = 39;


    insert_bst(root, 0);

    int k;
    for (k=0; k < n; k++) {
        insert_bst(root, values_to_insert[k]);
        printf("%d\n", search_bst(root, values_to_insert[k]));
    }


    for (k=0; k < n; k++) {
        delete_bst(root, values_to_insert[k]);
        printf("%d\n", search_bst(root, values_to_insert[k]));
    }

    return 0;
}

void insert_bst(node* root, int value) {
    // Is the value of the root node less than the value given?
    if (value < root->value) {
        // What if our root node is actually a leaf?
        if (root->left == NULL) { // root->left doesn't exist
            // Create a new left child node on the heap
            node* new_leaf = (node*) malloc(sizeof(node));
            // Assign the child node the value we want to insert
            new_leaf->value = value;
            // Connect the child and parent nodes of the tree
            root->left = new_leaf;
            root->left->parent = root;
            // printf("%d %d\n", new_leaf->value, root->value);
        }

        // So our root node has a left child already...
        // Do this recursively on that left child until the node is inserted
        // in a new leaf.
        else {
            insert_bst(root->left, value);
        }
    }
    // Everything is the same, just inverted -- gsub('left', 'right')
    else {
        if(!(root->right)) {
            node* new_leaf = (node*) malloc(sizeof(node));
            new_leaf->value = value;
            root->right = new_leaf;
            root->right->parent = root;
        }
        else {
            insert_bst(root->right, value);
        }
    }

}

int search_bst(node* root, int value) {
    if (value == root->value) {
        return 1;
    }
    else if (value < root->value) {
        if (root->left == NULL) {
            return 0;
        }
        else {
            search_bst(root->left, value);
        }
    }
    else {
        if (root->right == NULL) {
            return 0;
        }
        else {
            search_bst(root->right, value);
        }
    }
}

node* min_bst(node* root){
    if (root->left == NULL) {
        return root;
    }
    else {
        min_bst(root->left);
    }
}

void delete_bst(node* root, int value) {
    if (value < root->value) {
        if (root->left == NULL) {
            return;
        }
        else {
        delete_bst(root->left, value);
        }
    }
    else if (value > root->value) {
        if (root->right == NULL) {
            return;
        }
        else {
            delete_bst(root->right, value);
        }
    }
    else {
        // 4 cases when root->value == value

        // case 1: root is a leaf with no children.
        if ((root->left == NULL) && (root->right == NULL)) {
            free(root); // nothing else necessary.
        }
        // case 2: no left child
        else if ((root->left == NULL) && (root->right != NULL)) {
            if (root->parent != NULL) {
                root->right->parent = root->parent;
                if (root->parent->value > value) {
                    root->parent->left = root->right;
                }
                else {
                    root->parent->right = root->right;
                }
                free(root);
            }
            else {
                free(root); // just lop the top off the tree. #TrueRoot
            }
        }
        // case 3: no right child
        else if ((root->left != NULL) && (root->right == NULL)) {
            if (root->parent != NULL) {
                root->left->parent = root->parent;
                if (root->parent->value > value) {
                    root->parent->left = root->left;
                }
                else {
                    root->parent->right = root->left;
                }
                free(root);
            }
            else {
                free(root); // just lop the top off the tree. #TrueRoot
            }
        }
        // case 4: both right and left children
        else {
            if (root->parent != NULL) {
                if (root->parent->value > value) { // if parent's value > child, left child
                    root->parent->left = root->right;
                }
                else { // right child otherwise
                    root->parent->right = root->right;
                }
                // walk down leftmost path of right subtree
                node* newleft = min_bst(root->right);
                // put left subtree under min value from right subtree
                // still partitioned about value, so bst property upheld.
                newleft->left = root->left;
                free(root);
            }
            else {
                node* newleft = min_bst(root->right);
                newleft->left = root->left;
                free(root);
            }
        }
    }
}
