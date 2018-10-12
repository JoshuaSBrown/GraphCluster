
#ifndef UGLY_GRAPHNODE_HPP
#define UGLY_GRAPHNODE_HPP

#include <cstdint>
#include <iostream>
#include <typeinfo>
#include <tuple>
#include <sstream>

namespace ugly {

  template<class F, class...Ts, std::size_t...Is>
    void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>){
      using expander = int[];
      (void)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
    }

  template<class F, class...Ts>
    void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func){
      for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
    }

  template<class F, class...Ts, std::size_t...Is>
    void for_each_in_tuple_str(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>){
      using expander = int[];
      (std::string)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
    }

  template<class F, class...Ts>
    void for_each_in_tuple_str(const std::tuple<Ts...> & tuple, F func){
      for_each_in_tuple_str(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
    }

  template<class... Ts>
    class GraphNode {

      private: 
        int id;
        std::tuple<Ts...> tp;

      public:
        explicit GraphNode(int ID,Ts... ts) {
          id = ID;
          tp = std::tuple<Ts...>(ts...);          
        }

        int getId(void) { return id; }

        bool operator!=(const GraphNode<Ts...>& GN) const { return this->tp!=GN.tp; }
        bool operator==(const GraphNode<Ts...>& GN) const { return this->tp==GN.tp; }

        void test(void){
          for_each_in_tuple(tp,[](const auto &x) { std::cout << x << std::endl; });
        }

        std::string str(void){
          std::string result = "";
          for_each_in_tuple(tp,[&](const auto &x) { 
              std::stringstream ss;
              ss << x << ",";    
              ss >> result;
              });
          return result;
        }

        bool operator<(const GraphNode<Ts...>& GN) const{
          return this->tp<GN.tp; 
        }
        bool operator>(const GraphNode<Ts...>& GN) const{
          return this->tp>GN.tp; 
        }
        bool operator>=(const GraphNode<Ts...>& GN) const{
          return this->tp>=GN.tp; 
        }
        bool operator<=(const GraphNode<Ts...>& GN) const{
          return this->tp<=GN.tp; 
        }
    };
}
#endif // UGLY_GRAPHNODE_HPP
