/*******************************************************************************
 * NAME:	    test.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This file contains the source code which test the API.
 *
 * CREATED:	    11/25/2017
 *
 * LAST EDITED:	    11/26/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bitree.h"

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define FAIL "\033[1;31m"

/* This is specific to my terminal, I think. But since it only affects the
 * colors of the test output, it doesn't really matter
 */
#ifdef __APPLE__
#   define PASS "\033[1;32m"
#else
#   define PASS "\033[1;39m"
#endif

#define NC	"\033[0m"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int test_create(void);
static int test_destroy(void);
static int test_insl(void);
static int test_insr(void);
static int test_rem(void);
static int test_merge(void);
static int test_npreorder(void);
static int test_npostorder(void);
static int test_ninorder(void);

/* TODO: make print_tree static */
void print_tree(bitree * bitree, size_t null);
static bitree * prep_tree(void);

/*******************************************************************************
 * MAIN
 ***/

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
	  "Test (bitree_ninorder):\t\t%s\n",

	  test_create()	    	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_destroy()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_insl()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_insr()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_rem()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_merge()		? FAIL"Fail"NC : PASS"Pass"NC,
	  test_npreorder()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_npostorder()	? FAIL"Fail"NC : PASS"Pass"NC,
	  test_ninorder()	? FAIL"Fail"NC : PASS"Pass"NC);

#ifdef CONFIG_EXTENDED_TRAVERSAL_TEST

  printf("\n"FAIL"Pre-Order Test:"NC"\n");
  bitree * test_tree = prep_tree();
  print_tree(test_tree, 0);
  printf("\n");
  bitree * test_node = test_tree;
  int i = 0;
  do {
    test_node = bitree_npreorder(test_node);
    printf("%d: %p\n", i++, test_node);
  } while (test_node != NULL && test_node != test_tree);
  bitree_destroy(&test_tree);

  printf("\n"FAIL"Post-Order Test:"NC"\n");
  test_tree = prep_tree();
  print_tree(test_tree, 0);
  printf("\n");
  test_node = test_tree;
  i = 0;
  do {
    test_node = bitree_npostorder(test_node);
    printf("%d: %p\n", i++, test_node);
  } while (test_node != NULL && test_node != test_tree);
  bitree_destroy(&test_tree);

  printf("\n"FAIL"In-Order Test:"NC"\n");
  test_tree = prep_tree();
  print_tree(test_tree, 0);
  printf("\n");
  test_node = test_tree;
  i = 0;
  do {
    test_node = bitree_ninorder(test_node);
    printf("%d: %p\n", i++, test_node);
  } while (test_node != NULL && test_node != test_tree);
  bitree_destroy(&test_tree);

#endif /* CONFIG_EXTENDED_TRAVERSAL_TEST */

  return 0;
}


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
  /* Calling bitree_rem() twice on a node will cause a segfault.
   * TODO: Prevent segfault on double remove? */
  /* bitree_rem(test); */
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
   * Case 3:
   *	isroot(tree1) && !isfull(tree1) && isroot(tree2) && data    -> 0
   *	isroot(tree1) && !isfull(tree1) && isroot(tree2) && !data   -> 0
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

  /* Case 3: */
  /* isroot(tree1) && !isfull(tree1) && isroot(tree2) && data    -> 0 */
  bitree_rem(test1->right);
  if (test1->right != NULL)
    return 1;
  if (bitree_merge(test1, test2, pTest))
    return 1;

  /* Reset trees */
  bitree_destroy(&test1);
  pTest = malloc(sizeof(int));
  *pTest = 1;
  test1 = prep_tree(), test2 = prep_tree();
  if (test1 == NULL || test2 == NULL)
    return 1;

  bitree_rem(test1->left);
  if (test1->left != NULL)
    return 1;
  if (bitree_merge(test1, test2, NULL))
    return 1;
  /* isroot(tree1) && !isfull(tree1) && isroot(tree2) && !data   -> 0 */

  bitree_destroy(&test1);
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
  return 0;
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
  if (bitree_npostorder(test) != test->left->left)
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
  if (bitree_ninorder(test) != test->right)
    return 1;

  bitree_destroy(&test);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    print_tree
 *
 * DESCRIPTION:	    Prints a tree to STDOUT.
 *
 * ARGUMENTS:	    bitree: (bitree *) -- pointer to the tree to print.
 *		    null: (size_t) -- internal value. User should always pass
 *			0.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none.
 ***/
void print_tree(bitree * bitree, size_t null)
{
  if (bitree == NULL)
    return;
  printf("--->\n");
  if (null != 0)
    for (size_t i = 0; i < null; i++)
      printf("\t");
  printf("%s %p ",
	 bitree->parent == NULL ? "|" :
	 bitree->parent->left == bitree ? "L" : "R",
	 bitree);
  print_tree(bitree->left, ++null);
  print_tree(bitree->right, null);
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

/******************************************************************************/