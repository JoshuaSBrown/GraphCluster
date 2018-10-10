#ifndef UGLY_EDGEWEIGHTED_HPP
#define UGLY_EDGEWEIGHTED_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#include "edge.hpp"

namespace ugly {
// Composed of two integers describing a link
// between two vertices
  class EdgeWeighted : public Edge {
    private:
      static const std::string class_type;
      double weight_;
    public:
      EdgeWeighted() : weight_(1.0){
        object_type_ = "edgeweighted";
      };

      EdgeWeighted(int vertex1, int vertex2) : 
        Edge(vertex1,vertex2), 
        weight_(1.0){};

      EdgeWeighted(int vertex1, int vertex2,double weight) : 
        Edge(vertex1,vertex2),
        weight_(weight){};

      void setWeight(double weight){ weight_ = weight; }
      double getWeight() const { return weight_; }

  };

}

#endif // UGLY_EDGEWEIGHTED_HPP
