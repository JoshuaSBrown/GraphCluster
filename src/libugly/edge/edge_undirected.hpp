
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#ifndef GRAPH_EDGEUNDIRECTED_HPP
#define GRAPH_EDGEUNDIRECTED_HPP

namespace ugly {
  // Composed of two integers describing a link
  // between two vertices
  class EdgeUndirected : public Edge {
    public:
      EdgeUndirected(int vertex1, int vertex2);
  };

}
#endif // GRAPH_UNEDGEDIRECTED_HPP
