
#ifndef UGLY_GRAPHNODE_HPP
#define UGLY_GRAPHNODE_HPP

#include <cstdint>
#include <iostream>
#include <typeinfo>
#include <tuple>
#include <boost/lexical_cast.hpp>

namespace ugly {

  /*namespace std{
    namespace
    {
    template <class t>
    inline void hash_combine(std::size_t& seed, t const& v)
    {
    seed ^= hash<t>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    template <class tuple,size_t index = std::tuple_size<tuple>::value - 1>
    struct hashvalueimpl
    {
    static void apply(size_t& seed, tuple const& tuple)
    {
    hashvalueimpl<tuple, index-1>::apply(seed, tuple);
    hash_combine(seed, get<index>(tuple));
    }
    };

    template <class tuple>
    struct hashvalueimpl<tuple,0>
    {
    static void apply(size_t& seed, tuple const& tuple)
    {
    hash_combine(seed, get<0>(tuple));
    }
    };
    }

    template <typename ... tt>
    struct hash<std::tuple<tt...>> 
    {
    size_t
    operator()(std::tuple<tt...> const& tt) const
    {                                              
    size_t seed = 0;                             
    hashvalueimpl<std::tuple<tt...> >::apply(seed, tt);    
    return seed;                                 
    }                                              

    };
    }*/

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
        GraphNode(int ID,Ts... ts) {
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
              result.append(boost::lexical_cast<std::string>(x));
              result.append(",");
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
