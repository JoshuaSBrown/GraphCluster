
#include <iostream>
#include <list>
#include <cassert>
#include <vector>
#include "../CPP_ListContainerTemplate/ListContainerTemplate.hpp"
#include "../CPP_EdgeClass/EdgeClass.hpp"
#include "EdgesClass.hpp"

using namespace std;

// Internal Functions
int findIndNodeVert_Bonds(vector<vector<int>> vert_bonds,
                          int node_id){
  int index = 0;
  for(auto it=vert_bonds.begin();it!=vert_bonds.end();++it){
    if(it->at(0)==node_id) return index;
    index++;
  }
}

int findMatIndexNode(vector<vector<int>> mat, int vert,int vert_nei){

  int index=0;
  for(auto it=mat.begin();it!=mat.end();it++){
    if(it->at(0)==vert && it->at(1)==vert_nei){
      return index;
    }
    if(it->at(0)==vert_nei && it->at(1)==vert){
      return index;
    }
    index++;
  }
  // Returns -1 if the edge does not appear to exist
  return -1;
}

void printVecVec(vector<vector<int>> mat){
  for(auto it=mat.begin();it!=mat.end();it++){
    for(auto it2=it->begin();it2!=it->end();it2++){
      cout << *it2 << " ";
    }
    cout << endl;
  }
}

bool vertexExist(vector<int> branch, int vertex){
  for(auto ver=branch.begin();ver!=branch.end();++ver){
    if(*ver==vertex){
      return true;
    }
  }
  return false;
}

// Add one vector into another non redundantly meaning if an element
// already exists in target it is not added. 
void addVecNonRedundant( vector<int>& target, vector<int> addition){

  for(auto it=addition.begin();it!=addition.end();++it){
    bool unique = true;
    for(auto it2=target.begin();it2!=target.end();++it2){
      if(*it2==*it) {
        unique = false;
      }
    } 
    if(unique) target.push_back(*it);
  }

}

// This function is designed to remove elements across two pairs of 
// vectors that match. For instance if A1(1) = 1 and A2(1) = 3 and
// B1(4) = 3 and B2(4) = 1 it would remove the elements from all
// the A vectors at index 1 and all the elements from B vectors at
// index 4. Notice the order does not matter
void removeMatching(vector<int>& A,
                    vector<int>& A_vert,
                    vector<int>& B,
                    vector<int>& B_vert){

  vector<bool> A_keep;
  A_keep.resize(A.size());
  vector<bool> B_keep;
  B_keep.resize(B.size());

  for(auto it=A_keep.begin();it!=A_keep.end();++it){
    *it=true;
  }
  for(auto it=B_keep.begin();it!=B_keep.end();++it){
    *it=true;
  }


  for(int index=0;index<A.size();index++){
    bool remove = false;
    for(int index2=0;index2<B.size();index2++){
      if(A.at(index)==B.at(index2) && A_vert.at(index)==B_vert.at(index2)){
        A_keep.at(index) = false; 
        B_keep.at(index2) = false;
        break;
      }
      if(A.at(index)==B_vert.at(index2) && A_vert.at(index)==B.at(index2)){
        A_keep.at(index) = false; 
        B_keep.at(index2) = false;
        break;
      }
    }
  }


  vector<int> temp_A;
  vector<int> temp_A_vert;
  for(int index=0;index<A.size();index++){
    if(A_keep.at(index)){
      temp_A.push_back(A.at(index));
      temp_A_vert.push_back(A_vert.at(index));
    }
  }
    
  vector<int> temp_B;
  vector<int> temp_B_vert;
  for(int index=0;index<B.size();index++){
    if(B_keep.at(index)){
      temp_B.push_back(B.at(index));
      temp_B_vert.push_back(B_vert.at(index));
    }
  }
 
  // Overwrite the original vectors with the ones that do not
  // have redundant values
  A = temp_A;
  A_vert = temp_A_vert;
  B = temp_B;
  B_vert = temp_B_vert;

}

// Here we are going to add all the elements in addition to the
// target vector
void mergeVec(vector<int>& target, vector<int>& addition){
  for(auto it=addition.begin();it!=addition.end();++it){
    target.push_back(*it);
  }
}

// MergeBranches is called when it discovered that an edge has
// already been explored. This indicates that another branch
// must have explored the edge and thus two branches must be
// part of the same branch.  
void mergeBranches(vector<vector<int>>& unex_edge,
              vector<vector<int>>& exp_vert,
              vector<vector<int>>& vert_bonds,
              vector<vector<int>>& branches,
              int branch_ind,
              int start_ind,
              int neigh_vert_curr){

  int num_branches = vert_bonds.at(start_ind).at(1);

  // Step 1 Cycle through the branches
  for(int branch_ind2=0;branch_ind2<num_branches;branch_ind2++){

    cout << "Third for loop " << endl;
    cout << "unex vert " << neigh_vert_curr << endl;
    // Simply look for the vertices that are within the branch and
    // compare it with the unexplored vertex from the current branch
    if(branch_ind2!=branch_ind){
      // Checking different branch
  
      //cout << "Branch indices " << branch_ind << " " << branch_ind2 << endl;
      // Step 2
      // Determine if the branch_ind2 is pointing to the branch that
      // shares neigh_vert_curr
      bool merge = vertexExist(branches.at(branch_ind2),neigh_vert_curr);

      // If the vertex was found in branch_ind2 we now have the correct
      // branches ( branch_ind, branch_ind2 ) which must now be merged

      if(merge){
        // Determine which branch id is smaller
        int s_branch;
        int l_branch;
        if(branch_ind2<branch_ind){
          s_branch = branch_ind2;
          l_branch = branch_ind;
        }else{
          l_branch = branch_ind2;
          s_branch = branch_ind;
        }

        // Merge the larger into the smaller
        // Step 3 is to add the vertices in l_branch into the s_branch
        addVecNonRedundant(branches.at(s_branch),branches.at(l_branch));
        
        // Erase all the vertices in the large branch
        branches.at(l_branch).clear();

        // Step 4 is to check to see if any of the unexplored
        // edges/bonds are shared between the two branches if they
        // are they will be removed
        removeMatching(unex_edge.at(l_branch),
                       exp_vert.at(l_branch),
                       unex_edge.at(s_branch),
                       exp_vert.at(s_branch));

        // We are now going to merge the branch with the large index
        // into the branch with the smaller index
        mergeVec(exp_vert.at(s_branch),
                 exp_vert.at(l_branch));
        mergeVec(unex_edge.at(s_branch),
                 unex_edge.at(l_branch));

        // We are going to now clear out the l_branch unex_edge and exp_vert 
        unex_edge.at(l_branch).clear();
        exp_vert.at(l_branch).clear(); 
      
      } //if(merge) as in we have the right branch

    } // if(branch_ind!=branch_ind2) make sure we are dealing with different
      // branches
  }

  cout << "Merge Branches " << endl;
  for(int branch_ind2=0;branch_ind2<num_branches;branch_ind2++){
    cout << "Branch ind " << branch_ind2 << endl;
    for(int index=0;index<branches.at(branch_ind2).size();index++){
      cout << branches.at(branch_ind2).at(index) << endl;
    } 
  }
  
}

void exploreEdge(vector<vector<int>>& mat,
                 vector<vector<int>>& branches,
                 vector<vector<int>>& vert_bonds,
                 vector<vector<int>>& unex_edge,
                 vector<vector<int>>& exp_vert,
                 int neigh_vert_curr,
                 int curr_vert,
                 int branch_ind){

  // Step 1 indicate that the edge has now been explored
  int mat_index = findMatIndexNode(mat,curr_vert,neigh_vert_curr);
  mat.at(mat_index).at(2) = 1;
  // Step 2 Set the 5th matrix column to the branch num to 
  // indicate which branch explored the bond/edge
  mat.at(mat_index).at(4) = branch_ind;
  // Step 3 Add the vertex to the branch
  branches.at(branch_ind).push_back(neigh_vert_curr);

  // Step 4 Determine if this neigh_vert_curr has any bonds
  int neigh_vert_ind = findIndNodeVert_Bonds(vert_bonds,neigh_vert_curr);

  if(vert_bonds.at(neigh_vert_ind).at(1)>0){
  // If it does add them to the unexplored list
    for(int j=0;j<vert_bonds.at(neigh_vert_ind).at(1);j++){
      int id = vert_bonds.at(neigh_vert_ind).at(3+j);
      unex_edge.at(branch_ind).push_back(id);
      exp_vert.at(branch_ind).push_back(neigh_vert_curr);
    }
  } 
}

void exploreBranch(vector<vector<int>>& vert_bonds,
                   vector<vector<int>>& branches,
                   vector<vector<int>>& exp_vert,
                   vector<vector<int>>& unex_edge,
                   vector<vector<int>>& mat,
                          int start_ind){

  bool exp = false;
  int num_branches = vert_bonds.at(start_ind).at(1);
  // We will cycle through each branch id at the same speed until 
  // all of the branches have been fully explored
  while(exp==false){

    cout << "In uniqueBranches while loop exp " << exp << endl; 

    // Step 1 Cycle through each of the branches 
    for(int branch_ind=0;branch_ind<num_branches;branch_ind++){
      cout << unex_edge.at(branch_ind).size() << endl;

      // Step 2 determine if the branch has been fully explored
      // this is done by looking at the number of id's in the edge
      // vector or exp_vert vector

      if(unex_edge.at(branch_ind).size()>0){

        // Determine the id of the vertex that we have touched and that
        // is associated with the last edge
        int curr_vert = exp_vert.at(branch_ind).back();
        // Remove the vertex from teh exp_vert vector
        exp_vert.at(branch_ind).pop_back();
        // Ensure that the curr_vert is not already stored in the 
        // branch before adding it

        if(!vertexExist(branches.at(branch_ind),curr_vert)){
          // Add the vertex to the branch
          branches.at(branch_ind).push_back(curr_vert);
        }
        cout << "Printing unex_edge " << endl;
        // grab a neighbor of the curr_vert we will explore this
        // bond/edge first by pulling from the back of the array
        int neigh_vert_curr = unex_edge.at(branch_ind).back();
        unex_edge.at(branch_ind).pop_back();
       
         
        // Indicate the bond/edge was explored by incrementing
        vert_bonds.at(curr_vert).at(2)++;

        // Determine if this bond has been explored before or not
        // If it has been explored this branch may be connected to
        // another branch. If the branch that previously explored it
        // was different from the current one. If it was not different
        // we will simply increment to the next bond
        int mat_ind = findMatIndexNode(mat,curr_vert,neigh_vert_curr);
  
        if(mat.at(mat_ind).at(2)==1){

          if(mat.at(mat_ind).at(4)==branch_ind){
            // This means that the edge was already explored by the
            // same branch 
            // we don't need to do anything because we have already incremented
            // vert_bonds. meaning we will automatically move to the next option
            // We also do not need to add any edges/bonds to the unexplored list
            // because edge/bond has already been explored it must have come from
            // the other vertex and thus those bonds/edges have already been 
            // considered.  
          }else{

            // Let's make sure that the potential merge site is not the 
            // initial junction or starting index
            if(vert_bonds.at(start_ind).at(0)!=mat.at(mat_ind).at(0) &&
               vert_bonds.at(start_ind).at(1)!=mat.at(mat_ind).at(1)){
              cout << "merge branch" << endl;
              cout << "Number of branches " << unex_edge.size() << endl; 
              cout << "neigh_vert_curr " << neigh_vert_curr << endl;
              cout << "Current vert " << curr_vert << endl;
              // If this is the case we need to check to see which other
              // branch shares this edge. We will then proceed to merge
              // the branches. The branch with the larger branch id will
              // be merged with the one with the lower id.
              cout << endl;
              cout << "Printing unex_edges" << endl;
              int idx=0;
              for(auto it=unex_edge.at(branch_ind).begin();it!=unex_edge.at(branch_ind).end();++it){
                cout << exp_vert.at(branch_ind).at(idx) << " ";
                cout << *it << endl;
                idx++;
              }
              cout << "Branch index " << branch_ind << endl;
              cout << "matrix" << endl;
              printVecVec(mat);

              mergeBranches(unex_edge,
                            exp_vert,
                            vert_bonds,
                            branches,
                            branch_ind,
                            start_ind,
                            neigh_vert_curr);
            }
          }
        
        }else{
        // This means the edge/bond has not yet been explored

          cout << "neigh_vert_curr " << neigh_vert_curr << endl;
          cout << "Current vert " << curr_vert << endl;
          exploreEdge(mat,
                      branches,
                      vert_bonds,
                      unex_edge,
                      exp_vert,
                      neigh_vert_curr,
                      curr_vert,
                      branch_ind);
          
        }
      }            
    } // Cycle through branches

    // Run this test at the end of each iteration through the while loop
    // when it returns true it means that each branch has been fully 
    // explored. 
    exp = true;
    for(auto it = unex_edge.begin();it!=unex_edge.end();++it){
      if(it->size()!=0){
        exp=false;
        break;
      }
    }
  } // while(exp==false)

}

// This function may not be needed
void recalibrateVertex(Edges edgs, 
                       vector<vector<int>>& vert_bonds, 
                       int start_ind,
                       vector<vector<int>>& branches){

  // Here we need to change the values in vert_bonds to reflect
  // that the vertex indicated by start_ind may now very well
  // be split into different segments. Thus we need each branch to have
  // a unique id for referring to the same starting node.
  //
  // We will do this by letting the first branch take the original 
  // id of the starting vertex. While the other branches will use define
  // the starting node with unique id's, each of which has a value larger
  // than th elargest id currently in the node. 
  //
  // Find the largest id or index for the vertices in the list we 
  // will add the extra ids in excess of those that are currently 
  // in the list

  // Step 1 determine the largest id currently held by a node
  int max_id = edgs.maxVertex();  
  bool first = true;
  vector<int> copy_vert_start;
  int start_id = vert_bonds.at(start_ind).at(0);


  cout << "max_id is " << max_id << endl;
  // Step 2 Cycle through branches
  for(int branch_num=0;branch_num<vert_bonds.at(start_ind).at(1);branch_num++){

    if(branches.at(branch_num).size()!=0){
      // Step 3 for the first branch do not change the id of the starting node
      // we still need to change however, which edges are within the branch
      if(first){
        first = false;
        // Keep the same id as the original starting index
        copy_vert_start.push_back(vert_bonds.at(start_ind).at(0));
        // Number of bonds
        int freq = 0;
        copy_vert_start.push_back(freq);
        // Number of bonds that have been explored
        copy_vert_start.push_back(freq);
        // check to see what other neighboring vertices are in the branch
        // Cycle the neighbors 
        int num_nei = vert_bonds.at(start_ind).at(1);

        for(int index=0;index<num_nei;index++){
          int nei_id = vert_bonds.at(start_ind).at(3+index);
          //Check to see if the nei is in this branch
          for(int j=0;j<branches.at(branch_num).size();j++){
            if(nei_id==branches.at(branch_num).at(j)){
              copy_vert_start.push_back(nei_id);
              freq++;
            }
          }
        }
        
        // Update the vector<int> that will replace vert_bonds.at(start_ind)
        copy_vert_start.at(1) = freq;
        copy_vert_start.at(2) = freq;
   
      }else{
      
        // Step 4 For the other branches, excluding the first we need 
        // change what the id of the stating  node/vertex is
        max_id++;
        int new_id = max_id;
        
        // We will create a tempory vector<int> which we will append to the
        // end of vert_bonds once we have all the information for this new
        // vertex/node figured out. 
        vector<int> temp_vert;
        // The id of the relabeled starting node
        temp_vert.push_back(new_id);
        int freq = 0;
        // How many bonds are originating from the vertex start with 0
        temp_vert.push_back(freq);
        // How many of the bonds have been visited assume they all have for now
        temp_vert.push_back(freq);

        int num_nei = vert_bonds.at(start_ind).at(1);

        // Cycle through the original neighbors of the starting node
        for(int index=0;index<num_nei;index++){
          int nei_id = vert_bonds.at(start_ind).at(3+index);
          //Check to see if the nei is in this branch
          for(int j=0;j<branches.at(branch_num).size();j++){
            if(nei_id==branches.at(branch_num).at(j)){
              // If the neighbor is in this branch store it in our temporary
              // vector<int>
              temp_vert.push_back(nei_id);
              freq++;

              // Step 5 now what we need to do is change the definition
              // of the edge between the start node and nei_id, so that
              // it is actually between new_id and and nei_id.
              // This is only needed for the edges that describe nodes
              // in this branch
              int size = vert_bonds.size();
              for(int index4 = 0;index4<size;index4++){
                // Search through vert_bonds for nei_id
                if(vert_bonds.at(index4).at(0)==nei_id){
                  // Now that we have found the nei_id find where in 
                  // vert_bonds it described the relationship with
                  // the start node and replace it with new_id
                  int size_nei = vert_bonds.at(index4).at(1);
                  for(int index2 = 0;index2<size_nei;index2++){
                    if(vert_bonds.at(index4).at(3+index2)==start_id){
                      vert_bonds.at(index4).at(3+index2)==new_id;
                    } 
                  }
                }
              }
              
            }
          }

        }
      
        // Finally we can update the temporary vector<int> and 
        // append it to vert_bonds
        temp_vert.at(1) = freq;
        temp_vert.at(2) = freq; 
     
        // Append the new details onto the end of vert_bonds
        vert_bonds.push_back(temp_vert);
      }
    }
  }
  // Now at the end we can correct the original start verctor with 
  // copy. We cannot do this before now because we use the starting
  // row after the initial run 
  vert_bonds.at(start_ind)=copy_vert_start;  

  return;
}

Edges::Edges(Edge ed){
  this->push_back(ed);
}

// Grabs all the unique vertices and 
// returns them from a list
list<int> Edges::getVertices(void){

  list<int> vertices;
  // Begin by adding every Edge vertex to a single
  // list
  for(auto it=this->li.begin();it!=this->li.end();++it){
    vertices.push_back(it->getV1());  
    vertices.push_back(it->getV2());  
  } 
  // Now cycle through each element
  list<int> vertices_unique;
  for( auto it=vertices.begin() ; it!=vertices.end();++it){
    bool unique = true;
    auto it2 = it;
    it2++;
    for(;it2!=vertices.end();++it2){
      if(*it2==*it){
        unique = false;
      }
    }
    if(unique) vertices_unique.push_back(*it);
  }
  return vertices_unique; 
}

int Edges::maxVertex(void){

  auto it=this->li.begin();
  int max = it->getV1();
  if(it->getV2()>max){
    max = it->getV2();
  }

  for(auto it=this->li.begin();it!=this->li.end();++it){
    if(max<it->getV1()){
      max = it->getV1();
    }
    if(max<it->getV2()){
      max = it->getV2();
    }
  }
  return max;
}

vector<vector<int>> Edges::uniqueBranches(
  vector<vector<int>> mat,
  vector<vector<int>>& vert_bonds,
  int start_ind){


  cout << "start_ind " << start_ind << endl;
  // We will create a list of lists to determine which vertex is in
  // which branch
  vector<vector<int>> branches;

  int num_branches = vert_bonds.at(start_ind).at(1);  
  // Lets first make sure that the start_ind has more than two edges
  // If it does not we will consider the whole thing a single branch
  if(num_branches<3){
    
    // We will basically return all of the vertices
    auto vertices = this->getVertices();
    vector<int> temp;
    for(auto it=vertices.begin();it!=vertices.end();it++){
      temp.push_back(*it);
    }
    branches.push_back(temp);
    return branches;

  }else{

    // We have more than two bonds attached to the starting index
    // so we will create a branch for each of these bonds

    branches.resize(num_branches);
    // There is also a need to keep track of each edge that has not yet
    // been explored this is important for when we hit a dead end we 
    // should know where to pick back up from.

    vector<vector<int>> unex_edge;
    vector<vector<int>> exp_vert; 
    unex_edge.resize(num_branches);
    exp_vert.resize(num_branches);
    
    // Start by filling it with the edge id's connected to the starting
    // vertex. Remember that the 4th column and beyond is where the actual
    // Edge id's are listed
    cout << "Number bonds " << vert_bonds.at(start_ind).at(1) << endl;
    for(int i=0;i<vert_bonds.at(start_ind).at(1);i++){
      unex_edge.at(i).push_back(vert_bonds.at(start_ind).at(3+i));
      // The explored vertex in this case will be the id of the starting
      // vertex
      exp_vert.at(i).push_back(vert_bonds.at(start_ind).at(0));
    }

    exploreBranch(vert_bonds,
                  branches,
                  exp_vert,
                  unex_edge,
                  mat,
                  start_ind);

    cout << "recalibrating vertex id's" << endl;
    /*recalibrateVertex(*this, 
                      vert_bonds, 
                      start_ind,
                      branches);
    */
  } 
   
  return branches;

}

// This function works by splitting the list of edges up into 
// groups where each node in the group is attached to every 
// other node in the group. The attachement may occur through 
// many neighbors. For instance if you considered a bunch of 
// atoms with various bonds calling this function would split
// the atoms up into clusters or molecules. Each elements in
// the vector is a molecule and each int in the list represents
// an atom's id. 
vector<list<int>> Edges::getClusters(void){
 
  int size = li.size();
  
  // A row of three -1's 
  vector<int> row_init(3,-1);
  vector<vector<int>> mat(size,row_init);

  // Fill the first two elements with the ids from the edges
  int row_ind = 0;
  for(auto it=li.begin();it!=li.end();++it){
    mat.at(row_ind).at(0) = it->getV1();
    mat.at(row_ind).at(1) = it->getV2();
    row_ind++;
  }

  // Next step cycle through the rows any row that shares the
  // same id assign the same value 
  int cluster_id = 0;

  auto edge_elem = li.begin();
  // Unassigned values rows
  int unassigned_r=size;

  while(unassigned_r>0){

    //cout << "cluster id " << cluster_id << endl;
    auto row = mat.begin();
    int id = edge_elem->getV1();
    int id2 = edge_elem->getV2();
    bool restart;

    while(row!=mat.end()){    
      restart = false;
      bool match = false;
      if(row->at(2)!=cluster_id){
       // cout << "id " << row->at(2) << endl;
        if(row->at(0)==id || row->at(1)==id){
          
          if(row->at(2)!=-1 ){
            // means the elements are part of a different cluster
            // reassign the cluster id and start again
            cluster_id = row->at(2); 
            restart = true;
          }else{
            match = true;
          }
        }
        if(row->at(0)==id2 || row->at(1)==id2){
          if(row->at(2)!=-1 ){
            // means the elements are part of a different cluster
            // reassign the cluster id and start again
            cluster_id = row->at(2); 
            restart = true;
          }else{
            match = true;
          }
        }
        if(match){
          if(row->at(2)==-1){
            unassigned_r--;
           // cout << "u_r " << unassigned_r << endl;
          }
          row->at(2) = cluster_id;
        }
      }
      if(restart) {
        //cout << "restart" << endl;
        row=mat.begin();
        restart = false;
      }else{
        //cout << "Advance row" << endl;
        row++;
      }
    }
    if(!restart){
      cluster_id++;
      edge_elem++;
    }
  }
  // Now create a list of the clusters
  ListContainer<int> cluster;
  vector<list<int>> clusters;
  //cout << "Cluster id final " << cluster_id << endl;
  //cout << "size " << size << endl;
  // Cycle through the total number of clusters
  for(int i=0;i<cluster_id;i++){
    for(int j=0;j<size;j++){
      if(mat.at(j).at(2)==i){
        cluster.push_back(mat.at(j).at(0));
        cluster.push_back(mat.at(j).at(1));
      }
    }
    cluster.removeRedundant();
    //cout << "cluster size " << cluster.size() << endl;
    //cout << "i is " << i << endl;
    {
      list<int> temp;
      for(int j=0;j<cluster.size();j++){
        temp.push_back(cluster.at(j));
      }
      clusters.push_back(temp);
    }
    cluster.clear();
  }

  return clusters;
}

