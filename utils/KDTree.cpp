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

/* Function Prototypes */
bool KDTree::insert_node(Point *p) {
  bool exists; bool go_left;
  Node *leaf = find_node(p, &exists, &go_left);
  Node *new_leaf = new Node(p);
  // TODO do I need to assert exists != NULL and go_left != NULL
  // assert (exists != NULL && go_left != NULL);

  if (exists) {
    return true;
  }

  else {
    if (go_left) leaf->left = new_leaf;
    else leaf->right = new_leaf;
    return true;
  }

  return false;
}


Node *KDTree::find_node(Point *p, bool *exists, bool *go_left) {
  // keeps track of how many nodes we've seen to know which dim to check
  int depth = 0;
  // k is the number of dimensions for each point (i.e. kD-tree)
  int k = 2;
  Node *curr_node = this->root;

  // if only node is root
  if (curr_node->left == NULL && curr_node->right == NULL) {
      (*exists) = false; (*go_left) = (p->x < curr_node->data->x);
      return curr_node;
  }


  int curr_dim; int split_pt; int p_data; bool is_equal;

  cout << "\n";
  cout << "Find_node: " << " " << p->x << "," << p->y << "\n";
  cout << "before loop" << "\n";

  while (curr_node->left != NULL || curr_node->right != NULL) {
      cout << "inside loop" << "\n";
      curr_dim = depth % k;
      depth++;

      // choose the correct x or y so don't need a bunch of if-else
      split_pt = ((1 - curr_dim) * curr_node->data->x +
                      (curr_dim) * curr_node->data->y);
      p_data = ((1 - curr_dim) * p->x +
                      (curr_dim) * p->y);


      cout << split_pt << "\n";
      cout << p_data << "\n";

      if (p_data < split_pt) {
        cout << "less than" << "\n";
        // if we need to go left and there is no left
        if (curr_node->left == NULL) {
          (*go_left) = true;
          break;
        }
        else {
          curr_node = curr_node->left;
        }
      }
      else { // p_data >= split_pt
        cout << "greater than" << "\n";
        // if we need to go right and there is no right
        if (curr_node->right == NULL) {
          (*go_left) = false;
          break;
        }
        else {
          curr_node = curr_node->right;
        }
      }
  }

  is_equal = (curr_node->data->x == p->x && curr_node->data->y == p->y);
  (*exists) = is_equal;

  cout << curr_node->data->x << "," << curr_node->data->y << "\n";
  cout << "exists: " << (*exists) << "\n";
  cout << "go_left: " << (*go_left) << "\n";

  return curr_node;
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
}

/*





*/
