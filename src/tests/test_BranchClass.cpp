
#include <list>

#include "BranchClass.hpp"
#include "../CPP_EdgeClass/EdgeClass.hpp"

using namespace std;

int main(void){

  cout << "Testing: constructor" << endl;
  {
    list<Edge> list_ed;
    Edge ed(1,2);
    list_ed.push_back(ed);
    branches br(list_ed);
  }
  cout << "Testing: getMap" << endl;
  {
  // We will consider the following structure for our test case
  // 
  //          3
  //          |
  //      1 - 2 - 4 - 5
  //      |           |
  //      0 - 9 - 8 - 6 - 7  
  //
  
  // Creating the edges we have
    list<Edge> list_ed;
    Edge ed0(0,1);
    Edge ed1(1,2);
    Edge ed2(2,3);
    Edge ed3(2,4);
    Edge ed4(4,5);
    Edge ed5(5,6);
    Edge ed6(6,7);
    Edge ed7(6,8);
    Edge ed8(8,9);
    Edge ed9(9,0);
    
    list_ed.push_back(ed0);
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
    list_ed.push_back(ed7);
    list_ed.push_back(ed8);
    list_ed.push_back(ed9);
    
    branches br(list_ed);

    // Now we are going to explore starting from vertex 2
    br.exploreFromVertex(2);
    
    // Now we are going to get a map of the exploration
    vector<vector<int>> map = br.getMap();
 
    assert(map.at(0).size()==5); 
    // First element in the row is the vertex number 
    assert(map.at(0).at(0)==2);  
    // Second element is the distance from the starting vertex
    assert(map.at(0).at(1)==0);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(0).at(2)==0);  
    assert(map.at(0).at(3)==2);  
    assert(map.at(0).at(4)==1); 

    assert(map.at(1).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(1).at(0)==1);  
    // Second element is the distance from the starting vertex
    assert(map.at(1).at(1)==1);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(1).at(2)==0);  

    assert(map.at(2).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(2).at(0)==0);  
    // Second element is the distance from the starting vertex
    assert(map.at(2).at(1)==2);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(2).at(2)==0); 
 
    assert(map.at(3).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(3).at(0)==9);  
    // Second element is the distance from the starting vertex
    assert(map.at(3).at(1)==3);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(3).at(2)==0);  

    assert(map.at(4).size()==4);
    // First element in the row is the vertex number 
    assert(map.at(4).at(0)==8);  
    // Second element is the distance from the starting vertex
    assert(map.at(4).at(1)==4);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(4).at(2)==0);  
    assert(map.at(4).at(3)==2);  
    
    assert(map.at(5).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(5).at(0)==4);  
    // Second element is the distance from the starting vertex
    assert(map.at(5).at(1)==1);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(5).at(2)==2);  
    
    assert(map.at(6).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(6).at(0)==5);  
    // Second element is the distance from the starting vertex
    assert(map.at(6).at(1)==2);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(6).at(2)==2); 
 
    assert(map.at(7).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(7).at(0)==6);  
    // Second element is the distance from the starting vertex
    assert(map.at(7).at(1)==3);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(7).at(2)==2);
  
    assert(map.at(8).size()==3);
    // First element in the row is the vertex number 
    assert(map.at(8).at(0)==7);  
    // Second element is the distance from the starting vertex
    assert(map.at(8).at(1)==4);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(8).at(2)==2);

    assert(map.at(9).size()==3);  
    // First element in the row is the vertex number 
    assert(map.at(9).at(0)==3);  
    // Second element is the distance from the starting vertex
    assert(map.at(9).at(1)==1);  
    // The following numbers are the branches that can lay claim
    // to the vertex. 
    assert(map.at(9).at(2)==1);  

  }
  cout << "Testing: internal functions" << endl;
  {
    list<Edge> list_ed;
    Edge ed(1,2);
    list_ed.push_back(ed);
    branches br(list_ed);
    br.test_branchclass();
  }

  return 0;
}
