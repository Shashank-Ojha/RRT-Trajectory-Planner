/**
 *  @file Search-impl.cpp
 *  @brief Defines concrete types that the Search class can be used with.
 *  This is necessary for templates. For more information see:
 *    https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __SEARCH_IMPL_CPP
#define __SEARCH_IMPL_CPP

#include "utils/Point.h"
#include "Search.cpp"

template class Search<Point>;

#endif /* __SEARCH_IMPL_CPP */
