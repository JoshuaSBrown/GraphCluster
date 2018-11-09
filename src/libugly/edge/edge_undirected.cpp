#include "../../../include/ugly/edge_undirected.hpp"

namespace ugly {

const constants::EdgeType EdgeUndirected::class_type_ =
    constants::EdgeType::undirected;

constants::EdgeType EdgeUndirected::getClassType() {
  return EdgeUndirected::class_type_;
}

EdgeUndirected::EdgeUndirected(int vertex1, int vertex2) {
  if (vertex1 < vertex2) {
    vertex1_ = vertex1;
    vertex2_ = vertex2;
  } else {
    vertex1_ = vertex2;
    vertex2_ = vertex1;
  }
  edge_directed_ = false;
  object_type_   = constants::EdgeType::undirected;
}

EdgeUndirected& EdgeUndirected::operator=(const EdgeUndirected& edge) {
  vertex1_       = edge.vertex1_;
  vertex2_       = edge.vertex2_;
  edge_directed_ = edge.edge_directed_;
  object_type_   = edge.object_type_;
  return *this;
}
}
