
#ifndef UGLY_EDGEUNDIRECTED_HPP
#define UGLY_EDGEUNDIRECTED_HPP

#include <cassert>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#include "../../src/libugly/edge/edge.hpp"

namespace ugly {
// Composed of two integers describing a link
// between two vertices
class EdgeUndirected : public Edge {
 public:
  EdgeUndirected() : Edge(false) {
    object_type_   = constants::EdgeType::undirected;
    edge_directed_ = false;
  }

  EdgeUndirected(int vertex1, int vertex2);

  EdgeUndirected& operator=(const EdgeUndirected& edge);

  EdgeUndirected(const Edge& edge) : Edge(false) {
    if (edge.getEdgeType() == getClassType()) {
      object_type_   = constants::EdgeType::undirected;
      edge_directed_ = false;

      vertex1_ = edge.getVertex1();
      vertex2_ = edge.getVertex2();
    } else {
      throw std::invalid_argument("Cannot initialize directed edge");
    }
  }

  static constants::EdgeType getClassType();

 private:
  static const constants::EdgeType class_type_;
};
}

namespace std {
template <>
class hash<ugly::EdgeUndirected> {
 public:
  size_t operator()(const ugly::EdgeUndirected& edgeundirected) const {
    return hash<int>()(edgeundirected.getVertex1()) ^
           hash<int>()(edgeundirected.getVertex2());
  }
};
}

#endif  // UGLY_UNEDGEDIRECTED_HPP
