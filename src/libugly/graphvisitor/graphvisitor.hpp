
#ifndef UGLY_GRAPHVISITOR_HPP
#define UGLY_GRAPHVISITOR_HPP

#include <vector>
#include <list>
#include <set>
#include <map>

namespace ugly {

  class Edge;

  class GraphVisitor{
    public:
      GraphVisitor() {};
      void setStartingVertex(int vertex);
      bool exploredVertex(int vertex);
      virtual Edge getNextEdge() const;
      virtual void exploreEdge(Edge edge);
      virtual void addEdge(Edge edge);
      virtual void addEdges(std::vector<Edge> edges);
      bool verticesHaveBeenExplored(Edge edge) const;
      int getUnexploredVertex(Edge edge) const;
      int getExploredVertex(Edge edge) const;
      bool allEdgesExplored() const { return edges_to_explore_.size()==0 ;}
    protected:
      // First int is the vertex, the double is the distance
      std::map<int,double> explored_vertices_;
      std::set<Edge> explored_edges_;
      std::list<Edge> edges_to_explore_;
      int starting_vertex_;
  };

}

#endif // UGLY_GRAPHVISITOR_HPP
