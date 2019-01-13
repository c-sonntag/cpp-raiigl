#include <raiigl/program.hpp>

namespace raiigl {

  std::unique_ptr<raiigl::conceptual::index_manager> program::texture_indexed_singleton_up;

  raiigl::conceptual::index_manager& program::get_texture_indexed()
  {
    int max_texture_sampler( 0 );
    glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_sampler );

    const uint limit_max(
      ( max_texture_sampler > 30 ) ?
      ( static_cast<uint>( raiigl::textures_num::Texture00 ) + uint( max_texture_sampler ) ) :
      static_cast<uint>( raiigl::textures_num::Texture30 )
    );

    if( !texture_indexed_singleton_up )
      texture_indexed_singleton_up = std::make_unique<raiigl::conceptual::index_manager>(
        limit_max,
        static_cast<uint>( raiigl::textures_num::Texture10 )
      );
    return *texture_indexed_singleton_up;
  }

}



