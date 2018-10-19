#include "../../../include/ugly/edge_undirected.hpp"

namespace ugly {

  const constants::EdgeType EdgeUndirected::class_type_ = constants::EdgeType::undirected;

  constants::EdgeType EdgeUndirected::getClassType() { return class_type_; }
}
