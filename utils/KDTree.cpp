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

/*int set_dir(Point *A, Point *B, int *dir) {
  if (A.equals(B)) (*dir) = EXISTS;
  else if (A.at(0) )
}*/

/* Function Prototypes */
Node *find_node_helper(Point *p, Node* start_node, int *dir) {
  // keeps track of how many nodes we've seen to know which dim to check
  int depth = 0;
  // k is the number of dimensions for each point (i.e. kD-tree)
  int k = 2;
  Node *curr_node = start_node;

  // if only node is root
  if (curr_node->left == NULL && curr_node->right == NULL) {
      if (p->x < curr_node->data->x) (*dir) = LEFT;
      else (*dir) = RIGHT;
      return curr_node;
  }

  int curr_dim; int split_pt; int p_data; bool is_equal;
  while (curr_node->left != NULL || curr_node->right != NULL) {
      cout << "main loop" << "\n";
      curr_dim = depth % k;
      cout << "curr_dim: " << curr_dim << "\n";

      // check for equality at every interior node
      if (curr_node->data->equals(p)) {
        cout << "Interior found" << "\n";
        (*dir) = EXISTS;
        return curr_node;
      }

      // choose the correct splitting dimension for kd-tree node
      split_pt = curr_node->data->at(curr_dim);
      p_data = p->at(curr_dim);
      cout << "tree[curr_dim]: " << split_pt << "\n";
      cout << "p[curr_dim]: " << p_data << "\n";
      if (p_data < split_pt) {
        cout << "left" << "\n";
        if (curr_node->left == NULL) { // if we need to go left and there is no left
          cout << "can't go left" << '\n';
          (*dir) = LEFT; break;
        }
        else {
          cout << "going left" << '\n';
          curr_node = curr_node->left;
          depth++;
        }
      }
      else { // p_data >= split_pt
        cout << "right" << "\n";
        if (curr_node->right == NULL) { // if we need to go right and there is no right
          cout << "can't go right" << '\n';
          (*dir) = RIGHT; break;
        }
        else {
          cout << "going right" << '\n';

          curr_node = curr_node->right;
          depth++;
        }
      }
  }

  cout << "after main loop" << '\n';
  cout << "depth " << depth << '\n';
  cout << curr_node->data->at(depth % k) << "," <<  p->at(depth % k)<< '\n';

  if (curr_node->data->equals(p)) (*dir) = EXISTS;
  else if (p->at(depth % k) < curr_node->data->at(depth % k)) (*dir) = LEFT;
  else (*dir) = RIGHT;
  return curr_node;
}

bool KDTree::insert_node(Point *p) {
  int dir;

  cout << "Inserting " << p->x << ", " << p->y << '\n';
  Node *leaf = find_node_helper(p, this->root, &dir);
  Node *new_leaf = new Node(p);

  if (dir == EXISTS) { // node is already in the tree
    cout << "already exists" << "\n";
    cout << '\n';
    return true;
  }

  else {
    cout << "point didnt exist" << '\n';
    cout << "adding to " << dir << " direction" << '\n';
    if (dir == LEFT) leaf->left = new_leaf;
    else leaf->right = new_leaf;
    cout << '\n';
    return true;
  }

  return false;
}

Node *KDTree::find_node(Point *p) {
  int dir;
  Node *leaf = find_node_helper(p, this->root, &dir);
  // if dir == NULL the node exists, because there is no need to go to the
  // left or right to insert
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
