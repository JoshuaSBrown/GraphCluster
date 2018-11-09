#include "../../../include/ugly/edge_directed.hpp"

namespace ugly {

const constants::EdgeType EdgeDirected::class_type_ =
    constants::EdgeType::directed;

constants::EdgeType EdgeDirected::getClassType() {
  return EdgeDirected::class_type_;
}

EdgeDirected& EdgeDirected::operator=(const EdgeDirected& edge) {
  vertex1_ = edge.vertex1_;
  vertex2_ = edge.vertex2_;

  object_type_   = edge.object_type_;
  edge_directed_ = edge.edge_directed_;
  return *this;
}
}
