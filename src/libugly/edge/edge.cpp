
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

#include "EdgeClass.hpp"

using namespace std;

namespace ugly {

  int Edge::getOtherVertex(int vertex) const{
    if(vertex==vertex1_) {
      return vertex2_;
    }else if(vertex==vertex2_){
      return vertex1_;
    }
    throw runtime_error("Unable to determine the other vertex as the provided "
        "vertex is not stored in the edge.");
  }

  bool Edge::containsVertex(int vertex) const {
    return (vertex1_==vertex || vertex2_==vertex);
  }

  bool Edge::operator==(const Edge edge) const{
    if(vertex1_==edge.vertex1_ && vertex2_==edge.vertex2_) return true; 
    if(vertex2_==edge.vertex1_ && vertex2_==edge.vertex2_) return true; 
    return false;
  }

  bool Edge::operator!=(const Edge edge) const{
    return !(*this==edge);
  }

  bool Edge::operator<(const Edge edge) const{
    if(vertex1_<edge.vertex1_) return true;
    if(vertex1_>edge.vertex1_) return false;
    if(vertex2_<edge.vertex2_) return true;
    return false;
  }

  bool Edge::operator<=(const Edge edge) const{
    return (*this<edge || *this==edge);
  }

  bool Edge::operator>(const Edge edge) const{
    return !(*this<=edge);
  }


  bool Edge::operator>=(const Edge edge) const{
    return !(*this<edge);   
  }

  ostream& operator<<(ostream& os, const Edge edge){
    os << "Vertices" << endl;
    os << edge.vertex1_ << " " << edge.vertex2_ << endl; 
    return os;
  }

}
