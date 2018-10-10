
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#ifndef UGLY_EDGE_HPP
#define UGLY_EDGE_HPP

namespace ugly {
// Composed of two integers describing a link
// between two vertices
class Edge{
  private:
    int vertex1_;
    int vertex2_;
  public:
    Edge() :
      vertex1_(constants::unassigned),
      vertex2_(constants::unassigned){};

    Edge(int vertex1, int vertex2) : 
      vertex1_(vertex1), 
      vertex2_(vertex2){};

    Edge(int vertex1, int vertex2,double weight) : 
      vertex1_(vertex1), 
      vertex2_(vertex2){};

    int getOtherVertex(int vertex) const;
    int getVertex1(void) const;
    int getVertex2(void) const;

    bool containsVertex(int vertex) const;

    bool operator==(const Edge edge) const;
    bool operator!=(const Edge edge) const;

    // edge 1 is less than edge 2 if the smallest vertex in edge 1 (vert1)
    // is smaller than the vert1 in edge2. If they are the same than edge1
    // is less than edge2 if the second vertex (vert2) is smaller in edge1
    // than in edge2
    bool operator<(const Edge edge) const;
    bool operator>(const Edge edge) const;
    bool operator<=(const Edge edge) const;
    bool operator>=(const Edge edge) const;
    friend std::ostream& operator<<(std::ostream& os, const Edge edge); 
};

}

namespace std{
  template<>
    class hash<ugly::Edge>{
      public:
        size_t operator()(const Edge &edge) const
        {
          return hash<int>()(edge.getVertex1())^hash<int>()(edge.getVertex2());
        }
    };
}

#endif // UGLY_EDGE_HPP
