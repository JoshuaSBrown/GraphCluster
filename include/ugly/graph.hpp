
#ifndef UGLY_GRAPH_HPP
#define UGLY_GRAPH_HPP

#include <vector>
#include <list>
#include <unordered_map> 
#include <algorithm>

#include "../CPP_BranchClass/BranchClass.hpp"
#include "../CPP_EdgeClass/EdgeClass.hpp"
#include "../CPP_GraphNode/GraphNode.hpp"

template<class... Ts>
class GraphCluster {
    private: 
        // unique string that is associated with the specific structure
        // any graph cluster with the same structure should have the same structure_id
        std::string structure_id;

        static bool compare(std::pair<int,int> p1, std::pair<int,int> p2){
            return p1.second<p2.second;
        }
    public:
        GraphCluster(std::list<Edge> connections, std::vector<GraphNode<Ts...>> nodes){

            // Create a branches object, basically a network of vertices and their connections
            branches network(connections);
            // Find all the junctions, the first int in the pair is the vertex id the second
            // number is the number of bonds associated with that junction. A junction is defined
            // as having three or more bonds. 
            std::vector<std::pair<int,int>> pr_bonds = network.countJunctionEdges();

            // Check to see if this network has no junctions
            if(pr_bonds.size()==0){
            // If this is the case then we will simply grab all the edges
                pr_bonds = network.countEdges();
            }

            // first int is the number of bonds associated with the junctions
            // second int is the number of junctions with the specified number of bonds
            std::unordered_map<int,int> counts;
            for( auto pr=pr_bonds.begin() ; pr!=pr_bonds.end();pr++ ){
                if(counts.count(pr->second)==0){
                    counts[pr->second]=1;
                }else{
                    counts[pr->second]++;
                }
            }
            
            // Determine the number of bonds with the fewest junctions
            auto min_v = std::min_element(counts.begin(),counts.end(),this->compare);
            int num_bonds_min_num_junct = min_v->first;

            std::vector<int> junctions_interest;
            for( auto pr : pr_bonds ){
                if(pr.second==num_bonds_min_num_junct){
                    junctions_interest.push_back(pr.first);
                }
            } 

            // Now we are going to try to explore from each of the junctions of interest
            // we will do this by comparing every branch of each of the junctions. A junction with the 
            // "smallest branch" will be chosen. If more then one jucntion has this "smallest branch" then
            // the other branches associated with the conflicting junctions will be compared and so on...

            std::unordered_map<int,int> junc_branch_min;
            std::string min_branches = "";

            bool first = true;
            for( auto j : junctions_interest ){
                network.exploreFromVertex(j);
                auto branches_maps = network.getMap(); 
            
                // First we need to sort the nodes in the branch from smallest to largest
                // instead of having a vector of branch indices we are going to create vectors for each branch containing GraphNodes                
                // While we are doing this we will sort the GraphNodes first based on their distance from the starting vertex 
                std::unordered_map<int,std::vector<GraphNode<Ts...>>> map_gn;
                for( auto v : branches_maps ){
                    int id = v.at(0); // gets the id of the vertex    

                    // Find the Graph Node with that particular id there should only be one
                    auto it = find_if(nodes.begin(),nodes.end(),[id](GraphNode<Ts...> gn){return gn.getId()==id;});
                    // Gets the distance of the vertex from the starting point uses it as a key to add the GraphNode      
                    map_gn[v.at(1)].push_back(*it);
                }

                
                // Secondly based on the values stored in the graph nodes
                for( auto it = map_gn.begin(); it!=map_gn.end();it++){
                    sort(it->second.begin(),it->second.end());
                }

                // Next we create a string that represents the whole network
                std::string branch_str = "";
                for( auto it = map_gn.begin();it!=map_gn.end();it++){
                    for( auto gn : it->second ){
                        branch_str.append(gn.str());
                    }
                }   

                // First vertex 
                if(first){
                    first = false;
                    min_branches = branch_str;
                }else if(branch_str.compare(min_branches)<0){
                    min_branches = branch_str;
                    break;
                }
               
            }

            structure_id = min_branches;
        }

        std::string getLabel(void) { return this->structure_id;}

        bool operator!=(const GraphCluster<Ts...>& GC) const { 
            return this->structure_id.compare(GC.structure_id)!=0;
        }
        
        bool operator==(const GraphCluster<Ts...>& GC) const { 
            return !((*this)!=GC);
        }
              
};

#endif // UGLY_GRAPH_HPP
