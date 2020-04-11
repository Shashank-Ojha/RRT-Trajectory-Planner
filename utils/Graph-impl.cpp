/**
 *  @file Graph-impl.cpp
 *  @brief Defines concrete types that the Graph class can be used with.
 *  This is necessary for templates. For more information see:
 *    https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __GRAPH_IMPL_CPP
#define __GRAPH_IMPL_CPP

#include "Point.h"
#include "Graph.cpp"

template class Graph<Point>;

#endif /* __GRAPH_IMPL_CPP */
