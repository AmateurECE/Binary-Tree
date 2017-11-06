<h1>Binary Trees</h1>
<p>A <em>tree</em> is a hierarchical discrete structure which forms a subset of
  the class of discrete structures known as directed graphs. Specifically, it is
  acyclic, and may or may not be weighted. Specifically, a Binary Tree has no
  more than two children per node.</p>
<!-- TODO: insert the tree picture here. -->
<p>The structure of trees lends itself to different ways of traversing the tree.
  Traversing algorithms are not implemented as a part of this library, but they
  can be found as a part of my
  <a href="https://github.com/AmateurECE/Tree-Traversal">Traversing
    Algorithms</a> repository. This tree implementation has a diverse interface,
  explained below:</p>
<list>
  <li/><code>bitree_create</code> - Create a binary tree and return a pointer
  to it.
  <li/><code>bitree_destroy</code> - Destroy a binary tree.
  <li/><code>bitree_insl</code> - Insert a new node to the left of the specified
  node.
  <li/><code>bitree_insr</code> - Insert a new node to the right of the
  specified node.
  <li/><code>bitree_reml</code> - Remove the node to the left of the specified
  node.
  <li/><code>bitree_remr</code> - Remove the node to the right of the
  specified node.
  <li/><code>bitree_merge</code> - Merge the two trees specified.
  <li/><code>bitree_size</code> - Return the size of the tree specified.
  <li/><code>bitree_root</code> - Return a pointer to the root of the tree
  specified.
  <li/><code>bitree_isleaf</code> - Returns true if the node specified is
  a leaf.
  <li/><code>bitree_data</code> - Return the data pointer held in the node
  specified.
  <li/><code>bitree_left</code> - Return the left child of the node specified.
  <li/><code>bitree_right</code> - Return the right child of the node specified.
</list>
