#include "../../../include/ugly/edge_undirected.hpp"

namespace ugly {

  EdgeUndirected::EdgeUndirected(int vertex1, int vertex2){
    if(vertex1<vertex2){
      vertex1_ = vertex1;
      vertex2_ = vertex2;
    }else{
      vertex1_ = vertex2;
      vertex2_ = vertex1;
    }
  }
}
