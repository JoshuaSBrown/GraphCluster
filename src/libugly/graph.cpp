#include "../../include/ugly/graph.hpp"

namespace ugly {
  Graph::Graph(list<Edge> connections, vector<GraphNode<Ts...>> nodes){
    nodes_ = nodes;
    for( auto edge : connections ){
      neighboring_vertices_[edge.getVertex1()].insert(edge.getVertex2());
    }
  }

  vector<Edge> Graph::getEdgesConnectedToVertex(int vertex){
    vector<Edge> neighbor_edges;
    for( auto neighboring_vertex : neighboring_vertices_[vertex]){
      Edge edge(vertex,neighboring_vertex);  
      neighbor_edges.push_back(edge);
    }
    return neighbor_edges;
  }

}
