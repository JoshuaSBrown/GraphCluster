#include "../../../include/ugly/edge_undirected.hpp"

namespace ugly {

  const std::string EdgeUndirected::class_type_ = "edgeundirected";

  EdgeUndirected::EdgeUndirected(int vertex1, int vertex2) : Edge() {
    object_type_ = "edgeundirected";
    if(vertex1<vertex2){
      vertex1_ = vertex1;
      vertex2_ = vertex2;
    }else{
      vertex1_ = vertex2;
      vertex2_ = vertex1;
    }
  }

  EdgeUndirected::EdgeUndirected(const EdgeUndirected &edgeundirected) : Edge() {
    object_type_ = "edgeundirected";
    vertex1_ = edgeundirected.vertex1_;
    vertex2_ = edgeundirected.vertex2_;
  }

  EdgeUndirected& EdgeUndirected::operator=(const EdgeUndirected &edgeundirected){
    object_type_ = edgeundirected.object_type_;
    vertex1_ = edgeundirected.vertex1_;
    vertex2_ = edgeundirected.vertex2_;
    return *this;
  }

  std::string EdgeUndirected::getClassType() { return class_type_; }
}
