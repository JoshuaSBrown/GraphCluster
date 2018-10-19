
#include <memory>
#include "graphvisitor_depth_first.hpp"
#include "../../../include/ugly/edge_weighted.hpp"

using namespace std;

namespace ugly {

  GraphVisitorDepthFirst::GraphVisitorDepthFirst(){
    allowed_edge_types_.clear();
    allowed_edge_types_.push_back(constants::EdgeType::weighted);
  }

  void GraphVisitorDepthFirst::addEdges(vector<reference_wrapper<Edge>> edges){
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

  void GraphVisitorDepthFirst::addEdge_(Edge& ){
    return;
  }

  void GraphVisitorDepthFirst::exploreEdge_(Edge& edge){
    auto distance = getDistanceFromStartingVertexToEdge_(edge);
    explored_vertices_[getUnexploredVertex(edge)]=distance;
  }

  Edge& GraphVisitorDepthFirst::getEdgeShortestDistance_(){
    double distance;
    bool edge_uninitialized = true;
    auto edge_shortest_distance_away = edges_to_explore_.begin();

    for(auto edge_it=edges_to_explore_.begin();
        edge_it!=edges_to_explore_.end();
        ++edge_it ){

        auto edge_distance = getDistanceFromStartingVertexToEdge_(*edge_it);
        if(edge_uninitialized){
          distance = edge_distance;
          edge_shortest_distance_away = edge_it;
          edge_uninitialized=false;
        }else if(edge_distance<distance){
          distance = edge_distance;
          edge_shortest_distance_away = edge_it;
        }
    }
    if(edge_uninitialized){
      throw runtime_error("Cannot grab edge shortest distance away because "
          "there are no more edges to be explored");
    }
   
    return *edge_shortest_distance_away;
  }

  Edge& GraphVisitorDepthFirst::getNextEdge_(){
    return GraphVisitorDepthFirst::getEdgeShortestDistance_();
  }

  double 
    GraphVisitorDepthFirst::getDistanceFromStartingVertexToEdge_(
        const Edge& edge){

    auto exploredVertex = getExploredVertex(edge);
    auto edge_distance = explored_vertices_[exploredVertex];

    if(!edgeTypeAllowed_(edge)){
      throw invalid_argument("Edge type is not allowed in the depth first graph"
          " visitor.");
    }
    auto edge_weighted = static_cast<const EdgeWeighted&>(edge); 
    edge_distance += edge_weighted.getWeight();
    return edge_distance;
  }
}

