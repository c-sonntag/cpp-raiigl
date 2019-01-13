#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/types.hpp>
#include <raiigl/gl_types.hpp>

#include <GL/glew.h>

namespace raiigl {

  enum class texture_type : GLenum
  {
    Texture1D                 = GL_TEXTURE_1D,
    Texture2D                 = GL_TEXTURE_2D,
    Texture3D                 = GL_TEXTURE_3D,
    Texture1DArray            = GL_TEXTURE_1D_ARRAY,
    Texture2DArray            = GL_TEXTURE_2D_ARRAY,
    TextureRectangle          = GL_TEXTURE_RECTANGLE,
    TextureCubeMap            = GL_TEXTURE_CUBE_MAP,
    TextureCubeMapArray       = GL_TEXTURE_CUBE_MAP_ARRAY,
    TextureBuffer             = GL_TEXTURE_BUFFER,
    Texture2DMultisample      = GL_TEXTURE_2D_MULTISAMPLE,
    Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
  };

  enum class pixel_format : GLenum
  {
    Red            = GL_RED,
    RG             = GL_RG,
    RGB            = GL_RGB,
    BGR            = GL_BGR,
    RGBA           = GL_RGBA,
    BGRA           = GL_BGRA,
    RedInteger     = GL_RED_INTEGER,
    RGInteger      = GL_RG_INTEGER,
    RGBInteger     = GL_RGB_INTEGER,
    BGRInteger     = GL_BGR_INTEGER,
    RGBAInteger    = GL_RGBA_INTEGER,
    BGRAInteger    = GL_BGRA_INTEGER,
    StencilIndex   = GL_STENCIL_INDEX,
    DepthComponent = GL_DEPTH_COMPONENT,
    DepthStencil   = GL_DEPTH_STENCIL,
    Unknown        = GLenum( -1 )
  };

  enum class pixel_type : GLenum
  {
    UnsignedByte          = GL_UNSIGNED_BYTE,
    Byte                  = GL_BYTE,
    UnsignedShort         = GL_UNSIGNED_SHORT,
    Short                 = GL_SHORT,
    UnsignedInt           = GL_UNSIGNED_INT,
    Int                   = GL_INT,
    Float                 = GL_FLOAT,
    UnsignedByte332       = GL_UNSIGNED_BYTE_3_3_2,
    UnsignedByte233Rev    = GL_UNSIGNED_BYTE_2_3_3_REV,
    UnsignedShort565      = GL_UNSIGNED_SHORT_5_6_5,
    UnsignedShort565Rev   = GL_UNSIGNED_SHORT_5_6_5_REV,
    UnsignedShort4444     = GL_UNSIGNED_SHORT_4_4_4_4,
    UnsignedShort4444Rev  = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UnsignedShort5551     = GL_UNSIGNED_SHORT_5_5_5_1,
    UnsignedShort1555Rev  = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UnsignedInt8888       = GL_UNSIGNED_INT_8_8_8_8,
    UnsignedInt8888Rev    = GL_UNSIGNED_INT_8_8_8_8_REV,
    UnsignedInt1010102    = GL_UNSIGNED_INT_10_10_10_2,
    UnsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV
  };

  enum class internal_format_type : GLint
  {
    DepthComponent  = GL_DEPTH_COMPONENT, RG              = GL_RG,
    DepthStencil    = GL_DEPTH_STENCIL,   RGB             = GL_RGB,
    Red             = GL_RED,             RGBA            = GL_RGBA,

    R8            = GL_R8,           RGBA8Snorm    = GL_RGBA8_SNORM,     R16UI    = GL_R16UI,
    R8Snorm       = GL_R8_SNORM,     RGB10A2       = GL_RGB10_A2,        R32I     = GL_R32I,
    R16           = GL_R16,          RGB10A2UI     = GL_RGB10_A2UI,      R32UI    = GL_R32UI,
    R16Snorm      = GL_R16_SNORM,    RGBA12        = GL_RGBA12,          RG8I     = GL_RG8I,
    RG8           = GL_RG8,          RGBA16        = GL_RGBA16,          RG8UI    = GL_RG8UI,
    RG8Snorm      = GL_RG8_SNORM,    SRGB8         = GL_SRGB8,           RG16I    = GL_RG16I,
    RG16          = GL_RG16,         SRGB8Alpha8   = GL_SRGB8_ALPHA8,    RG16UI   = GL_RG16UI,
    RG16Snorm     = GL_RG16_SNORM,   R16F          = GL_R16F,            RG32I    = GL_RG32I,
    R3G3B2        = GL_R3_G3_B2,     RG16F         = GL_RG16F,           RG32UI   = GL_RG32UI,
    RGB4          = GL_RGB4,         RGB16F        = GL_RGB16F,          RGB8I    = GL_RGB8I,
    RGB5          = GL_RGB5,         RGBA16F       = GL_RGBA16F,         RGB8UI   = GL_RGB8UI,
    RGB8          = GL_RGB8,         R32F          = GL_R32F,            RGB16I   = GL_RGB16I,
    RGB8Snorm     = GL_RGB8_SNORM,   RG32F         = GL_RG32F,           RGB16UI  = GL_RGB16UI,
    RGB10         = GL_RGB10,        RGB32F        = GL_RGB32F,          RGB32I   = GL_RGB32I,
    RGB12         = GL_RGB12,        RGBA32F       = GL_RGBA32F,         RGB32UI  = GL_RGB32UI,
    RGB16Snorm    = GL_RGB16_SNORM,  R11FG11FB10F  = GL_R11F_G11F_B10F,  RGBA8I   = GL_RGBA8I,
    RGBA2         = GL_RGBA2,        RGB9E5        = GL_RGB9_E5,         RGBA8UI  = GL_RGBA8UI,
    RGBA4         = GL_RGBA4,        R8I           = GL_R8I,             RGBA16I  = GL_RGBA16I,
    RGB5A1        = GL_RGB5_A1,      R8UI          = GL_R8UI,            RGBA16UI = GL_RGBA16UI,
    RGBA8         = GL_RGBA8,        R16I          = GL_R16I,            RGBA32I  = GL_RGBA32I,
    RGBA32UI = GL_RGBA32UI,

    CompressedRed       = GL_COMPRESSED_RED,        CompressedSignedRedRgtc1       = GL_COMPRESSED_SIGNED_RED_RGTC1,
    CompressedRG        = GL_COMPRESSED_RG,         CompressedRGRgtc2              = GL_COMPRESSED_RG_RGTC2,
    CompressedRGB       = GL_COMPRESSED_RGB,        CompressedSignedRGRgtc2        = GL_COMPRESSED_SIGNED_RG_RGTC2,
    CompressedRGBA      = GL_COMPRESSED_RGBA,       CompressedRGBABptcUnorm        = GL_COMPRESSED_RGBA_BPTC_UNORM,
    CompressedSRGB      = GL_COMPRESSED_SRGB,       CompressedSRGBAlphaBptcUnorm   = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
    CompressedSRGBAlpha = GL_COMPRESSED_SRGB_ALPHA, CompressedRGBBptcSignedFloat   = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
    CompressedRedRgtc1  = GL_COMPRESSED_RED_RGTC1,  CompressedRGBBptcUnsignedFloat = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
  };

  enum class texture_image1d_type : GLenum
  {
    Texture1D      = GL_TEXTURE_1D,
    ProxyTexture1D = GL_PROXY_TEXTURE_1D
  };

  enum class texture_image2d_type : GLenum
  {
    Texture2D               = GL_TEXTURE_2D,
    ProxyTexture2D          = GL_PROXY_TEXTURE_2D,
    Texture1DArray          = GL_TEXTURE_1D_ARRAY,
    ProxyTexture1DArray     = GL_PROXY_TEXTURE_1D_ARRAY,
    TextureRectangle        = GL_TEXTURE_RECTANGLE,
    ProxyTextureRectangle   = GL_PROXY_TEXTURE_RECTANGLE,
    TextureCubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    TextureCubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    TextureCubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    TextureCubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    TextureCubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    TextureCubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    ProxyTextureCubeMap     = GL_PROXY_TEXTURE_CUBE_MAP
  };

  enum class minifying_filter_type : GLint
  {
    Nearest              = GL_NEAREST,
    Linear               = GL_LINEAR,
    NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
    LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR
  };

  enum class magnification_filter_type : GLint
  {
    Nearest = GL_NEAREST,
    Linear  = GL_LINEAR
  };

  enum class wrap_type : GLint
  {
    ClampToEdge       = GL_CLAMP_TO_EDGE,
    // deprecied : ClampToBorder     = GL_CLAMP_TO_BORDER,
    MirroredRepeat    = GL_MIRRORED_REPEAT,
    Repeat            = GL_REPEAT,
    MirrorClampToEdge = GL_MIRROR_CLAMP_TO_EDGE
  };


  struct texture : public classes::non_copyable
  {
   public:
    const texture_type base_type;
    const GLuint id;

   protected:
    bool invalid_state = false;

   private:
    __forceinline GLuint gen_texture()
    {
      GLuint id;
      glGenTextures( 1, &id );
      return id;
    }

   public:
    texture( const texture_type _base_type ) :
      base_type( std::move( _base_type ) ),
      id( gen_texture() )
    {}

    virtual __forceinline ~texture()
    {
      if( ( id > 0 ) && !invalid_state )
        glDeleteTextures( 1, &id );
      invalid_state = true;
    }

   public:
    __forceinline texture( texture&& t ) :
      base_type( std::move( t.base_type ) ),
      id( std::move( t.id ) ),
      invalid_state( std::move( t.invalid_state ) ),
      m_last_pixel_format( std::move( t.m_last_pixel_format ) ),
      m_last_textures_num( std::move( t.m_last_textures_num ) )
    { const_cast<GLuint&>( t.id ) = 0; t.invalid_state = true; }

   protected:
    pixel_format m_last_pixel_format{ pixel_format( -1 ) };
    textures_num m_last_textures_num{ textures_num::None };

   public:
    __forceinline pixel_format last_pixel_format() const { return m_last_pixel_format; }
    __forceinline textures_num last_textures_num() const { return m_last_textures_num; }

   public:
    __forceinline void bind() const
    { glBindTexture( static_cast<GLenum>( base_type ), id ); }

    __forceinline void bind( const texture_type other_type )
    { glBindTexture( static_cast<GLenum>( other_type ), id ); }

    __forceinline void unbind() const
    { glBindTexture( static_cast<GLenum>( base_type ), 0 ); }

   public:
    __forceinline void send_image1d( const texture_image1d_type target, const GLint level, const internal_format_type internalformat, const uint width, const pixel_format format, pixel_type pixel, const GLvoid* const data, const uint border = 0 )
    {
      glTexImage1D( static_cast<GLenum>( target ), level, static_cast<GLint>( internalformat ), static_cast<GLsizei>( width ), static_cast<GLint>( border ), static_cast<GLenum>( format ), static_cast<GLenum>( pixel ), data );
      m_last_pixel_format = format;
    }

    __forceinline void send_image1d( const GLint level, const internal_format_type internalformat, const uint width, const pixel_format format, pixel_type pixel, const GLvoid* const data, const uint border = 0 )
    { send_image1d( static_cast<texture_image1d_type>( base_type ), level, internalformat, width, format, pixel, data, border ); }

   public:
    __forceinline void send_image2d( const texture_image2d_type target, const GLint level, const internal_format_type internalformat, const uint width, uint height, const pixel_format format, pixel_type pixel, const GLvoid* const data, const uint border = 0 )
    {
      glTexImage2D( static_cast<GLenum>( target ), level, static_cast<GLint>( internalformat ), static_cast<GLsizei>( width ), static_cast<GLsizei>( height ), static_cast<GLint>( border ), static_cast<GLenum>( format ), static_cast<GLenum>( pixel ), data );
      m_last_pixel_format = format;
    }

    __forceinline void send_image2d( const GLint level, const internal_format_type internalformat, const uint width, uint height, const pixel_format format, pixel_type pixel, const GLvoid* const data, const uint border = 0 )
    { send_image2d( static_cast<texture_image2d_type>( base_type ), level, internalformat, width, height, format, pixel, data, border ); }

   protected:
    __forceinline void set_param( const GLenum pname, GLint param )
    { glTexParameteri( static_cast<GLenum>( base_type ), pname, param ); }

   public:
    __forceinline void set_param_minifying_filter( const minifying_filter_type param = minifying_filter_type::NearestMipmapLinear )
    { set_param( GL_TEXTURE_MIN_FILTER, static_cast<GLint>( param ) ); }

    __forceinline void set_param_magnification_filter( const magnification_filter_type param = magnification_filter_type::Linear )
    { set_param( GL_TEXTURE_MIN_FILTER, static_cast<GLint>( param ) ); }

    __forceinline void set_param_minifying_and_magnification_filter( const minifying_filter_type min = minifying_filter_type::NearestMipmapLinear, const magnification_filter_type mag = magnification_filter_type::Linear )
    { set_param_minifying_filter( min ); set_param_magnification_filter( mag ); }

   public:
    __forceinline void set_param_wrap_s( const wrap_type param = wrap_type::Repeat )
    { set_param( GL_TEXTURE_WRAP_S, static_cast<GLint>( param ) ); }

    __forceinline void set_param_wrap_t( const wrap_type param = wrap_type::Repeat )
    { set_param( GL_TEXTURE_WRAP_T, static_cast<GLint>( param ) ); }

    __forceinline void set_param_wrap_r( const wrap_type param = wrap_type::Repeat )
    { set_param( GL_TEXTURE_WRAP_R, static_cast<GLint>( param ) ); }

    __forceinline void set_param_wrap_str( const wrap_type s = wrap_type::Repeat, const wrap_type t = wrap_type::Repeat, const wrap_type r = wrap_type::Repeat )
    { set_param_wrap_s( s ); set_param_wrap_t( t ); set_param_wrap_r( r ); }

    __forceinline void set_param_wrap( const wrap_type str = wrap_type::Repeat )
    { set_param_wrap_str( str, str, str ); }

   public:
    __forceinline void bind_on_texture( const raiigl::textures_num num )
    {
      m_last_textures_num = num;
      glActiveTexture( static_cast<GLenum>( num ) );
      bind();
      glActiveTexture( 0 );
    }

  };

}


