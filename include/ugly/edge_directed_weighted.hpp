#ifndef UGLY_EDGEDIRECTEDWEIGHTED_HPP
#define UGLY_EDGEDIRECTEDWEIGHTED_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#include "../../src/libugly/edge/edge.hpp"

namespace ugly {
// Composed of two integers describing a link
// between two vertices
  class EdgeDirectedWeighted : public Edge {
    private:
      static const constants::EdgeType class_type_;
      double weight_;
    public:
      EdgeDirectedWeighted() : weight_(1.0) {
        object_type_ = constants::EdgeType::directed_weighted;
        edge_directed_ = true;
      }

      EdgeDirectedWeighted(int vertex1, int vertex2) : 
        Edge(vertex1,vertex2), 
        weight_(1.0) {
          object_type_ = constants::EdgeType::directed_weighted;
          edge_directed_=true;
        }

      EdgeDirectedWeighted(int vertex1, int vertex2,double weight) : 
        Edge(vertex1,vertex2),
        weight_(weight){
          object_type_ = constants::EdgeType::directed_weighted;
          edge_directed_ = true;
        }

      EdgeDirectedWeighted(const EdgeDirectedWeighted &edgeweighted) : Edge(edgeweighted) {
        weight_ = edgeweighted.weight_ ;
      }

      EdgeDirectedWeighted& operator=(const EdgeDirectedWeighted &EdgeDirectedWeighted);

      void setWeight(double weight){ weight_ = weight; }
      double getWeight() const { return weight_; }

      static constants::EdgeType getClassType();

  };

}

#endif // UGLY_EDGEDIRECTEDWEIGHTED_HPP
