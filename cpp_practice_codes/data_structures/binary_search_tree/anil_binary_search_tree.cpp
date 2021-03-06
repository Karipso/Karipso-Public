/* This is an implementation of a binary search tree. No duplicates are allowed
   and only positive integers are accepted!
*/

/* TO DO: 1) Check if "new" keyword initializes pointers inside the
             insert function to null or not!
          2) Code a version to make bst work with negative integers!
          4) Check the recursive calls to ~bst_node() triggered by ~bst() */

#include "anil_binary_search_tree.h"

/**
 * @return true if the binary search tree is empty and false if not.
 * @brief This function checks if a binary search tree is empty or not.
 * @author Anil Celik Maral, 2019.10.18
 * @update Anil Celik Maral, 2021.06.07  */
bool anil::bst::is_empty() {
    return root == nullptr;
}

#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS

/**
 * @param node is the node that will be inserted into the binary search tree.
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is inserted into the binary search tree is returned.
 * @brief The function recursively searches the tree according to the rules of
 *        a general binary search tree to insert the new data accordingly by
 *        creating a new node.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the operation form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The recursive insert algorithm for the is taken from
 *         https://github.com/gzc/CLRS/blob/master/C12-Binary-Search-Trees/
 *         12.3.md.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst_node* anil::bst::insert(bst_node* node, int new_data) {
  if (node == nullptr) {
    node = new bst_node;
    node->data = new_data;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    if (root == nullptr) { // Tree was empty
      root = node;
      root->parent = nullptr;
    }
  } else if (new_data > node->data) {
    node->right = insert(node->right, new_data);
    node->right->parent = node;
  } else {
    node->left = insert(node->left, new_data);
    node->left->parent = node;
  }
  return node;
}

/**
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is created to insert the new data into the binary
 *         search tree is returned or if the value specified by new data
 *         already exists, the functions returns the address of that node.
 * @brief This is a wrapper function for the actual recursive insert function.
 *        Duplicates are not allowed; therefore, the function checks if the 
 *        data that is to be inserted already exists or not. If it exists, the
 *        address of the existing node is returned. Otherwise, a new node
 *        is created with new_data as its member and the function returns the
 *        address to this newly created node.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.06.07 */
anil::bst_node* anil::bst::insert(int new_data) {
  bst_node* node = search(new_data);
  if (!node) { // If the data doesn't already exist
    node = insert(root, new_data);
  }
  return node;
}

#elif ANIL_BST_USE_ITERATIVE_VERSIONS

/**
 * @param new_node is the node that will be inserted into the binary search 
 *        tree.
 * @return The node that is inserted into the binary search tree is returned.
 * @brief The function iteratively searches for the correct the position,
 *        where the new node should be inserted, in the binary search tree
 *        according to the rules of a general binary search tree.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the operation form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The insertion algorithm is taken from page 294 of 3rd edition of
 *         CLRS.
 * @author Anil Celik Maral, 2019.08.10
 * @update Anil Celik Maral, 2021.06.04  */
anil::bst_node* anil::bst::insert(bst_node* new_node) {
  bst_node* parent_of_new_node = nullptr;
  bst_node* position_new_node_will_be_inserted_at = root;
  while (position_new_node_will_be_inserted_at != nullptr) {
    parent_of_new_node = position_new_node_will_be_inserted_at;
    if (new_node->data < position_new_node_will_be_inserted_at->data) {
      position_new_node_will_be_inserted_at = 
        position_new_node_will_be_inserted_at->left;
    } else {
      position_new_node_will_be_inserted_at = 
        position_new_node_will_be_inserted_at->right;
    }
  }
  new_node->parent = parent_of_new_node;
  if (parent_of_new_node == nullptr) {
    root = new_node;  // Tree was empty
  } else if (new_node->data < parent_of_new_node->data) {
    parent_of_new_node->left = new_node;
  } else {
    parent_of_new_node->right = new_node;
  }
  return new_node;
}

/**
 * @param new_data is the data that will be inserted into the binary search 
 *        tree.
 * @return The node that is created to insert the new data into the binary
 *         search tree is returned or if the value specified by new data
 *         already exists, the functions returns the address of that node.
 * @brief This is a wrapper function for the actual iterative insert function.
 *        Duplicates are not allowed; therefore, the function checks if the data
 *        that is to be inserted already exists or not. If it exists, the
 *        address of the existing node is returned. Otherwise, a new node
 *        is created with new_data as its member and the function returns the 
 *        address to this newly created node.
 * @author Anil Celik Maral, 2019.08.10
 * @update Anil Celik Maral, 2021.06.04  */
anil::bst_node* anil::bst::insert(int new_data) {
  bst_node* new_node = search(new_data);
  if (!new_node) { // If the data doesn't already exist
    new_node = new bst_node;
    new_node->data = new_data;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;
    insert(new_node);
  }
  return new_node;
}

#endif


/**
 * @param node is the node that we start our inorder tree walk at.
 * @param ostream is an object such as a file or stdout where the information
 *        will be printed to.
 * @return void
 * @brief This function uses inorder tree walk algorithm to print node's
 *        subtree and itself inorder. This means that it prints the key of 
 *        the root of a subtree between printing the values in its left subtree
 *        and printing those in its right subtree.
 * @credit The inorder tree walk algorithm is taken from page 288 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.05.31  */
void anil::bst::print_inorder(std::ostream& os, bst_node* node) {
  if (node != nullptr) {
    print_inorder(os, node->left);
    os << node->data << ", ";
    print_inorder(os, node->right);
  }
}

/**
 * @param ostream is an object such as a file or stdout where the information
 *        will be printed to.
 * @return void
 * @brief This is a wrapper function for the actual print inorder function.
 *        This is done to reduce usage errors and so that the printing always
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.11
 * @update Anil Celik Maral, 2021.05.31  */
void anil::bst::print_inorder(std::ostream& os) {
  print_inorder(os, root);
}

#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS

/**
 * @param node is the node that we start the search at, which is usually the
 *             root.
 * @param data_we_search_for is the value that we look for in the binary
 *        search tree.
 * @return This function returns a pointer to the node with the value 
 *         data_we_search_for, if one exists; otherwise, it returns 
 *         nullptr.
 * @brief This function starts at the node specified by the node parameter and
 *        searches for the node that contains the value data_we_search_for
 *        using the binary search tree properties.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The recursive search algorithm is taken from page 290 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search(bst_node* node,
  int data_we_search_for) {
  if (node == nullptr || data_we_search_for == node->data) {
    return node;
  }
  if (data_we_search_for < node->data) {
    return search(node->left, data_we_search_for);
  } else { // data_we_search_for > node->data
    return search(node->right, data_we_search_for);
  }
}

/**
 * @param data_we_search_for is the value that we look for in the binary
 *        search tree.
 * @return This function returns a pointer to the node with the value
 *         data_we_search_for, if one exists; otherwise, it returns nullptr.
 * @brief This is a wrapper function for the actual recursive search function.
 *        This is done to reduce usage errors and so that the search always 
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search(int data_we_search_for) {
  return search(root, data_we_search_for);
}

#elif ANIL_BST_USE_ITERATIVE_VERSIONS

/**
 * @param node is the node that we start the search at, which is usually the
 *             root.
 * @param data_we_search_for is the value that we look for in the binary
 *        search tree.
 * @return This function returns a pointer to a node with the
 *         value data_we_search_for, if one exists; otherwise, it returns 
 *         nullptr.
 * @brief This function starts at the node specified by the node parameter and
 *        searches for the node that contains the value data_we_search_for
 *        using the binary search tree properties.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The iterative search algorithm is taken from page 291 of 3rd 
 *         edition of CLRS.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search(bst_node* node, 
  int data_we_search_for) {
  while (node != nullptr && data_we_search_for != node->data) {
    if (data_we_search_for < node->data) {
      node = node->left;
    } else {  // data_we_search_for > node->data
      node = node->right;
    }
  }
  return node;
}

/**
 * @param data_we_search_for is the value that we look for in the binary search
 *        tree.
 * @return This function returns a pointer to the node with the value
 *         data_we_search_for, if one exists; otherwise, it returns nullptr.
 * @brief This is a wrapper function for the actual iterative search function.
 *        This is done to reduce usage errors and so that the search always
 *        starts at the root.
 * @author Anil Celik Maral, 2019.08.12
 * @update Anil Celik Maral, 2021.05.31  */
anil::bst_node* anil::bst::search(int data_we_search_for) {
  return search(root, data_we_search_for);
}

#endif

#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS

/**
 * @param node is the node that we check to see if it contains the minimum 
 *        element in the binary search tree.
 * @return This function returns a pointer to a node with the minimum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This function finds the minimum value in the binary search tree by
 *        following left child pointers from the root until we encounter a
 *        nullptr. This means that to get the minimum value in our binary
 *        search tree, we only need to go to the leftmost node.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The recursive search algorithm for the minimum value is taken from
 *         https://github.com/gzc/CLRS/blob/master/C12-Binary-Search-Trees/
 *         12.2.md.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst_node* anil::bst::find_min(bst_node* node) {
  if (node->left != nullptr) {
    return find_min(node->left);
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the minimum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This is a wrapper function for the actual recursive search function
 *        for the minimum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst_node* anil::bst::find_min() {
  return find_min(root); 
}

#elif ANIL_BST_USE_ITERATIVE_VERSIONS

/**
 * @param node is the node that we check to see if it contains the minimum 
 *        element in the binary search tree.
 * @return This function returns a pointer to the node with the minimum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This function finds the minimum value in the binary search tree by
 *        following left child pointers from the root until we encounter a
 *        nullptr. This means that to get the minimum value in our binary search
 *        tree, we only need to go to the leftmost node.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The iterative search algorithm for the minimum value is taken from
 *         page 291 of 3rd edition of CLRS.
 * @time complexity: O(h), where h is the height of the tree. The sequence of
 *                   nodes encountered forms a simple path downward from the
 *                   root.
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_min(bst_node* node) {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the minimum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This is a wrapper function for the actual iterative search function
 *        for the minimum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_min() {
  return find_min(root);
}

#endif

#ifdef ANIL_BST_USE_RECURSIVE_VERSIONS

/**
 * @param node is the node that we check to see if it contains the maximum 
 *        element in the binary search tree.
 * @return This function returns a pointer to a node with the maximum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This function finds the maximum value in the binary search tree by
 *        following the right child pointers from the root until we encounter a
 *        nullptr. This means that to get the maximum value in our binary
 *        search tree, we only need to go to the rightmost node.
 * @time complexity: O(h), where h is the height of the tree. The nodes
 *       encountered during the recursion form a simple path downward from
 *       the root of the tree.
 * @space complexity: O(1)
 * @credit The recursive search algorithm for the maximum value is taken from
 *         https://github.com/gzc/CLRS/blob/master/C12-Binary-Search-Trees/
 *         12.2.md.
 * @author Anil Celik Maral, 2019.08.13  */
anil::bst_node* anil::bst::find_max(bst_node* node) {
  if (node->right != nullptr) {
    return find_max(node->right);
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the maximum value
 *         if one exists; otherwise, it returns nullptr (if the tree is empty).
 * @brief This is a wrapper function for the actual recursive search function
 *        for the maximum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst_node* anil::bst::find_max() {
  return find_max(root); 
}

#elif ANIL_BST_USE_ITERATIVE_VERSIONS

/**
 * @param node is the node that we check to see if it contains the maximum 
 *        element in the binary search tree.
 * @return This function returns a pointer to the node with the maximum value
 *         if one exists; otherwise, it returns a nullptr (if the tree is
 *         empty).
 * @brief This function finds the maximum value in the binary search tree by
 *        following the right child pointers starting from the root until we
 *        encounter a nullptr. This means that to get the maximum value in our
 *        binary search tree, we only need to go to the rightmost node.
 * @time complexity: O(h), where h is the height of the tree. The sequence of
 *                   nodes encountered forms a simple path downward from the
 *                   root.
 * @space complexity: O(1)
 * @credit The iterative search algorithm for the maximum value is taken from
 *         page 291 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_max(bst_node* node) {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

/**
 * @param none
 * @return This function returns a pointer to a node with the maximum value
 *         if one exists; otherwise, it returns a nullptr (if the tree is
 *         empty).
 * @brief This is a wrapper function for the actual iterative search function
 *        for the maximum value. This is done to reduce usage errors and so 
 *        that the search always starts at the root.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::find_max() {
  return find_max(root);
}

#endif

/**
 * @param node is the node whose data we return to the caller.
 * @return This function returns the data stored in the node.
 * @brief This is an access function that returns the data stored in a node.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @author Anil Celik Maral, 2019.09.02
 * @update Anil Celik Maral, 2021.06.07  */
int anil::bst::get_node_data(bst_node* node) {
  return node->data;
}

/**
 * @param node is the node whose successor we search for.
 * @return This function returns a pointer to the node that is the successor of
 *         the node given in the node parameter of this function, if one
 *         exists; otherwise, it returns nullptr if the tree is empty or the
 *         node given in the node parameter of this function has the largest
 *         value in the binary search tree.
 * @brief This function finds the successor of the node given in the node
 *        parameter of this function. The successor of a node is the node with
 *        the smallest value greater than the value of the node whose successor
 *        we are looking for.
 * @time complexity: O(h), where h is the height of the tree, since we either
 *                   follow a simple path up the tree or follow a simple path
 *                   down the tree.
 * @space complexity: O(1)
 * @credit The algorithm for finding the successor of a node is taken from page
 *         292 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::successor(bst_node* node) {

  // If the right subtree of node is nonempty, then the successor of node is
  // just the leftmost node in node's right subtree.
  if (node->right != nullptr) {
    return find_min(node->right);
  }

  // If the right subtree of node is empty and node has a successor y, then y
  // is the lowest ancestor of node whose left child is also an ancestor of
  // node. To find y, we simply go up the tree from node until we encounter
  // a node that is the left child of its parent.
  bst_node* temp = node;
  bst_node* possible_successor_node = node->parent;
  while (possible_successor_node != nullptr &&
    temp == possible_successor_node->right) {
    temp = possible_successor_node;
    possible_successor_node = possible_successor_node->parent;
  }
  return possible_successor_node;
}

/**
 * @param node is the node whose predecessor we search for.
 * @return This function returns a pointer to the node that is the predecessor
 *         of the node given in the node parameter of this function, if one 
 *         exists; otherwise, it returns nullptr if the tree is empty or the
 *         node given in the node parameter of this function has the smallest
 *         value in the binary search tree.
 * @brief This function finds the predecessor of the node given in the node 
 *        parameter of this function. The predecessor of a node is the node
 *        with the largest value less than the value of node whose predecessor
 *        we are looking for.
 * @time complexity: O(h), where h is the height of the tree, since we either
 *                   follow a simple path up the tree or follow a simple path
 *                   down the tree.
 * @space complexity: O(1)
 * @credit Predecessor algorithm is written by me; however, it is symmetric to
 *         the successor algorithm given on page 292 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.03  */
anil::bst_node* anil::bst::predecessor(bst_node* node) {

  // If the left subtree of node is nonempty, then the predecessor of node
  // is just the rightmost node in node's left subtree.
  if (node->left != nullptr) {
    return find_max(node->left);
  }

  // If the left subtree of node is empty and node has a predecessor y, then y
  // is the lowest ancestor of node whose right child is also an ancestor of
  // node. To find y, we simply go up the tree from node until we encounter
  // a node that is the right child of its parent.
  bst_node* temp = node;
  bst_node* possible_predecessor_node = node->parent;
  while (possible_predecessor_node != nullptr &&
    temp == possible_predecessor_node->left) {
    temp = possible_predecessor_node;
    possible_predecessor_node = possible_predecessor_node->parent;
  }
  return possible_predecessor_node;
}

/**
 * @param replaced is the node that we replace with the node pointed by
 *        replacing parameter.
 * @param replacing is the node that replaces the node pointed by replaced
 *        parameter.
 * @return void
 * @brief This function moves subtrees around within the binary search tree
 *        by replacing one subtree as a child of its parent with another
 *        subtree. When transplant() replaces the subtree rooted at node
 *        replaced with the subtree rooted at node replacing, node replaced's
 *        parent becomes node replacing's parent, and replaced's parent ends
 *        up having replacing as its appropriate child.
 * @warning This function does not attempt to update replacing->left and 
 *          replacing->right; doing so, or not doing so, is the responsibility
 *          of transplant()'s caller.
 * @time complexity: O(1)
 * @space complexity: O(1)
 * @credit The algorithm for replacing one subtree as a child of its parent
 *         with another subtree is taken from page 296 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.13
 * @update Anil Celik Maral, 2021.06.04  */
void anil::bst::transplant(bst_node* replaced, bst_node* replacing) {
  if (replaced->parent == nullptr) {
    root = replacing;
  } else if (replaced == replaced->parent->left) {
    replaced->parent->left = replacing;
  } else {  // replaced == replaced->parent->right
    replaced->parent->right = replacing;
  }

  if (replacing != nullptr) {
    replacing->parent = replaced->parent;
  }
}

/**
 * @param node_to_be_deleted is the node that we delete from the binary search
 *        tree.
 * @return void
 * @brief This function removes the node pointed by the parameter
 *        node_to_be_deleted from the binary search tree while protecting the
 *        properties of the binary search tree. Therefore, all of the binary
 *        search tree properties still hold for the remaining tree after the
 *        said node has been removed from the tree.
 * @time complexity: O(h), where h is the height of the tree, since we either
 *                   follow a simple path up the tree or follow a simple path
 *                   down the tree. Each line of remove(), including the calls
 *                   to transplant(), takes constant time, except for the call
 *                   to find_min(). Thus, remove() runs in O(h) time on a tree
 *                   of height h.
 * @space complexity: O(1)
 * @credit The algorithm for removing a node from the binary search tree is
 *         taken from page 298 of 3rd edition of CLRS.
 * @author Anil Celik Maral, 2019.08.14
 * @update Anil Celik Maral, 2021.06.07  */
void anil::bst::remove(bst_node* node_to_be_deleted) {
  if (node_to_be_deleted == nullptr) {
    return;
  }

  // If node_to_be_deleted has no left child, then we replace
  // node_to_be_deleted by its right child, which may or may not be nullptr.
  // When node_to_be_deleted's right child is nullptr, this case deals with the
  // situation in which node_to_be_deleted has no children. When
  // node_to_be_deleted's right child is not a nullptr, this case handles the
  // situation in which node_to_be_deleted has just one child, which is its
  // right child.
  if (node_to_be_deleted->left == nullptr) {
    transplant(node_to_be_deleted, node_to_be_deleted->right);

  // If node_to_be_deleted has just one child, which is its left child, 
  // then we replace node_to_be_deleted by its left child.
  } else if (node_to_be_deleted->right == nullptr) {
        transplant(node_to_be_deleted, node_to_be_deleted->left);

  // Otherwise, node_to_be_deleted has both a left and a right child. We
  // find node_to_be deleted's successor, which lies in node_to_be_deleted's
  // right subtree and has no left child. We want to splice successor out of
  // its current location and have it replace node_to_be_deleted in the
  // tree.
  } else {
    bst_node* successor = find_min(node_to_be_deleted->right);

    // If successor is node_to_be_deleted's right child, then we replace
    // node_to_be_deleted by successor, leaving successor's right child 
    // alone. Otherwise, successor lies within node_to_be_deleted's right
    // subtree but its not node_to_be_deleted's right child. In this case,
    // we first replace successor by its own right child, and then we 
    // replace node_to_be_delete by successor.
    if (successor->parent != node_to_be_deleted) {
      transplant(successor, successor->right);
      successor->right = node_to_be_deleted->right;
      successor->right->parent = successor;
    }
    transplant(node_to_be_deleted, successor);
    successor->left = node_to_be_deleted->left;
    successor->left->parent = successor;   
  }
  delete node_to_be_deleted; 
}

/**
 * @param node is the node whose subtree and itself gets deleted.
 * @return void
 * @brief This function deletes a binary search subtree whose root is located
 *        at the node parameter by recursively deleting every node in the tree
 *        following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.15
 * @update Anil Celik Maral, 2021.06.07  */
void anil::bst::delete_bst(bst_node* node) {
  if (node == nullptr) { return; }
  delete_bst(node->left);  
  delete_bst(node->right); 
  delete node;
  node = nullptr;
}

/**
 * @param none
 * @return void
 * @brief This function deletes an entire binary search tree by triggering a
 *        call to delete_bst(), which then recursively deletes every
 *        node in the tree following a post-order tree traversal.
 * @author Anil Celik Maral, 2019.08.14
 * @update Anil Celik Maral, 2021.06.07  */
anil::bst::~bst() {
  delete_bst(root);
}
