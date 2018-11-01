
#ifndef UGLY_HASHPAIR_HPP
#define UGLY_HASHPAIR_HPP

namespace std
{
  template<>
    struct hash<std::pair<int,int>>{
      size_t operator()( const std::pair<int,int>& key) const
      {
        size_t hash_value = 17;
        hash_value = hash_value*31+hash<int>()( key.first );
        hash_value = hash_value*31+hash<int>()( key.second );
        return hash_value;
      }
    };
}

#endif // UGLY_HASHPAIR_HPP
