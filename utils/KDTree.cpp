/**
 *  @file KDTree.cpp
 *  @brief Implements KDTree data structure as defined in KDTree.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <math.h>

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

double Node::node_dist(Node *other) {
  return this->data->dist(*(other->data));
}

NodeDist::NodeDist(Node *node, int dist) {
  this->node = node;
  this->dist = dist;
}

bool NodeDist::compare_dist(NodeDist *other) {
  if (other == NULL) {
    cout << "comparing with NULL" << "\n";
  }
  if (other->dist < this->dist) {
    this->node = other->node;
    this->dist = other->dist;
    return true;
  }
  else {
    return false;
  }
}

/* Args
   curr_node:   The node within the kd-tree that you are comparing with to see
              which direction to go, also comparing the distance at that node
   best_so_far: A NodeDist class that keeps track of the Node* that is closest
              to test, as well as the corresponding distance
   test:        The point we are trying to find a neighbor of
   depth:     Number of node we have seen, tells us which dimension to compare
              with

   Returns
   A NodeDist object giving the closest neighbor and the corresponding distance
 */
NodeDist *nearest_neighbor_helper(Node *curr_node, NodeDist* best_so_far,
                                  Node* test, int depth) {
  if (curr_node == NULL) return NULL;
  // TODO dealing with NULL's ?

  // check current node
  int curr_dist = test->node_dist(curr_node);
  NodeDist *curr_node_dist = new NodeDist(curr_node, curr_dist);
  bool found_closer_nn = best_so_far->compare_dist(curr_node_dist);

  // check left or right node depending on curr_dim
  int k = 2; /* number of dimensions */
  int curr_dim = depth % k;
  int dir; // to check if we need to look across the split
  if (test->data->at(curr_dim) < curr_node->data->at(curr_dim)) { // proceed left
    depth++;
    dir = LEFT;
    best_so_far = (nearest_neighbor_helper(curr_node->left, best_so_far,
                                          test, depth));
  }
  else { // proceed down tree to the right
    depth++;
    dir = RIGHT;
    best_so_far = (nearest_neighbor_helper(curr_node->right, best_so_far,
                                          test, depth));
  }

  /* have to check opposite side of split if the hypersphere centered at test
  with radius best_dist crosses the splitting boundary */
  int radius = fabs((test->data->at(curr_dim) - curr_node->data->at(curr_dim)));
  if (radius < best_so_far->dist) {
    if (dir == LEFT)  {
      best_so_far = (nearest_neighbor_helper(curr_node->right, best_so_far,
                                            test, depth));
    }
    else {
      best_so_far = (nearest_neighbor_helper(curr_node->left, best_so_far,
                                            test, depth));
    }
  }
  return best_so_far;
}

KDTree::KDTree(Point *init_pt) {
  this->root = new Node(init_pt);
}

Point *KDTree::nearest_neighbor(Point *p) {
  NodeDist *best_so_far = new NodeDist(NULL, INT_MAX);
  Node *curr_node = this->root;
  Node *test = new Node(p);
  NodeDist *node_dist = nearest_neighbor_helper(curr_node, best_so_far, test, 0);
  int best_dist = node_dist->dist;
  Node* nn_node = node_dist->node;
  // want to return the point b/c node interface is unncessary
  return nn_node->data;
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
