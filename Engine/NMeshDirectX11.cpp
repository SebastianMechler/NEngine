#include "NMeshDirectX11.h"

#include "NMemory.h"

namespace Nully
{
  NPrimitiveTopology NMeshDirectX11::GetTopology()
  {
    return m_primitiveTopology;
  }
  void NMeshDirectX11::SetTopology(const NPrimitiveTopology a_topology)
  {
    m_primitiveTopology = a_topology;
  }
  const NVector3& NMeshDirectX11::GetBoundingMin()
  {
	  return m_boundingMin;
  }
  const NVector3& NMeshDirectX11::GetBoundingMax()
  {
	  return m_boundingMax;
  }
  void NMeshDirectX11::SetBoundingMin(const NVector3& a_min)
  {
	  m_boundingMin = a_min;
  }
  void NMeshDirectX11::SetBoundingMax(const NVector3& a_max)
  {
	  m_boundingMax = a_max;
  }
  NMeshDirectX11* NMeshDirectX11::Load(ID3D11Device* a_device, NObj& a_obj)
  {
    NFaces faces = a_obj.GetFaces();
    NVertex normals = a_obj.GetNormals();
    NUvs uvs = a_obj.GetUVs();
    bool hasUvs = a_obj.HasUVs();

    uint32_t numIndices = 3;
    NVertex verts = a_obj.GetVertices();
    NVertexDefault* vertices = new NVertexDefault[faces.size() * numIndices];
    NSmartArrayPtr<NVertexDefault> safeDeletevertices = vertices; // prevent memory leak
    
    uint32_t i = 0;
    for (auto& face : faces)
    {
      vertices[i].normal = normals[face.normalIndex - 1];
      vertices[i].position = verts[face.v1 - 1];
      (hasUvs) ? vertices[i].uv = uvs[face.uv1 - 1] : vertices[i].uv = NVector2(1.0f, 1.0f);

      vertices[i + 1].normal = normals[face.normalIndex - 1];
      vertices[i + 1].position = verts[face.v2 - 1];
      (hasUvs) ? vertices[i + 1].uv = uvs[face.uv2 - 1] : vertices[i + 1].uv = NVector2(1.0f, 1.0f);


      vertices[i + 2].normal = normals[face.normalIndex - 1];
      vertices[i + 2].position = verts[face.v3 - 1];
      (hasUvs) ? vertices[i + 2].uv = uvs[face.uv3 - 1] : vertices[i + 2].uv = NVector2(1.0f, 1.0f);

      i += numIndices;
    }
    
    NMeshDirectX11* mesh = new NMeshDirectX11();
    
    if (!mesh->m_vertexBuffer.Load(a_device, vertices, faces.size() * numIndices))
    {
      NSafeDelete(mesh);
      return nullptr;
    }
    
	mesh->SetBoundingMin(a_obj.GetMin());
	mesh->SetBoundingMax(a_obj.GetMax());

    return mesh;
  }
  NMeshDirectX11* NMeshDirectX11::LoadAABB(ID3D11Device* a_device, const NAABB& a_aabb)
  {
	  if (!a_device)
	  {
		  return nullptr;
	  }

	  NVector3 a_min = a_aabb.center - a_aabb.size;
	  NVector3 a_max = a_aabb.center + a_aabb.size;

	  // create geometry
	  const uint32_t numVerts = 8;

	  NVertexDefault vertices[numVerts];
	  vertices[0].position = NVector3(a_min.x, a_min.y, a_max.z); // bottmLeft (FRONT)
	  vertices[1].position = NVector3(a_max.x, a_min.y, a_max.z); // bottomRight (FRONT)
	  vertices[2].position = NVector3(a_max.x, a_max.y, a_max.z); // topRight (FRONT)
	  vertices[3].position = NVector3(a_min.x, a_max.y, a_max.z); // topLeft (FRONT)

	  vertices[4].position = NVector3(a_min.x, a_min.y, a_min.z); // bottmLeft (BACK)
	  vertices[5].position = NVector3(a_max.x, a_min.y, a_min.z); // bottomRight (BACK)
	  vertices[6].position = NVector3(a_max.x, a_max.y, a_min.z); // topRight (BACK)
	  vertices[7].position = NVector3(a_min.x, a_max.y, a_min.z); // topLeft (BACK)

	  const uint32_t numIndices = 12 * 2; // 12 lines * 2 (12 lines must be defined by two points to draw a line)
	  uint32_t indices[numIndices] =
	  {
		// FRONT
		0, 1, // bottomLeft to bottomRight
		1, 2, // bottomRight to topRight
		0, 3, // bottomLeft to topLeft
		3, 2, // topLeft to topRight

		// BACK
		4, 5, // bottomLeft to bottomRight
		5, 6, // bottomRight to topRight
		4, 7, // bottomLeft to topLeft
		7, 6, // topLeft to topRight

		// LINES BETWEEN FRONT AND BACK
		3, 7, // topLeft (FRONT) to topLeft (BACK)
		2, 6, // topRight (FRONT) to topRight (BACK)
		0, 4, // bottomLeft (FRONT) to bottomLeft (BACK)
		1, 5, // bottomRight (FRONT) to bottomRight (BACK)
	  };


	  NMeshDirectX11* mesh = new NMeshDirectX11();
	  if (!mesh)
	  {
		  return nullptr;
	  }

	  // create vertex buffer
	  if (!mesh->m_vertexBuffer.Load(a_device, vertices, numVerts))
	  {
		  NSafeDelete(mesh);
		  return nullptr;
	  }

	  // set topology
	  mesh->SetTopology(NPrimitiveTopology::LineList);

	  // create index buffer
	  if (!mesh->m_indexBuffer.Create(a_device, indices, numIndices))
	  {
		  NSafeDelete(mesh);
		  return nullptr;
	  }

	  return mesh;
  }
  NMeshDirectX11* NMeshDirectX11::LoadTerrain(ID3D11Device* a_device, float a_width, float a_depth, uint32_t a_m, uint32_t a_n)
  {
    float dx = a_width / a_m; // deltaX
    float dz = a_depth / a_n; // deltaZ

    float du = 1.0f / a_m; // delta U coordinate
    float dv = 1.0f / a_n; // delta V coordinate

    uint32_t numVerts = (a_m+1) * (a_n+1);
    uint32_t numFaces = a_m * a_n * 2;
    uint32_t numIndices = numFaces * 3;

    NVertexDefault* terrain = new NVertexDefault[numVerts];
    NSmartArrayPtr<NVertexDefault> safeDeletevertices = terrain; // prevent memory leak

    // Create terrain grid
    for (uint32_t m = 0; m < a_m; m++)
    {
      for (uint32_t n = 0; n < a_n; n++)
      {
        terrain[m*a_n + n].position = NVector3(m * dx, 0.0f, n * dz);
        terrain[m*a_n + n].normal = NVector3::up;
        terrain[m*a_n + n].uv = NVector2(m * du, n * dv);
      }
    }

    uint32_t* indices = new uint32_t[numIndices];
    NSmartArrayPtr<uint32_t> safeDeleteIndices = indices; // prevent memory leak

    uint32_t currentIndex = 0;

    // Create index buffer
    for (uint32_t m = 0; m < a_m-1; m++)
    {
      for (uint32_t n = 0; n < a_n-1; n++)
      {
        terrain[m*a_n + n]; // topLeft
        terrain[m*a_n + n + 1]; // bottomLeft
        terrain[m*a_n + a_n + n]; // topRight
        terrain[m*a_n + a_n + n + 1]; // bottomRight

        // first triangle
        indices[currentIndex] = m*a_n + n + 1; // bottomLeft
        indices[currentIndex+1] = m*a_n + n; // topLeft
        indices[currentIndex+2] = m*a_n + a_n + n + 1; // bottomRight

        // second triangle
        indices[currentIndex+3] = m*a_n + a_n + n + 1; // bottomRight
        indices[currentIndex+4] = m*a_n + n; // topLeft
        indices[currentIndex+5] = m*a_n + a_n + n; // topRight

        currentIndex += 6;
      }
    }

    NMeshDirectX11* mesh = new NMeshDirectX11();

    if (!mesh)
    {
      return nullptr;
    }

    mesh->SetTopology(NPrimitiveTopology::TriangleList);

    if (!mesh->m_vertexBuffer.Load(a_device, terrain, numVerts))
    {
      NSafeDelete(mesh);
      return nullptr;
    }

    if (!mesh->m_indexBuffer.Create(a_device, indices, numIndices))
    {
      NSafeDelete(mesh);
      return nullptr;
    }

    return mesh;
  }
  void NMeshDirectX11::Set(ID3D11DeviceContext* a_deviceContext)
  {
    if (a_deviceContext)
    {
      m_vertexBuffer.SetBuffer(a_deviceContext);

      if (m_indexBuffer.GetCount() > 0)
      {
        m_indexBuffer.SetBuffer(a_deviceContext);
      }
    }
  }
  NMeshDirectX11::NMeshDirectX11()
    : m_primitiveTopology(NPrimitiveTopology::TriangleList)
  {
  }
  NMeshDirectX11::~NMeshDirectX11()
  {
  }
}
