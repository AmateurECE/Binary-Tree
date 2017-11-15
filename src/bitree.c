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
 * LAST EDITED:	    11/14/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#ifdef CONFIG_DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

#include "bitree.h"

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#ifdef CONFIG_DEBUG
#define FAIL	"\033[1;31m"
#define PASS	"\033[1;39m"
#define NC	"\033[0m"
#endif

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG
static int test_create();
static int test_destroy();
static int test_insl();
static int test_insr();
static int test_rem();
static int test_merge();
static int test_npreorder();
static int test_npostorder();
static int test_ninorder();
static int test_nlevelorder();

static bitree * prep_tree();
#endif

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
 * NOTES:	    none.
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
 *		    internal associated memory and sets `*tree' to point to NULL
 *
 * ARGUMENTS:	    tree: (bitree **) -- pointer to the tree pointer to free.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none.
 ***/
void bitree_destroy(bitree ** tree)
{
  if (tree == NULL || *tree == NULL)
    return;
  
  bitree_rem(*tree);

  /* bitree_rem() frees the memory, so *tree now contains garbage. Let's
   * make that a little more safe.
   */
  *tree = NULL;
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
 * NOTES:	    none.
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
 * NOTES:	    none.
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

void bitree_rem(bitree * node)
{ /* TODO: bitree_rem */ return; }
int bitree_merge(bitree * tree1, bitree * tree2, void * data)
{ /* TODO: bitree_merge */ return 1; }
bitree * bitree_npreorder(bitree * node)
{ /* TODO: bitree_npreorder */ return NULL; }
bitree * bitree_npostorder(bitree * node)
{ /* TODO: bitree_npostorder */ return NULL; }
bitree * bitree_ninorder(bitree * node)
{ /* TODO: bitree_ninorder */ return NULL; }
bitree * bitree_nlevelorder(bitree * node)
{ /* TODO: bitree_nlevelorder */ return NULL; }

/*******************************************************************************
 * MAIN
 ***/

#ifdef CONFIG_DEBUG
int main(int argc, char * argv[])
{
  srand((unsigned)time(NULL));

  fprintf(stderr,
	  
	  "Test (bitree_create):\t\t%s\n"
	  "Test (bitree_destroy):\t\t%s\n"
	  "Test (bitree_insl):\t\t%s\n"
	  "Test (bitree_insr):\t\t%s\n"
	  "Test (btiree_rem):\t\t%s\n"
	  "Test (bitree_merge):\t\t%s\n"
	  "Test (bitree_npreorder):\t%s\n"
	  "Test (bitree_npostorder):\t%s\n"
	  "Test (bitree_ninorder):\t\t%s\n"
	  "Test (bitree_nlevelorder):\t%s\n",

	  test_create()	    	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_destroy()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_insl()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_insr()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_rem()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_merge()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_npreorder()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_npostorder()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_ninorder()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_nlevelorder()	? FAIL"Fail"NC : PASS"Pass"NC);

}
#endif

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    test_create
 *
 * DESCRIPTION:	    Tests the bitree_create() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
#ifdef CONFIG_DEBUG
static int test_create()
{
  /* Test cases:
   *	NULL, data
   *	free, data
   *	free, NULL
   */
  bitree * test;
  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  *pTest = 1;
  if ((test = bitree_create(NULL, pTest)) == NULL)
    return 1;
  bitree_destroy(&test);
  if (test != NULL)
    return 1;

  if ((test = bitree_create(free, pTest)) == NULL)
    return 1;
  bitree_destroy(&test);
  if (test != NULL)
    return 1;

  if ((test = bitree_create(free, NULL)) != NULL)
    return 1;

  return 0;
}

/*******************************************************************************
 * FUNCTION:	    test_destroy
 *
 * DESCRIPTION:	    Test the bitree_destroy() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_destroy()
{
  /* Test cases:
   *	NULL (input)
   *	Empty tree
   *	Non-empty tree
   */
  /* As long as we don't get a segfault, these tests will pass */
  /* Null input */
  bitree_destroy(NULL);

  /* Empty Tree */
  bitree * test;
  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  if ((test = bitree_create(free, pTest)) == NULL)
    return 1;
  bitree_destroy(&test);
  if (test != NULL)
    goto error_exit;

  /* Non-empty tree */
  pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  *pTest = 1;
  if ((test = bitree_create(free, pTest)) == NULL)
    return 1;
  /* Add stuff to the tree */
  pTest = NULL;
  for (int i = 0; i < 5; i++) {
    if ((pTest = malloc(sizeof(int))) == NULL)
      goto error_exit;
    *pTest = rand() % 20;
    if (bitree_insl(test, (void *)pTest))
      goto error_exit;
    test = bitree_left(test);
  }
  bitree_destroy(&test);
  if (test != NULL)
    goto error_exit;

  return 0;

 error_exit: {
    if (test != NULL)
      bitree_destroy(&test);
    if (pTest != NULL)
      free(pTest);
    return 1;    
  }
}

/*******************************************************************************
 * FUNCTION:	    test_insl
 *
 * DESCRIPTION:	    Tests the bitree_insl() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the tests pass,  1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_insl()
{
  /* Test cases:
   *	NULL, data
   *	test, NULL
   *	Insertion into non-empty node
   *	Insertion into full node
   */
  bitree * test = NULL;
  int * pTest = NULL;
  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
  if ((test = bitree_create(free, pTest)) == NULL)
    return 1;
  *pTest = rand() % 20;

  /* NULL, data */
  if (!bitree_insl(NULL, pTest))
    goto error_exit;

  /* test, NULL */
  if (!bitree_insl(test, NULL))
    goto error_exit;

  /* Insertion into non-empty node */
  if (bitree_insl(test, pTest))
    goto error_exit;
  if (test->left == NULL)
    goto error_exit;

  /* Insertion into full node */
  if (!bitree_insl(test, pTest))
    goto error_exit;
  bitree_destroy(&test);
  if (test != NULL)
    goto error_exit;
  
  return 0;

 error_exit: {
    if (test != NULL)
      bitree_destroy(&test);
    if (pTest != NULL)
      free(pTest);
    return 1;
  }
}

/*******************************************************************************
 * FUNCTION:	    test_insr
 *
 * DESCRIPTION:	    Tests the bitree_insr() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_insr()
{
  /* Test cases:
   *	NULL, data
   *	test, NULL
   *	Insertion into non-empty node
   *	Insertion into full node
   */
  bitree * test = NULL;
  int * pTest = NULL;
  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
  *pTest = rand() % 20;
  if ((test = bitree_create(free, pTest)) == NULL)
    return 1;

  /* NULL, data */
  if (!bitree_insr(NULL, pTest))
    goto error_exit;

  /* test, NULL */
  if (!bitree_insr(test, NULL))
    goto error_exit;

  /* Insertion into non-empty node */
  if (bitree_insr(test, pTest))
    goto error_exit;
  if (test->right == NULL)
    goto error_exit;

  /* Insertion into full node */
  if (!bitree_insr(test, pTest))
    goto error_exit;
  bitree_destroy(&test);
  if (test != NULL)
    goto error_exit;

  return 0;

 error_exit: {
    if (test != NULL)
      bitree_destroy(&test);
    if (pTest != NULL)
      free(pTest);
    return 1;
  }
}

/*******************************************************************************
 * FUNCTION:	    test_rem
 *
 * DESCRIPTION:	    Tests the bitree_rem() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_rem()
{
  /* Test cases:
   *	NULL, data
   *	test, NULL
   *	Remove an existing node
   *	Tree is empty
   *	Remove a non-existing node
   */
  /* As long as we don't get a segfault, these tests will pass */
  bitree * test = NULL;
  int * pTest = NULL;

  /* NULL */
  bitree_rem(test);

  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
  *pTest = rand() % 20;

  /* Remove an existing node */
  if ((test = bitree_create(free, pTest)) == NULL)
    goto error_exit;
  if (bitree_insl(test, (void *)pTest))
    goto error_exit;
  bitree_rem(test->left);
  if (test->left != NULL)
    goto error_exit;

  /* Tree is empty, non-existing node. */
  bitree_rem(test->left);
  bitree_rem(test);
  bitree_rem(test); /* Call again to be sure we don't segfault. */
  return 0;

 error_exit: {
    if (test != NULL)
      bitree_destroy(&test);
    if (pTest != NULL)
      free(pTest);
    return 1;
  }
}

/*******************************************************************************
 * FUNCTION:	    test_merge
 *
 * DESCRIPTION:	    Test the bitree_merge() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_merge()
{

  /* Case 1:
   *	isroot(tree1) && isfull(tree1) && isroot(tree2) && data	    -> 0
   *	isroot(tree1) && isfull(tree1) && isroot(tree2) && !data    -> -1
   *	isroot(tree1) && isfull(tree1) && !isroot(tree2) && data    -> -1
   * Case 2:
   *	!isroot(tree1) && !isfull(tree1) && isroot(tree2) && data   -> 0
   *	!isroot(tree1) && !isfull(tree1) && isroot(tree2) && !data  -> 0
   *	!isroot(tree1) && !isfull(tree1) && !isroot(tree2)	    -> -1
   *	!isroot(tree1) && isfull(tree1)				    -> -1
   * NULL, tree2, (data | NULL)					    -> -1
   * tree1, NULL, (data | NULL)					    -> -1
   * tree1 and tree2 are on the same tree.			    -> -1
   */
  bitree * test1 = prep_tree();
  bitree * test2 = prep_tree();
  int * pTest = malloc(sizeof(int));
  *pTest = 1;
  if (test1 == NULL || test2 == NULL || pTest == NULL)
    return 1;

  /* isroot(tree1) && isfull(tree1) && isroot(tree2) && data */
  if (bitree_merge(test1, test2, pTest))
    return 1;

  /* Reset trees */
  bitree_destroy(&test1);
  bitree_destroy(&test2);
  pTest = malloc(sizeof(int));
  *pTest = 1;
  test1 = prep_tree(), test2 = prep_tree();
  if (test1 == NULL || test2 == NULL)
    return 1;

  /* isroot(tree1) && isfull(tree1) && isroot(tree2) && !data */
  if (!bitree_merge(test1, test2, NULL))
    return 1;

  /* isroot(tree1) && isfull(tree1) && !isroot(tree2) && data */
  if (!bitree_merge(test1, test2->left, pTest))
    return 1;

  /* Case 2: */
  /* !isroot(tree1) && !isfull(tree1) && isroot(tree2) && data */
  if (bitree_merge(test1->right, test2, pTest))
    return 1;

  /* Reset trees */
  bitree_destroy(&test1);
  bitree_destroy(&test2);
  pTest = malloc(sizeof(int));
  *pTest = 1;
  test1 = prep_tree(), test2 = prep_tree();
  if (test1 == NULL || test2 == NULL)
    return 1;

  /* !isroot(tree1) && !isfull(tree1) && isroot(tree2) && !data */
  if (bitree_merge(test1->right, test2, NULL))
    return 1;

  /* Reset trees */
  bitree_destroy(&test1);
  bitree_destroy(&test2);
  pTest = malloc(sizeof(int));
  *pTest = 1;
  test1 = prep_tree(), test2 = prep_tree();
  if (test1 == NULL || test2 == NULL)
    return 1;

  /* !isroot(tree1) && !isfull(tree1) && !isroot(tree2) */
  if (!bitree_merge(test1->right, test2->right, NULL))
    return 1;

  /* !isroot(tree1) && isfull(tree1) */
  if (!bitree_merge(test1->left, test2, NULL))
    return 1;

  /* NULL, tree2, (data | NULL) */
  if (!bitree_merge(NULL, test2, pTest))
    return 1;

  /* tree1, NULL, (data | NULL) */
  if (!bitree_merge(test1, NULL, pTest))
    return 1;

  /* tree1 and tree2 are on the same tree. */
  if (!bitree_merge(test1, test1->left, pTest))
    return 1;

  bitree_destroy(&test1);
  bitree_destroy(&test2);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    test_npreorder
 *
 * DESCRIPTION:	    Test the bitree_npreorder() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_npreorder()
{
  /* Test cases:
   *	NULL			    -> NULL
   *	Tree is empty		    -> Root
   *	Next node exists	    -> Next
   *	Next node does not exist    -> Root
   */

  /* NULL */
  if(bitree_npreorder(NULL))
    return 1;

  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  *pTest = 1;
  bitree * test = bitree_create(free, pTest);
  if (test == NULL)
    return 1;

  /* Tree is empty */
  if (bitree_npreorder(test) != test)
    return 1;

  bitree_destroy(&test);
  test = prep_tree();
  if (test == NULL)
    return 1;

  /* Next node exists */
  if (bitree_npreorder(test) != test->left)
    return 1;

  /* Next node does not exist */
  if (bitree_npreorder(test->right) != test)
    return 1;

  bitree_destroy(&test);
  return 1;
}

/*******************************************************************************
 * FUNCTION:	    test_npostorder
 *
 * DESCRIPTION:	    Tests the bitree_npostorder() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_npostorder()
{
  /* Test cases:
   *	NULL
   *	Tree is empty
   *	Next node exists
   *	Next node does not exist
   */

  /* NULL */
  if(bitree_npostorder(NULL))
    return 1;

  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  *pTest = 1;
  bitree * test = bitree_create(free, pTest);
  if (test == NULL)
    return 1;

  /* Tree is empty */
  if (bitree_npostorder(test) != test)
    return 1;

  bitree_destroy(&test);
  test = prep_tree();
  if (test == NULL)
    return 1;

  /* Next node exists */
  if (bitree_npostorder(test->left->left) != test->left->right)
    return 1;

  /* Next node does not exist */
  if (bitree_npostorder(test) != test)
    return 1;

  bitree_destroy(&test);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    test_ninorder
 *
 * DESCRIPTION:	    Tests the bitree_ninorder() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_ninorder()
{
  /* Test cases:
   *	NULL
   *	Tree is empty
   *	Next node exists
   *	Next node does not exist
   */

  /* NULL */
  if(bitree_ninorder(NULL))
    return 1;

  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  *pTest = 1;
  bitree * test = bitree_create(free, pTest);
  if (test == NULL)
    return 1;

  /* Tree is empty */
  if (bitree_ninorder(test) != test)
    return 1;

  bitree_destroy(&test);
  test = prep_tree();
  if (test == NULL)
    return 1;

  /* Next node exists */
  if (bitree_ninorder(test->left->left) != test->left)
    return 1;

  /* Next node does not exist */
  if (bitree_ninorder(test->right) != test)
    return 1;

  bitree_destroy(&test);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    test_nlevelorder
 *
 * DESCRIPTION:	    Test the bitree_nlevelorder() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_nlevelorder()
{
  /* Test cases:
   *	NULL
   *	Tree is empty
   *	Next node exists
   *	Next node does not exist
   */

  /* NULL */
  if(bitree_nlevelorder(NULL))
    return 1;

  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return 1;
  *pTest = 1;
  bitree * test = bitree_create(free, pTest);
  if (test == NULL)
    return 1;

  /* Tree is empty */
  if (bitree_nlevelorder(test) != test)
    return 1;

  bitree_destroy(&test);
  test = prep_tree();
  if (test == NULL)
    return 1;

  /* Next node exists */
  if (bitree_nlevelorder(test) != test->left)
    return 1;

  /* Next node does not exist */
  if (bitree_nlevelorder(test->left->right) != test)
    return 1;

  bitree_destroy(&test);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    prep_tree
 *
 * DESCRIPTION:	    This function prepares a bitree struct for testing. It's
 *		    purpose is to prevent code pasting.
 *
 * ARGUMENTS:	    
 *
 * RETURN:	    
 *
 * NOTES:	    
 ***/
static bitree * prep_tree()
{
  bitree * tree = NULL;
  int * pTest = malloc(sizeof(int));
  if (pTest == NULL)
    return NULL;
  *pTest = 1;
  if ((tree = bitree_create(free, pTest)) == NULL)
    goto error_exit;

  int test = 0;
  while (1) {
    if ((pTest = malloc(sizeof(int))) == NULL)
      goto error_exit;
    *pTest = rand() % 20;
    
    switch((test++)) {
    case 0:
      if (bitree_insl(tree, (void *)pTest))
	goto error_exit;
      break;
    case 1:
      if (bitree_insl(tree->left, (void *)pTest))
	goto error_exit;
      break;
    case 2:
      if (bitree_insr(tree->left, (void *)pTest))
	goto error_exit;
      break;
    case 3:
      if (bitree_insr(tree, (void *)pTest))
	goto error_exit;
      break;
    default:
      goto break_loop;
    }
    continue; /* Unconditional continue */
  break_loop:
    break;
  }
  
  return tree;

 error_exit: {
    if (tree != NULL)
      bitree_destroy(&tree);
    if (pTest != NULL)
      free(pTest);
    return NULL;
  }
}
#endif

/******************************************************************************/
