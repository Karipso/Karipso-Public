/* This is an implementation of a binary search tree! */

#include "anil_binary_search_tree.h"

bool anil::bst::is_empty() {
    return root == NULL;
}

anil::bst_node* anil::bst::insert(bst_node* node, int new_data) {
    // If bst doesn't exist, create a new node as the root. Otherwise,
    // we can insert a new node when there's no child node at a
    // particular place.
    if (node == NULL) {
        node = new bst_node;
        node->data = new_data;
        //node->left = NULL; Check if new initializes them to NULL
        //node->right = NULL;
        //node->parent = NULL;
    // If the given data is greater than current node's data, then go
    // to the right subtree.
    } else if (new_data > node->data) {
        node->right = insert(node->right, new_data);
        node->right->parent = node;
    // If the given data is smaller than current node's data, then go
    // to the left subtree.
    } else {
        node->left = insert(node->left, new_data);
        node->left->parent = node;
    }
    return node;
}

void anil::bst::insert(int new_data) {
    // Invoking the other insert() function and passing the root node
    // and the new data to it. The reasoning behind this implementation
    // is to reduce the amount of incorrect usage by guaranteeing that
    // the root node is always passed to the insert function initially.
    root = insert(root, new_data);
}

void anil::bst::print_io(bst_node* node) {
    if (node == NULL) { return; }   // Return if the node is empty!
    print_io(node->left);           // Traverse left-subtree
    std::cout << node->data << ' ';
    print_io(node->right);          // Traverse right-subtree
}

/* The reasoning behind this implementation is to reduce the amount of
   incorrect usage by guaranteeing that the root node is always passed
   to the print_io function initially. */
void anil::bst::print_io() {
    print_io(root); // Print the nodes in inorder.
}

anil::bst_node* anil::bst::search(bst_node* node, int data) {
    if (node == NULL) {     // Couldn't find the given data
        return NULL;
    } else if (node->data == data) {
        return node;
    } else if (data > node->data) {
        return search(node->right, data);
    } else {    // (data < node->data)
        return search(node->left, data);
    }
}

/* The reasoning behind this implementation is to reduce the amount of
   incorrect usage by guaranteeing that the root node is always passed
   to the search function initially. */
bool anil::bst::search(int data) {
    bst_node* result = search(root, data);
    return result == NULL ? false : true;
}

/* To get the minimum data in our binary search tree, we only need to
   go to the leftmost node. */
int anil::bst::find_min(bst_node* node) {
    if (node == NULL) {                 // BST is empty.
        return -1;
    } else if (node->left == NULL) {    // Found min.
        return node->data;
    } else {
        return find_min(node->left);
    }
}

/* To get the maximum data in our binary search tree, we only need to
   go to the rightmost node. */
int anil::bst::find_max(bst_node* node) {
    if (node == NULL) {                 // BST is empty.
        return -1;
    } else if (node->right == NULL) {   // Found max.
        return node->data;
    } else {
        return find_max(node->right);
    }
}

int anil::bst::successor(bst_node* node) {
    // The successor is the minimum data value of the right-subtree
    if (node->right != NULL) {
        return find_min(node->right);
    }

    // If there is no right-subtree:
    bst_node* pano = node->parent;  // Parent node = pano
    bst_node* cuno = node;          // Current node = cuno

    // While we haven't reached the root and current node is its
    // parent's right child:
    while ((pano != NULL) && (cuno == pano->right)) {
        cuno = pano;
        pano = cuno->parent;
    }

    // If the parent node is not NULL, then we found a successor!
    return pano == NULL ? -1 : pano->data;
}

int anil::bst::successor(int data) {
    // First, search and find data's node!
    bst_node* node = search(root, data);

    // If the data's node or its successor wasn't found return -1.
    return node == NULL ? -1 : successor(node);
}

int anil::bst::predecessor(bst_node* node) {
    // The predecessor is the maximum data value of the left-subtree
    if (node->left != NULL) {
        return find_max(node->left);
    }

    // If there is no left-subtree:
    bst_node* pano = node->parent;  // Parent node = pano
    bst_node* cuno = node;          // Current node = cuno

    // While we haven't reached the root and current node is its
    // parent's left child:
    while ((pano != NULL) && (cuno == pano->left)) {
        cuno = pano;
        pano = cuno->parent;
    }
    
    // If the parent node is not NULL, then we found a predecessor!
    return pano == NULL ? -1 : pano->data;
}

int anil::bst::predecessor(int data) {
    // First, search and find data's node!
    bst_node* node = search(root, data);

    // If the data's node or its predecessor wasn't found return -1.
    return node == NULL ? -1 : predecessor(node);
}

anil::bst_node* anil::bst::remove () {

}

anil::linked_list::~linked_list() {
    while (!is_empty()) {
        remove(head);
    }
}
