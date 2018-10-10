
#include <memory>
#include "graphvisitor_depth_first.hpp"
#include "../edge/edge_weighted.hpp"

using namespace std;

namespace ugly {


  void GraphVisitorDepthFirst::exploreEdge(shared_ptr<Edge> edge){
    if(explored_edges_.count(edge)){
      throw invalid_argument("Cannot explore edge that has already been "
          "explored.");
    } 
    if(!verticesHaveBeenExplored(edge)){
      // If the vertices have not been explored get the one that has not been
      // explored and add it to the explored vertices
      explored_vertices_[getExploredVertex(edge)]=0.0;
    }
    // Explore the edge 
    explored_edges_.insert(edge);
  }

  void GraphVisitorDepthFirst::addEdge(shared_ptr<Edge> edge){
    if(explored_edges_.count(edge)){
      throw invalid_argument("Cannot add edge it has already been explored");
    }
    edges_to_explore_.push_back(edge);
  }

  void GraphVisitorDepthFirst::addEdges(vector<shared_ptr<Edge>> edges){
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

  shared_ptr<Edge> GraphVisitorDepthFirst::getEdgeShortestDistance_(){
    double distance;
    bool edge_uninitialized = true;
    shared_ptr<EdgeWeighted> edge_shortest_distance_away;
    auto edges_to_explore_ = getEdgesToExplore_<EdgeWeighted>();
    for(auto edge : edges_to_explore_ ){
      if(!verticesHaveBeenExplored(edge)){
        auto edge_distance = getDistanceFromStartingVertexToEdge_(edge);
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
    if(edge_uninitialized){
      throw runtime_error("Cannot grab edge shortest distance away because "
          "there are no more edges to be explored");
    }
    return dynamic_pointer_cast<Edge>(edge_shortest_distance_away);
  }

  shared_ptr<Edge> GraphVisitorDepthFirst::getNextEdge(){
    return GraphVisitorDepthFirst::getEdgeShortestDistance_();
  }

  double GraphVisitorDepthFirst::getDistanceFromStartingVertexToEdge_(
     shared_ptr<EdgeWeighted> edge){

    auto exploredVertex = getExploredVertex(edge);
    auto edge_distance = explored_vertices_[exploredVertex];
    edge_distance += edge->getWeight();
    return edge_distance;
  }

}

