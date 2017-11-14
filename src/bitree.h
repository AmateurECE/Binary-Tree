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
 * LAST EDITED:	    11/14/2017
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
 * Merges tree2 into the node specified at tree1. If tree1 is the root, and has
 * two children nodes, a new node is created which becomes the new root of the
 * tree, with its children being the root of tree1 and tree2, and has data data.
 * Otherwise, if tree1 has only one child node, the root of tree2 is inserted
 * to the free child spot. In the latter case, the value of data is not used.
 * If tree2 is not a root node, an error is returned.
 */
extern int bitree_merge(bitree * tree1, bitree * tree2, void * data);

#endif /* __ET_BITREE_H_ */

/******************************************************************************/
