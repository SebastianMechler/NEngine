#pragma once

#include "NObj.h"
#include "NPrimitiveTopology.h"

namespace Nully
{
  class IMesh
  {
  public:
    //virtual bool Load(IGraphics* a_graphics, NObj& a_obj) const = 0;

    //virtual void Dummy() = 0;

    virtual NPrimitiveTopology GetTopology() = 0;
    virtual void SetTopology(const NPrimitiveTopology a_topology) = 0;

    virtual ~IMesh() {}
  };
}
