/**
 *  @file KDTree.cpp
 *  @brief Implements KDTree data structure as defined in KDTree.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <limits>
#include <cfloat>
#include <unordered_set>
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


KDTree::KDTree(Point *init_pt) {
  this->root = new Node(init_pt);
}

int get_decision(Point *curr_pt, Point *p, int curr_dim) {
  if (curr_pt == p) {
    return EXISTS;
  }
  else if ((*p)[curr_dim] < (*curr_pt)[curr_dim]) {
    return LEFT;
  }
  else {
    return RIGHT;
  }
}

/* Function Prototypes */
Node *find_node_helper(Point *p, Node* start_node, int &dir) {
  // keeps track of how many nodes we've seen to know which dim to check
  int depth = 0;
  Node *curr_node = start_node;
  int curr_dim; int decision;
  // if we are not at a leaf
  while (curr_node->left != NULL || curr_node->right != NULL) {
      curr_dim = depth % K;

      // checks if points are equal, and if not which branch to traverse,
      // given the correct dim
      decision = get_decision(curr_node->data, p, curr_dim);

      if (decision == EXISTS) {
        dir = decision;
        return curr_node;
      }

      else if (decision == LEFT) {
        if (curr_node->left == NULL) {
          dir = decision;
          break;
        }
        else {
          curr_node = curr_node->left;
          depth++;
        }
      }

      else {
        if (curr_node->right == NULL) {
          dir = decision;
          break;
        }
        else {
          curr_node = curr_node->right;
          depth++;
        }
      }
  }
  // we have reached a leaf and need to make our last decision
  // note: if tree is just root, will come straight here
  decision = get_decision(curr_node->data, p, (depth % K));
  dir = decision;
  return curr_node;
}

bool KDTree::insert_node(Point *p) {
  int dir;
  // finds the node or the closest one
  Node *leaf = find_node_helper(p, this->root, dir);
  if (dir == EXISTS) {
    return true;
  }
  else {
    Node *new_leaf = new Node(p);
    if (dir == LEFT) leaf->left = new_leaf;
    else if (dir == RIGHT) leaf->right = new_leaf;
    else return false;
    return true;
  }
}

Node *KDTree::find_node(Point *p) {
  int dir;
  Node *leaf = find_node_helper(p, this->root, dir);
  if (dir == EXISTS) {
    return leaf;
  }
  else {
    return NULL;
  }
}

void update_dist(pair<Node*, double> &best_so_far, pair<Node*, double> &other) {
  if (other.second < best_so_far.second) {
    best_so_far.first = other.first;
    best_so_far.second = other.second;
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
void nearest_neighbor_helper(Node *curr_node,  pair<Node*, double> &best_so_far,
                                  Point* test, int depth) {
  if (curr_node == NULL) { return; }

  double curr_dist = test->dist(*(curr_node->data));
  pair<Node*, double> compare_point = {curr_node, curr_dist};
  update_dist(best_so_far, compare_point);


  int curr_dim = depth % K;
  int dir;
  if (test->at(curr_dim) < curr_node->data->at(curr_dim)) {
    dir = LEFT;
    nearest_neighbor_helper(curr_node->left, best_so_far, test, depth+1);
  }
  else {
    dir = RIGHT;
    nearest_neighbor_helper(curr_node->right, best_so_far, test, depth+1);
  }

  /* have to check opposite side of split if the hypersphere centered at test
  with radius best_dist crosses the splitting boundary */
  double boundary_dist = (test->at(curr_dim) - curr_node->data->at(curr_dim));
  if (fabs(boundary_dist) < best_so_far.second) {
    if (dir == LEFT)  {
      nearest_neighbor_helper(curr_node->right, best_so_far, test, depth+1);
    }
    else {
      nearest_neighbor_helper(curr_node->left, best_so_far, test, depth+1);
    }
  }
}

Point *KDTree::nearest_neighbor(Point *p) {
  pair<Node*, double> best_so_far = {NULL, DBL_MAX}; // TODO: fix to DBL_MAX
  nearest_neighbor_helper(this->root, best_so_far, p, 0);
  return best_so_far.first->data;
}

void points_in_radius_helper(Node *curr_node, unordered_set<Point*> &within,
                             Point* test, double radius, int depth) {

  if (curr_node == NULL) { return; }
  if (curr_node->data == test) { return; } /* Don't add the test point */

  // Check current node
  double curr_dist = test->dist(*(curr_node->data));
  if(curr_dist < radius) {
    within.insert(curr_node->data);
  }

  // Check left or right node depending on curr_dim
  int curr_dim = depth % K;
  int dir; // to check if we need to look across the split
  if (test->at(curr_dim) < curr_node->data->at(curr_dim)) {
    dir = LEFT;
    points_in_radius_helper(curr_node->left, within, test, radius, depth+1);
  }
  else {
    dir = RIGHT;
    points_in_radius_helper(curr_node->right, within, test, radius, depth+1);
  }

  /* have to check opposite side of split if the hypersphere centered at test
  with radius best_dist crosses the splitting boundary */
  double boundary_dist = (test->at(curr_dim) - curr_node->data->at(curr_dim));
  if (fabs(boundary_dist) < radius) {
    if (dir == LEFT)  {
      points_in_radius_helper(curr_node->right, within, test, radius, depth+1);
    }
    else {
      points_in_radius_helper(curr_node->left, within, test, radius, depth+1);
    }
  }
}

unordered_set<Point*> KDTree::points_in_radius(Point *p, double radius) {
  unordered_set<Point*> within;
  points_in_radius_helper(this->root, within, p, radius, 0);
  return within;
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
