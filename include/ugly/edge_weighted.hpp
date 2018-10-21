#ifndef UGLY_EDGEWEIGHTED_HPP
#define UGLY_EDGEWEIGHTED_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#include "../../src/libugly/edge/edge.hpp"

namespace ugly {
// Composed of two integers describing a link
// between two vertices
  class EdgeWeighted : public Edge {
    private:
      static const constants::EdgeType class_type_;
      double weight_;
    public:
      EdgeWeighted() : weight_(1.0) {
        object_type_ = constants::EdgeType::weighted;
        edge_directed_ = false;
      }

      EdgeWeighted(int vertex1, int vertex2) : 
        Edge(vertex1,vertex2), 
        weight_(1.0) {
          object_type_ = constants::EdgeType::weighted;
          edge_directed_=false;
          if(vertex1<vertex2){
            vertex1_ = vertex1; 
            vertex2_ = vertex2; 
          }else{
            vertex1_ = vertex2; 
            vertex2_ = vertex1; 
          }
        }

      EdgeWeighted(int vertex1, int vertex2,double weight) : 
        weight_(weight){
          object_type_ = constants::EdgeType::weighted;
          edge_directed_ = false;
          if(vertex1<vertex2){
            vertex1_ = vertex1; 
            vertex2_ = vertex2; 
          }else{
            vertex1_ = vertex2; 
            vertex2_ = vertex1; 
          }
        }

      EdgeWeighted(const EdgeWeighted &edgeweighted) : Edge(edgeweighted) {
        weight_ = edgeweighted.weight_ ;
      }

      EdgeWeighted& operator=(const EdgeWeighted &EdgeWeighted);

      void setWeight(double weight){ weight_ = weight; }
      double getWeight() const { return weight_; }

      static constants::EdgeType getClassType();

  };

}

#endif // UGLY_EDGEWEIGHTED_HPP
