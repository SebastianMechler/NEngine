#include "NObj.h"

namespace Nully
{
  NObj::NObj()
    : m_hasUvs(false)
  {
  }

  NObj::NObj(const char * a_file)
    : m_hasUvs(false)
  {
    Load(a_file);
  }

  bool NObj::Load(const char * a_file)
  {
    if (a_file == nullptr)
    {
      return false;
    }

    // Open File and Read the Size
    NFile obj;
    if (obj.Open(a_file, NFileMode::Read) != NResult::Success)
    {
      return false;
    }

    auto size = static_cast<uint32_t>(obj.GetFileSize(a_file));

    // wrong size? return
    if (size == 0)
    {
      return false;
    }

    // create unique_ptr so the delete[] will be called on leaving scope
    NSmartArrayPtr<char> buffer = new char[size + 1];

    // buffer which will be incremented and worked with
    char* workBuffer = buffer.Get();

    // read the whole file into buffer
    obj.Read(workBuffer, size);
    *(workBuffer + size) = '\0'; // set zero termination

    bool isWorkDone = false;
    uint32_t lineLength = 0;
    NObjDataType type = NObjDataType::Unused;

    size_t numVertices = 0;
    size_t numNormals = 0;
    size_t numUvs = 0;
    size_t numFaces = 0;

    // read whole file and check how many vertices, ... we've got
    while (!isWorkDone)
    {
      type = GetObjType(workBuffer); // get object type from the first two characters

      lineLength = GetNewLineLength(workBuffer, isWorkDone); // find the length of the line which is determined by '\n' character
      switch (type)
      {
      case NObjDataType::Vertex:
        numVertices++;
        break;
      case NObjDataType::Normal:
        numNormals++;
        break;
      case NObjDataType::Name:
        break;
      case NObjDataType::Uv:
        numUvs++;
        break;
      case NObjDataType::Face:
        // check what faceType we've got
        // quad or triangulated
        
        numFaces++;
        break;
      case NObjDataType::Unused:
        break;
      default:
        break;
      }

      // increment the buffer which will then point to the next line
      workBuffer += lineLength;
    }

    isWorkDone = false;
    lineLength = 0;
    type = NObjDataType::Unused;
    workBuffer = buffer.Get();

    m_vertices.reserve(numVertices);
    m_normals.reserve(numNormals);
    m_faces.reserve(numFaces);
    m_uvs.reserve(numUvs);


    while (!isWorkDone)
    {
      type = GetObjType(workBuffer); // get object type from the first two characters

      lineLength = GetNewLineLength(workBuffer, isWorkDone); // find the length of the line which is determined by '\n' character
      switch (type)
      {
      case NObjDataType::Vertex:
      case NObjDataType::Normal:
        ToNVector3(workBuffer, type, lineLength);
        break;
      case NObjDataType::Name:
        ToName(workBuffer, lineLength);
        break;
      case NObjDataType::Uv:
        ToUV(workBuffer, lineLength);
        break;
      case NObjDataType::Face:
        ToFace(workBuffer, lineLength);
        break;
      case NObjDataType::Unused:
        break;
      default:
        break;
      }

      // increment the buffer which will then point to the next line
      workBuffer += lineLength;
    }

    return true;
  }
  NVertex& NObj::GetVertices()
  {
    return m_vertices;
  }
  NVertex& NObj::GetNormals()
  {
    return m_normals;
  }
  NFaces& NObj::GetFaces()
  {
    return m_faces;
  }
  NString& NObj::GetName()
  {
    return m_objName;
  }
  NUvs& NObj::GetUVs()
  {
    return m_uvs;
  }
  bool NObj::HasUVs() const
  {
    return m_hasUvs;
  }
  const NVector3& NObj::GetMin()
  {
	  return m_min;
  }
  const NVector3& NObj::GetMax()
  {
	  return m_max;
  }
  NObjDataType NObj::GetObjType(char * a_buffer)
  {
    if (a_buffer == nullptr)
    {
      return NObjDataType::Unused;
    }

    char objType[2];
    objType[0] = *a_buffer;
    objType[1] = *(a_buffer + 1);

    if (objType[0] == 'v' && objType[1] == 'n')
    {
      return NObjDataType::Normal;
    }
    if (objType[0] == 'v' && objType[1] == 't')
    {
      return NObjDataType::Uv;
    }
    else if (objType[0] == 'v')
    {
      return NObjDataType::Vertex;
    }
    else if (objType[0] == 'f')
    {
      return NObjDataType::Face;
    }
    else if (objType[0] == 'o')
    {
      return NObjDataType::Name;
    }
    else
    {
      return NObjDataType::Unused;
    }
  }
  void NObj::ToNVector3(char* a_buffer, NObjDataType a_type, uint32_t a_lineLength)
  {
    NVector3 tmp;

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    char dirt;
    if (a_type == NObjDataType::Vertex)
    {
      // this is a vertex
      // v 0.137950 0.980785 -0.137950
      sscanf_s(a_buffer, "%c %f %f %f", &dirt, 1, &tmp.x, &tmp.y, &tmp.z);

	  // min values for collider
	  if (tmp.x < m_min.x)
	  {
		  m_min.x = tmp.x;
	  }
	  
	  if (tmp.y < m_min.y)
	  {
		  m_min.y = tmp.y;
	  }
	  
	  if (tmp.z < m_min.z)
	  {
		  m_min.z = tmp.z;
	  }

	  // max values
	  if (tmp.x > m_max.x)
	  {
		  m_max.x = tmp.x;
	  }

	  if (tmp.y > m_max.y)
	  {
		  m_max.y = tmp.y;
	  }

	  if (tmp.z > m_max.z)
	  {
		  m_max.z = tmp.z;
	  }

      m_vertices.push_back(tmp);
    }
    else if (a_type == NObjDataType::Normal)
    {
      // this is a vertex normal
      // vn 0.0464 0.8810 -0.4709
      sscanf_s(a_buffer, "%c%c %f %f %f", &dirt, 1, &dirt, 1, &tmp.x, &tmp.y, &tmp.z);
      m_normals.push_back(tmp);
    }
  }

  void NObj::ToName(char* a_buffer, uint32_t a_lineLength)
  {
    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

                                          // incoming buffer looks like:
                                          // o Cube
                                          // so we have to move by two bytes
    m_objName = NString(a_buffer + 2, a_lineLength - 2);
  }
  void NObj::ToFace(char * a_buffer, uint32_t a_lineLength)
  {
    NFace face = {};

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    if (m_hasUvs)
    {
      char tmp;
      sscanf_s(a_buffer, "%c %u/%u/%u %u/%u/%u %u/%u/%u",
              &tmp, 1,
              &face.v1, &face.uv1, &face.normalIndex, // faceID//uvID//normalID
              &face.v2, &face.uv2, &face.normalIndex,
              &face.v3, &face.uv3, &face.normalIndex);
    }
    else
    {
      char tmp;
      sscanf_s(a_buffer, "%c %u//%u %u//%u %u//%u",
              &tmp, 1,
              &face.v1, &face.normalIndex, // faceID//normalID
              &face.v2, &face.normalIndex,
              &face.v3, &face.normalIndex);
    }

    m_faces.push_back(face);
  }
  void NObj::ToUV(char * a_buffer, uint32_t a_lineLength)
  {
    m_hasUvs = true;

    NVector2 tmp;

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    char dirt;
    // vt 0.853468120098 0.894985675812
    sscanf_s(a_buffer, "%c%c %f %f", &dirt, 1, &dirt, 1, &tmp.x, &tmp.y);
    m_uvs.push_back(tmp);
  }
  uint32_t NObj::GetNewLineLength(const char* buffer, bool& a_isNullterminationFound)
  {
    for (uint32_t i = 0; i < 1024; i++)
    {
      if (*buffer == '\n')
      {
        // found new line
        return i + 1;
      }
      else if (*buffer == '\0')
      {
        // end is found
        a_isNullterminationFound = true;
        return i + 1;
      }

      buffer++;
    }

    a_isNullterminationFound = true;
    return 0;
  }
}

