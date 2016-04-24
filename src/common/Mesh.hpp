#pragma once
#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "common/Types.hpp"
#include "common/Logger.hpp"

#include "OGRE/OgreMath.h"
//#include <OgreDataStream.h>

namespace Robotarium
{
	namespace common
	{
		class Mesh;

		class SubMesh;

		typedef boost::shared_ptr<Robotarium::common::Mesh> MeshPtr;

		typedef boost::shared_ptr<Robotarium::common::SubMesh> SubMeshPtr;

		typedef std::vector<MeshPtr> MeshVec;

		typedef std::vector<SubMeshPtr> SubMeshVec;

		typedef boost::shared_ptr<Robotarium::common::MeshVec> MeshVecPtr;


		class Mesh
		{
			/// \brief Constructor
		public: Mesh();

				/// \brief Destructor
		public: virtual ~Mesh();

				/// \brief Set the path which contains the mesh resource
				/// \param[in] _path the file path
		public: void SetPath(const Robotarium::String &_path);

				/// \brief Get the path which contains the mesh resource
				/// \return the path to the mesh resource
		public: Robotarium::String GetPath() const;

				/// \brief Set the name of this mesh
				/// \param[in] _n the name to set
		public: void SetName(const Robotarium::String &_n);

				/// \brief Get the name of this mesh
				/// \return the name
		public: Robotarium::String GetName() const;

				/// \brief Return the number of vertices
				/// \return the count
		public: Robotarium::UInt32 GetVertexCount() const;

				/// \brief Return the number of normals
				/// \return the count
		public: Robotarium::UInt32 GetNormalCount() const;

				/// \brief Return the number of indices
				/// \return the count
		public: Robotarium::UInt32 GetIndexCount() const;

				/// \brief Return the number of texture coordinates
				/// \return the count
		public: Robotarium::UInt32 GetTexCoordCount() const;

				/// \brief Add a submesh mesh.
				/// The Mesh object takes ownership of the submesh.
				/// \param[in] _child the submesh
		public: void AddSubMesh(SubMeshPtr _child);

				/// \brief Get the number of children
				/// \return the count
		public: Robotarium::UInt32 GetSubMeshCount() const;

				/// \brief Get a child mesh
				/// \param[in] _i the index
				/// \return the submesh. An exception is thrown if the index is out of
				/// bounds
		public: const SubMeshPtr GetSubMesh(unsigned int _i) const;

				/// \brief Get a child mesh by name.
				/// \param[in] _name Name of the submesh.
				/// \return The submesh, NULL if the _name is not found.
		public: const SubMeshPtr GetSubMesh(const std::string &_name) const;

				/// \brief The name of the mesh
		private: Robotarium::String mName;

				 /// \brief The path of the mesh resource
		private: Robotarium::String mPath;

				 /// \brief The sub mesh array.
		private: SubMeshVec mSubMeshes;
		};

		class SubMesh
		{
			/// \brief Constructor
		public: SubMesh();

				/// \brief Copy Constructor
				//public: SubMesh(const SubMesh *_mesh);

				/// \brief Destructor
		public: virtual ~SubMesh();

				/// \brief Set the name of this mesh
				/// \param[in] _n the name to set
		public: void SetName(const Robotarium::String &_n);

				/// \brief Get the name of this mesh
				/// \return the name
		public: Robotarium::String GetName() const;

				/// \brief Add an index to the mesh
				/// \param[in] _index the new vertex index
		public: void AddIndex(Robotarium::UInt32 _index);

				/// \brief Add a vertex to the mesh
				/// \param[in] _vertex the new position
		public: void AddVertex(const Robotarium::Vec3 &_vertex);

				/// \brief Add a vertex to the mesh
				/// \param[in] _x position along x
				/// \param[in] _y position along y
				/// \param[in] _z position along z
		public: void AddVertex(double _x, double _y, double _z);

				/// \brief Add a normal to the mesh
				/// \param[in] _normal the normal
		public: void AddNormal(const Robotarium::Vec3 &_normal);

				/// \brief Add a normal to the mesh
				/// \param[in] _x position along x
				/// \param[in] _y position along y
				/// \param[in] _z position along z
		public: void AddNormal(double _x, double _y, double _z);

				/// \brief Add a texture coord to the mesh
				/// \param[in] _u position along u
				/// \param[in] _v position along v
		public: void AddTexCoord(double _u, double _v);

				/// \brief Add a texture coord to the mesh
				/// \param[in] _tex_coord the texture coord
		public: void AddTexCoord(const Robotarium::Vec2 &_tex_coord);


				/// \brief Get a vertex
				/// \param[in] _i the vertex index
				/// \return the position or throws an exception
		public: Robotarium::Vec3 GetVertex(Robotarium::UInt32 _i) const;

				/// \brief Set a vertex
				/// \param[in] _i the index
				/// \param[in] _v the position
		public: void SetVertex(Robotarium::UInt32 _i, const Robotarium::Vec3 &_vertex);

				/// \brief Get a normal
				/// \param[in] _i the normal index
				/// \return the orientation of the normal, or throws an exception
		public: Robotarium::Vec3 GetNormal(Robotarium::UInt32 _i) const;

				/// \brief Set a normal
				/// \param[in] _i the normal index
				/// \param[in] _n the normal direction
		public: void SetNormal(Robotarium::UInt32 _i, const Robotarium::Vec3 &_n);

				/// \brief Get a tex coord
				/// \param[in] _i the texture index
				/// \return the texture coordinates
		public: Robotarium::Vec2 GetTexCoord(Robotarium::UInt32 _i) const;

				/// \brief Set a tex coord
				/// \param[in] _i
				/// \param[in] _t
		public: void SetTexCoord(Robotarium::UInt32 _i, const Robotarium::Vec2 &_t);

				/// \brief Get an index
				/// \param[in] _i
		public: Robotarium::UInt32 GetIndex(Robotarium::UInt32 _i) const;

				/// \brief Return the number of vertices
		public: Robotarium::UInt32 GetVertexCount() const;

				/// \brief Return the number of normals
		public: Robotarium::UInt32 GetNormalCount() const;

				/// \brief Return the number of indicies
		public: Robotarium::UInt32 GetIndexCount() const;

				/// \brief Return the number of texture coordinates
		public: Robotarium::UInt32 GetTexCoordCount() const;
				
				/// \brief Put all the data into flat arrays
				/// \param[in] _verArr
				/// \param[in] _indArr
		public: void FillArrays(float **_vertArr, int **_indArr) const;
				
				/// \brief Put all the data into flat arrays
				/// \param[in] _verArr
				/// \param[in] _indArr
		public: void FillArrays2(float **_vertArr, uint32_t **_indArr) const;

				/// \brief Scale all vertices by _factor
				/// \param[in] _factor Scaling factor
		public: void Scale(Robotarium::Real _factor);

				/// \brief Move all vertices by _vec.
				/// \param[in] _vec Amount to translate vertices.
		public: void Translate(const Robotarium::Vec3 &_vec);

				/// \brief Scale all vertices by the _factor vector
				/// \param[in] _factor Scaling vector
		public: void SetScale(const Robotarium::Vec3 &_factor);

				/// \brief The name of the SubMesh
		private: Robotarium::String mName;

				 /// \brief the vertex array
		private: std::vector< Robotarium::Vec3 > mVertices;

				 /// \brief the vertex index array
		private: std::vector<Robotarium::UInt32> mIndices;

				 /// \brief the normal array
		private: std::vector< Robotarium::Vec3 > mNormals;

				 /// \brief the texture coordinate array
		private: std::vector< Robotarium::Vec2 > mTexCoords;

				 /// \brief Indicates that the mesh has been changed
		public:	void SetDirty();

		};
	}
}

#endif