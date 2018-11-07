#pragma once

#include <GL/glew.h>

namespace raiigl {

  enum class primitive_type : GLenum
  {
    Points                 = GL_POINTS,
    LineStrip              = GL_LINE_STRIP,
    LineLoop               = GL_LINE_LOOP,
    Lines                  = GL_LINES,
    LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY,
    LinesAdjacency         = GL_LINES_ADJACENCY,
    TriangleStrip          = GL_TRIANGLE_STRIP,
    TriangleFan            = GL_TRIANGLE_FAN,
    Triangles              = GL_TRIANGLES,
    TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
    TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY,
    Patches                = GL_PATCHES,
    None                   = 0xFFFF, /**< hack for other script */
  };

  enum class indice_type : GLenum
  {
    Ubyte  = GL_UNSIGNED_BYTE,
    Ushort = GL_UNSIGNED_SHORT,
    Uint   = GL_UNSIGNED_INT
  };

  enum class data_type : GLenum
  {
    Uint                = GL_UNSIGNED_INT,
    Byte                = GL_BYTE,           Half_float          = GL_HALF_FLOAT,
    Ubyte               = GL_UNSIGNED_BYTE,  Float               = GL_FLOAT,
    Short               = GL_SHORT,          Double              = GL_DOUBLE,
    Ushort              = GL_UNSIGNED_SHORT, Int_2_10_10_10_rev  = GL_INT_2_10_10_10_REV,
    Int                 = GL_INT,            Uint_2_10_10_10_rev = GL_UNSIGNED_INT_2_10_10_10_REV,
  };

  enum class gl_capabilities : GLenum
  {
    Blend             = GL_BLEND,               DepthClamp             = GL_DEPTH_CLAMP,
    ClipDistance0     = GL_CLIP_DISTANCE0,      DepthTest              = GL_DEPTH_TEST,
    ClipDistance1     = GL_CLIP_DISTANCE1,      Dither                 = GL_DITHER,
    ClipDistance2     = GL_CLIP_DISTANCE2,      FramebufferSrgb        = GL_FRAMEBUFFER_SRGB,
    ClipDistance3     = GL_CLIP_DISTANCE3,      LineSmooth             = GL_LINE_SMOOTH,
    ClipDistance4     = GL_CLIP_DISTANCE4,      Multisample            = GL_MULTISAMPLE,
    ClipDistance5     = GL_CLIP_DISTANCE5,      PolygonOffsetFill      = GL_POLYGON_OFFSET_FILL,
    ColorLogicOp      = GL_COLOR_LOGIC_OP,      PolygonOffsetLine      = GL_POLYGON_OFFSET_LINE,
    CullFace          = GL_CULL_FACE,           PolygonOffsetPoint     = GL_POLYGON_OFFSET_POINT,
    DebugOutput       = GL_DEBUG_OUTPUT,        PolygonSmooth          = GL_POLYGON_SMOOTH,
    PrimitiveRestart  = GL_PRIMITIVE_RESTART,   ScissorTest            = GL_SCISSOR_TEST,
    RasterizerDiscard = GL_RASTERIZER_DISCARD,  StencilTest            = GL_STENCIL_TEST,
    SampleAlphaToOne  = GL_SAMPLE_ALPHA_TO_ONE, TextureCubeMapSeamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
    SampleCoverage    = GL_SAMPLE_COVERAGE,     ProgramPointSize       = GL_PROGRAM_POINT_SIZE,
    SampleShading     = GL_SAMPLE_SHADING,      DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
    SampleMask        = GL_SAMPLE_MASK,         SampleAlphaToCoverage  = GL_SAMPLE_ALPHA_TO_COVERAGE,
    PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
    PointSize = GL_POINT_SIZE, PointSmooth = GL_POINT_SMOOTH
  };

  enum class blend_func_type : GLenum
  {
    Zero                  = GL_ZERO,                     One                   = GL_ONE,
    SrcColor              = GL_SRC_COLOR,                OneMinusSrcAlpha      = GL_ONE_MINUS_SRC_ALPHA,
    OneMinusSrcColor      = GL_ONE_MINUS_SRC_COLOR,      DstAlpha              = GL_DST_ALPHA,
    DstColor              = GL_DST_COLOR,                OneMinusDstAlpha      = GL_ONE_MINUS_DST_ALPHA,
    OneMinusDstColor      = GL_ONE_MINUS_DST_COLOR,      ConstantColor         = GL_CONSTANT_COLOR,
    SrcAlpha              = GL_SRC_ALPHA,                OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
    OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA, ConstantAlpha         = GL_CONSTANT_ALPHA,
  };


  enum class deth_func_type : GLenum
  {
    Never       = GL_NEVER,
    Less        = GL_LESS,
    Equal       = GL_EQUAL,
    LessEqual   = GL_LEQUAL,
    Greater     = GL_GREATER,
    NotEqual    = GL_NOTEQUAL,
    GreatEqual  = GL_GEQUAL,
    Always      = GL_ALWAYS
  };

  enum class textures_num : GLenum
  {
    Texture00 = GL_TEXTURE0,  Texture11 = GL_TEXTURE11,  Texture22 = GL_TEXTURE22,
    Texture01 = GL_TEXTURE1,  Texture12 = GL_TEXTURE12,  Texture23 = GL_TEXTURE23,
    Texture02 = GL_TEXTURE2,  Texture13 = GL_TEXTURE13,  Texture24 = GL_TEXTURE24,
    Texture03 = GL_TEXTURE3,  Texture14 = GL_TEXTURE14,  Texture25 = GL_TEXTURE25,
    Texture04 = GL_TEXTURE4,  Texture15 = GL_TEXTURE15,  Texture26 = GL_TEXTURE26,
    Texture05 = GL_TEXTURE5,  Texture16 = GL_TEXTURE16,  Texture27 = GL_TEXTURE27,
    Texture06 = GL_TEXTURE6,  Texture17 = GL_TEXTURE17,  Texture28 = GL_TEXTURE28,
    Texture07 = GL_TEXTURE7,  Texture18 = GL_TEXTURE18,  Texture29 = GL_TEXTURE29,
    Texture08 = GL_TEXTURE8,  Texture19 = GL_TEXTURE19,  Texture30 = GL_TEXTURE30,
    Texture09 = GL_TEXTURE9,  Texture20 = GL_TEXTURE20,  Texture31 = GL_TEXTURE31,
    Texture10 = GL_TEXTURE10, Texture21 = GL_TEXTURE21,
  };
}

