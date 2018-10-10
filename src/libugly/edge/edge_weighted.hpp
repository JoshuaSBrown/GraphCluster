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
      int vertex1_;
      int vertex2_;
      double weight_;
    public:
      EdgeWeighted() :
        vertex1_(constants::unassigned),
        vertex2_(constants::unassigned),
        weight_(1.0){};

      EdgeWeighted(int vertex1, int vertex2) : 
        vertex1_(vertex1), 
        vertex2_(vertex2), 
        weight_(1.0){};

      EdgeWeighted(int vertex1, int vertex2,double weight) : 
        vertex1_(vertex1), 
        vertex2_(vertex2),
        weight_(weight){};

      EdgeWeighted::setWeight(double weight){ weight_ = weight; }
      EdgeWeighted::getWeight() const { return weight_; }

  };

}

#endif // UGLY_EDGEWEIGHTED_HPP
