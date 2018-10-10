

#include "graphvisitor_depth_first.hpp"

namespace ugly {

  EdgeWeighted GraphVisitorDepthFirst::getNextEdge(){
    return edges_to_explore_.front();
  }

  void GraphVisitorDepthFirst::exploreEdge(Edge edge){
    if(explored_edges_.count(edge)){
      throw invalid_argument("Cannot explore edge that has already been "
          "explored.");
    } 
    if(!verticesHaveBeenExplored){
      // If the vertices have not been explored get the one that has not been
      // explored and add it to the explored vertices
      explored_vertices_.insert(getUnexploredVertex(edge));
    }
    // Explore the edge 
    explored_edges_.insert(edge);
  }

  void GraphVisitorDepthFirst::addEdge(EdgeWeighted edge){
    if(explored_edges_.count(edge)){
      throw invalid_argument("Cannot add edge it has already been explored");
    }
    edges_to_explore_.push_back(edge);
  }

  void GraphVisitorDepthFirst::addEdges(vector<EdgeWeighted> edges){
    for( auto edge : edges){
      addEdge(edge);
    }
  }

  double GraphVisitorDepthFirst::getDistanceOfVertex(int vertex){
    if(explored_vertices_.count(vertex)){
      return explored_vertices_[vertex];
    }
    throw invalid_argument("Cannot get distance to vertex as the vertex has not"
        " yet been explored.");
  }

  /****************************************************************************
   * Private Internal Methods
   ****************************************************************************/

  EdgeWeighted GraphVisitorDepthFirst::getEdgeShortestDistance_(){
    double distance;
    bool edge_uninitialized = true;
    Edge edge_shortest_distance_away;

    for(auto edge : edges_to_explore_ ){
      if(!verticesHaveBeenExplored(edge)){
        edge_distance = getDistanceFromStartingVertexToEdge_(edge);
        if(edge_uninitialized){
          distance = edge_distance;
          edge_shortest_distance_away = edge;
          edge_uninitialized=true;
        }else if(edge_distance<distance){
          distance = edge_distance;
          edge_shortest_distance_away = edge;
        }
      }
    }
    if(first){
      throw runtime_error("Cannot grab edge shortest distance away because "
          "there are no more edges to be explored");
    }
    return edge_shortest_distance_away;
  }

  double GraphVisitorDepthFirst::getDistanceFromStartingVertexToEdge_(
      EdgeWeighted edge){

    auto exploredVertex = edge.getExploredVertex(edge);
    auto edge_distance = explored_vertices_[exploredVertex];
    edge_distance += edge.getWeight();
    return edge_distance;
  }

}

