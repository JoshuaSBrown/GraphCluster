
#include <list>
#include <vector>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "../CPP_Vec_VecTemplate/Vec_VecTemplate.hpp"
#include "../CPP_ListContainerTemplate/ListContainerTemplate.hpp"
#include "../CPP_EdgeClass/EdgeClass.hpp"
#include "BranchClass.hpp"

using namespace std;

/******************************************************************
 * Private Branch Map Functions                                   *
 ******************************************************************/

// Given two vertices find their index in the edge_map object
// if we are unable to find it return a value of -1
int branches::_branch_map::_edge_mapInd(int vert1, int vert2){
  for(unsigned long index=0;index<_edge_map.size();index++){
    if(_edge_map.at(index,0)==vert1 && _edge_map.at(index,1)==vert2){
      return index;
    }
    if(_edge_map.at(index,0)==vert2 && _edge_map.at(index,1)==vert1){
      return index;
    }
  }
  return -1;
}

vector<int> branches::_branch_map::_edge_mapRow(Edge ed){
  vector<int> temp;
  for(unsigned long index=0;index<_edge_map.size();index++){
    if(_edge_map.at(index,0)==ed.getV1() && _edge_map.at(index,1)==ed.getV2()){
      temp = this->_edge_map.at(index);
      return temp;
    }
    if(_edge_map.at(index,0)==ed.getV2() && _edge_map.at(index,1)==ed.getV1()){
      temp = this->_edge_map.at(index);
      return temp;
    }
  }
  return temp;
}
/******************************************************************
 * Public Branch Map Functions                                    *
 ******************************************************************/
branches::_branch_map::_branch_map(list<Edge> edgs){

/* Define the _edge_map object */

  // Step 1 Determine the number of edges 
  int size_edges = edgs.size();
  // Step 2 create an empty row with default values of -1
  vector<int> row(5,-1);
  // Step 3 Initialize _edge_map with rows
  VecVecContainer<int> temp_edge_map(size_edges,row);
  this->_edge_map = temp_edge_map;
  
  int row_index = 0;
  for(auto it=edgs.begin();it!=edgs.end();it++){
    // Assign vertex to first column
    this->_edge_map.at(row_index,0) = it->getV1();
    // Assign neigh vertex to second column
    this->_edge_map.at(row_index,1) = it->getV2();
    // Indicate if edge has been visited = 0
    this->_edge_map.at(row_index,2) = 0;
    // Give the edge an identifying number
    this->_edge_map.at(row_index,3) = row_index;
    row_index++;
  }

/* Define the vert_bonds object */

  // Step 4 Determine the number of unique vertices in the edge list
  //        and store them in the vector
  vector<int> vertices;
  for(auto it=edgs.begin();it!=edgs.end();it++){
    auto it2 = it;
    it2++;
    int vert1 = it->getV1();
    int vert2 = it->getV2();
    bool v1_unique = true;
    bool v2_unique = true;
    while(it2!=edgs.end()){
      if(it2->getV1()==vert1 || it2->getV2()==vert1){
        v1_unique = false;
      }
      if(it2->getV1()==vert2 || it2->getV2()==vert2){
        v2_unique = false;
      }
      if(!v2_unique && !v1_unique) break;
      it2++;
    }
    if(v2_unique) vertices.push_back(vert2);
    if(v1_unique) vertices.push_back(vert1);
  }

  // Step 5 initialize the rows to values of 0 
  vector<int> ver_row(3,0);
  // Step 6 create as many rows as there are vertices
  VecVecContainer<int> temp_vert_bonds(vertices.size(),ver_row);
  this->vert_bonds = temp_vert_bonds;

  // Step 7 Add each vertex on it's own row with the neighboring
  //        vertices associated with it
  row_index = 0;
  for(auto it=vertices.begin();it!=vertices.end();++it){
    // Set the vertex
    this->vert_bonds.at(row_index,0) = *it;
    // Cycle through the bonds and add them to the appropriate row
    int num_bonds_single_vert = 0;
    for(auto bond=edgs.begin();bond!=edgs.end();bond++){
      if(bond->getV1()==*it){
        // Add the neighboring vertex
        this->vert_bonds.push_back(row_index,bond->getV2());
        num_bonds_single_vert++;
      }
      if(bond->getV2()==*it){
        // Add the neighboring vertex
        this->vert_bonds.push_back(row_index,bond->getV1());
        num_bonds_single_vert++;
      }
    }
    // Set the number of bonds or the vertex located at row_index
    this->vert_bonds.at(row_index,1)=num_bonds_single_vert;
    row_index++;
  }
}



// Determine which vertices have 3 or more bonds/edges return
// the ids of the vertices that do in a vector
vector<int> branches::_branch_map::getJunctionVert(){
  vector<int> junction_vert;

  for(unsigned long ind=0;ind<vert_bonds.size();ind++){
    if(this->vert_bonds.at(ind,1)>2){
      junction_vert.push_back(this->vert_bonds.at(ind,0));
    }
  }
  return junction_vert;
}

// Return all the vertices in a single vector. 
vector<int> branches::_branch_map::getVert(){
    vector<int> vertices;
    for(unsigned long ind=0;ind<vert_bonds.size();ind++){
        vertices.push_back(this->vert_bonds.at(ind,0));
    }
    return vertices;
}

// Find the number of bonds associated with vertex id "vertID" if
// the vertex is not found return -1.
int branches::_branch_map::getBonds(int vertID){
  for(unsigned long index=0; index<vert_bonds.size();index++){
    if(this->vert_bonds.at(index,0)==vertID){
      return this->vert_bonds.at(index,1);
    }
  }
  return -1;
}

// Determine which neighbors are associated with the vertex "vertID"
// return them as a vector of ints
vector<int> branches::_branch_map::getNeighs(int vertID){
  vector<int> neighs;
  for(unsigned long index = 0;index<this->vert_bonds.size();index++){
    if(this->vert_bonds.at(index,0)==vertID){
      for(int index2=0;index2<this->vert_bonds.at(index,1);index2++){
        neighs.push_back(this->vert_bonds.at(index,3+index2));
      }
    }
  }
  return neighs;
}

// Determine the edges associated with vertex id "vertID"
vector<Edge> branches::_branch_map::getEdges(int vertID){
  vector<Edge> edgs;
  for(unsigned long index=0;index<this->vert_bonds.size();index++){
    if(this->vert_bonds.at(index,0)==vertID){
      for(int index2=0;index2<this->vert_bonds.at(index,1);index2++){
        Edge ed(vertID,this->vert_bonds.at(index,3+index2));
        edgs.push_back(ed);
      }
    }
  }
  return edgs;
}

list<Edge> branches::_branch_map::getAllEdges(void){
  ListContainer<Edge> allEdges;
  for(auto vec_row=this->vert_bonds.begin();
           vec_row!=this->vert_bonds.end();
           vec_row++){
  
    int vert1 = vec_row->at(0);
    for(int ind=0;ind<vec_row->at(1);ind++){ 
      if(vert1<vec_row->at(ind+3)){
        Edge ed(vert1,vec_row->at(ind+3));
        allEdges.push_back(ed);
      }else{
        Edge ed(vec_row->at(ind+3),vert1);
        allEdges.push_back(ed);
      }
    }
  }
  allEdges.removeRedundant();
  return allEdges.getList();
}

/* This function is designed to find all the edges associated
 * with a particular branch */
vector<Edge> branches::_branch_map::getBranchEdges(vector<int> branch){

  vector<Edge> branchEdgs;

  for(auto ver=branch.begin();ver!=branch.end();ver++){
    vector<Edge> edgs = this->getEdges(*ver);
    // Cycle through the edgs
    for(auto ed = edgs.begin();ed!=edgs.end();ed++){
      // find the vertex that is not ver
      int other_vert = ed->getOtherV(*ver);
      // We will search within the current branch 
      auto ver_inner = ver;
      ver_inner++;
      while(ver_inner!=branch.end()){
        if(other_vert==*ver_inner){
          // Store the edge
          branchEdgs.push_back(*ed);
          break;
        }
        ver_inner++;
      }
    }
  }

  return branchEdgs;
}

/* This is not the same exploreEdge as is in the _exploration_map 
 * function. This function has to do with the edge in general whereas
 * the function in the _exploration_map class has to do with the edge
 * assocated with a given branch */
void branches::_branch_map::exploreEdge(Edge ed, int branch_ind){
  // Find the edge in the edge map
  for(unsigned long index=0;index<this->_edge_map.size();index++){
    if(ed.getV1()==this->_edge_map.at(index,0) && ed.getV2()==this->_edge_map.at(index,1)){
      // Indicate that the edge has now been explored 
      this->_edge_map.at(index,2)++;
      this->_edge_map.at(index,4) = branch_ind;
      return;
    }
    if(ed.getV1()==this->_edge_map.at(index,1) && ed.getV2()==this->_edge_map.at(index,0)){
      // Indicate that the edge has now been explored 
      this->_edge_map.at(index,2)++;
      this->_edge_map.at(index,4) = branch_ind;
      return;
    }
  }
}

int branches::_branch_map::exploreStatus(Edge ed){
  vector<int> row = this->_edge_mapRow(ed);
  return row.at(2);
}

// Determine if the edge has been explored by another branch
//int branches::_branch_map::branchStatus(Edge ed){
//  vector<int> row = this->_edge_mapRow(ed);
//  return row.at(4);
//}

/******************************************************************
 * Exploration Map Class                                          *
 ******************************************************************/

branches::_exploration_map::_exploration_map(int start_vert, _branch_map bm){
  
  // Determine the number of branches based on the starting_vertex
  int num_branches = bm.getBonds(start_vert);

  this->starting_vertex = start_vert;
  // Resize the internal matrix to match the number of branches
  this->mat.resize(num_branches);

  this->branch_vertices.resize(num_branches);  

  // Now cycle through the bm and determine the edges associated with
  // the starting vertex "start_vert"
  vector<Edge> edgs = bm.getEdges(start_vert);
  // These will be considered the unexplored edges we will add them
  // as such 
  int branch_ind = 0;
  for(auto it = edgs.begin();it!=edgs.end();it++){
    this->addUnexpEdge(branch_ind,start_vert,*it);
    branch_ind++;
  } 
}

branches::_exploration_map::_exploration_map(int start_vert, Edge ed){
  
  // Determine the number of branches based on the starting_vertex
  int num_branches = 1;
  this->starting_vertex = start_vert;
  // Resize the internal matrix to match the number of branches
  this->mat.resize(num_branches);

  this->branch_vertices.resize(num_branches);  

  // These will be considered the unexplored edges we will add them
  // as such 
  this->addUnexpEdge(0,start_vert,ed);
}

/* adds stores the vertex and stores it with it's distance from the 
 * starting junction, adds the ids of the vertex and it's neighbor
 * to the to the mat object*/
void branches::_exploration_map::addUnexpEdge(int branch_ind, int explored_vert_id, Edge ed){

  assert(explored_vert_id!=-1);
  this->_addVertex(branch_ind,explored_vert_id);

  // Check to see if the edge has already been added
  // First check to see if both vertices used by the edge are currently stored
  // If they are the edge will do nothing
  if(this->_vertexExplored(branch_ind,ed.getV1()) && this->_vertexExplored(branch_ind,ed.getV2())){
    return;
  }
  if( !edgeExist(ed, branch_ind)){
      vector<int> vert;
      vert.push_back(explored_vert_id);
      vert.push_back(ed.getOtherV(explored_vert_id));
      this->mat.at(branch_ind).push_back(vert);
  }
}

void branches::_exploration_map::_removeVertex(int branch_ind, int vertID){
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      this->branch_vertices.at(branch_ind).rotateToBack(index);
      this->branch_vertices.at(branch_ind).pop_back();
    }
  }
}

void branches::_exploration_map::_addVertex(int branch_ind, int vertID){

  bool found_vertID = false;
  // If this is the first vertex to be added to the branch
  if(this->branch_vertices.at(branch_ind).size()==0){
    // Vertex id
    vector<int> temp;
    // ID of vertex
    temp.push_back(vertID);
    // Distance from starting vertex
    temp.push_back(0);
    // Branch it belongs too
    temp.push_back(branch_ind);
  
    assert(vertID!=-1);
    this->branch_vertices.at(branch_ind).push_back(temp);
  }else {
    int distance = -1;
    // Check to see if the vertex is referred to in any of the 
    // currently stored edges
    int unexplored_vertex_neigh = -1;

    // Exploring edges 
    for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){
      int explored_id = this->mat.at(branch_ind).at(index,0);
      if(vertID==this->mat.at(branch_ind).at(index,1)){
        unexplored_vertex_neigh = explored_id;
      } 
      if(vertID==explored_id){
        found_vertID = true;
        // Check to be sure that the vertex has already been 
        // added to the branch. If it has not but an edge exists
        // for it then there is an error
        bool error = true;
        for(unsigned long index2=0;index2<this->branch_vertices.at(branch_ind).size();index2++){
          if(this->branch_vertices.at(branch_ind).at(index2,0)==vertID){
            error = false;
            break;
          }
        }
       
        if(error){
          exit(1);
        } 
        // This means that the vertex should have already been added
        // and we do not need to do anything
        break;
      }
    }
    // Explore already stored vertices
    if(this->_vertexExplored(branch_ind,vertID)){
      found_vertID = true;
    }
    if(!found_vertID){
      // If we did not find the vertex we need to add it but first
      // we need to determine how far away it is from the starting 
      // vertex we will do this by determining the edge that represents
      // the vertex we are currently interested in (which should be a neigh
      // of a currently stored edge) with a vertex that has already been
      // explored (unexplored_vertex_neigh)
      for(unsigned long index2=0;index2<this->branch_vertices.at(branch_ind).size();index2++){
        if(this->branch_vertices.at(branch_ind).at(index2,0)==unexplored_vertex_neigh){
          distance = this->branch_vertices.at(branch_ind).at(index2,1);
        }
      }
      vector<int> temp;
      temp.push_back(vertID);
      temp.push_back(distance+1);
      temp.push_back(branch_ind);
      this->branch_vertices.at(branch_ind).push_back(temp);
      assert(vertID!=-1);
    }
    
  }
}

/* This function will remove all edges that are being explored from the vertex
 * given by vert_id that are in mat. It will not remove edges that have vert_id
 * listed as the unexplored vertex. In this case rows in the mat structure  where the
 * second column is vert_id. 
void branches::_exploration_map::_removeEdgesAroundExploredVertex(int vert_id, int branch_ind){
  
  VecVecContainer<int> temp_mat;
  for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){
    if(this->mat.at(branch_ind).at(index,0)!=vert_id){
      auto row = mat.at(branch_ind).at(index);
      temp_mat.push_back(row);
    }
  }
  this->mat.at(branch_ind) = temp_mat;
}
*/

/* Remove the edge from the explored list. */
void branches::_exploration_map::_removeEdge(Edge ed, int branch_ind){

  int vert1 = ed.getV1();
  int vert2 = ed.getV2();

  bool edge_found = false;

  if(this->mat.at(branch_ind).size()==1){
    if(mat.at(branch_ind).at(0,0)==vert1 && mat.at(branch_ind).at(0,1)==vert2){
      mat.at(branch_ind).pop_back();
      return;
    }else if(mat.at(branch_ind).at(0,0)==vert2 && mat.at(branch_ind).at(0,1)==vert1){
      mat.at(branch_ind).pop_back();
      return;
    }else{
      cerr << "ERROR The edge you are trying to remove from the current branch" << endl;
      cerr << "      does not exist in the branch" << endl;
      exit(1);
    }
  }else{

    vector<Edge> edgs = getUnexpEdges(branch_ind);

    for(unsigned long index=0;index<edgs.size();index++){
      if(edgs.at(index)==ed){
        // Search through the mat and delete it
        int ind = 0;
        for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){ 
          if(this->mat.at(branch_ind).at(ind,0)==vert1 && 
              this->mat.at(branch_ind).at(ind,1)==vert2){

            if(mat.at(branch_ind).size()>1){ 
              this->mat.at(branch_ind).rotateToBack(index);
            }
            this->mat.at(branch_ind).pop_back();
            edge_found = true;
            break; 
            // This must be an else if statement because if the previous
            // if statement is triggered and an element is removed it will
            // make the .at(ind,0) an invalid argument
          }else if(this->mat.at(branch_ind).at(ind,0)==vert2 && 
              this->mat.at(branch_ind).at(ind,1)==vert1){

            if(mat.at(branch_ind).size()>1){ 
              this->mat.at(branch_ind).rotateToBack(index);
            }
            this->mat.at(branch_ind).pop_back(); 
            edge_found = true;
            break;
          }
          ind++;
        }

      }
    }

  }
 
  if(!edge_found){ 
    cerr << "ERROR The edge you are trying to remove from the current branch" << endl;
    cerr << "      does not exist in the branch." << endl;
    cerr << "      The edge is" << endl;
    cerr << endl;
    cerr << ed << endl;
    exit(1);
  }
}

/* Testing Remove Edge */
int branches::_exploration_map::test_removeEdge(void){
  // Three branches
  this->mat.resize(3);
  vector<int> row(5,-1);
  mat.at(0).push_back(row);
  mat.at(0).push_back(row);

  mat.at(1).push_back(row);

  mat.at(2).push_back(row);
  mat.at(2).push_back(row);
  mat.at(2).push_back(row);

  // Make sure they contain values for the vertices
  // Edge 0-1
  mat.at(0).at(0,0) = 0;
  mat.at(0).at(0,1) = 1;
  // Edge 1-2
  mat.at(0).at(1,0) = 1;
  mat.at(0).at(1,1) = 2;

  // Edge 3-4
  mat.at(1).at(0,0) = 3;
  mat.at(1).at(0,1) = 4;

  // Edge 0-1
  mat.at(2).at(0,0) = 0;
  mat.at(2).at(0,1) = 1;
  // Edge 6-7
  mat.at(2).at(1,0) = 6;
  mat.at(2).at(1,1) = 7;
  // Edge 7-8
  mat.at(2).at(2,0) = 7;
  mat.at(2).at(2,1) = 8;

  // Branch id 0 and branch id 2 share the edge 0-1
  // Remove the edge from id 0
  Edge ed(0,1);
  this->_removeEdge(ed,0);
  
  // One edge  should be left in branch 0
  assert(mat.at(0).size()==1);
  assert(mat.at(0).at(0,0)==1);
  assert(mat.at(0).at(0,1)==2);

  Edge ed1(1,2);
  this->_removeEdge(ed1,0);
  assert(mat.at(0).size()==0);

  Edge ed2(6,7);
  this->_removeEdge(ed2,2);
  assert(mat.at(2).size()==2);
  assert(mat.at(2).at(0,0)==0);
  assert(mat.at(2).at(0,1)==1);
  assert(mat.at(2).at(1,0)==7);
  assert(mat.at(2).at(1,1)==8);
  return 0;
}

/* Determine if the explored vertex in ed is associated with any other edges 
 * that are claimed by another branch. Return a -1 if there is no contested
 * vertices. Return the id of the contested vertex if there is  */
int branches::_exploration_map::contestedEdge(int branch_ind,Edge ed){
 
  assert(branch_ind>-1); 
  // Step 1 grab the vertices assicated with the edge ed
  int vert1 = ed.getV1();
  int vert2 = ed.getV2();
  // Cycle the branches
  for(unsigned long branch=0;branch<this->mat.size();branch++){
    // Ignore the current branch_ind
    if(branch!=static_cast<unsigned long>(branch_ind)){
      for(unsigned long index=0;index<this->branch_vertices.at(branch).size();index++){
        if(this->branch_vertices.at(branch).at(index,0)==vert1){
          if(vert1!=this->starting_vertex) return vert1;
        }
        if(this->branch_vertices.at(branch).at(index,0)==vert2){
          if(vert2!=this->starting_vertex) return vert2;
        }
      }
    }
  }
  return -1;
}

/* Determine if the vertex indicated by "vertID" has already been stored */
bool branches::_exploration_map::_vertexExplored(int branch_ind, int vertID){
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      return true;
    }
  }
  return false;
}

void branches::_exploration_map::_setDistance(int branch_ind, int vertID, int dist){
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      this->branch_vertices.at(branch_ind).at(index,1)=dist;
    }
  }
}

/* Add a branch identifier if it has not already been added */
void branches::_exploration_map::_addBranchIdentifier(int branch_ind, int vertID, int branch_identifier){
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      for(unsigned long index2=2;index2<this->branch_vertices.at(branch_ind).at(index).size();index2++){
        if(this->branch_vertices.at(branch_ind).at(index,index2)==branch_identifier) return;
      }
      this->branch_vertices.at(branch_ind).at(index).push_back(branch_identifier);
    }
  }
}

/* Add all the branch identifiers if they have not already been added */
void branches::_exploration_map::_addBranchIdentifiers(int branch_ind, int vertID, vector<int> branch_identifiers){
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      for(auto branch_ident=branch_identifiers.begin();branch_ident!=branch_identifiers.end();branch_ident++){
        bool found = false;
        for(unsigned long index2=2;index2<this->branch_vertices.at(branch_ind).at(index).size();index2++){
          if(this->branch_vertices.at(branch_ind).at(index,index2)==*branch_ident){
            found=true;
            break;
          }
        }
        if(found==false){
          this->branch_vertices.at(branch_ind).at(index).push_back(*branch_ident);
        }
      }
    }
  }
}

/* Grab an unexplored edge. Grabs the first one listed in the branch */
Edge branches::_exploration_map::getUnexpEdge(int branch_ind){
  Edge ed(this->mat.at(branch_ind).at(0,0),this->mat.at(branch_ind).at(0,1));
  return ed;
}

// Returns the unexplored edges that are associated with the vertex given by "vertID"
vector<Edge> branches::_exploration_map::getUnexpEdges(int branch_ind,int vertID){
  vector<Edge> edgs;
  for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){
    if(this->mat.at(branch_ind).at(index,0)==vertID || this->mat.at(branch_ind).at(index,1)==vertID){
      Edge temp(this->mat.at(branch_ind).at(index,0),this->mat.at(branch_ind).at(index,1));
      edgs.push_back(temp);
    }
  }
  return edgs;
}

/* Return all the edges that have not been explored */
vector<Edge> branches::_exploration_map::getUnexpEdges(int branch_ind){
  vector<Edge> edgs;
  for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){
    Edge temp(this->mat.at(branch_ind).at(index,0),this->mat.at(branch_ind).at(index,1));
    edgs.push_back(temp);
  }
  return edgs;
}

/* Get all the edges that were explored by the branch "branch_ind" */
vector<Edge> branches::_exploration_map::getExpEdges(int branch_ind, _branch_map bm){
  vector<Edge> edgs;
  
  // Cycle through the vetices and see for every two vertices determine if there
  // is an edge in the bm that connects them.
  vector<int> br_verts = this->getBranchVertices(branch_ind);
  for(auto vert1=br_verts.begin();vert1!=br_verts.end();vert1++){

    auto vert2 = vert1;
    vert2++;
    for(;vert2!=br_verts.end();vert2++){
      Edge ed_temp(*vert2,*vert1);
      vector<Edge> edgs = bm.getEdges(*vert1); 
      for(auto ed=edgs.begin();ed!=edgs.end();ed++){
        if(ed_temp==*ed){
          edgs.push_back(ed_temp);
          break;
        }
      }
    }
  }
  return edgs;
}

/* Return all the vertices that have been explored by a particular branch */
vector<int> branches::_exploration_map::getBranchVertices(int branch_ind){
  
  VecVecContainer<int> vertices = this->branch_vertices.at(branch_ind); 

  vector<int> verts;
  for(unsigned long index = 0;index<vertices.size();index++){
    verts.push_back(vertices.at(index,0));
  }
  return verts;
}

int branches::_exploration_map::getNumUnexploredEdges(int branch_ind){
  return this->mat.at(branch_ind).size();
}
   
bool branches::_exploration_map::edgeExist(Edge ed, int branch_ind){
  
  //cerr << "%%%%%%%%%%%%%%%%%%%%" << endl;
  //cerr << "Looking for edge " << endl;
  //cerr << ed << endl;
  //cerr << "Edges in branch " << branch_ind << endl;
  bool torf = false;
  for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){
    Edge temp(this->mat.at(branch_ind).at(index,0),this->mat.at(branch_ind).at(index,1));
    //cerr << temp << endl;
    if(temp==ed){
      torf = true;
    }
  }
  //cerr << "%%%%%%%%%%%%%%%%%%%%" << endl;
  return torf;
}

/* This function works by taking the the branch given by "branch_ind"
 * it will then look at the provided edge "ed" with the use of the 
 * branch map "bm". Using the edge we will be able to quickly see
 * which vertex has the smaller distance. If the distances are the
 * same nothing will be done. In the case the distances are not the 
 * same the vertex with the lower distance will be used we will call
 * this vertex i. The branch or branches that have laid claim to the
 * vertex i will be found. Then we will proceed to create an exploration
 * map centered at vertex i. (NOTE the distances associaciated with this
 * exploration map should not be used). The exploration map will be used
 * to march through the branch map and only update vertices whos
 * distances are larger than what will be provided by the current exploration.
 * Eg 
 * 
 * 1b1 d1 - 2b1 d2 - 3b1 d3 - 7b1 d4
 *  |                 |        | 
 * 0b2 d0 - 5b2 d1 - 4b2 d2 - 6b2 d3
 *
 * The id of the vertex is given by the first number, and the branch 
 * that has claimed the vertex is given by the second number the final
 * number is the distance from the starting vertex which we have used
 * vertex 0 "0b2" 
 * In this case there are two branch overlap rules
 * 
 * 3b1 d3  7b1 d4
 *   |       |
 * 4b2 d2 ,6b2 d3 
 *
 * When we resolve the first one by calling updateBranchDistances, we 
 * will end up with the following figure
 *
 * 1b1 d1 - 2b1 d2 - 3b1b2 d3 - 7b1b2 d4
 *  |                 |          | 
 * 0b2 d0 - 5b2 d1 - 4b2 d2   - 6b2 d3
 *
 * Notice that vertex 3 and 7 are now claimed by both branch 1 and 2,
 * this is because the distances from the branch 2 vertices are just
 * as close to nodes 3 and 7. Wheras vertices 6 and 4 are further
 * from branch 1 then they are from branch 2. Thus vertices 4 and 6
 * are not claimed by branch 1. 
 *
 * Merging the second branch overlap rule will not cause any changes 
 * for this example. */
void branches::_exploration_map::updateBranchDistances(int branch_ind,Edge ed,_branch_map bm){

  // Determine which vertex associated with the edge has the smaller distance
  int winning_vertex;  

  if((getDistance(branch_ind,ed.getV1()))<getDistance(branch_ind,ed.getV2())){
    winning_vertex = ed.getV1();
  }else if((getDistance(branch_ind,ed.getV2()))<getDistance(branch_ind,ed.getV1())){
    winning_vertex = ed.getV2();
  }else{
    // Distances are the same there is no need to update anything
    return;
  }

  // Grab the branch ids associated with the winning_vertex (the vertex
  // with the smaller distance)
  vector<int> br_identifiers = this->getBranchIdentifiers(branch_ind,winning_vertex);  
  
  // Here we are using the winning vertex as the starting point ok?
  // WARNING we are not using the distances from em_dist, we are simply
  // using it to explore from the winning_vertex location 
  _exploration_map em_dist(winning_vertex,ed);

  /**************************************************************/
  /* Local explore edge function specific to updating distances */
  /**************************************************************/
  while(em_dist.getNumUnexploredEdges(0)>0){
    // Step 1 See what vertex is associated with the edge that has
    //        not been explored
    ed = em_dist.getUnexpEdge(0);
    int vert;
    // Get the unexplored vertex
    if(ed.getV1()==em_dist.starting_vertex){
      vert=ed.getV2();
    }else if(ed.getV2()==em_dist.starting_vertex){
      vert=ed.getV1();
    }else{
      vert = em_dist.getUnexploredVertex(ed,0); 
    }
    // Step 2 Add the vertex to the explored list
    if(vert!=-1){
      assert(vert!=-1);
      em_dist._addVertex(0,vert);

      // Update the branch identifers associated with the vertex
      // This is where the branch identifiers are laying claim to 
      // the now newly explored vertex "vert"
      this->_addBranchIdentifiers(branch_ind,vert,br_identifiers);

      // Step 3 Determine the neighboring vertices to "vert"
      vector<int> neighs = bm.getNeighs(vert);

      // Add each neigh as an edge except if they match the current edge
      // or if they are not in the parent _exploration_map
      for(auto it=neighs.begin();it!=neighs.end();it++){
        if(*it!=ed.getOtherV(vert)){
          Edge temp(vert,*it);

          // Determine if the vertex is currently stored in the parent _exploration_map
          if(em_dist._vertexExplored(0,vert)){

            // Determine if the neigh vertex has a distance value that 
            // is greater than the current vertex value
            int neigh_vert = temp.getOtherV(vert);
            if(this->getDistance(branch_ind,neigh_vert)>getDistance(branch_ind,vert)){  

              // add the edge
              em_dist.addUnexpEdge(0,vert,temp);
            }
          }
        }
      }
    }
    em_dist._removeEdge(ed,0);
  }
 
}

/* Determine how many vertices away from the starting vertex the vertex 
 * defined by "vertID" is */
int branches::_exploration_map::getDistance(int branch_ind, int vertID){
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      return this->branch_vertices.at(branch_ind).at(index,1);
    }
  }
  return -1;
}

/* This function is designed to get all the branches that can lay claim to 
 * the vertex "vertID". The criteria that a branch can lay claim to a vertex
 * depends on the distance of the vertex  "vertID" to the starting vertex.
 * if the "vertID" is closer to branch i than branch j than branch i will lay
 * claim to "vertID", if both branches are the same distance from "vertID" both
 * branch i and j will lay claim to "vertID" */ 
vector<int> branches::_exploration_map::getBranchIdentifiers(int branch_ind, int vertID){
  vector<int> branch_ids;
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==vertID){
      for(unsigned long index2=2;index2<this->branch_vertices.at(branch_ind).at(index).size();index2++){
        branch_ids.push_back(this->branch_vertices.at(branch_ind).at(index,index2));
      }
    }
  }
  return branch_ids;
}

/* This looks through all the vertices and determines which branches
 * exist */
vector<int> branches::_exploration_map::getBranchIdentifiers(void){

  vector<int> branch_vec;
  for(unsigned long i=0;i<this->branch_vertices.size();i++){
    VecVecContainer<int> branch = this->branch_vertices.at(0);
    for(unsigned long j=0;j<branch.size();j++){
      if(branch_vec.size()==0){
        // First branch added
        for(unsigned long k=2;k<branch.size();k++){
          branch_vec.push_back(branch.at(j,k));
        }
      }else{
        // Need to check to see if the branch is already recorded before
        // adding it. 
        for(unsigned long k=2;k<branch.size();k++){
          bool found = false;
          for(unsigned long L=0;L<branch_vec.size();L++){
            if(branch_vec.at(L)==branch.at(j,k)){
              found = true;
              break;
            }
          }
          if(!found) branch_vec.push_back(branch.at(j,k));
        }
      }
    }
  }  
  return branch_vec;
}

vector<vector<int>> branches::_exploration_map::getVertDistances(int branch_ind){
  vector<vector<int>> vert_dist;
  
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    vert_dist.push_back(this->branch_vertices.at(branch_ind).at(index));
  }
  return vert_dist;
}

int branches::_exploration_map::getNumBranches(void){
  return this->branch_vertices.size();
}

int branches::_exploration_map::getExploredVertex(Edge ed, int branch_ind){

  for(unsigned long index=0;index<this->mat.at(branch_ind).size();index++){
    if(this->mat.at(branch_ind).at(index,0)==ed.getV1() && 
       this->mat.at(branch_ind).at(index,1)==ed.getV2()){
      return this->mat.at(branch_ind).at(index,0);
    }
    if(this->mat.at(branch_ind).at(index,0)==ed.getV2() && 
       this->mat.at(branch_ind).at(index,1)==ed.getV1()){
      return this->mat.at(branch_ind).at(index,0);
    }
  }
  
  int ind1 = 0;
  int ind2 = 0;
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==ed.getV1()){
      ind1 = index;
    }
    if(this->branch_vertices.at(branch_ind).at(index,0)==ed.getV2()){
      ind2 = index;
    }
  }
  
  // Both vertices were found in the branch, because I can only
  // return one value I'm going to return an error. 
  if(ind1!=0 && ind2!=0){
    return -1;
  }else if(ind1!=0){
    return this->branch_vertices.at(branch_ind).at(ind1,0);
  }else if(ind2!=0){
    return this->branch_vertices.at(branch_ind).at(ind2,0);
  }
  return -1;
}

/* Given an edge determine which vertex associated with the edge has not yet
 * been explored. Will return -1 if unable to find the edge, or if both
 * vertices have already been explored. */
int branches::_exploration_map::getUnexploredVertex(Edge ed, int branch_ind){

  int ind1 = -1;
  int ind2 = -1;
  int vert1 = -1;
  int vert2 = -1;
  int ind = 0;
  for(unsigned long index=0;index<this->branch_vertices.at(branch_ind).size();index++){
    if(this->branch_vertices.at(branch_ind).at(index,0)==ed.getV1()){
      ind1 = ind;
      vert1 = ed.getV2();
    }
    if(this->branch_vertices.at(branch_ind).at(index,0)==ed.getV2()){
      ind2 = ind;
      vert2 = ed.getV1();
    }
    ind++;
  }
  
  // Both vertices were found in the branch, because I can only
  // return one value I'm going to return an error. 
  if(ind1!=-1 && ind2!=-1){
    return -1;
  }else if(ind1!=-1){
    // Before we return the vertex we need to ensure that it is part
    // of one of the edges that the current branch is allowed to explore
    // For instance if we start off a the starting vertex of 1 
    // 0 <- 1 -> 2 Edge 1,2 may be assigned to branch 1 and thus if we pass
    //             Edge 1,2 to branch 0 then it should return -1 because the
    //             edge is not assigne to branch 0;
    //
    // We only need to search in the second column of mat which should be the
    // unexplored vertex
    for(auto expl_row=this->mat.at(branch_ind).begin();
        expl_row!=this->mat.at(branch_ind).end();
        expl_row++){
        
        // Checking second column
        if(expl_row->at(1)==vert1){
          return vert1;
        }
    }
  }else if(ind2!=-1){

    for(auto expl_row=this->mat.at(branch_ind).begin();
        expl_row!=this->mat.at(branch_ind).end();
        expl_row++){

      // Checking second column
      if(expl_row->at(1)==vert2){
        return vert2;
      }
    }
  }

  return -1;
}

void branches::_exploration_map::putBranchOverlapRule(int branch1, int branch2, Edge ed){
  vector<int> overlap_rule;
  overlap_rule.push_back(branch1);
  overlap_rule.push_back(branch2);
  overlap_rule.push_back(ed.getV1());
  overlap_rule.push_back(ed.getV2());
  this->branch_overlap_rule.push_back(overlap_rule);
}

/* Check if a branch overlap rule exists for the provided edge */
bool branches::_exploration_map::branchOverlapRuleExist(Edge ed){
  if( branch_overlap_rule.size()==0) return false;
  
  for(unsigned long index=0;index<this->branch_overlap_rule.size();index++){
    if(this->branch_overlap_rule.at(index,2)==ed.getV1() && this->branch_overlap_rule.at(index,3)==ed.getV2()){
      return true;
    }
    if(this->branch_overlap_rule.at(index,2)==ed.getV2() && this->branch_overlap_rule.at(index,3)==ed.getV1()){
      return true;
    }
  }
  return false;
}

/* Given an edge return the branch overlap rule associated with the edge */
vector<int> branches::_exploration_map::getBranchOverlapRule(Edge ed){
  vector<int> row;
   for(unsigned long ind=0;ind<this->branch_overlap_rule.size();ind++){
    if(this->branch_overlap_rule.at(ind,2)==ed.getV1() && this->branch_overlap_rule.at(ind,3)==ed.getV2()){
      for(unsigned long index=0;index<this->branch_overlap_rule.size(ind);index++){
        row.push_back(branch_overlap_rule.at(ind,index));
      }
      return row;
    }
    if(this->branch_overlap_rule.at(ind,2)==ed.getV2() && this->branch_overlap_rule.at(ind,3)==ed.getV1()){
      for(unsigned long index=0;index<this->branch_overlap_rule.size(ind);index++){
        row.push_back(branch_overlap_rule.at(ind,index));
      }
      return row;
    }
  }
  return row; 
}

vector<vector<int>> branches::_exploration_map::getBranchOverlapRules(){
  vector<vector<int>> Rules;
  vector<int> row;
  row.resize(4);
  for(unsigned long ind=0;ind<this->branch_overlap_rule.size();ind++){
    for(unsigned long index=0;index<this->branch_overlap_rule.size(ind);index++){
      row.at(index) = this->branch_overlap_rule.at(ind,index);
    }
    Rules.push_back(row);
  }
  return Rules; 
}

/* This function basically return the branch_vertices but for a specific
 * branch and it returns it in a vector vector format. */
vector<vector<int>> branches::_exploration_map::getMap(int branch_ind){
  return this->branch_vertices.at(branch_ind).getData();
}

vector<vector<int>> branches::_exploration_map::getMap(void){
/* If no branch is specified get the data for all the branches */
  vector<vector<int>> map = this->branch_vertices.at(0).getData();
  int num_branch = this->getNumBranches();
  for(int branch_ind=1;branch_ind<num_branch;branch_ind++){
    vector<vector<int>> temp_map = this->branch_vertices.at(branch_ind).getData();

    // We will treate the first element as a special case because
    // All the branches should have started at the same point so 
    // all the branches should be able to lay claim to the first 
    // vertex. Note when calling insert we do not start a begin()
    // but at the next iteration. 
    map.insert(map.end(),++temp_map.begin(),temp_map.end());
    for(unsigned long ind=2;ind<temp_map.at(0).size();ind++){
      map.at(0).push_back(temp_map.at(0).at(ind));
    }
  }
  return map;
}

/* Given two branch_ids return the list of edges where the branches overlap */
vector<Edge> branches::_exploration_map::getOverlappingEdges(int branch1, int branch2){
  vector<Edge> edgs;
   for(unsigned long index=0;index<this->branch_overlap_rule.size();index++){
    if(this->branch_overlap_rule.at(index,1)==branch1 && this->branch_overlap_rule.at(index,0)==branch2){
      Edge ed(this->branch_overlap_rule.at(index,2),this->branch_overlap_rule.at(index,3));
      edgs.push_back(ed);
    }
    if(this->branch_overlap_rule.at(index,0)==branch1 && this->branch_overlap_rule.at(index,1)==branch2){
      Edge ed(this->branch_overlap_rule.at(index,2),this->branch_overlap_rule.at(index,3));
      edgs.push_back(ed);
    }
  }
  return edgs; 
}

/* This function will find all the branches that have stored the vertex contested_vertex
 * in the branch_vertices function */
vector<int> branches::_exploration_map::getBranchesContestVertex(int contested_vertex){
  vector<int> contested_br;
  
  for(unsigned long branch=0;branch<this->mat.size();branch++){
    // Check the first column of the branch_vertices attribute for the conctested vertex
    vector<int> temp = this->branch_vertices.at(branch).getMatchInd(0,contested_vertex);
    if(temp.size()>0){
      contested_br.push_back(branch);
    }
  }
  return contested_br;
}

/* Find which of the vertices in the edge are claimed by the neigh_branch this 
 * will be the vertex of conflict. If there is an error for instance if the function
 * finds both vertices in the edge are claimed by the same branch then there is no conflict
 * will return -1, or if neigther vertex is in the neigh branch will also return -1 */
int branches::_exploration_map::findVertexConflict(int neigh_branch, Edge ed){

  int vert1 = ed.getV1();
  int vert2 = ed.getV2();
  
  // Cycle through the branch vertices and determine which vertices are found
  bool vert1_found = false;
  bool vert2_found = false;
  
  for(auto vert_row=this->branch_vertices.at(neigh_branch).begin();
      vert_row!=this->branch_vertices.at(neigh_branch).end();
      vert_row++){
    if(vert_row->at(0)==vert1){
      vert1_found=true;
    }
    if(vert_row->at(0)==vert2){
      vert2_found=true;
    }
  }
  
  // Error only a single branch should have claimed each vertex. 
  if(vert1_found && vert2_found){
    return -1;
  }
  // Error neither vertices in the edge were claimed by the branch.
  if(!vert1_found && !vert2_found){
    return -1;
  }
  if(vert1_found) return vert1;
  if(vert2_found) return vert2;

  // If this is the case there is some weird error
  return -1;
} 

/* Here the branch id must be different from the branch id associated
 * with the edge. This function makes sure that none of the edges and vertices
 * stored for each branch are shared.
 * As an example consider this scenario
 * 
 *  0 - 1 - 2 
 *
 * Where:
 *  -> Indicates the edge is explored
 * |-> Indicates the edge has not yet been explored but is visible to the branch
 *
 * Branch 0 starts at vertex 0 
 *
 *  0  -> 1 |-> 2
 *
 * Branch 1 starts at vertex 2
 * 
 *  0 <-| 1 <-  2
 *
 * At this point we will have an overlap when we try to explore from branch 0 
 *
 *  0  -> 1  x  2
 *    
 * For branch 1 we need to make sure that we do not explore 0 <-| 1 because it 
 * overlaps with branch 0 which already lays claim to edge 0  -> 1. 
 *
 * Thus we should end up for branch 1 with a single vertex
 *
 *        1  x  2
 *
 * In this case branch_id would be 1 and neigh_branch ends up becoming 0. The 
 * neigh_branch has already laid claim to vertex 1 and edge 0  -> 1.
 * 
 *****************************************************************************
 * Let's consider a more complicated example
 *
 *  0 - 1 - 2
 *      | 
 *      3
 *
 * Branch 0 exploring from vertex 0
 *
 *  0  -> 1 |-> 2
 *        -
 *        |
 *        v
 *        3
 *
 * Branch 1 exploring from vertex 2
 * 
 *  0 <-| 1 <-  2
 *        -
 *        |
 *        v
 *        3
 * 
 * Secenario I
 * Branch 0 explores 1 - 2 and finds it is already taken by branch 1
 * 
 *   0  x  1      and for branch 1   0  x  1 <-  2
 *                                         -
 *                                         |
 *                                         v
 *                                         3
 * 
 * Scenario 2 branch 0 explores the 1 - 3 edge
 * 
 *  0  -> 1 |-> 2   
 *         
 *        |
 *        v
 *        3
 * 
 * Branch 1 then has a conflict if it explores anything else end up with
 * 
 *  0  -> 1  x  2   and Branch 1 becomes   1 x 2
 *         
 *        |
 *        v
 *        3
 *
 *****************************************************************************
 * Here is a more involved case
 *
 *  0 - 1 - 2 
 *  |   |   |
 *  3 - 4 - 5 
 *  |   |   |
 *  6 - 7 - 8
 *   
 * Lets say branch 0 starts exploring from 0 and 1 starts exploring from 5 and
 * we have the following exploration maps
 *
 * Branch 0              Branch 1
 *
 *  0  -> 1 |-> 2         0 <-| 1 <-  2
 *  ^     ^                     ^     ^
 *  |     |                     |     |
 *                              -
 *  3  -> 4 |-> 5         3 <-| 4 <-  5
 *        -                     -     
 *  |     |                     |     |
 *  v     v                     v     v
 *  6  -> 7 |-> 8         6 <-| 7 <-  8  
 *
 */
void branches::_exploration_map::removeBranchOverlapAtEdge(int branch_id, Edge ed){

  // To illustrate what is going on here we will provide a diagram illustrating a situation
  //
  //    0 - 1 
  //    |   |
  //    4   2 - 5
  //     \ /
  //      3 
  //
  // Where both branches start exploring form vertex 0. The case below should never occur
  //
  // Branch 0             Branch 1
  //
  //                            1
  //    0 -> 1            0     ^
  //         |            |     |
  //         v            v     -
  //         2 -> 5       4     2 |-> 5
  //         -                  ^
  //        /              \   /
  //       v                v   
  //       3                3
  //
  // This is where we will find there is an overlap
  //
  // Branch 0             Branch 1
  //
  //                            
  //    0 -> 1            0    
  //         |            |    
  //         v            v    
  //         2 -> 5       4    2
  //         -                 ^
  //        /              \  /
  //       v                v- 
  //       3                3
  //
  // It is now Branch 1s turn to explore an edge and it is exploring edge 2,3

  // Step 1 Determine what the other branch is
  int neigh_branch = otherBranch(ed,branch_id); 

  // Step 2 Determine which vertex is the source of conflict between the two branches
  //        This is done by looking at the edge and checking which of the two vertices
  //        in the edge has been claimed by the neighboring branch. 
  int vert_conflict = this->findVertexConflict(neigh_branch, ed);
  if(vert_conflict==-1){
    cerr << "ERROR vert_conflict is -1, this can occur if both vertices have been claimed" << endl;
    cerr << "      by the same branch, or if there is no conflict." << endl;
    assert(vert_conflict!=-1);
  }

  // We will proceed by removing the edge on branch 1 that is attempting to explore edge 2,3
  this->_removeEdge(ed,branch_id);  
  
  // We will also proactively remove the same edge from branch 0 
  this->_removeEdge(ed,neigh_branch);

  // Our diagram should now look like this:
  //
  // Branch 0             Branch 1
  //
  //                            
  //    0 -> 1            0    
  //         |            |    
  //         v            v    
  //         2 -> 5       4    2
  //                           
  //        x              \  x
  //                        v 
  //       3                3
  //

  // And now we should be good to go  
}

// Look through the vertices stored in all the branches accept the one 
// passed in and return the id of the branch where one of the vertices is found
// at least one of the vertices is found. If more than one branch is found
// to claim the vertices in the edge other than branch_ind than return an error
// in the form of value -1
int branches::_exploration_map::otherBranch(Edge ed, int branch_ind){

  int vert1 = ed.getV1();
  int vert2 = ed.getV2();

  int otherBr = -1;
  int count = 0;
  for(auto branch_verts=this->branch_vertices.begin();
          branch_verts!=this->branch_vertices.end();
          branch_verts++){
    for(auto vert=branch_verts->begin();vert!=branch_verts->end();vert++){
      if(vert1==vert->at(0)){
        // Determine which branch the vertex is attached too
        if(otherBr==-1 && vert->at(2)!=branch_ind){
          otherBr = vert->at(2);
          assert(otherBr!=-1);
          count++;
        }
      }else if(vert2==vert->at(0)){
        if(otherBr==-1 && vert->at(2)!=branch_ind){
          otherBr = vert->at(2);
          assert(otherBr!=-1);
          count++;
        }
      }     
    }
  }

  if(count>1){
    return -1;
  }
  return otherBr;
}

// All branches that share an edge are connected
void branches::_exploration_map::mergeAllOverlapRules(_branch_map bm){
  
  // Make sure the system has been fully explored before proceeding
  for(unsigned long branch_ind=0;branch_ind<mat.size();branch_ind++){
    assert(mat.at(branch_ind).size()==0);
  }
  // Step 1 Create variables to overwrite 
  VecVecContainer<int> bv_temp;

  // Step 2 determine the number of branches
  unsigned long numBranches = this->branch_vertices.size();

  unsigned long numRules = this->branch_overlap_rule.size();
  // Step 3 Cycle through branches
  for(unsigned long branch_ind=0;branch_ind<numBranches;branch_ind++){
    
    // Step 4 cycle through the branch overlap rules and determine
    //        which ones pertain to branch_ind 
    unsigned long rule_ind = 0;
    while(rule_ind<numRules){

      bool mergeVertices = false; 
      bool ruleRelevant = false;

      int other_branch;
      // Ensure that branches in the overlap rule are not less than 0
      if(this->branch_overlap_rule.at(rule_ind).at(0)<0 ||
         this->branch_overlap_rule.at(rule_ind).at(1)<0){
        cerr << "ERROR you have a negative branch which you are about to"
             << " convert to an unsigned int this is not safe.          "   << endl;
        cerr << "ERROR in branches::_exploration_map::mergeAllOverlapRules" << endl;
        exit(1);
      }

      unsigned long branch_ind_long0 = static_cast<unsigned long> (this->branch_overlap_rule.at(rule_ind).at(0));
      unsigned long branch_ind_long1 = static_cast<unsigned long> (this->branch_overlap_rule.at(rule_ind).at(1));
      if(branch_ind_long0==branch_ind){
        // Rules are only relevant if the second branch id in the 
        // rule is greater than the current branch id or if all smaller branch ids
        // have already been merged
        if(branch_ind_long1>branch_ind){
          ruleRelevant = true;
          mergeVertices = true;
          other_branch = this->branch_overlap_rule.at(rule_ind).at(1);
        }

      }else if(branch_ind_long1==branch_ind){

        if(branch_ind_long0>branch_ind){
          ruleRelevant = true;
          mergeVertices = true;
          other_branch = this->branch_overlap_rule.at(rule_ind).at(0);
        }
      }
     
      if(branch_ind_long0==branch_ind_long1){
        // This means the vertices have already been merged but the rule is still
        // relevant because we have to update the distances and erase the rule
        ruleRelevant = true;
      }

      if(ruleRelevant){
     
        if(mergeVertices){ 
          bv_temp = this->branch_vertices.at(branch_ind);

          // Cycle through the other branch and add all the vertices to the 
          // current branch_ind, as long as the distance for the vertex is not 0
          // because that would indicate that it is the starting point 
          unsigned long vert_ind;
          for(vert_ind=0;vert_ind<this->branch_vertices.at(other_branch).size();vert_ind++){
            vector<int> row;
            // First  col1 of row - the vert id
            // Second col2 of row - distance from starting point
            // Third  col3 of row - the branch it was originally associated with
            for(unsigned long ind=0;ind<this->branch_vertices.at(other_branch).at(vert_ind).size();ind++){
              row.push_back(this->branch_vertices.at(other_branch).at(vert_ind,ind));
            }
            if(row.at(1)!=0){
              bv_temp.push_back(row);
            }else{

              // The first vertex in the branch is a special case because all
              // the branches should be able to lay claim to this vertex. 
              // Simply append to the first row in bv_temp 
              for(unsigned long ind_b=2;ind_b<row.size();ind_b++){
                bv_temp.at(0).push_back(row.at(ind_b));
              }
            }
          }

          // Overwrite the previous branch_vertices
          this->branch_vertices.at(branch_ind) = bv_temp;  
          // Clear out the vertices that were in the previous branch
          this->branch_vertices.at(other_branch).clear();
          // Change all the rules that refer to the "other_branch" to now refer 
          // to the current branch_ind
          for(unsigned long rule_ind2=0;rule_ind2<numRules;rule_ind2++){
            if(this->branch_overlap_rule.at(rule_ind2).at(0)==other_branch){
              // Switch the branch
              this->branch_overlap_rule.at(rule_ind2).at(0)=branch_ind;
            }else if(this->branch_overlap_rule.at(rule_ind2).at(1)==other_branch){
              this->branch_overlap_rule.at(rule_ind2).at(1)=branch_ind;
            }
          } 
        }
        // Update the distances in each branch based on the rules that where merged
        // took place
        // Index at 0 and 1 should be the same at this point, they have to be the same
        // if they are on the same molecule
        //int branch = this->branch_overlap_rule.at(rule_ind,0);
        // Create an edge
        Edge temp_ed(this->branch_overlap_rule.at(rule_ind,2),this->branch_overlap_rule.at(rule_ind,3));
        updateBranchDistances(branch_ind,temp_ed,bm);
        // Finally clear out the old branch_rules
        //this->branch_overlap_rule.clear();
        this->branch_overlap_rule.erase(rule_ind);
        
        // If the rule was found to be relevant we need to start over
        rule_ind = 0;
        // The number of rules also decreases
        numRules--;
      }else{
        // If the rule was not relevant move to the next one
        rule_ind++;
      } 
    }
  }
  
  // And remove branches that are now empty from the branch vertices
  vector<VecVecContainer<int>> bv_t;
  for(unsigned long branch_ind=0;branch_ind<numBranches;branch_ind++){
    if(this->branch_vertices.at(branch_ind).size()>0){
      bv_t.push_back(this->branch_vertices.at(branch_ind));
    }
  }
  // Overwrite the previos branch vertices
  this->branch_vertices = bv_t;
}

/* Check to see if all the edges in each branch have been fully explored */
bool branches::_exploration_map::allBranchesComplete(void){
  bool exp = true;
  for(int branch_ind=0;branch_ind<this->getNumBranches();branch_ind++){
    if(this->getNumUnexploredEdges(branch_ind)>0){
      exp = false;
      break;
    }
  }

  // Also need to make sure that all the appropriate overlap rules exist
  // Take for instance this case
  // 
  //   b1   b2
  // 1 -> 2 <- 3
  //
  // All the edges have been explored from a global point of view but
  // if an overlap rule does not exist between branch1 and branch2 with
  // vertex 2 then the branch 2 will still have edge 2,1 as listed as unexplored
  // and branch 1 will have edge 2,3 listed as unexplored

  return exp;
}

void branches::_exploration_map::exploreEdge(Edge ed,int branch_ind,  _branch_map bm){
  // Step 1 See what vertex is associated with the edge that has
  //        not been explored
  int vert = this->getUnexploredVertex(ed,branch_ind); 
  
    
  // Check to make sure that the vertex has not already been explored before
  // attempting to add more edges and the vertex
  if(vert!=-1){
    // Step 2 Determine the neighboring vertices to "vert"
    vector<int> neighs = bm.getNeighs(vert);
    bool AddVert = false;
    // Add each neigh as an edge except if they match the current edge
    for(auto it=neighs.begin();it!=neighs.end();it++){
      if(*it!=ed.getOtherV(vert)){
        Edge temp(vert,*it);
        AddVert = true;
        this->addUnexpEdge(branch_ind,vert,temp);
      }
    }
    // If no edges were added we still need to add
    // the vertex by itself
    if(!AddVert){
      assert(vert!=-1);
      this->_addVertex(branch_ind,vert);
    }
  }
  this->_removeEdge(ed,branch_ind);
   
}

/* Return a value of 0 if there are no edges to explore else
 * return a value of 1 to indicate success */
int branches::_exploration_map::exploreBranches(_branch_map bm){

  // Step 1 check to make sure that there are edges to explore
  while(this->allBranchesComplete()==false){

    // Step 2 Cycle through the branches exploring one edge at a time
    for(int branch_ind=0;branch_ind<this->getNumBranches();branch_ind++){
      //cerr << "####################################" << endl;
      //cerr << "Exploring Branch " << branch_ind << " number unexplored edges " << this->getNumUnexploredEdges(branch_ind) << endl;
      // Ensure that this branch has unexplored edges
      if(this->getNumUnexploredEdges(branch_ind)>0){
        // Randomly grab an edge
        Edge ed = this->getUnexpEdge(branch_ind);
        // Check to see if it has already been explored
        // Dont just check the edge you pulled out but if there is more
        // than this particular edge associated with the explored vertex
        // check to see if they have also been explored by some other 
        // branch. This is to avoid a situation like this:
        //
        //            Branch 0               Branch 1
        //
        //  1    2    1    2                 1    2
        //    \ /      \   ^                 ^    ^
        //     3        v /                   \  /
        //    / \        3                     --
        //   4   5       --                     3
        //             |    |                  ^  |
        //             V    v                  |  V
        //             4    5                  4  5
        //            
        // Where branch 0 has edges 1,3 and 2,3 and branch 1 has edges 3,4, and 3,5
        // At this point it would become very hard to create an overlap statement 

        // Check if there is a contested edge that uses the same explored vertex as edge ed
        int contested_vert = this->contestedEdge(branch_ind,ed);
        
        // If contested_vert is equal to -1 than it means that there is no contested vertex
        if(contested_vert!=-1){
          // Determine which branch claims this vertex
          
          vector<int> branches_contest = this->getBranchesContestVertex(contested_vert);

          // If more than one branch contests the vertex it is a problem, the contested vertex 
          // should not yet have been explored by branch_ind, so it should only at most belong 
          // to a single other branch. 
          if(branches_contest.size()!=1){           
            cerr << "ERROR more than one branch has claimed the vertex this should not be allowed" << endl;
            cerr << "      for any vertex except the starting vertex" << endl;
            cerr << "      The contested vertex is " << contested_vert << endl;
            cerr << "      It is contested between the following branches" << endl;
            for(auto br_id=branches_contest.begin();br_id!=branches_contest.end();br_id++){
              cerr << *br_id << endl;
            }
            cerr << "ERROR in exploreBranches" << endl;
            exit(1);
          }

          // Determine which branch has explored it
          int branch = branches_contest.at(0);
         
          // Determine if this is the same branch as the current branch
          if(branch==branch_ind){
            // If it is we need to make sure that the distances 
            // are correctly updated to reflect how close they are
            // to the starting junction 
            this->updateBranchDistances(branch,ed,bm);
            // Remove the edge from the branch


          }else{
            // If this is the case we need to determine how the branches will be
            // merged... we will not merge them yet though. 
            this->putBranchOverlapRule(branch_ind,branch,ed);
            // We also need to prevent branches from overlapping any further at
            // this point.
            this->removeBranchOverlapAtEdge(branch_ind, ed);
          }
        }else{

          // This means that the edge has not yet been explored 
          bm.exploreEdge(ed,branch_ind);
          this->exploreEdge(ed,branch_ind,bm);        
        }
      }
    }
  }

  // Branches
  int br_ind = 0;
  for(auto branch_iter=this->branch_vertices.begin();
           branch_iter!=this->branch_vertices.end();branch_iter++){

    for(auto vert_iter=branch_iter->begin();
             vert_iter!=branch_iter->end();
             vert_iter++){
      for(auto vert_info_iter=vert_iter->begin();
               vert_info_iter!=vert_iter->end();
               vert_info_iter++){

      }
    }
    br_ind++;
  }

  return 1;
}

/******************************************************************
 * Branches Class                                                 *
 ******************************************************************/
branches::branches(list<Edge> edgs){
  // Initilaize branch map
  _branch_map bm_temp(edgs);
  this->bm=bm_temp;
}

/* Get all the junctions from the original branch map. This will not
 * get junctions that exist after the branches have been explored. 
 * all vertices with 3 or more edges will be considered a junction */
vector<int> branches::getJunctions(){
  return this->bm.getJunctionVert();
}

vector<pair<int,int>> branches::countJunctionEdges(){
    auto juncts = getJunctions();
    vector<pair<int,int>> junct_count;
    for( auto j : juncts ){
        pair<int, int> pr(j,bm.getBonds(j));
        junct_count.push_back(pr);
    }
    return junct_count;
}

vector<pair<int,int>> branches::countEdges(){
   auto verts = bm.getVert();
   vector<pair<int,int>> vert_count;
   for( auto v : verts ){
        pair<int, int> pr(v,bm.getBonds(v));
        vert_count.push_back(pr);
   } 
    return vert_count;
}


void branches::exploreFromVertex(int vertID){

  _branch_map bm_temp(this->bm.getAllEdges());
  this->bm = bm_temp;

  _exploration_map em_temp(vertID,this->bm);
  this->em = em_temp;
  em.exploreBranches(this->bm);
  em.mergeAllOverlapRules(this->bm);
}

/* This will return the number of branches currently found from 
 * the last exploration. */
int branches::numBranches(void){
  return this->em.getNumBranches();
}

/* This function will return a vector of vectors containing
 * the ids of all the vertices in the branches that were explored
 * In the 2nd column will be the distance from 
 * the exploration point. The following columns will list the
 * ids of the branches that can lay claim to each of the vertices. */
vector<vector<int>> branches::getMap(void){
  return this->em.getMap();
}

/* Grab the indices found for the exploration */
vector<int> branches::getBranchIndices(void){
  return this->em.getBranchIdentifiers();  
}

/* Unlike the function "getMap" this only gets the map of the specified 
 * branch. Each vertex in the branch is returned such that we have
 * the following ouput. 
 * col 1 vertex id
 * col 2 distance from starting point, i
 * col 3+ all the branches that lay claim to the vertex excluding 
 *        "branch_ind" because it is a given. */
vector<vector<int>> branches::getBranchMap(int branch_ind){
  vector<vector<int>> full_map = this->em.getMap();
  
  vector<vector<int>> local_map;
  // Cycle through the map and if the branch lays claim to the
  // vertex add it
  for(auto row=full_map.begin();row!=full_map.end();row++){
    vector<int> temp_row;
    for(unsigned long col_ind=2;col_ind<row->size();col_ind++){
      if(row->at(col_ind)==branch_ind){
        temp_row.push_back(row->at(0));
        temp_row.push_back(row->at(1));
        // Add branches only if they are not branch_ind
        for(unsigned long ind=2;ind<row->size();ind++){
          if(row->at(ind)!=branch_ind){
            temp_row.push_back(row->at(ind));
          }
        }
        local_map.push_back(temp_row);
        break;
      }
    }
  }
  return local_map;  

}

/* This function by returning the vertices and the distances of
 * the branch "branch_ind" */
vector<vector<int>> branches::getBranchDist(int branch_ind){
  vector<vector<int>> full_map = this->em.getMap();
  
  vector<vector<int>> Dist;
  // Cycle through the map and if the branch lays claim to the
  // vertex add it
  for(auto row=full_map.begin();row!=full_map.end();row++){
    vector<int> temp_row;
    for(unsigned long col_ind=2;col_ind<row->size();col_ind++){
      if(row->at(col_ind)==branch_ind){
        temp_row.push_back(row->at(0));
        temp_row.push_back(row->at(1));
        Dist.push_back(temp_row);
        break;
      }
    }
  }
  return Dist;  
}

vector<vector<int>> branches::getBranches(void){

  vector<vector<int>> Branches;

  for(int branch_ind=0;branch_ind<this->em.getNumBranches();branch_ind++){

    vector<int> branch = this->em.getBranchVertices(branch_ind);
    Branches.push_back(branch);
  }
  return Branches;
}

vector<vector<Edge>> branches::getBranchesEdges(void){
   
  vector<vector<Edge>> allEdges;

  for(int branch_ind=0;branch_ind<this->em.getNumBranches();branch_ind++){

    vector<int> branch = this->em.getBranchVertices(branch_ind);

    vector<Edge> branchEdges = this->bm.getBranchEdges(branch);
    // Only grab the edges that describe interactions between the vertices
    // in the branch
    allEdges.push_back(branchEdges);

  }

  return allEdges; 
}

/******************************************************************
 * Test Branch Class                                              *
 ******************************************************************/
int branches::test_branchclass(void){

  cout << "Testing: _branch_map constructor" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(2,3);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);     
    list_ed.push_back(ed2);     
    list_ed.push_back(ed3);

    // Calling constructor
    _branch_map bm(list_ed); 
  }

  cout << "Testing: getJunctionVert" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
    
    _branch_map bm(list_ed);
    vector<int> junc = bm.getJunctionVert();
    assert(junc.at(0)==1);
    assert(junc.at(1)==4);
    assert(junc.size()==2);
  }

  cout << "Testing: getNeighs" << endl;
  {

   // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
   
    _branch_map bm(list_ed);
    vector<int> neigh = bm.getNeighs(0);
    assert(neigh.size()==1);
    assert(neigh.at(0)==1);
    neigh = bm.getNeighs(1);
    assert(neigh.size()==3);
    assert(neigh.at(0)==0);
    assert(neigh.at(1)==2);
    assert(neigh.at(2)==3);
    neigh = bm.getNeighs(2);
    assert(neigh.size()==1);
    assert(neigh.at(0)==1);
    neigh = bm.getNeighs(3);
    assert(neigh.size()==2);
    assert(neigh.at(0)==1);
    assert(neigh.at(1)==4);
    neigh = bm.getNeighs(4);
    assert(neigh.size()==3);
    assert(neigh.at(0)==3);
    assert(neigh.at(1)==5);
    assert(neigh.at(2)==6);
  }

  cout << "Testing: getEdges" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
    vector<Edge> edgs = bm.getEdges(0);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed1);
    edgs = bm.getEdges(1);
    assert(edgs.size()==3);
    assert(edgs.at(0)==ed1);  
    assert(edgs.at(1)==ed2);
    assert(edgs.at(2)==ed3);     
  } 

  cout << "Testing: getAllEdges" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
    list<Edge> edgs = bm.getAllEdges();
    
    assert(edgs.size()==6); 
  }

  cout << "Testing: exploreEdge" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
     
    // Duplicate of ed6 for testing
    Edge ed7(6,4);
 
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
    int branch_ind = 1;
   // assert(bm.branchStatus(ed1)==-1);
    bm.exploreEdge(ed1,branch_ind);
    //assert(bm.branchStatus(ed1)==1);

    branch_ind = 2;
    //assert(bm.branchStatus(ed7)==-1);
    bm.exploreEdge(ed7,branch_ind);
    //assert(bm.branchStatus(ed6)==2);
 
  }

  cout << "Testing: _exploration_map constructor " << endl;
  {
  // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);

    // Using 0 as the starting vertex
    _exploration_map em(0,bm);

    // Using an edge to initialize the map
    _exploration_map em2(0,ed1);
  }

  cout << "Testing: _removeEdge" << endl;
  { 
    _exploration_map em1;
    em1.test_removeEdge();
  }

  cout << "Testing: getNumBranches" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);

    // Using 0 as the starting vertex
    _exploration_map em1(0,bm);
    assert(em1.getNumBranches()==1);
    
    _exploration_map em2(1,bm);
    assert(em2.getNumBranches()==3);
  }
  
  cout << "Testing: getUnexpEdges" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);

    // Using 1 as the starting vertex
    _exploration_map em1(1,bm);
    vector<Edge> edgs = em1.getUnexpEdges(0);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed1);
    edgs = em1.getUnexpEdges(1);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed2);
    edgs = em1.getUnexpEdges(2);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed3);
   
    // Getting the edges associated with a specific vertex
    int vertex=1;
    edgs = em1.getUnexpEdges(0,vertex);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed1);
 
  }
  
  cout << "Testing: getDistance"<< endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);

    // Using 1 as the starting vertex
    _exploration_map em1(1,bm);
    // First int refers to the branch 
    // Second int refers to the vertex id
    // Each branch at this point only has the first vertex in
    // the explored group. 
    assert(em1.getDistance(0,1)==0);
    assert(em1.getDistance(1,1)==0);
    assert(em1.getDistance(2,1)==0);
  }
 
  cout << "Testing: getUnexploredVertex" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);

    // Using 1 as the starting vertex
    _exploration_map em1(1,bm);
    assert(em1.getUnexploredVertex(ed1,0)==0);    
    assert(em1.getUnexploredVertex(ed2,1)==2);    
    assert(em1.getUnexploredVertex(ed3,2)==3);    
  }
 
  cout << "Testing: addEdge" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
    // Using 1 as the starting vertex
    _exploration_map em1(1,bm);
    int branch=2;
    int explored_vert = 3;
    vector<Edge> edgs = em1.getUnexpEdges(branch);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed3); 
    em1.addUnexpEdge(branch,explored_vert,ed4);
    // Unlike exploreEdge addEdge does not delete anything 
    edgs = em1.getUnexpEdges(branch);
    assert(edgs.size()==2);
    assert(edgs.at(0)==ed3);
    assert(em1.getDistance(branch,1)==0);
    assert(edgs.at(1)==ed4);
    assert(em1.getDistance(branch,3)==1);
  } 
 
  cout << "Testing: exploreEdge" << endl;
  {
    // Creating a list of edges
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
    
    // Using 1 as the starting vertex
    _exploration_map em1(1,bm);
    em1.exploreEdge(ed3,2,bm);
    vector<Edge> edgs = em1.getUnexpEdges(2);
    assert(edgs.size()==1);
    assert(edgs.at(0)==ed4); 
    assert(em1.getUnexploredVertex(ed4,2)==4);
    em1.exploreEdge(ed4,2,bm);
    edgs = em1.getUnexpEdges(2);
    assert(edgs.size()==2);
    assert(edgs.at(0)==ed5);
    assert(edgs.at(1)==ed6);
    
    assert(em1.getDistance(2,1)==0);
    assert(em1.getDistance(2,3)==1);
  }

  cout << "Testing: allBranchesComplete" << endl;
  {

    Edge ed1(0,1);
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    _branch_map bm(list_ed);
    _exploration_map em1(1,bm);
    assert(em1.allBranchesComplete()==false);
    em1.exploreEdge(ed1,0,bm);
    assert(em1.allBranchesComplete()==true);

    // Lets look at a more complicated example.
    //        - - - - -
    //      |           |
    //  3 - 2 - 5   9 - 8 - 11
    //  |   |   |   |   |   |
    //  0 - 1 - 4 - 6 - 7 - 10 
    Edge ed2(1,2);
    Edge ed3(2,3);
    Edge ed4(0,3);
    Edge ed5(1,4);
    Edge ed6(4,5);
    Edge ed7(2,5);
    Edge ed8(4,6);
    Edge ed9(6,9);
    Edge ed10(6,7);
    Edge ed11(7,8);
    Edge ed12(8,9);
    Edge ed13(7,10);
    Edge ed14(10,11);
    Edge ed15(8,11);
    Edge ed16(2,8);

    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
    list_ed.push_back(ed7);
    list_ed.push_back(ed8);
    list_ed.push_back(ed9);
    list_ed.push_back(ed10);
    list_ed.push_back(ed11);
    list_ed.push_back(ed12);
    list_ed.push_back(ed13);
    list_ed.push_back(ed14);
    list_ed.push_back(ed15);
    list_ed.push_back(ed16);

    _branch_map bm2(list_ed);
    // Exploring from vertex 6
    _exploration_map em2(6,bm2);
    assert(em2.allBranchesComplete()==false);
    em2.exploreEdge(ed8,0,bm2);
    assert(em2.allBranchesComplete()==false);
    em2.exploreEdge(ed6,0,bm2);
    assert(em2.allBranchesComplete()==false);
    em2.exploreEdge(ed7,0,bm2);
    assert(em2.allBranchesComplete()==false);
    em2.exploreEdge(ed10,2,bm2);
    assert(em2.allBranchesComplete()==false);
    em2.exploreEdge(ed11,2,bm2);
    assert(em2.allBranchesComplete()==false);
    em2.exploreEdge(ed9,1,bm2); 
    assert(em2.allBranchesComplete()==false);
  }

  cout << "Testing: getUnexpEdge" << endl;
  {
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
 
    _exploration_map em1(1,bm);
    // Grab from the first branch
    Edge ed = em1.getUnexpEdge(0);
    assert(ed==ed1);
    // Grab from the second branch
    ed = em1.getUnexpEdge(1); 
    assert(ed==ed2);
    // Grab from the third branch
    ed = em1.getUnexpEdge(2);
    assert(ed==ed3);
  }
  
  cout << "Testing: getExploredVertex" << endl;
  {
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
 
    _exploration_map em1(1,bm);
    int vert = em1.getExploredVertex(ed1,0);
    assert(vert==1);
    vert = em1.getExploredVertex(ed2,0);
    assert(vert==-1);
    
    vert = em1.getExploredVertex(ed2,1);
    assert(vert==1);
    vert = em1.getExploredVertex(ed1,1);
    assert(vert==-1);
    vert = em1.getExploredVertex(ed3,1);
    assert(vert==-1);
       
    vert = em1.getExploredVertex(ed3,2);
    assert(vert==1);
    vert = em1.getExploredVertex(ed2,2);
    assert(vert==-1);
    vert = em1.getExploredVertex(ed1,2);
    assert(vert==-1);
  }

  cout << "Testing: getUnexploredVertex" << endl;
  {
    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed3(1,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(4,6);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
  
    _branch_map bm(list_ed);
 
    _exploration_map em1(1,bm);
    int vert = em1.getUnexploredVertex(ed1,0);
    assert(vert==0);
    vert = em1.getUnexploredVertex(ed2,0);
    assert(vert==-1);
    
    vert = em1.getUnexploredVertex(ed2,1);
    assert(vert==2);
    vert = em1.getUnexploredVertex(ed1,1);
    assert(vert==-1);
    vert = em1.getUnexploredVertex(ed3,1);
    assert(vert==-1);
       
    vert = em1.getUnexploredVertex(ed3,2);
    assert(vert==3);
    vert = em1.getUnexploredVertex(ed2,2);
    assert(vert==-1);
    vert = em1.getUnexploredVertex(ed1,2);
    assert(vert==-1);

  }

  cout << "Testing: putBranchOverlapRule" << endl;
  {

//
//          7 - 6 - 5
//          |       |
//  0 - 1 - 2 - 3 - 4
//

    Edge ed1(0,1);
    Edge ed2(1,2);
    Edge ed8(7,2);
    Edge ed3(2,3);
    Edge ed4(3,4);
    Edge ed5(4,5);
    Edge ed6(5,6);
    Edge ed7(6,7);
    
    list<Edge> list_ed;
    list_ed.push_back(ed1);
    list_ed.push_back(ed2);
    list_ed.push_back(ed3);
    list_ed.push_back(ed4);
    list_ed.push_back(ed5);
    list_ed.push_back(ed6);
    list_ed.push_back(ed7);
    list_ed.push_back(ed8);
  
    _branch_map bm(list_ed);

    // Using junction at site id 2 
    _exploration_map em1(2,bm); 
    // Setting up run 
    // 1. grab an edge
    // 2. check if the edge has been explored
    // 3. Explore the edge in both the branch map and exploration map
    
    // Step 1
    Edge ed = em1.getUnexpEdge(1);
    assert(ed==ed3);
    // Step 2
    //int status = bm.branchStatus(ed);
    //assert(status==-1);
    // Step 3
    bm.exploreEdge(ed,1);
    em1.exploreEdge(ed,1,bm);

//          7 - 6 - 5
//          |       |
//  0 - 1 - 2 x 3 - 4

    // Repeat with branch 3
    // Step 1
    ed = em1.getUnexpEdge(2);
    assert(ed==ed8);
    // Step 2
   // status = bm.branchStatus(ed);
    //assert(status==-1);
    // Step 3
    bm.exploreEdge(ed,2);
    em1.exploreEdge(ed,2,bm);

//          7 - 6 - 5
//          x       |
//  0 - 1 - 2 x 3 - 4

    // Repeat with branch 2
    // Step 1
    ed = em1.getUnexpEdge(1);
    assert(ed==ed4);
    // Step 2
    //status = bm.branchStatus(ed);
    //assert(status==-1);
    // Step 3
    bm.exploreEdge(ed,1);
    em1.exploreEdge(ed,1,bm);
    // Repeat with branch 3
    // Step 1
    ed = em1.getUnexpEdge(2);
    assert(ed==ed7);
    // Step 2
    //status = bm.branchStatus(ed);
    //assert(status==-1);
    // Step 3
    bm.exploreEdge(ed,2);
    em1.exploreEdge(ed,2,bm);


//          7 x 6 - 5
//          x       |
//  0 - 1 - 2 x 3 x 4

    cout << "Testing: contestedEdge" << endl;
    // Repeat with branch 2
    // Step 1
    ed = em1.getUnexpEdge(1);
    assert(ed==ed5);
    // Step 2
    //status = bm.branchStatus(ed);
    //assert(status==-1);
    // Step 3 Before exploring let's ensure the edge is
    //        is not contested
    int contested_vert = em1.contestedEdge(1,ed);
    assert(contested_vert==-1);
    bm.exploreEdge(ed,1);
    em1.exploreEdge(ed,1,bm);

    // Repeat with branch 3
    // Step 1
    ed = em1.getUnexpEdge(2);
    assert(ed==ed6);
    // Step 2
    //status = bm.branchStatus(ed);
    //assert(status==-1);
    // Step 3
    contested_vert = em1.contestedEdge(2,ed);
    assert(contested_vert!=-1);
    // This should indicate that the edge is contested 
    // branch 1 already holds vertex 5 so this should be 
    // the value of the contested vertex
    assert(contested_vert==5);


//          7 x 6 x 5
//          x       x
//  0 - 1 - 2 x 3 x 4
//
// At this point all the edges have been explored

    // Repeat with Branch 2
    // Step 1
    ed = em1.getUnexpEdge(1);
    assert(ed==ed6);
    // Step 2
    // Edge 6 has already been explored by branch 3 with id 2
    //status = bm.branchStatus(ed);
    //assert(status==2);
    // Step 3b Now that a branch has already claimed this edge 
    //         we will create an overlap rule or statement that
    //         stores the conflict
    em1.putBranchOverlapRule(1,2,ed);

    cout << "Testing: getBranchOverlapRule" << endl;  
    vector<int>  rule = em1.getBranchOverlapRule(ed);
    assert(rule.at(0)==1);
    assert(rule.at(1)==2);
    assert(rule.at(2)==ed.getV1());
    assert(rule.at(3)==ed.getV2());
    
    cout << "Testing: getOverlappingEdges" << endl;
    vector<Edge> edge_r = em1.getOverlappingEdges(1,2);
    assert(edge_r.at(0)==ed);

    cout << "Testing: getBranchVertices " << endl;
    vector<int> verts_1 = em1.getBranchVertices(1);
    // Check to make sure that vertex 5 and 4 are stored in 
    // branch id 1 (branch 2)
    int count5 = 0;
    int count4 = 0;
    for(auto it=verts_1.begin();it!=verts_1.end();it++){
      if(*it==5){
        count5++;
      }
      if(*it==4){
        count4++;
      }
    }
    assert(count5==1);
    assert(count4==1);
    // Check to make sure that edge 6 is in branch id 1
    vector<Edge> egs_1 = em1.getUnexpEdges(1);
    assert(egs_1.at(0)==ed6);

    vector<int> verts_2 = em1.getBranchVertices(2);
    // Check to make sure that vertex 5 is nost stored in 
    // branch id 2 (branch 3) and that vertex 6 is stored
    // in branch id 2
    count5 = 0;
    int count6 = 0;
    for(auto it=verts_2.begin();it!=verts_2.end();it++){
      if(*it==5){
        count5++;
      }
      if(*it==6){
        count6++;
      }
    }
    assert(count5==0);
    assert(count6==1);

  }

  cout << "Testing: exploreBranches" << endl;
  {

    cout << "Test 1" << endl;
    {
    //
    // 0 - 1 - 2 
    //

    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      vector<vector<int>> vd = em1.getVertDistances(0);
      
      // Check that the first vertex is 0 
      assert(vd.at(0).at(0)==0);
      // Check that the distance of vertex 0 is 0
      assert(vd.at(0).at(1)==0);    
      
      // Check that the second vertex is 1
      assert(vd.at(1).at(0)==1);
      // Check that the distance of vertex 1 is 1
      assert(vd.at(1).at(1)==1);    
        
      // Check that the third vertex is 2
      assert(vd.at(2).at(0)==2);
      // Check that the distance of vertex 2 is 2
      assert(vd.at(2).at(1)==2);    
      
    }

    cout << "Test 2" << endl;
    {
    //
    //     3
    //     |
    // 0 - 1 - 2 
    //

    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(1,3);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      vector<vector<int>> vd = em1.getVertDistances(0);
      
      assert(vd.size()==4); 
      // Check that the first vertex is 0 
      assert(vd.at(0).at(0)==0);
      // Check that the distance of vertex 0 is 0
      assert(vd.at(0).at(1)==0);    
      
      // Check that the second vertex is 1
      assert(vd.at(1).at(0)==1);
      // Check that the distance of vertex 1 is 1
      assert(vd.at(1).at(1)==1);    
        
      // Check that the third vertex is 2
      assert(vd.at(2).at(0)==2);
      // Check that the distance of vertex 2 is 2
      assert(vd.at(2).at(1)==2);    
      
      // Check that the fourth vertex is 3
      assert(vd.at(3).at(0)==3);
      // Check that the distance of vertex 3 is 2
      assert(vd.at(3).at(1)==2);   

      // Changing location of junction to vertex id 1
      _exploration_map em2(1,bm);
      rv = em2.exploreBranches(bm);
      assert(rv==1);
      assert(em2.getNumBranches()==3);
      // Grabbing the vertices that are in branch 0
      vector<vector<int>> vd2 = em2.getVertDistances(0);
      // Should be two vertices
      assert(vd2.size()==2);
 
      // id of first vertex
      assert(vd2.at(0).at(0)==1);
      // dist from junction of first vertex
      assert(vd2.at(0).at(1)==0);

      // id of second vertex
      assert(vd2.at(1).at(0)==0);
      // dist from junction of second vertex
      assert(vd2.at(1).at(1)==1);
 
      // Grabbing the vertices that are in branch 1
      vector<vector<int>> vd3 = em2.getVertDistances(1);
      // Should be two vertices
      assert(vd3.size()==2);
 
      // id of first vertex
      assert(vd3.at(0).at(0)==1);
      // dist from junction of first vertex
      assert(vd3.at(0).at(1)==0);

      // id of second vertex
      assert(vd3.at(1).at(0)==2);
      // dist from junction of second vertex
      assert(vd3.at(1).at(1)==1);
 
      // Grabbing the vertices that are in branch 2
      vector<vector<int>> vd4 = em2.getVertDistances(2);
      // Should be two vertices
      assert(vd4.size()==2);
 
      // id of first vertex
      assert(vd4.at(0).at(0)==1);
      // dist from junction of first vertex
      assert(vd4.at(0).at(1)==0);

      // id of second vertex
      assert(vd4.at(1).at(0)==3);
      // dist from junction of second vertex
      assert(vd4.at(1).at(1)==1);
     
    }

    cout << "Test 3" << endl;
    {
    //
    // 1 - 2 - 3
    // |       |
    // 0 - 5 - 4
    //         
    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(4,5);
      Edge ed6(5,0);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
 
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      assert(em1.getNumBranches()==2);

      // Grab branch id 0
      vector<vector<int>> vd = em1.getVertDistances(0);
      
      assert(vd.size()==4); 
      // Check that the first vertex is 0 
      assert(vd.at(0).at(0)==0);
      // Check that the distance of vertex 0 is 0
      assert(vd.at(0).at(1)==0);    
 
      assert(vd.at(1).at(0)==1);
      assert(vd.at(1).at(1)==1);    
 
      assert(vd.at(2).at(0)==2);
      assert(vd.at(2).at(1)==2);    

      assert(vd.at(3).at(0)==3);
      assert(vd.at(3).at(1)==3);
 
      // Grab branch id 0
      vector<vector<int>> vd2 = em1.getVertDistances(1);
     
      assert(vd2.size()==3); 
      // Check that the first vertex is 0 
      assert(vd2.at(0).at(0)==0);
      // Check that the distance of vertex 0 is 0
      assert(vd2.at(0).at(1)==0);    
 
      assert(vd2.at(1).at(0)==5);
      assert(vd2.at(1).at(1)==1);    
 
      assert(vd2.at(2).at(0)==4);
      assert(vd2.at(2).at(1)==2);    
 
      vector<vector<int>>  Rules = em1.getBranchOverlapRules();
      assert(Rules.size()==1);
      assert(Rules.at(0).at(0)==1);    
      assert(Rules.at(0).at(1)==0);    
      if(Rules.at(0).at(2)==4){
          assert(Rules.at(0).at(3)==3);    
      }else{
          assert(Rules.at(0).at(2)==3);    
          assert(Rules.at(0).at(3)==4);    
      }
    }
   
    cout << "Test 4" << endl;
    {
    //
    // 1 - 2 - 3 - 9 - 8
    // |       |       |
    // 0 - 5 - 4 - 6 - 7
    //         
    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(4,5);
      Edge ed6(5,0);
      Edge ed7(4,6);
      Edge ed8(6,7);
      Edge ed9(7,8);
      Edge ed10(8,9);
      Edge ed11(9,3);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);
      list_ed.push_back(ed7);
      list_ed.push_back(ed8);
      list_ed.push_back(ed9);
      list_ed.push_back(ed10);
      list_ed.push_back(ed11);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
 
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      assert(em1.getNumBranches()==2);

      // Grab branch id 0
      vector<vector<int>> vd = em1.getVertDistances(0);

      assert(vd.size()==6);

      assert(vd.at(0).at(0)==0);
      assert(vd.at(0).at(1)==0);

      assert(vd.at(1).at(0)==1);
      assert(vd.at(1).at(1)==1);

      assert(vd.at(2).at(0)==2);
      assert(vd.at(2).at(1)==2);

      assert(vd.at(3).at(0)==3);
      assert(vd.at(3).at(1)==3);

      assert(vd.at(4).at(0)==9);
      assert(vd.at(4).at(1)==4);

      assert(vd.at(5).at(0)==8);
      assert(vd.at(5).at(1)==5);

      vector<vector<int>> vd2 = em1.getVertDistances(1);

      assert(vd2.size()==5);

      assert(vd2.at(0).at(0)==0);
      assert(vd2.at(0).at(1)==0);

      assert(vd2.at(1).at(0)==5);
      assert(vd2.at(1).at(1)==1);

      assert(vd2.at(2).at(0)==4);
      assert(vd2.at(2).at(1)==2);

      assert(vd2.at(3).at(0)==6);
      assert(vd2.at(3).at(1)==3);

      assert(vd2.at(4).at(0)==7);
      assert(vd2.at(4).at(1)==4);

      vector<vector<int>>  Rules = em1.getBranchOverlapRules();
      assert(Rules.size()==2);
      assert(Rules.at(0).at(0)==1);    
      assert(Rules.at(0).at(1)==0);    
      if(Rules.at(0).at(2)==4){
          assert(Rules.at(0).at(3)==3);    
      }else{
          assert(Rules.at(0).at(2)==3);    
          assert(Rules.at(0).at(3)==4);    
      }

      assert(Rules.at(1).at(0)==0);    
      assert(Rules.at(1).at(1)==1);    
      if(Rules.at(1).at(2)==7){
          assert(Rules.at(1).at(3)==8);    
      }else{
          assert(Rules.at(1).at(2)==8);    
          assert(Rules.at(1).at(3)==7);    
      }
            
    // Explore using a different starting point

    //
    // 1 - 2 - 3 - 9 - 8
    // |       |       |
    // 0 - 5 - 4 - 6 - 7
    //         
      //cerr << "########################################################" << endl;
      // Using 5 as the starting vertex
      _exploration_map em2(5,bm);
 
      rv = em2.exploreBranches(bm);
      assert(rv==1);
      assert(em2.getNumBranches()==2);

      // Grab branch id 0
      vector<vector<int>> vd3 = em2.getVertDistances(0);
      assert(vd3.size()==7);
      
      assert(vd3.at(0).at(0)==5);
      assert(vd3.at(0).at(1)==0);

      assert(vd3.at(1).at(0)==4);
      assert(vd3.at(1).at(1)==1);

      assert(vd3.at(2).at(0)==3);
      assert(vd3.at(2).at(1)==2);

      assert(vd3.at(3).at(0)==6);
      assert(vd3.at(3).at(1)==2);

      assert(vd3.at(4).at(0)==9);
      assert(vd3.at(4).at(1)==3);

      assert(vd3.at(5).at(0)==7);
      assert(vd3.at(5).at(1)==3);

      assert(vd3.at(6).at(0)==8);
      assert(vd3.at(6).at(1)==4);

      // Grab branch id 1
      vector<vector<int>> vd4 = em2.getVertDistances(1);
      assert(vd4.size()==4);
      
      assert(vd4.at(0).at(0)==5);
      assert(vd4.at(0).at(1)==0);

      assert(vd4.at(1).at(0)==0);
      assert(vd4.at(1).at(1)==1);

      assert(vd4.at(2).at(0)==1);
      assert(vd4.at(2).at(1)==2);

      assert(vd4.at(3).at(0)==2);
      assert(vd4.at(3).at(1)==3);

      vector<vector<int>>  Rules2 = em2.getBranchOverlapRules();
      assert(Rules2.size()==1);
      assert(Rules2.at(0).at(0)==0);    
      assert(Rules2.at(0).at(1)==1);    
      if(Rules2.at(0).at(2)==2){
          assert(Rules2.at(0).at(3)==3);
      }else{
          assert(Rules2.at(0).at(2)==3);    
          assert(Rules2.at(0).at(3)==2);    
      }
      // Explore using a different starting point

    //
    // 1 - 2 - 3 - 9 - 8
    // |       |       |
    // 0 - 5 - 4 - 6 - 7
    //         
      //cerr << "########################################################" << endl;
      // Using 4 as the starting vertex
      _exploration_map em3(4,bm);
 
      rv = em3.exploreBranches(bm);
      assert(rv==1);
      assert(em3.getNumBranches()==3);

      // Grab branch id 0
      vector<vector<int>> vd5 = em3.getVertDistances(0);

      assert(vd5.size()==4);

      assert(vd5.at(0).at(0)==4);
      assert(vd5.at(0).at(1)==0);

      assert(vd5.at(1).at(0)==3);
      assert(vd5.at(1).at(1)==1);

      assert(vd5.at(2).at(0)==2);
      assert(vd5.at(2).at(1)==2);

      assert(vd5.at(3).at(0)==9);
      assert(vd5.at(3).at(1)==2);

      // Grab branch id 1
      vector<vector<int>> vd6 = em3.getVertDistances(1);

      assert(vd6.size()==4);

      assert(vd6.at(0).at(0)==4);
      assert(vd6.at(0).at(1)==0);

      assert(vd6.at(1).at(0)==5);
      assert(vd6.at(1).at(1)==1);

      assert(vd6.at(2).at(0)==0);
      assert(vd6.at(2).at(1)==2);

      assert(vd6.at(3).at(0)==1);
      assert(vd6.at(3).at(1)==3);

      // Grab branch id 2
      vector<vector<int>> vd7 = em3.getVertDistances(2);

      assert(vd7.size()==4);

      assert(vd7.at(0).at(0)==4);
      assert(vd7.at(0).at(1)==0);

      assert(vd7.at(1).at(0)==6);
      assert(vd7.at(1).at(1)==1);

      assert(vd7.at(2).at(0)==7);
      assert(vd7.at(2).at(1)==2);

      assert(vd7.at(3).at(0)==8);
      assert(vd7.at(3).at(1)==3);

      vector<vector<int>>  Rules3 = em3.getBranchOverlapRules();
      assert(Rules3.size()==2);
      assert(Rules3.at(0).at(0)==0);    
      assert(Rules3.at(0).at(1)==1);    
      if(Rules3.at(0).at(2)==1){
          assert(Rules3.at(0).at(3)==2);    
      }else{
          assert(Rules3.at(0).at(2)==2);    
          assert(Rules3.at(0).at(3)==1);    
      }
      assert(Rules3.at(1).at(0)==2);    
      assert(Rules3.at(1).at(1)==0);    
      if(Rules3.at(1).at(2)==9){
          assert(Rules3.at(1).at(3)==8);    
      }else{
          assert(Rules3.at(1).at(2)==8);    
          assert(Rules3.at(1).at(3)==9);    
      } 
    }

    cout << "Test 5" << endl;
    {
      // Lets look at a more complicated example.
      //        - - - - -
      //      |           |
      //  3 - 2 - 5   9 - 8 - 11
      //  |   |   |   |   |   |
      //  0   1 - 4 - 6 - 7 - 10 
      //Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(0,3);
      Edge ed5(1,4);
      Edge ed6(4,5);
      Edge ed7(2,5);
      Edge ed8(4,6);
      Edge ed9(6,9);
      Edge ed10(6,7);
      Edge ed11(7,8);
      Edge ed12(8,9);
      Edge ed13(7,10);
      Edge ed14(10,11);
      Edge ed15(8,11);
      Edge ed16(2,8);

      list<Edge> list_ed;
      //list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);
      list_ed.push_back(ed7);
      list_ed.push_back(ed8);
      list_ed.push_back(ed9);
      list_ed.push_back(ed10);
      list_ed.push_back(ed11);
      list_ed.push_back(ed12);
      list_ed.push_back(ed13);
      list_ed.push_back(ed14);
      list_ed.push_back(ed15);
      list_ed.push_back(ed16);

      _branch_map bm2(list_ed);

      _exploration_map em2(6,bm2);
 
      int rv = em2.exploreBranches(bm2);
      assert(rv==1);
      assert(em2.getNumBranches()==3);

      assert(em2.allBranchesComplete()==true);



    }
  }

  cout << "Testing: mergeAllOverlapRules" << endl;
  {
    cout << "Test 1" << endl;
    {
      //
      //     3
      //     |
      // 0 - 1 - 2 
      //

      // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(1,3);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
      int rv = em1.exploreBranches(bm);
      assert(rv==1);

      em1.mergeAllOverlapRules(bm);
      // All the branches should be the same as before the merge
      vector<vector<int>> vd = em1.getVertDistances(0);
      
 
      assert(vd.size()==4); 

      assert(vd.at(0).at(0)==0);
      assert(vd.at(0).at(1)==0);    
      
      assert(vd.at(1).at(0)==1);
      assert(vd.at(1).at(1)==1);    
        
      assert(vd.at(2).at(0)==2);
      assert(vd.at(2).at(1)==2);    
      
      assert(vd.at(3).at(0)==3);
      assert(vd.at(3).at(1)==2);   

      // Check the branch identifiers are correctly configures
      // Because there was only one branch the vertices should
      // all be claimed by branch 0
      vector<int> brIdent0 = em1.getBranchIdentifiers(0,0); 
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,1); 
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,2); 
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,3); 
      assert(brIdent0.at(0)==0);

      // Changing location of junction to vertex id 1
      _exploration_map em2(1,bm);
      rv = em2.exploreBranches(bm);
      assert(rv==1);
      assert(em2.getNumBranches()==3);
      
      vector<vector<int>> vd2 = em2.getVertDistances(0);
      // Should be two vertices
      assert(vd2.size()==2);
 
      assert(vd2.at(0).at(0)==1);
      assert(vd2.at(0).at(1)==0);

      assert(vd2.at(1).at(0)==0);
      assert(vd2.at(1).at(1)==1);

      // Non of the branches overlap so each vetex should 
      // be claimed by a single branch identifier 
      brIdent0 = em2.getBranchIdentifiers(0,0);
      assert(brIdent0.at(0)==0);
      brIdent0 = em2.getBranchIdentifiers(0,1);
      assert(brIdent0.at(0)==0);
 
      // Grabbing the vertices that are in branch 1
      vector<vector<int>> vd3 = em2.getVertDistances(1);
      // Should be two vertices
      assert(vd3.size()==2);
 
      assert(vd3.at(0).at(0)==1);
      assert(vd3.at(0).at(1)==0);

      assert(vd3.at(1).at(0)==2);
      assert(vd3.at(1).at(1)==1);
 
      brIdent0 = em2.getBranchIdentifiers(1,1);
      assert(brIdent0.at(0)==1);
      brIdent0 = em2.getBranchIdentifiers(1,1);
      assert(brIdent0.at(0)==1);

      // Grabbing the vertices that are in branch 2
      vector<vector<int>> vd4 = em2.getVertDistances(2);
      // Should be two vertices
      assert(vd4.size()==2);
 
      assert(vd4.at(0).at(0)==1);
      assert(vd4.at(0).at(1)==0);

      assert(vd4.at(1).at(0)==3);
      assert(vd4.at(1).at(1)==1);
 
      brIdent0 = em2.getBranchIdentifiers(2,1);
      assert(brIdent0.at(0)==2);
      brIdent0 = em2.getBranchIdentifiers(2,3);
      assert(brIdent0.at(0)==2);
    }

    cout << "Test 2" << endl;
    {
    //
    // 1 - 2 - 3
    // |       |
    // 0 - 5 - 4
    //         
    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(4,5);
      Edge ed6(5,0);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
 
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      assert(em1.getNumBranches()==2);

      em1.mergeAllOverlapRules(bm);
      
      assert(em1.getNumBranches()==1);

      // Grab branch id 0
      vector<vector<int>> vd = em1.getVertDistances(0);
      
      assert(vd.size()==6); 
      // Check that the first vertex is 0 
      assert(vd.at(0).at(0)==0);
      // Check that the distance of vertex 0 is 0
      assert(vd.at(0).at(1)==0);    
 
      assert(vd.at(1).at(0)==1);
      assert(vd.at(1).at(1)==1);    
 
      assert(vd.at(2).at(0)==2);
      assert(vd.at(2).at(1)==2);    

      assert(vd.at(3).at(0)==3);
      assert(vd.at(3).at(1)==3);
      
      assert(vd.at(4).at(0)==5);
      assert(vd.at(4).at(1)==1);
    
      assert(vd.at(5).at(0)==4);
      assert(vd.at(5).at(1)==2);

      // Grab identifiers from branch 0 because it is 
      // a loop the other branches will have been merged 
      // this does not mean that the branch identifier has been
      // changed to 0 though. 

      vector<int> brIdent0 = em1.getBranchIdentifiers(0,0);
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,1);
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,2);
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,3);
      assert(brIdent0.at(0)==0);
      // Here the identifier changes to 1 because it was originally
      // explored by branch 1 this also makes it possible to distinguish
      // between different positions within the molecule 
      brIdent0 = em1.getBranchIdentifiers(0,4);
      assert(brIdent0.at(0)==1);
      brIdent0 = em1.getBranchIdentifiers(0,5);
      assert(brIdent0.at(0)==1);

      vector<vector<int>>  Rules = em1.getBranchOverlapRules();
      assert(Rules.size()==0);
    }
   
    cout << "Test 3" << endl;
    {
    //
    // 1 - 2 - 3 - 9 - 8
    // |       |       |
    // 0 - 5 - 4 - 6 - 7
    //         
    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(4,5);
      Edge ed6(5,0);
      Edge ed7(4,6);
      Edge ed8(6,7);
      Edge ed9(7,8);
      Edge ed10(8,9);
      Edge ed11(9,3);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);
      list_ed.push_back(ed7);
      list_ed.push_back(ed8);
      list_ed.push_back(ed9);
      list_ed.push_back(ed10);
      list_ed.push_back(ed11);

      _branch_map bm(list_ed);

      // Using 0 as the starting vertex
      _exploration_map em1(0,bm);
 
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      assert(em1.getNumBranches()==2);

      em1.mergeAllOverlapRules(bm);
      
      assert(em1.getNumBranches()==1);
      // Grab branch id 0
      vector<vector<int>> vd = em1.getVertDistances(0);

      assert(vd.size()==10);

      assert(vd.at(0).at(0)==0);
      assert(vd.at(0).at(1)==0);

      assert(vd.at(1).at(0)==1);
      assert(vd.at(1).at(1)==1);

      assert(vd.at(2).at(0)==2);
      assert(vd.at(2).at(1)==2);

      assert(vd.at(3).at(0)==3);
      assert(vd.at(3).at(1)==3);

      assert(vd.at(4).at(0)==9);
      assert(vd.at(4).at(1)==4);

      assert(vd.at(5).at(0)==8);
      assert(vd.at(5).at(1)==5);

      assert(vd.at(6).at(0)==5);
      assert(vd.at(6).at(1)==1);

      assert(vd.at(7).at(0)==4);
      assert(vd.at(7).at(1)==2);

      assert(vd.at(8).at(0)==6);
      assert(vd.at(8).at(1)==3);

      assert(vd.at(9).at(0)==7);
      assert(vd.at(9).at(1)==4);

      // This will be a little more complicated 

      // Exploration by only branch 0 
      vector<int> brIdent0 = em1.getBranchIdentifiers(0,0);
      assert(brIdent0.size()==2);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.at(1)==1);
      brIdent0 = em1.getBranchIdentifiers(0,1);
      assert(brIdent0.at(0)==0);
      brIdent0 = em1.getBranchIdentifiers(0,2);
      assert(brIdent0.at(0)==0);

      // The following vertices should have been 
      // explored by both branches 
      brIdent0 = em1.getBranchIdentifiers(0,3);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.at(1)==1);
      brIdent0 = em1.getBranchIdentifiers(0,8);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.at(1)==1);
      brIdent0 = em1.getBranchIdentifiers(0,9);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.at(1)==1);
      
      // Exploration only by branch 1
      brIdent0 = em1.getBranchIdentifiers(0,4);
      assert(brIdent0.at(0)==1);
      brIdent0 = em1.getBranchIdentifiers(0,5);
      assert(brIdent0.at(0)==1);
      brIdent0 = em1.getBranchIdentifiers(0,6);
      assert(brIdent0.at(0)==1);
      brIdent0 = em1.getBranchIdentifiers(0,7);
      assert(brIdent0.at(0)==1);

      vector<vector<int>>  Rules = em1.getBranchOverlapRules();
      assert(Rules.size()==0);
 
    // Explore using a different starting point

    //
    // 1 - 2 - 3 - 9 - 8
    // |       |       |
    // 0 - 5 - 4 - 6 - 7
    //         
      //cerr << "########################################################" << endl;
      // Using 4 as the starting vertex
      _exploration_map em3(4,bm);
 
      rv = em3.exploreBranches(bm);
      assert(rv==1);
      assert(em3.getNumBranches()==3);

      em3.mergeAllOverlapRules(bm);
      
      assert(em3.getNumBranches()==1);
      // Grab branch id 0
      vector<vector<int>> vd5 = em3.getVertDistances(0);

      assert(vd5.size()==10);

      assert(vd5.at(0).at(0)==4);
      assert(vd5.at(0).at(1)==0);

      assert(vd5.at(1).at(0)==3);
      assert(vd5.at(1).at(1)==1);

      assert(vd5.at(2).at(0)==2);
      assert(vd5.at(2).at(1)==2);

      assert(vd5.at(3).at(0)==9);
      assert(vd5.at(3).at(1)==2);

      assert(vd5.at(4).at(0)==5);
      assert(vd5.at(4).at(1)==1);

      assert(vd5.at(5).at(0)==0);
      assert(vd5.at(5).at(1)==2);

      assert(vd5.at(6).at(0)==1);
      assert(vd5.at(6).at(1)==3);

      assert(vd5.at(7).at(0)==6);
      assert(vd5.at(7).at(1)==1);

      assert(vd5.at(8).at(0)==7);
      assert(vd5.at(8).at(1)==2);

      assert(vd5.at(9).at(0)==8);
      assert(vd5.at(9).at(1)==3);

      vector<vector<int>>  Rules3 = em3.getBranchOverlapRules();
      assert(Rules3.size()==0);

      // Exploration by only branch 0 
      brIdent0 = em3.getBranchIdentifiers(0,4);
      assert(brIdent0.size()==3);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.at(1)==1);
      assert(brIdent0.at(2)==2);

      //         3 b0
      //          ^
      //          |
      // 5 b1 <- 4 b0 -> 6 b2

      brIdent0 = em3.getBranchIdentifiers(0,5);
      assert(brIdent0.at(0)==1);
      assert(brIdent0.size()==1);
      brIdent0 = em3.getBranchIdentifiers(0,3);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.size()==1);
      brIdent0 = em3.getBranchIdentifiers(0,6);
      assert(brIdent0.at(0)==2);
      assert(brIdent0.size()==1);

      // branch 0 
      brIdent0 = em3.getBranchIdentifiers(0,2);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.size()==1);
      brIdent0 = em3.getBranchIdentifiers(0,9);
      assert(brIdent0.at(0)==0);
      assert(brIdent0.size()==1);
      // Vertex 8 and 1 should be shared
      brIdent0 = em3.getBranchIdentifiers(0,1);
      assert(brIdent0.size()==2);
      assert(brIdent0.at(0)==1);
      assert(brIdent0.at(1)==0);
      brIdent0 = em3.getBranchIdentifiers(0,8);
      assert(brIdent0.size()==2);
      assert(brIdent0.at(0)==2);
      assert(brIdent0.at(1)==0);
     
      // branch 1 
      brIdent0 = em3.getBranchIdentifiers(0,0);
      assert(brIdent0.size()==1);
      assert(brIdent0.at(0)==1);
      
      // branch 2
      brIdent0 = em3.getBranchIdentifiers(0,7);
      assert(brIdent0.size()==1);
      assert(brIdent0.at(0)==2);
    }

     cout << "Test 4" << endl;
    {
    //
    // 1 - 2 - 3       8 - 9 - 10 
    // |       |       |       |
    // 0 - 5 - 4 - 6 - 7 -12 - 11
    //         
    // Creating a list of edges
      Edge ed1(0,1);
      Edge ed2(1,2);
      Edge ed3(2,3);
      Edge ed4(3,4);
      Edge ed5(4,5);
      Edge ed6(5,0);
      Edge ed7(4,6);
      Edge ed8(6,7);
      Edge ed9(7,8);
      Edge ed10(8,9);
      Edge ed11(9,10);
      Edge ed12(10,11);
      Edge ed13(11,12);
      Edge ed14(12,7);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);
      list_ed.push_back(ed7);
      list_ed.push_back(ed8);
      list_ed.push_back(ed9);
      list_ed.push_back(ed10);
      list_ed.push_back(ed11);
      list_ed.push_back(ed12);
      list_ed.push_back(ed13);
      list_ed.push_back(ed14);

      _branch_map bm(list_ed);

      // Using 4 as the starting vertex
      _exploration_map em1(4,bm);
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      assert(em1.getNumBranches()==3);

      em1.mergeAllOverlapRules(bm);
      
      assert(em1.getNumBranches()==2);
      // Grab branch id 0
      vector<vector<int>> vd = em1.getVertDistances(0);

      assert(vd.size()==6);

      assert(vd.at(0).at(0)==4);
      assert(vd.at(0).at(1)==0);

      assert(vd.at(1).at(0)==3);
      assert(vd.at(1).at(1)==1);

      assert(vd.at(2).at(0)==2);
      assert(vd.at(2).at(1)==2);

      assert(vd.at(3).at(0)==1);
      assert(vd.at(3).at(1)==3);

      assert(vd.at(4).at(0)==5);
      assert(vd.at(4).at(1)==1);

      assert(vd.at(5).at(0)==0);
      assert(vd.at(5).at(1)==2);

      vector<vector<int>> vd2 = em1.getVertDistances(1);

      assert(vd2.size()==8);
  
      assert(vd2.at(0).at(0)==4);
      assert(vd2.at(0).at(1)==0);
     
      assert(vd2.at(1).at(0)==6);
      assert(vd2.at(1).at(1)==1);
      
      assert(vd2.at(2).at(0)==7);
      assert(vd2.at(2).at(1)==2);
      
      assert(vd2.at(3).at(0)==8);
      assert(vd2.at(3).at(1)==3);
      
      assert(vd2.at(4).at(0)==12);
      assert(vd2.at(4).at(1)==3);
      
      assert(vd2.at(5).at(0)==9);
      assert(vd2.at(5).at(1)==4);
      
      assert(vd2.at(6).at(0)==11);
      assert(vd2.at(6).at(1)==4);
      
      assert(vd2.at(7).at(0)==10);
      assert(vd2.at(7).at(1)==5);
      vector<vector<int>>  Rules = em1.getBranchOverlapRules();
      assert(Rules.size()==0);
    }

    cout << "Test 5" << endl;
    {
    //      - - - - - -
    //     |           |
    // 3 - 2 - 5   9 - 8 - 11 
    // |   |   |   |   |   |
    // 0 - 1 - 4 - 6 - 7 -10
    //         
    // Creating a list of edges
      Edge ed1(2,3);
      Edge ed2(2,1);
      Edge ed3(2,5);
      Edge ed4(2,8);
      Edge ed5(3,0);
      Edge ed6(0,1);
      Edge ed7(1,4);
      Edge ed8(5,4);
      Edge ed9(4,6);
      Edge ed10(6,7);
      Edge ed11(6,9);
      Edge ed12(8,7);
      Edge ed13(8,9);
      Edge ed14(8,11);
      Edge ed15(7,10);
      Edge ed16(11,10);

      list<Edge> list_ed;
      list_ed.push_back(ed1);
      list_ed.push_back(ed2);
      list_ed.push_back(ed3);
      list_ed.push_back(ed4);
      list_ed.push_back(ed5);
      list_ed.push_back(ed6);
      list_ed.push_back(ed7);
      list_ed.push_back(ed8);
      list_ed.push_back(ed9);
      list_ed.push_back(ed10);
      list_ed.push_back(ed11);
      list_ed.push_back(ed12);
      list_ed.push_back(ed13);
      list_ed.push_back(ed14);
      list_ed.push_back(ed15);
      list_ed.push_back(ed16);

      _branch_map bm(list_ed);

      // Using 2 as the starting vertex
      _exploration_map em1(2,bm);
      int rv = em1.exploreBranches(bm);
      assert(rv==1);
      em1.mergeAllOverlapRules(bm);
      assert(em1.getNumBranches()==1);
      vector<int> vertsall = em1.getBranchVertices(0);
      assert(vertsall.size()==12);

      _branch_map bm2(list_ed);
      _exploration_map em2(1,bm2);
      rv = em2.exploreBranches(bm2);
      assert(rv==1);
      em2.mergeAllOverlapRules(bm2);
      assert(em2.getNumBranches()==1);
      vertsall = em2.getBranchVertices(0);
      assert(vertsall.size()==12);
 
      _branch_map bm3(list_ed);
      _exploration_map em3(4,bm3);
      rv = em3.exploreBranches(bm3);
      assert(rv==1);
      em3.mergeAllOverlapRules(bm3);
      assert(em3.getNumBranches()==1);
      vertsall = em3.getBranchVertices(0);
      assert(vertsall.size()==12);
 
      _branch_map bm4(list_ed);
      _exploration_map em4(6,bm4);
      rv = em4.exploreBranches(bm4);
      assert(rv==1);
      vector<vector<int>>  Rules = em4.getBranchOverlapRules();

      em4.mergeAllOverlapRules(bm4);
      assert(em4.getNumBranches()==1);

      _branch_map bm5(list_ed);
       _exploration_map em5(8,bm5);
      rv = em5.exploreBranches(bm5);
      assert(rv==1);
      em5.mergeAllOverlapRules(bm5);
      assert(em5.getNumBranches()==1);
     
      _branch_map bm6(list_ed);
       _exploration_map em6(7,bm6);
      rv = em6.exploreBranches(bm6);
      assert(rv==1);
      em6.mergeAllOverlapRules(bm6);
      assert(em6.getNumBranches()==1);
      
    }

  }
  return 0;
}
