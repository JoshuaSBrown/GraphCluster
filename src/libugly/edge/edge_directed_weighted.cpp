
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

#include "../../../include/ugly/edge_directed_weighted.hpp"

using namespace std;

namespace ugly {

const constants::EdgeType EdgeDirectedWeighted::class_type_ =
    constants::EdgeType::directed_weighted;

constants::EdgeType EdgeDirectedWeighted::getClassType() {
  return EdgeDirectedWeighted::class_type_;
}

EdgeDirectedWeighted& EdgeDirectedWeighted::operator=(
    const EdgeDirectedWeighted& edgedirectedweighted) {
  vertex1_ = edgedirectedweighted.vertex1_;
  vertex2_ = edgedirectedweighted.vertex2_;
  weight_  = edgedirectedweighted.weight_;

  object_type_   = edgedirectedweighted.object_type_;
  edge_directed_ = edgedirectedweighted.edge_directed_;
  return *this;
}
}
