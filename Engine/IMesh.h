#pragma once

#include "NObj.h"
#include "NPrimitiveTopology.h"
#include "NVector3.h"

namespace Nully
{
  class IMesh
  {
  public:
    virtual NPrimitiveTopology GetTopology() = 0;
    virtual void SetTopology(const NPrimitiveTopology a_topology) = 0;
	virtual const NVector3& GetBoundingMin() = 0;
	virtual const NVector3& GetBoundingMax() = 0;
	virtual void SetBoundingMin(const NVector3& a_min) = 0;
	virtual void SetBoundingMax(const NVector3& a_max) = 0;

    virtual ~IMesh() {}
  };
}
