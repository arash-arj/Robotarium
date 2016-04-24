#pragma once
#ifndef __MESH_LOADER_HPP__
#define __MESH_LOADER_HPP__

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include "common/Types.hpp"
#include "common/Logger.hpp"
#include "common/Mesh.hpp"

namespace Robotarium
{
	namespace common
	{
		class MeshLoader
		{
		public:	static common::MeshPtr Import(Robotarium::String _path, Robotarium::String _name);
		};
	}
}

#endif