#ifndef UGLY_EDGEWEIGHTED_HPP
#define UGLY_EDGEWEIGHTED_HPP

#include <cassert>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#include "edge_directed_weighted.hpp"

namespace ugly {
// Composed of two integers describing a link
// between two vertices
class EdgeWeighted : public EdgeDirectedWeighted {
 private:
  static const constants::EdgeType class_type_;

 public:
  EdgeWeighted() {
    object_type_   = constants::EdgeType::weighted;
    edge_directed_ = false;
  }

  EdgeWeighted(int vertex1, int vertex2) {
    object_type_   = constants::EdgeType::weighted;
    edge_directed_ = false;
    weight_        = 1.0;
    if (vertex1 < vertex2) {
      vertex1_ = vertex1;
      vertex2_ = vertex2;
    } else {
      vertex1_ = vertex2;
      vertex2_ = vertex1;
    }
  }

  EdgeWeighted(int vertex1, int vertex2, double weight) {
    object_type_   = constants::EdgeType::weighted;
    edge_directed_ = false;
    weight_        = weight;
    if (vertex1 < vertex2) {
      vertex1_ = vertex1;
      vertex2_ = vertex2;
    } else {
      vertex1_ = vertex2;
      vertex2_ = vertex1;
    }
  }

  EdgeWeighted(const EdgeWeighted &edgeweighted)
      : EdgeDirectedWeighted(edgeweighted){};

  EdgeWeighted(cdonst Edge &edge) {
    if (edge.getEdgeType() == getClassType()) {
      const EdgeWeighted *edw = static_cast<const EdgeWeighted *>(&edge);
      object_type_            = constants::EdgeType::weighted;
      vertex1_                = edw->getVertex1();
      vertex2_                = edw->getVertex2();
      weight_                 = edw->getWeight();
      edge_directed_          = false;
    } else {
      throw std::invalid_argument("Cannot initialize edgeweighted");
    }
  }

  EdgeWeighted &operator=(const EdgeWeighted &EdgeWeighted);

  static constants::EdgeType getClassType();
};
}

#endif  // UGLY_EDGEWEIGHTED_HPP
