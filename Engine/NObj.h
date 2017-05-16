#pragma once

#include <iostream>

#include "NObjFace.h"
#include "NObjDataType.h"
#include "NVector3.h"
#include "NString.h"
#include "NFile.h"
#include "NVector.h"
#include "NVector2.h"
#include "NMemory.h"

namespace Nully
{
  typedef NVector<NVector3> NVertex;
  typedef NVector<NFace> NFaces;
  typedef NVector<NVector2> NUvs;

  class NObj
  {
  public:
    NObj();
    NObj(const char* a_file);
    bool Load(const char* a_file);

    NVertex& GetVertices();
    NVertex& GetNormals();
    NFaces& GetFaces();
    NString& GetName();
    NUvs& GetUVs();
    bool HasUVs() const;

  private:
    NObjDataType GetObjType(char* buffer);
    void ToNVector3(char* a_buffer, NObjDataType a_type, uint32_t a_lineLength);
    void ToName(char* a_buffer, uint32_t a_lineLength);
    void ToFace(char* a_buffer, uint32_t a_lineLength);
    void ToUV(char* a_buffer, uint32_t a_lineLength);

    uint32_t GetNewLineLength(const char* buffer, bool& a_isNullterminationFound);

    NString m_objName;
    NVertex m_vertices;
    NVertex m_normals;
    NFaces m_faces;
    NUvs m_uvs;

    bool m_hasUvs;
  };
}
