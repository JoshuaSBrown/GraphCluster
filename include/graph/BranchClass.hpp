/* 
 * Purpose: this class was developed in order to sort through a graph
 * of vertices and edges. The class is initialized by first passing in a 
 * list of edges. The user can then specify which vertex the graph will
 * be explored from. 
 * 
 * The number of edges attached to the chosen starting vertex will 
 * determine the number of branches. In the case, that two branches 
 * attempt to explore the same vertex the branch that attempts to 
 * explore it first will have priority. 
 * 
 * When the second branch attempts to access the contested vertex an 
 * overlap rule will be created, which will state the branches involved
 * and along which edge. Further exploration from the contested vertex
 * will subsequently be asigned to the first branch. 
 *
 * Once exploration of all branches is complete, as in each branch has
 * explored every edge connected to it, the overlap rules will be
 * addressed. 
 *
 *
 * Developed by Joshua Brown
 */

#ifndef _BRANCHCLASS_HPP_
#define _BRANCHCLASS_HPP_

#include <list>
#include <vector>
#include <iostream>


#include "../CPP_Vec_VecTemplate/Vec_VecTemplate.hpp"
#include "../CPP_EdgeClass/EdgeClass.hpp"

// Conventions
// _ - underscores before a class or function mean that the function or
//     class is an internal class or function. 

class branches {
  private:


    // This class is responsible for defining the relationships between
    // the different vertices. It contains information about every vertex 
    // and it contains the relationships between the connected vertices. 
    class _branch_map {
      private:

        // Defines the relationships between the vertices
        // col 1 - id of the vertex
        // col 2 - number of bonds attached to the vertex
        // col 3 - is the number of bonds that have been accessed
        // col 4+ - the ids of the vertices the vertex is attached too
        VecVecContainer<int> vert_bonds;

        // This object defines the relationships of the edges
        // It defines which edge has been explored and which
        // branch the edge belongs too
        // Also defines if the edge has been explored from
        // both directions.
        //
        // col 1 - id of 1 vert in the edge
        // col 2 - id of 2nd vert in the edge
        // col 3 - if the edge has been explored, 0 if not, 1 if it has
        // col 4 - id of the edge
        // col 5 - branch number the edge is associated with -1 if not
        //         yet assigned
        VecVecContainer<int> _edge_map;

        // Where in the edge_map VecVecContainer is the edge defined by
        // vert1 and vert2 
        int _edge_mapInd(int vert1, int vert2);

        // Return the row the edge is located in
        std::vector<int> _edge_mapRow(Edge ed);
      public:
        _branch_map(){};

        // To initialize a branch_map pass in all the edges in the graph
        _branch_map(std::list<Edge> edgs);

        // This function will return a vector with a list of all the
        // vertices that may be considered a junction. A junction is
        // a vertex with 3 or more edges connected to it. 
        std::vector<int> getJunctionVert();

        // Grabs all the vertices in the network
        std::vector<int> getVert();

        // This function will return the number of bonds or edges
        // connected to a vertex with the id vertID. 
        int getBonds(int vertID);

        // This function returns the vertices neighboring vertID in a
        // vector. More specifically it returns the vertices connected to
        // vertID through an edge. 
        std::vector<int> getNeighs(int vertID);

        // Returns the edges that describe vertID
        std::vector<Edge> getEdges(int vertID);
        std::list<Edge> getAllEdges(void);
        std::vector<Edge> getBranchEdges(std::vector<int> branch);
        void exploreEdge(Edge ed,int branch_ind);
        int exploreStatus(Edge ed);

        // Determine if an edge has been explored by another
        // branch return the branch id if it has, or a value of -1
        // if it hasn't
        //int branchStatus(Edge ed);
    } bm;


    class _exploration_map{
      private:

        // This member tells us which vertex we are starting our 
        // exploration from. 
        int starting_vertex;

        // This object is constantly changing and
        // defines which edges are currently being looked at
        // but have not been fully explored for each branch.
        // Here the row will correspond to the branch_id
        // col 1 - vertex that has been explored
        // col 2 - vertex that has not been explored
        std::vector<VecVecContainer<int>> mat;

        // Each index in the parent std::vector represents a branch
        // Each row represents a vertex that has been explored in the
        // branch and the column will contain the distance of each of
        // the vertices from the starting vertex
        // col 1 - vertex id
        // col 2 - distance from starting vertex
        // col 3+- branch exploration identifiers
        //
        // If one branch is closer to the vertex than another it
        // will overwrite the identifier. If both branches are equal
        // distance from the vertex then both identifiers are stored. 
        //
        // branch_vertices.at(branch_ind).at(0,0) = vertex id
        // branch_vertices.at(branch_ind).at(0,1) = distance from starting vertex
        // branch_vertices.at(branch_ind).at(0,2+) = branch id closest to 
        // the node. 
        //
        // Note the order in the rows is not conserved because of how we
        // delete the vertices.
        std::vector<VecVecContainer<int>> branch_vertices;

        // Keep track of where the branches overlap
        // col 1 - branch id 1
        // col 2 - branch id 2
        // col 3 - vertex id 1
        // col 4 - vertex id 2
        VecVecContainer<int> branch_overlap_rule;

        void _removeVertex(int branch_ind, int vertID);
        void _addVertex(int branch_ind, int vertID);
        void _removeEdge(Edge ed,int branch_ind);
        bool _vertexExplored(int branch_ind, int vertID);
        void _setDistance(int branch_ind, int vertID, int dist);
        void _addBranchIdentifier(int branch_ind, int vertID, int branch_identifier);
        void _addBranchIdentifiers(int branch_ind, int vertID, std::vector<int> branch_identifiers);
      public:
        _exploration_map() {};
        _exploration_map(int start_vert, _branch_map bm);
        _exploration_map(int start_vert, Edge ed);
        int test_removeEdge(void);

        // To add data to the exploration_map object you have
        // to indicate 1. which branch the edge you are adding is located on
        //             2. which one of the vertices defining the edge has
        //                been explored
        //             3. The actual edge
        std::vector<Edge>             getExpEdges(int branch_ind,_branch_map bm);
        void                          addUnexpEdge(int branch_ind,int explored_vert_id, Edge ed);
        Edge                          getUnexpEdge(int branch_ind);
        std::vector<Edge>             getUnexpEdges(int branch_ind);
        std::vector<Edge>             getUnexpEdges(int branch_ind,int vertID);
        std::vector<int>              getBranchVertices(int branch_ind);
        bool                          edgeExist(Edge ed, int branch_ind);
        int                           getNumUnexploredEdges(int branch_ind);
        std::vector<int>              getBranchIdentifiers(int branch_ind, int vertID);
        std::vector<int>              getBranchIdentifiers(void);
        int                           getDistance(int branch_ind, int vertID);
        std::vector<std::vector<int>> getVertDistances(int branch);
        void                          updateBranchDistances(int branch_ind,Edge ed,_branch_map bm);
        int                           getNumBranches(void);
        int                           getExploredVertex(Edge ed, int branch_ind);
        int                           getUnexploredVertex(Edge ed, int branch_ind);
        std::vector<Edge>             getOverlappingEdges(int branch1, int branch2);
        std::vector<int>              getBranchOverlapRule(Edge ed);
        std::vector<std::vector<int>> getBranchOverlapRules();
        std::vector<int>              getBranchesContestVertex(int contested_vertex);
        int                           findVertexConflict(int neigh_branch, Edge ed);
        std::vector<std::vector<int>> getMap(int branch_ind);
        std::vector<std::vector<int>> getMap(void);
        int                           contestedEdge(int branch_ind, Edge ed);
        void                          putBranchOverlapRule(int branch1, int branch2, Edge ed);
        bool                          branchOverlapRuleExist(Edge ed);
        void                          removeBranchOverlapAtEdge(int branch, Edge ed);

        // Determine the branch other than branch_id that claims the vertices
        // in the edge, if there is more than one than return -1 
        int                           otherBranch(Edge ed, int branch_id);
        // All branches that are connected are merged into a single branch
        void                          mergeAllOverlapRules(_branch_map bm);
        bool                          allBranchesComplete();
        void                          exploreEdge(Edge ed, int branch_ind,_branch_map bm);
        int                           exploreBranches(_branch_map bm);
    } em;

    branches(){}; 
  public:

    // To initialize a branch object a list of edges defining the vertices
    // are needed. 
    branches(std::list<Edge> edgs);
  
    // Get junctions will return the number of vertices that have 3 or more
    // edges connected to them. 
    std::vector<int> getJunctions();

    // Returns a vector of pairs the first number is the id of the vertex
    // the second number is the number of bonds. 
    std::vector<std::pair<int,int>> countJunctionEdges();    
    // The same as above but counts all the vertices and their bonds
    std::vector<std::pair<int,int>> countEdges();

    // This function will explore the graph starting at the vertex defined
    // by vertID
    void exploreFromVertex(int vertID);

    // Returns the total number of branches
    int numBranches(void);

    // This will return the indices of the branches. It is necessary because
    // some of the branch ids might dissappear after being merged into a 
    // different branch. 
    std::vector<int> getBranchIndices(void);

    // When no branch is specified the getMap will return a vector of vectors.
    // Where each row in the vector represents a vertex in the graph. 
    // col1 - this is the id of the vertex
    // col2 - this is the distance of the vertex from the starting vertex
    // col3+ - this represents the ids of the branches that claim the vertex 
    std::vector<std::vector<int>> getMap(void);

    // When a branch is specified the map associated with that specific branch
    // is returned
    std::vector<std::vector<int>> getMap(int branch_ind);
    
    std::vector<std::vector<int>> getBranchMap(int branch_ind);

    // This function returns with the vertex ids and their associated distance
    // from the starting vertex. 
    std::vector<std::vector<int>> getBranchDist(int branch_ind);

    // This returns the vertices that are in each branch
    std::vector<std::vector<int>> getBranches();

    // This function returns the edges that are in each branch
    std::vector<std::vector<Edge>> getBranchesEdges();
    int test_branchclass(void);
};


#endif
