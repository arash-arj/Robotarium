#include "MeshLoader.hpp"

using namespace Robotarium;
using namespace common;


//common::MeshPtr MeshLoader::Import(Robotarium::String _path, Robotarium::String _name)
//{
//assimp:
//	AssimpLoader::AssOptions opts;
//	opts.quietMode = false;
//	opts.logFile = "ass.log";
//	opts.customAnimationName = "";
//	opts.dest = "";
//	opts.animationSpeedModifier = 1.0;
//	opts.lodValue = 250000;
//	opts.lodFixed = 0;
//	opts.lodPercent = 20;
//	opts.lodStrategy = "Distance";
//	opts.numLods = 0;
//	opts.usePercent = true;
//	opts.params = (AssimpLoader::LP_GENERATE_SINGLE_MESH);
//	opts.source = _path;
//
//	Ogre::MeshPtr mesh;
//	Ogre::SkeletonPtr skeleton;
//
//	AssimpLoader loader;
//	if(loader.convert(opts, &mesh, &skeleton))
//	{
//		if(skeleton.getPointer())
//		{
//			mesh.getPointer()->_notifySkeleton(skeleton);
//			mesh.getPointer()->setSkeletonName(skeleton.getPointer()->getName());
//		}
//
//		mesh = mesh.getPointer()->clone(_name);
//	}
//	else
//	{
//		LogErr << "Error when importing 3d file: Not supported by Robotarium, look into the asslog for details." << std::endl;
//	}
//
//	Robotarium::common::MeshPtr mesh_ptr(static_cast<common::Mesh*>(mesh.getPointer()));
//
//	return mesh_ptr;
//
//
//}


common::MeshPtr MeshLoader::Import(const Robotarium::String _path, const Robotarium::String _name)
{
	common::MeshPtr _dest(new common::Mesh());

	Assimp::Importer importer;
	const aiScene * modelScene = importer.ReadFile(_path.c_str(),
		aiProcess_MakeLeftHanded|
		aiProcess_FlipWindingOrder|
		aiProcess_FlipUVs|
		aiProcess_PreTransformVertices|
		aiProcess_CalcTangentSpace|
		aiProcess_GenSmoothNormals|
		aiProcess_Triangulate|
		aiProcess_FixInfacingNormals|
		aiProcess_FindInvalidData |
		aiProcess_ValidateDataStructure | 0
		);

	if(!modelScene)
	{
		LogErr << "Error when importing 3d file: "\
			"Not supported by Robotarium,"\
			"look into the asslog for details." << std::endl;
		return NULL;
	}

	for (unsigned int n = 0; n < modelScene->mNumMeshes; ++n)
	{
		const aiMesh* mesh = modelScene->mMeshes[n];

		common::SubMeshPtr sub_mesh(new common::SubMesh());

		sub_mesh->SetName(mesh->mName.C_Str());

		for (unsigned int t = 0; t < mesh->mNumVertices; ++t) 
		{

			sub_mesh->AddVertex(mesh->mVertices[t].x, mesh->mVertices[t].y, mesh->mVertices[t].z);

			if(mesh->HasNormals())
				sub_mesh->AddNormal(mesh->mNormals[t].x, mesh->mNormals[t].y, mesh->mNormals[t].z);

			if(mesh->HasTextureCoords(0))
				sub_mesh->AddTexCoord(mesh->mTextureCoords[0][t].x, mesh->mTextureCoords[0][t].y);
		}		
		
		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) 
		{
			const aiFace* face = &mesh->mFaces[t];
			sub_mesh->AddIndex(face->mIndices[0]);
			sub_mesh->AddIndex(face->mIndices[1]);
			sub_mesh->AddIndex(face->mIndices[2]);
		}
		
		if(sub_mesh->GetName().empty())
		{
			sub_mesh->SetName(_name + "_" + Ogre::StringConverter::toString(n));
		}
		
		std::cout << "~~~~~SubMesh added~~~~~~" << std::endl;
		std::cout << "         Name~~~~~~~~~~~" << sub_mesh->GetName() << std::endl;
		std::cout << "  VertexCount~~~~~~~~~~~" << sub_mesh->GetVertexCount() << std::endl;
		std::cout << "  NormalCount~~~~~~~~~~~" << sub_mesh->GetNormalCount() << std::endl;
		std::cout << "   IndexCount~~~~~~~~~~~" << sub_mesh->GetIndexCount() << std::endl;
		std::cout << "TexCoordCount~~~~~~~~~~~" << sub_mesh->GetTexCoordCount() << std::endl;
		_dest->AddSubMesh(sub_mesh);
	}

	_dest->SetName(_name);

	return _dest;
}