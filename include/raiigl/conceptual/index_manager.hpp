#pragma once

#include <raiigl/types.hpp>

#include <set>
#include <stdexcept>

namespace raiigl {
  namespace conceptual {

    struct index_manager
    {
     public:
      const uint min, max;

     protected:
      std::set<uint> allocated_values;

     public:
      index_manager( uint _max = 100, uint _min = 0 ) :
        min( std::move( _min ) ), max( std::move( _max ) ) {}

      uint new_index() {
        for ( uint i( min ); i < max; ++i ) {
          if ( allocated_values.find( i ) == allocated_values.end() ) {
            allocated_values.insert( i );
            return i;
          }
        }
        throw std::runtime_error(
          "[raiigl::index_manager::new_index] Can't found new index in range "
          + std::to_string( min )
          + "-" + std::to_string( max )
        );
      }

     public:
      void mark_index( const uint index ) {
        if ( allocated_values.find( index ) != allocated_values.end() )
          throw std::runtime_error( "[raiigl::index_manager::mark_index] Index(" + std::to_string( index ) + ") already used" );
        allocated_values.insert( index );
      }

     public:
      void free_index( const uint index ) {
        allocated_values.erase( index );
      }
    };

  }
}


