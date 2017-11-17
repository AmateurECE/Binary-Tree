/*******************************************************************************
 * NAME:	    bitree.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This function contains the public interface for the Binary
 *		    Tree implementation in bitree.c.
 *
 * CREATED:	    11/06/2017
 *
 * LAST EDITED:	    11/16/2017
 ***/

#ifndef __ET_BITREE_H_
#define __ET_BITREE_H_

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define bitree_isempty(tree)	((tree)->size == 0)
#define bitree_isleaf(tree)	((tree)->left == NULL && (tree)->right == NULL)
#define bitree_left(tree)	((tree)->left)
#define bitree_right(tree)	((tree)->right)
#define bitree_size(tree)	(*((tree)->size))
#define bitree_root(tree)	((tree)->root)
#define bitree_parent(tree)	((tree)->parent)
#define bitree_data(tree)	((tree)->data)

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _Node_ {

  struct _Node_ * root;
  struct _Node_ * parent;
  struct _Node_ * left;
  struct _Node_ * right;
  
  int * size;
  void (*destroy)(void *);
  void * data;

} bitree;

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

/* TODO: Fix the documentation here. */

extern bitree * bitree_create(void (*destroy)(void *), void * data);
/* Even if the node that is passed is not the root node, the whole tree is
 * destroyed
 */
extern void bitree_destroy(bitree ** tree);
extern int bitree_insl(bitree * parent, void * data);
extern int bitree_insr(bitree * parent, void * data);
extern void bitree_rem(bitree * node);

/* These functions return the next node struct in a tree traversal, assuming
 * the algorithm specified (or NULL if there is no more). They can be used in
 * loop structures, for flow control, or to develop complex and efficient
 * traversal algorithms.
 */
extern bitree * bitree_npreorder(bitree * node);
extern bitree * bitree_npostorder(bitree * node);
extern bitree * bitree_ninorder(bitree * node);
extern bitree * bitree_nlevelorder(bitree * node);

/**
 * This merging function is greedy, and uses any means possible to merge the two
 * trees it is passed. There is generally two cases which affect the behaviour
 * of this function:
 *
 * Case 1: The node at `tree1' is the root of its tree, `tree1' already has two
 *	children, and `tree2' is the root of its tree.
 *	    In this case, a new node is generated, which contains data `data',
 *	and its children are `tree1' and `tree2', left to right, respectively.
 * Case 2: The node at `tree1' is the root of its tree, and it has at least one
 *	unoccupied child, and the node at `tree2' is the root of its tree.
 *	    In this case, `tree2' is applied to one of the free children of
 *	`tree1', with the left child being given precedence.
 * Case 3: The node at `tree1' is not the root of its tree, it has at least one
 *	unoccupied child position, and the node at `tree2' is the root of its
 *	tree.
 *	    In this case, `tree2' is applied to `tree1', with the left child
 *	of `tree1' given precedence.
 *
 * Any cases which do not exactly fit into these criteria will result in the
 * failure of the function. The two trees cannot be on the same tree. In
 * addition, if tree1->destroy does not point to the same function as
 * tree2->destroy, or if both are not NULL, the function will return an error.
 */
extern int bitree_merge(bitree * tree1, bitree * tree2, void * data);

#endif /* __ET_BITREE_H_ */

/******************************************************************************/
