#pragma once

#include <raiigl/types.hpp>
#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/gl330.hpp>
#include <raiigl/gl430.hpp>


namespace raiigl {

  struct gl_context : public classes::non_copyable
  {
    inline static gl_context * get_current()
    { /**< @todo */ return nullptr; }

    template<typename Tgl>
    inline Tgl * get_version()
    { /**< @todo */ return nullptr; }

  };


  // ---- ---- Get version specialisation ---- ----

  template<>
  inline gl330 * gl_context::get_version()
  { /**< @todo */ return nullptr;  }

  template<>
  inline gl430 * gl_context::get_version()
  { /**< @todo */ return nullptr;  }


}

