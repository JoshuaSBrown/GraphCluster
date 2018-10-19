#include "../../../include/ugly/edge_directed.hpp"

namespace ugly {

  const constants::EdgeType EdgeDirected::class_type_ = constants::EdgeType::directed;

  constants::EdgeType EdgeDirected::getClassType() { return class_type_; }
}
