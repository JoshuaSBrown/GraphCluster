
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#ifndef GRAPH_EDGECLASS_HPP
#define GRAPH_EDGECLASS_HPP

// Composed of two integers describing a link
// between two vertices
class Edge{
  private:
    int vert1;
    int vert2;
  public:
    Edge() {}
    Edge(int ID1, int ID2);
    int getOtherV(int ver) const;
    int getV1(void) const { return vert1;}
    int getV2(void) const { return vert2;}

    bool contains(int ID) const;

    bool operator==(const Edge ed) const;
    bool operator!=(const Edge ed) const;

    // edge 1 is less than edge 2 if the smallest vertex in edge 1 (vert1)
    // is smaller than the vert1 in edge2. If they are the same than edge1
    // is less than edge2 if the second vertex (vert2) is smaller in edge1
    // than in edge2
    bool operator<(const Edge ed) const;
    bool operator>(const Edge ed) const;
    bool operator<=(const Edge ed) const;
    bool operator>=(const Edge ed) const;
    friend std::ostream& operator<<(std::ostream& os, const Edge ed); 
};

namespace std{
    template<>
        class hash<Edge>{
            public:
                size_t operator()(const Edge &ed) const
                {
                    return hash<int>()(ed.getV1())^hash<int>()(ed.getV2());
                }
        };
};

#endif // GRAPH_EDGECLASS_HPP
