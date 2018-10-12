
#ifndef GRAPH_EDGEDIRECTED_HPP
#define GRAPH_EDGEDIRECTED_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

namespace ugly {
  // Composed of two integers describing a link
  // between two vertices
  class EdgeDirected : public Edge {
    public:
      EdgeDirected() {};
  };
}
#endif // GRAPH_EDGEDIRECTED_HPP
