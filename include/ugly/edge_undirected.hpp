
#ifndef UGLY_EDGEUNDIRECTED_HPP
#define UGLY_EDGEUNDIRECTED_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <utility>

#include "../../src/libugly/edge/edge.hpp"

namespace ugly {
  // Composed of two integers describing a link
  // between two vertices
  class EdgeUndirected : public Edge {
    public:
      EdgeUndirected() {};
      EdgeUndirected(int vertex1, int vertex2);
      EdgeUndirected(const EdgeUndirected &edgeundirected);

      EdgeUndirected& operator=(const EdgeUndirected &edgeundirected);
      static std::string getClassType();
    private:
      static const std::string class_type_;
  };

}

namespace std{
  template<>
    class hash<ugly::EdgeUndirected>{
      public:
        size_t operator()(const ugly::EdgeUndirected &edgeundirected) const
        {
          return hash<int>()(edgeundirected.getVertex1())^hash<int>()(edgeundirected.getVertex2());
        }
    };
}

#endif // UGLY_UNEDGEDIRECTED_HPP
