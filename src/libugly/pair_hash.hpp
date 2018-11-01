
#ifndef UGLY_PAIRHASH_HPP
#define UGLY_PAIRHASH_HPP

#include <functional>
#include <utility>

namespace ugly
{
  namespace hash_functions {
    struct hash {
      template<typename T, typename G>
        size_t operator()( const std::pair<T,G>& key) const
        {
          size_t hash_value = 17;
          hash_value = hash_value*31+std::hash<T>()( key.first );
          hash_value = hash_value*31+std::hash<G>()( key.second );
          return hash_value;
        }
    };
  }
}

#endif // UGLY_PAIRHASH_HPP
