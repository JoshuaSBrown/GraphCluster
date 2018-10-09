
#include <iostream>
#include <vector>
#include <list>
#include <cassert>

#include "EdgesClass.hpp"

using namespace std;

int main(){

  cout << "Beginning Test" << endl;
  cout << "Testing Constructor Edges" << endl;
  {
    Edge ed(2,3);
    Edges eds(ed);
  }

  cout << "Testing push_back" << endl;
  {
    Edge ed(2,3);
    Edge ed2(2,4);
    Edges eds(ed);
    eds.push_back(ed2);
  }

  cout << "Testing operator << " << endl;
  {
    Edge ed(2,3);
    Edge ed2(2,4);
    Edges eds(ed);
    eds.push_back(ed2);
    cout << eds << endl;
  }
 
  cout << "Testing removeRedundant" << endl;
  {
    Edge ed(2,3);
    Edge ed2(2,4);
    Edges eds(ed);
    eds.push_back(ed2);
    eds.removeRedundant();
    cout << eds << endl;

    eds.push_back(ed2);
    eds.push_back(ed);
    eds.removeRedundant();
    cout << eds << endl;
  }

  cout << "Testing: getVertices" << endl;
  {
    Edge ed(2,3);
    Edge ed2(2,4);
    Edges eds(ed);
    eds.push_back(ed2);
    list<int> ver = eds.getVertices();
    for(auto it=ver.begin();it!=ver.end();++it){
      cout << *it << endl;
    } 
  }
 
  cout << "Testing: getClusters" << endl;
  {
    Edge ed(2,3);
    Edge ed2(2,4);
    Edges eds(ed);
    eds.push_back(ed2);
    
    Edge ed3(5,1);
    eds.push_back(ed3);
    Edge ed4(7,5);
    eds.push_back(ed4);
    Edge ed5(1,9);
    eds.push_back(ed5);
    Edge ed6(4,8);
    eds.push_back(ed6);

    auto clusters = eds.getClusters();
  
    cout << "size " << clusters.size() << endl;  
    assert(clusters.size()==2);
    assert(clusters.at(0).size()==4);  
    assert(clusters.at(1).size()==4);  
  }

  cout << "Testing: getSegments" << endl;
  {

// Shape should look like this 
//
//  0 - 1 - 2 - 3 - 4
//          |
//          5
//          |
//          6
//
// This should lead to a total of 3 segments
//
// 0 - 1 - 2
//
// 2 - 3 - 4
//
// 2 - 5 - 6
//
    {
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(2,5);
      Edge ed6(5,6);

      Edges eds(ed1);
      eds.push_back(ed2);
      eds.push_back(ed3);
      eds.push_back(ed4);
      eds.push_back(ed5);
      eds.push_back(ed6);

      auto segs = eds.getSegments();
      
      cout << "Printing Segments" << endl;
      for(auto seg=segs.begin();seg!=segs.end();seg++){
        cout << *seg << endl;
      }
    }

// Shape sould look like this 
//
// 0 - 1 - 2 - 3 - 4
//         |       |
//         5       6
//         |       |
//         7 - 8 - 9
//
// This should lead to a total of 2 segments
//
// 0 - 1 - 2
//
// 2 - 3 - 4
// |       |
// 5       6
// |       |
// 7 - 8 - 9
//

    {
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(2,5);
      Edge ed6(4,6);
      Edge ed7(5,7);
      Edge ed8(6,9);
      Edge ed9(7,8);
      Edge ed10(8,9);
    
      Edges eds(ed1);
      eds.push_back(ed2); 
      eds.push_back(ed3); 
      eds.push_back(ed4); 
      eds.push_back(ed5); 
      eds.push_back(ed6); 
      eds.push_back(ed7); 
      eds.push_back(ed8); 
      eds.push_back(ed9); 
      eds.push_back(ed10);

      auto segs = eds.getSegments();
      
      cout << "Printing Segments" << endl;
      for(auto seg=segs.begin();seg!=segs.end();seg++){
        cout << *seg << endl;
      }
    }

// Shape should look like this
//
// 5           6
// |           |
// 0 - 1 - 2 - 3 - 4
// |           |
// 7           8
//
// This should lead to a total of 6 segments
// 
// 0 - 5
// 
// 0 - 7
//
// 0 - 1 - 2 - 3
//
// 3 - 6
//
// 3 - 8
//
// 3 - 4
//

  {
    Edge ed1(0,5);
    Edge ed2(0,7);
    Edge ed3(0,1);
    Edge ed4(1,2);
    Edge ed5(2,3);
    Edge ed6(3,4);
    Edge ed7(6,3);
    Edge ed8(3,8);

    Edges eds(ed1);
    eds.push_back(ed2);
    eds.push_back(ed3);
    eds.push_back(ed4);
    eds.push_back(ed5);
    eds.push_back(ed6);
    eds.push_back(ed7);
    eds.push_back(ed8);
   
    auto segs = eds.getSegments();
     
    cout << "Printing Segments" << endl;
    for(auto seg=segs.begin();seg!=segs.end();seg++){
      cout << *seg << endl;
    }

  }  


  }

  return 0;
}
