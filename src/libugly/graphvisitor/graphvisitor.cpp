
#include <stdexcept>
#include "../edge/edge.hpp"
#include "graphvisitor.hpp"

using namespace std;

namespace ugly {

  void GraphVisitor::setStartingVertex(int vertex){
    starting_vertex_ = vertex;
    explored_vertices_[vertex] = 0.0;
  }

  bool GraphVisitor::exploredVertex(int vertex){
    return explored_vertices_.count(vertex);
  }

  void GraphVisitor::exploreEdge(shared_ptr<Edge>){
    throw runtime_error("Cannot call exploreEdge from base class must define it"
        " in the derived class.");
  }

  void GraphVisitor::addEdge(shared_ptr<Edge>){
    throw runtime_error("Cannot call addEdge from base class must define it in "
        "the derived class.");
  }

  void GraphVisitor::addEdges(vector<shared_ptr<Edge>>){
    throw runtime_error("Cannot call addEdges from base class must define it in"
        " the derived class.");
  }

  bool GraphVisitor::verticesHaveBeenExplored(shared_ptr<Edge> edge) const {
    if(explored_vertices_.count(edge->getVertex1()) && 
       explored_vertices_.count(edge->getVertex2())){ 
      return true;
    }
    return false;
  }

  int GraphVisitor::getUnexploredVertex(shared_ptr<Edge> edge) const {
    if(verticesHaveBeenExplored(edge)){
      throw invalid_argument("Cannot find unexplored vertex as both vertices "
        "have been explored.");
    }
    if(explored_vertices_.count(edge->getVertex1())){
      return edge->getVertex2();
    }
    if(explored_vertices_.count(edge->getVertex2())){
      return edge->getVertex1();
    }
    throw invalid_argument("Both vertices have not been explored so you cannot "
        "return a single vertex.");
  }

  int GraphVisitor::getExploredVertex(shared_ptr<Edge> edge) const {
    return edge->getOtherVertex(getUnexploredVertex(edge));
  }

  shared_ptr<Edge> GraphVisitor::getNextEdge_(){
    throw runtime_error("Cannot call getNextEdge from base class must "
        "define in the derived class.");
  }

}
