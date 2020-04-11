/**
 *  @file KDTree.cpp
 *  @brief Implements KDTree data structure as defined in KDTree.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include "Point.h"
#include "KDTree.h"

Node::Node(Point *root) {
  this->data = root;
  this->left = NULL;
  this->right = NULL;
}

Node::Node(Point *root, Node *left, Node *right) {
  this->data = root;
  this->left = left;
  this->right = right;
}

KDTree::KDTree(Point *init_pt) {
  this->root = new Node(init_pt);
}

Point *KDTree::nearest_neighbor(Point *p) {
  (void)p;
  return NULL;
}

int get_decision(Point *curr_pt, Point *p, int curr_dim) {
  if (curr_pt->equals(p)) {
    return EXISTS;
  }
  else if (p->at(curr_dim) < curr_pt->at(curr_dim)) {
    return LEFT;
  }
  else {
    return RIGHT;
  }
}

/* Function Prototypes */
Node *find_node_helper(Point *p, Node* start_node, int *dir) {
  // keeps track of how many nodes we've seen to know which dim to check
  int depth = 0;
  // k is the number of dimensions for each point (i.e. kD-tree)
  int k = 2;
  Node *curr_node = start_node;
  int curr_dim; int split_pt; int p_data; bool is_equal; int decision;
  // if we are not at a leaf
  while (curr_node->left != NULL || curr_node->right != NULL) {
      curr_dim = depth % k;

      // checks if points are equal, and if not which branch to traverse,
      // given the correct dim
      decision = get_decision(curr_node->data, p, curr_dim);

      if (decision == EXISTS) {
        (*dir) = decision;
        return curr_node;
      }

      else if (decision == LEFT) {
        if (curr_node->left == NULL) { // if we need to go left and there is no left
          (*dir) = decision;
          break;
        }
        else {
          curr_node = curr_node->left; // proceed to left
          depth++; // increment depth because we are visiting another node
        }
      }

      else {
        if (curr_node->right == NULL) { // if we need to go right and there is no right
          (*dir) = decision; break; // break because
        }
        else {
          curr_node = curr_node->right; // proceed to the right
          depth++; // increment depth because we are visiting another node
        }
      }
  }
  // we have reached a leaf and need to make our last decision
  // note: if tree is just root, will come straight here
  decision = get_decision(curr_node->data, p, (depth % k));
  (*dir) = decision;
  return curr_node;
}

bool KDTree::insert_node(Point *p) {
  int dir;
  // traverse the kdtree looking for our node
  Node *leaf = find_node_helper(p, this->root, &dir);
  if (dir == EXISTS) { // node is already in the tree, don't need to do anything
    return true;
  }
  else {
    // create new leaf because we did not find the node we want to insert
    Node *new_leaf = new Node(p);
    if (dir == LEFT) leaf->left = new_leaf;
    else if (dir == RIGHT) leaf->right = new_leaf;
    else cout << "?" << '\n'; return false;
    return true;
  }
}

Node *KDTree::find_node(Point *p) {
  int dir;
  Node *leaf = find_node_helper(p, this->root, &dir);
  if (dir == EXISTS) {
    return leaf;
  }
  else {
    return NULL;
  }
}

void inorder_traversal_helper(Node *node) {
  if (node == NULL)
      return;
  /* first recur on left child */
  inorder_traversal_helper(node->left);
  /* then print the data of node */
  cout << node->data->x << "," << node->data->y << "\n";
  /* now recur on right child */
  inorder_traversal_helper(node->right);
}

void KDTree::print_inorder()
{
    cout << '\n';
    Node *node = this->root;
    inorder_traversal_helper(node);
    cout << '\n';
}

/*





*/
