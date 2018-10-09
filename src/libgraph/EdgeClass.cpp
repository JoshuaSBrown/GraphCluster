
#include <iostream>
#include <vector>
#include <list>

#include "EdgeClass.hpp"

using namespace std;

Edge::Edge(int ID1,int ID2){
    vert1 = ID1;
    vert2 = ID2;
    if(ID2<ID1) {
        vert1 = ID2;
        vert2 = ID1;
    }
} 

int Edge::getOtherV(int ver) const{
    if(ver==vert1) {
        return vert2;
    }else{
        return vert1;
    }
}

bool Edge::contains(int ID) const {
    return (vert1==ID || vert2==ID);
}

bool Edge::operator==(const Edge ed) const{
    if(this->vert1==ed.vert1 && this->vert2==ed.vert2) return true; 
    if(this->vert2==ed.vert1 && this->vert1==ed.vert2) return true; 
    return false;
}

bool Edge::operator!=(const Edge ed) const{
    return !(*this==ed);
}

bool Edge::operator<(const Edge ed) const{
    if(this->vert1<ed.vert1) return true;
    if(this->vert1>ed.vert1) return false;
    if(this->vert2<ed.vert2) return true;
    return false;
}

bool Edge::operator<=(const Edge ed) const{
    return (*this<ed || *this==ed);
}

bool Edge::operator>(const Edge ed) const{
    return !(*this<=ed);
}


bool Edge::operator>=(const Edge ed) const{
    return !(*this<ed);   
}

ostream& operator<<(ostream& os, const Edge ed){
    os << "Vertices" << endl;
    os << ed.vert1 << " " << ed.vert2 << endl; 
    return os;
}

