# Binary Tree #

A <em>tree</em> is a hierarchical discrete structure which forms a subset of
the class of discrete structures known as directed graphs. Specifically, it is
acyclic, and may or may not be weighted. Specifically, a Binary Tree has no
more than two children per node.
<!-- TODO: insert the tree picture here. -->

The structure of trees lends itself to different ways of traversing the tree.
Traversing algorithms are not implemented as a part of this library, but they
can be found as a part of my
<a href="https://github.com/AmateurECE/Tree-Traversal">Traversing
Algorithms</a> repository. This tree implementation has a diverse interface,
explained below:

* `bitree_create` - Create a binary tree and return a pointer to it.
* `bitree_destroy` - Destroy a binary tree.
* `bitree_insl` - Insert a new node to the left of the specified node.
* `bitree_insr` - Insert a new node to the right of the specified node.
* `bitree_rem` - Remove the node to the left of the specified node.
* `bitree_merge` - Merge the two trees specified.
* `bitree_size` - Return the size of the tree specified.
* `bitree_root` - Return a pointer to the root of the tree specified.
* `bitree_isleaf` - Returns true if the node specified is a leaf.
* `bitree_data` - Return the data pointer held in the node specified.
* `bitree_left` - Return the left child of the node specified.
* `bitree_right` - Return the right child of the node specified.
