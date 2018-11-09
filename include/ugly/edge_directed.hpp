
#ifndef GRAPH_EDGEDIRECTED_HPP
#define GRAPH_EDGEDIRECTED_HPP

#include <cassert>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#include "../../src/libugly/edge/edge.hpp"

namespace ugly {
// Composed of two integers describing a link
// between two vertices
class EdgeDirected : public Edge {
 public:
  EdgeDirected() : Edge() { object_type_ = constants::EdgeType::directed; }

  EdgeDirected(int vertex1, int vertex2) : Edge(vertex1, vertex2) {
    object_type_ = constants::EdgeType::directed;
  }

  EdgeDirected(const Edge& edge) {
    if (edge.getEdgeType() == getClassType()) {
      object_type_ = constants::EdgeType::directed;

      vertex1_ = edge.getVertex1();
      vertex2_ = edge.getVertex2();
    } else {
      throw std::invalid_argument("Cannot initialize directed edge");
    }
  }

  EdgeDirected& operator=(const EdgeDirected& edge);

  static constants::EdgeType getClassType();

 private:
  static const constants::EdgeType class_type_;
};
}
#endif  // GRAPH_EDGEDIRECTED_HPP
