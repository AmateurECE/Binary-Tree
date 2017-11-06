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
 * LAST EDITED:	    11/06/2017
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

#define FAIL	"\033[1;31m"
#define NC	"\033[0m"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

#ifdef CONFIG_DEBUG
static int test_create();
static int test_destroy();
static int test_insl();
static int test_insr();
static int test_reml();
static int test_remr();
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

bitree * bitree_create(void (*destroy)(void *)) { return NULL; }
void bitree_destroy(bitree ** tree) { return; }
int bitree_insl(bitree * parent, void * data) { return 1; }
int bitree_insr(bitree * parent, void * data) { return 1; }
void bitree_reml(bitree * node) { return; }
void bitree_remr(bitree * node) { return; }
int bitree_merge(bitree * tree1, bitree * tree2, void * data) { return 1; }
bitree * bitree_npreorder(bitree * node) { return NULL; }
bitree * bitree_npostorder(bitree * node) { return NULL; }
bitree * bitree_ninorder(bitree * node) { return NULL; }
bitree * bitree_nlevelorder(bitree * node) { return NULL; }

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
	  "Test (bitree_reml):\t\t%s\n"
	  "Test (btiree_remr):\t\t%s\n"
	  "Test (bitree_merge):\t\t%s\n"
	  "Test (bitree_npreorder):\t%s\n"
	  "Test (bitree_npostorder):\t%s\n"
	  "Test (bitree_ninorder):\t\t%s\n"
	  "Test (bitree_nlevelorder):\t%s\n",

	  test_create()	    	? FAIL"Fail"NC : "Pass",
	  test_destroy()	? FAIL"Fail"NC : "Pass",
	  test_insl()		? FAIL"Fail"NC : "Pass",
	  test_insr()		? FAIL"Fail"NC : "Pass",
	  test_reml()		? FAIL"Fail"NC : "Pass",
	  test_remr()		? FAIL"Fail"NC : "Pass",
	  test_merge()		? FAIL"Fail"NC : "Pass",
	  test_npreorder()	? FAIL"Fail"NC : "Pass",
	  test_npostorder()	? FAIL"Fail"NC : "Pass",
	  test_ninorder()	? FAIL"Fail"NC : "Pass",
	  test_nlevelorder()	? FAIL"Fail"NC : "Pass");

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
   *	NULL, free
   *	test_compare, NULL
   *	test_compare, free
   */
  bitree * test;
  if ((test = bitree_create(NULL)) == NULL)
    return 1;
  bitree_destroy(&test);
  if (test != NULL)
    return 1;

  if ((test = bitree_create(free)) == NULL)
    return 1;
  bitree_destroy(&test);
  if (test != NULL)
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
  if ((test = bitree_create(free)) == NULL)
    return 1;
  bitree_destroy(&test);
  if (test != NULL)
    goto error_exit;

  /* Non-empty tree */
  if ((test = bitree_create(free)) == NULL)
    return 1;
  /* Add stuff to the tree */
  int * pTest = NULL;
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
  bitree * test;
  if ((test = bitree_create(free)) == NULL)
    return 1;
  int * pTest = NULL;
  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
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
  bitree * test;
  if ((test = bitree_create(free)) == NULL)
    return 1;
  int * pTest;
  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
  *pTest = rand() % 20;
  /* NULL, data */
  if (!bitree_insr(NULL, pTest))
    goto error_exit;
  /* test, NULL */
  if (!bitree_insr(test, NULL))
    goto error_exit;
  /* Insertion into non-empty node */
  if (bitree_insr(test, pTest))
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
 * FUNCTION:	    test_reml
 *
 * DESCRIPTION:	    Tests the bitree_reml() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the tests fail, 1 otherwise.
 *
 * NOTES:	    
 ***/
static int test_reml()
{
  /* Test cases:
   *	NULL
   *	Remove an existing node
   *	Tree is empty
   *	Remove a non-existing node
   */
  bitree * test = NULL;
  int * pTest = NULL;
  /* NULL */
  bitree_reml(NULL);
  /* Remove an existing node */
  if ((test = bitree_create(free)) == NULL)
    goto error_exit;
  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
  *pTest = rand() % 20;
  if (bitree_insl(test, (void *)pTest))
    goto error_exit;
  bitree_reml(test);
  if (test->left != NULL)
    goto error_exit;
  /* Tree is empty, non-existing node. */
  if (!bitree_isempty(test))
    goto error_exit;
  bitree_reml(test);

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
 * FUNCTION:	    test_remr
 *
 * DESCRIPTION:	    Tests the bitree_remr() function.
 *
 * ARGUMENTS:	    none.
 *
 * RETURN:	    int -- 0 if the test passes, 1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int test_remr()
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
  bitree_remr(test);
  /* Remove an existing node */
  if ((test = bitree_create(free)) == NULL)
    goto error_exit;
  if ((pTest = malloc(sizeof(int))) == NULL)
    goto error_exit;
  *pTest = rand() % 20;
  if (bitree_insl(test, (void *)pTest))
    goto error_exit;
  bitree_remr(test);
  if (test->right != NULL)
    goto error_exit;
  /* Tree is empty, non-existing node. */
  bitree_remr(test);

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
   *	isroot(tree1) && isfull(tree1) && isroot(tree2) && data
   *	isroot(tree1) && isfull(tree1) && isroot(tree2) && !data
   *	isroot(tree1) && isfull(tree1) && !isroot(tree2) && data
   * Case 2:
   *	!isroot(tree1) && !isfull(tree1) && data
   *	!isroot(tree1) && !isfull(tree1) && !data
   *	!isroot(tree1) && !isfull(tree1)
   * NULL, tree2, (data | NULL)
   * tree1, NULL, (data | NULL)
   * tree1 and tree2 are on the same tree.
   * !isroot(tree1) && isfull(tree1)
   */
  return 1;
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
   *	NULL
   *	Tree is empty
   *	Next node exists
   *	Next node does not exist
   */
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
  return 1;
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
  return 1;
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
  return 1;
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
  bitree * test = NULL;
  int * pTest = NULL;
  if ((test = bitree_create(free)) == NULL)
    goto error_exit;

  int test = 0;
  while (1) {
    if ((pTest = malloc(sizeof(int))) == NULL)
      goto error_exit;
    *pTest = rand() % 20;
    
    switch((test++)) {
    case 0:
      if (bitree_insl(test, (void *)pTest))
	goto error_exit;
      break;
    case 1:
      if (bitree_insl(test->left, (void *)pTest))
	goto error_exit;
      break;
    case 2:
      if (bitree_insr(test->left, (void *)pTest))
	goto error_exit;
      break;
    case 3:
      if (bitree_insr(test, (void *)pTest))
	goto error_exit;
      break;
    default:
      goto break_loop;
    }
    continue; /* Unconditional continue */
  break_loop:
    break;
  }
  
  return test;

 error_exit: {
    if (test != NULL)
      bitree_destroy(test);
    if (pTest != NULL)
      free(pTest);
    return NULL;
  }
}
#endif

/******************************************************************************/
