#pragma once

namespace Nully
{
  enum class NPrimitiveTopology
  {
    PointList, // points are not connected
    TriangleList, // triangles are not connected
    TriangleStrip, // triangles are connected
    LineList, // lines are not connected
    LineStrip, // lines are connected
  };
}
