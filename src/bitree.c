/*******************************************************************************
 * NAME:	    bitree.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the C source implementation of a Binary
 *		    Tree. Project flow:
 *			-> Syntactical Test -- Ensure the program compiles
 *			-> Functional Test -- Ensure all of the tests pass
 *			-> Memory Test -- Ensure there are no memory leaks
 *
 * CREATED:	    11/06/2017
 *
 * LAST EDITED:	    12/01/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

/* TODO: Create traversal_define() macros
 * Example: #define DEFINE_TRAVERSAL(type, name, action)
 * -> name(bitree * node) { /\* Do traversal of type, perform action *\/ }
 * This allows the user to do whatever they want without being limited by C's
 * function types. For example, if my data is just integers, and I only wanted
 * to increment each one in the tree, I could do it like this:
 *
 * DEFINE_TRAVERSAL(PREORDER, traverse_and_increment, {*(node->data)++;});
 * /\* And then later, call: *\/
 * traverse_and_increment(treeroot);
 */

/* Helper functions used by the 'traverse-type' functions. */
static bitree * npreorder_helper(bitree * node, bitree * original);
static bitree * npostorder_helper(bitree * node, bitree * original);
static bitree * ninorder_helper(bitree * node, bitree * original);

/* Used by bitree_merge to update tree parameters */
static int update_size(bitree * node, int * size, bitree * root);

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    bitree_create
 *
 * DESCRIPTION:	    This function allocates and initializes a binary tree, and
 *		    returns a pointer to it.
 *
 * ARGUMENTS:	    destroy: (void (*)(void *)) -- function to call when
 *			removing an element (can be NULL).
 *		    data: (void *) -- data to initialize root element with.
 *
 * RETURN:	    bitree * -- pointer to new struct, or NULL.
 *
 * NOTES:	    Theta(1)
 ***/
bitree * bitree_create(void (*destroy)(void *), void * data)
{
  if (data == NULL)
    return NULL;
  bitree * tree = malloc(sizeof(bitree));
  if (tree == NULL)
    return NULL;

  *tree = (bitree){
    .root = tree,
    .parent = NULL,
    .left = NULL,
    .right = NULL,
  
    .size = malloc(sizeof(int)),
    .destroy = destroy,
    .data = data
  };

  if (tree->size == NULL) {
    free(tree);
    return NULL;
  }

  *(tree->size) = 1;
  return tree;
}

/*******************************************************************************
 * FUNCTION:	    bitree_destroy
 *
 * DESCRIPTION:	    Removes, if any, all elements from the tree, then frees all
 *		    internal associated memory. Does not set `*tree' to NULL.
 *
 * ARGUMENTS:	    tree: (bitree **) -- pointer to the tree pointer to free.
 *
 * RETURN:	    void.
 *
 * NOTES:	    Theta(n)
 ***/
void bitree_destroy(bitree ** tree)
{
  if (tree == NULL || *tree == NULL)
    return;
  
  bitree_rem(*tree);
}

/*******************************************************************************
 * FUNCTION:	    bitree_insl
 *
 * DESCRIPTION:	    This function inserts a new node into the binary tree left
 *		    of the node in `parent', with data `data'.
 *
 * ARGUMENTS:	    parent: (bitree *) -- the parent of the new node.
 *		    data: (void *) -- the data to place in the new node.
 *
 * RETURN:	    int -- 0 on success, -1 on failure.
 *
 * NOTES:	    Theta(1)
 ***/
int bitree_insl(bitree * parent, void * data)
{
  /* Do not allow NULL inputs */
  if (parent == NULL || data == NULL)
    return -1;
  /* Do not allow insertion if the node is already occupied */
  if (parent->left != NULL)
    return -1;

  bitree * new = malloc(sizeof(bitree));
  if (new == NULL)
    return -1;
  *new = (bitree){
    .root = parent->root,
    .parent = parent,
    .left = NULL,
    .right = NULL,
    .size = parent->size,
    .destroy = parent->destroy,
    .data = data
  };

  parent->left = new;
  *(parent->size) += 1;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    bitree_insr
 *
 * DESCRIPTION:	    This function inserts a new node to the right of `parent'
 *		    with data `data'.
 *
 * ARGUMENTS:	    parent: (bitree *) -- the parent of the new node.
 *		    data: (void *) -- data to populate the new node.
 *
 * RETURN:	    int -- 0 on success, -1 on failure.
 *
 * NOTES:	    Theta(1)
 ***/
int bitree_insr(bitree * parent, void * data)
{
  if (parent == NULL || data == NULL)
    return -1;
  if (parent->right != NULL)
    return -1;

  bitree * new = malloc(sizeof(bitree));
  if (new == NULL)
    return -1;
  *new = (bitree){
    .root = parent->root,
    .parent = parent,
    .left = NULL,
    .right = NULL,
    .size = parent->size,
    .destroy = parent->destroy,
    .data = data
  };

  parent->right = new;
  *(parent->size) += 1;
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    bitree_rem
 *
 * DESCRIPTION:	    This function removes, if any, all children of the node
 *		    passed, and finally the node itself.
 *
 * ARGUMENTS:	    node: (bitree *) -- the node to remove.
 *
 * RETURN:	    void
 *
 * NOTES:	    Theta(n), n is the size of the subtree
 ***/
void bitree_rem(bitree * node)
{
  if (node == NULL)
    return;

  bitree_rem(node->left);
  bitree_rem(node->right);

  if (node->root == node) {
    free(node->size);    
  } else {
    *(node->size) -= 1;
    if (node->parent->left == node)
      node->parent->left = NULL;
    else
      node->parent->right = NULL;
  }

  if (node->destroy != NULL)
    node->destroy(node->data);
  free(node);
}

/*******************************************************************************
 * FUNCTION:	    bitree_merge
 *
 * DESCRIPTION:	    Merges two bitrees, without splicing them into each other.
 *		    This implementation is unordered, so we make no attempt
 *		    to balance the tree when merging.
 *
 * ARGUMENTS:	    tree1: (bitree *) -- the host tree
 *		    tree2: (bitree *) -- the tree to splice in
 *		    data: (void *) -- this param is used only when a new node
 *			needs to be created in order to merge the trees.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    O(m + n), Omega(n); m = *(tree1->size), n = *(tree2->size)
 ***/
int bitree_merge(bitree * tree1, bitree * tree2, void * data)
{
  /* Test for bad inputs */
  if (tree1 == NULL
      || tree2 == NULL
      || tree2->root != tree2
      || tree1->root == tree2->root
      || tree1->destroy != tree2->destroy)
    return -1;

  /* Test for case 1 */
  if (tree1->root == tree1
      && tree1->left != NULL
      && tree1->right != NULL
      && data) {

    bitree * newroot = bitree_create(tree1->destroy, data);
    if (newroot == NULL)
      return -1;
    *(newroot->size) += *(tree1->size) + *(tree2->size);

    newroot->left = tree1;
    tree1->parent = newroot;

    newroot->right = tree2;
    tree2->parent = newroot;

    free(tree1->size);
    free(tree2->size);

    /* Recursively update `size' and `root' */
    update_size(newroot, newroot->size, newroot);
  }
  /* Test for case 2 & case 3 */
  else if (tree1->left == NULL || tree1->right == NULL) {

    if (tree1->left == NULL)
      tree1->left = tree2;
    else
      tree1->right = tree2;

    tree2->parent = tree1;
    *(tree1->root->size) += *(tree2->size);
    free(tree2->size);

    /* Recursively update `size' and `root' */
    update_size(tree2, tree1->root->size, tree1->root);

  } else {
    return -1;
  }

  return 0;
}

/*******************************************************************************
 * FUNCTION:	    bitree_npreorder
 *
 * DESCRIPTION:	    This function returns the next node that would be operated
 *		    on if the tree were being traversed with a preorder
 *		    algorithm. See the documentation for an example of how this
 *		    function could be used.
 *
 * ARGUMENTS:	    node: (bitree *) -- the current node.
 *
 * RETURN:	    bitree * -- pointer to the next node, or NULL if there was
 *		    a problem.
 *
 * NOTES:	    Omega(1), O(log(n))
 *		    THIS IS NOT A TRAVERSAL FUNCTION. It does not 'traverse' the
 *		    tree in a traditional sense. See the documentation in the
 *		    header file.
 ***/
bitree * bitree_npreorder(bitree * node)
{
  if (node == NULL || *(node->size) == 1)
    return node;

  if (node->left != NULL)
    return node->left;
  if (node->right != NULL)
    return node->right;
  return npreorder_helper(node->parent, node);
}

/*******************************************************************************
 * FUNCTION:	    bitree_npostorder
 *
 * DESCRIPTION:	    This function returns the next node that would be operated
 *		    on if the tree were being traversed with a postorder
 *		    algorithm. See the documentation for an example of how this
 *		    function could be used.
 *
 * ARGUMENTS:	    node: (bitree *) -- the current node.
 *
 * RETURN:	    bitree * -- pointer to the next node, or NULL if there was
 *		    a problem.
 *
 * NOTES:	    Omega(1), O(log(n))
 *		    THIS IS NOT A TRAVERSAL FUNCTION. It does not 'traverse' the
 *		    tree in a traditional sense. See the documentation in the
 *		    header file.
 *		    Post-Order traversals begin at the leftmost node. The user
 *		    should keep this in mind when using this function.
 ***/
bitree * bitree_npostorder(bitree * node)
{
  if (node == NULL || *(node->size) == 1)
    return node;
  if (node == node->root)
    return npostorder_helper(node->left, node);
  return npostorder_helper(node->parent, node);
}

/*******************************************************************************
 * FUNCTION:	    bitree_ninorder
 *
 * DESCRIPTION:	    This function returns the next node that would be operated
 *		    on if the tree were being traversed with a inorder
 *		    algorithm. See the documentation for an example of how this
 *		    function could be used.
 *
 * ARGUMENTS:	    node: (bitree *) -- the current node.
 *
 * RETURN:	    bitree * -- pointer to the next node, or NULL if there was
 *		    a problem.
 *
 * NOTES:	    Omega(1), O(log(n))
 *		    THIS IS NOT A TRAVERSAL FUNCTION. It does not 'traverse' the
 *		    tree in a traditional sense. See the documentation in the
 *		    header file.
 *		    In-Order traversals begin at the leftmost node. The user
 *		    should keep this in mind when using this function.
 ***/
bitree * bitree_ninorder(bitree * node)
{
  if (node == NULL || *(node->size) == 1)
    return node;
  if (node->root == node)
    return ninorder_helper(node->right, node);
  if (node->right != NULL)
    return ninorder_helper(node->right, node);
  return ninorder_helper(node->parent, node);
}

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    npreorder_helper
 *
 * DESCRIPTION:	    This is a helper function for bitree_npreorder(). If the
 *		    next node in traversal is not immediately accesible from the
 *		    current node, this function will find it.
 *
 * ARGUMENTS:	    node: (bitree *) -- on the first call, this pointer usually
 *			contains the value of original->parent.
 *		    original: (bitree *) -- pointer to the first node passed.
 *
 * RETURN:	    bitree * -- pointer to the next node in preorder traversal.
 *
 * NOTES:	    none.
 ***/
static bitree * npreorder_helper(bitree * node, bitree * original)
{
  /* Assumptions (given from bitree_npreorder):
   * original is not NULL
   * there is more than one node in the tree.
   * original->left is NULL
   * original->right is NULL
   */
  if (node == NULL)
    return original;
  if (node->left == original && node->right == NULL)
    return npreorder_helper(node->parent, node);
  else if (node->left == original && node->right != NULL)
    return node->right;

  return npreorder_helper(node->parent, node);;
}

/*******************************************************************************
 * FUNCTION:	    npostorder_helper
 *
 * DESCRIPTION:	    This is a helper function for bitree_npostorder(). If the
 *		    next node in traversal is not immediately accesible from the
 *		    current node, this function will find it.
 *
 * ARGUMENTS:	    node: (bitree *) -- on the first call, this pointer usually
 *			contains the value of original->parent.
 *		    original: (bitree *) -- pointer to the first node passed.
 *
 * RETURN:	    bitree * -- pointer to the next node in postorder traversal.
 *
 * NOTES:	    none.
 ***/
static bitree * npostorder_helper(bitree * node, bitree * original)
{
  if (node == NULL)
    return original;

  /* We're recursing downwards */
  if (node->parent == original) {
    if (bitree_isleaf(node))
      return node;
    if (node->left != NULL)
      return npostorder_helper(node->left, node);
    if (node->right != NULL)
      return npostorder_helper(node->right, node);
  }
  /* We're recursing upwards */
  else if (original->parent == node) {
    if (node->right == original)
      return node;
    else if (node->right != NULL)
      return npostorder_helper(node->right, node);
  }

  return NULL;
}

/*******************************************************************************
 * FUNCTION:	    ninorder_helper
 *
 * DESCRIPTION:	    This is a helper function for bitree_ninorder(). If the
 *		    next node in traversal is not immediately accesible from the
 *		    current node, this function will find it.
 *
 * ARGUMENTS:	    node: (bitree *) -- on the first call, this pointer usually
 *			contains the value of original->parent.
 *		    original: (bitree *) -- pointer to the first node passed.
 *
 * RETURN:	    bitree * -- pointer to the next node in inorder traversal.
 *
 * NOTES:	    none.
 ***/
static bitree * ninorder_helper(bitree * node, bitree * original)
{
  if (node == NULL)
    return original;

  /* Recursing down the left tree */
  if (original->left == node) {
    if (node->left == NULL)
      return node;
    return ninorder_helper(node->left, node);
  }
  /* Recursing down the right tree */
  else if (original->right == node) {
    if (node->left != NULL)
      return ninorder_helper(node->left, node);
    return node;
  }
  /* Recursing upwards */
  else if (original->parent == node && node->root->right != original) {
    if (node->left == original)
      return node;
    if (node->right == original)
      return ninorder_helper(node->parent, node);
  }

  return ninorder_helper(node->root->left, node->root);
}

/*******************************************************************************
 * FUNCTION:	    update_size
 *
 * DESCRIPTION:	    Called by bitree_merge to recursively update the 'size' and
 *		    'root' parameter in each node of the tree.
 *
 * ARGUMENTS:	    node: (bitree *) -- the node to update
 *		    size: (int *) -- pointer to the new size int.
 *		    root: (bitree *) -- new root for the merged tree
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int update_size(bitree * node, int * size, bitree * root)
{
  if (node == NULL)
    return 0;
  node->size = size;
  node->root = root;
  update_size(node->left, size, root);
  update_size(node->right, size, root);
  return 0;
}

/******************************************************************************/
