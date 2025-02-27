/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:Joseph Krieter
 * Email: krieterj@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h> 

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
	struct bst* bst = (struct bst*)malloc(sizeof(struct bst));
	
	if(!bst){
		printf("AAAAAHHHHHH");
		return NULL; 
	}
	
	bst->root = NULL; 
	// bst->root = (struct bst_node*)malloc(sizeof(struct bst_node)); 
	// bst->root->left = NULL; 
	// bst->root->right = NULL; 
	
	return bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
	if(bst){
		bst_free_recur(bst->root); 
		free(bst); 
	}
	return;
}

//Helper function for the free function
void bst_free_recur(struct bst_node* node){
	if (!node) return; 
	bst_free_recur(node->left);
	bst_free_recur(node->right); 
	free(node); 
}


/* This is a function to help me implement a size function recursively which has a better runtime than 
 * running it iteratively. 
 *
 * Param - a bst node (the root) 
 *
 */
int bst_size_recursive(struct bst_node* node){
	if(!node) return 0;
	return 1 + bst_size_recursive(node->left) + bst_size_recursive(node->right);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
	if(!bst->root || !bst){
		return 0; 
	}	
	return bst_size_recursive(bst->root); 
}



/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
	
	struct bst_node* newnode = (struct bst_node*)malloc(sizeof(struct bst_node)); 
	newnode->key = key; 
	newnode->value = value; 
	newnode->left = NULL; 
	newnode->right = NULL; 
	
	struct bst_node* current = bst->root; 
	
	if(bst->root == NULL){
		bst->root = newnode; 
		return; 
	}
	
	while(current){
		if(key < current->key){
			if(!current->left){
				current->left = newnode;
				break; 
			}
			current = current->left; 
		} else {
			if(!current->right){
				current->right = newnode; 
				break; 
			}
			current = current->right; 
		}
	}
	
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
	if (!bst || !bst->root) return;

    struct bst_node* parent = NULL;
    struct bst_node* current = bst->root;

    // Find the node to remove and its parent
    while (current && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (!current) return; // Key not found

    // Case 1: Node has no children or only one child
    if (!current->left || !current->right) {
        struct bst_node* temp = current->left ? current->left : current->right;

        if (!parent) {
            bst->root = temp;
        } else if (parent->left == current) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
        free(current);
    }
    // Case 2: Node has two children
    else {
        struct bst_node* successor_parent = current;
        struct bst_node* successor = current->right;

        // Find the in-order successor (leftmost node in the right subtree)
        while (successor->left) {
            successor_parent = successor;
            successor = successor->left;
        }

        // Replace the current node's key and value with the successor's
        current->key = successor->key;
        current->value = successor->value;

        // Remove the successor
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
        } else {
            successor_parent->right = successor->right;
        }
        free(successor);
    }
  return;
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
	if (!bst || !bst->root) return NULL;

    struct bst_node* current = bst->root;
    while (current) {
        if (key == current->key) {
            return current->value;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
  if (!bst || !bst->root) return -1; 
  return bst_height_recur(bst->root);
 }

 int bst_height_recur(struct bst_node* node){
	if(!node) return -1; 
	int left_height = bst_height_recur(node->left);
	int right_height = bst_height_recur(node->right); 
	return 1 + (left_height > right_height ? left_height : right_height); 
 }

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
    if (!bst || !bst->root) return 0;
    return bst_path_sum_recur(bst->root, sum);
}

int bst_path_sum_recur(struct bst_node* node, int sum) {
    if (!node) return 0;
    if (!node->left && !node->right) return sum == node->key; // Leaf node
    return bst_path_sum_recur(node->left, sum - node->key) ||
           bst_path_sum_recur(node->right, sum - node->key);
}
/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
    if (!bst || !bst->root) return 0;
    return bst_range_sum_recur(bst->root, lower, upper);
}

int bst_range_sum_recur(struct bst_node* node, int lower, int upper) {
    if (!node) return 0;

    int sum = 0;

    if (node->key >= lower && node->key <= upper) {
        sum += node->key;
    }

    if (node->key > lower) {
        sum += bst_range_sum_recur(node->left, lower, upper);
    }

    if (node->key < upper) {
        sum += bst_range_sum_recur(node->right, lower, upper);
    }

    return sum;
}
