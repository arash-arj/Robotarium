#include "common/Mesh.hpp"

using namespace Robotarium;
using namespace common;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::AddSubMesh(SubMeshPtr _sub)
{
  this->mSubMeshes.push_back(_sub);
}

void Mesh::SetPath(const Robotarium::String &_path)
{
	this->mName = _path;
}

Robotarium::String Mesh::GetPath() const
{
	return this->mPath;
}

void Mesh::SetName(const Robotarium::String &_name)
{
	this->mName = _name;
}

Robotarium::String Mesh::GetName() const
{
	return this->mName;
}

Robotarium::UInt32 Mesh::GetSubMeshCount() const
{
	return this->mSubMeshes.size();
}

const SubMeshPtr Mesh::GetSubMesh(unsigned int i) const
{
	if (i < this->mSubMeshes.size())
		return this->mSubMeshes[i];
	else
	{
		LogErr << "Invalid index: " << i << " >= " << this-mSubMeshes.size() << std::endl;
		return 0;
	}
}

const SubMeshPtr Mesh::GetSubMesh(const std::string &_name) const
{
	// Find the submesh with the provided name.
	for (std::vector<SubMeshPtr>::const_iterator iter = this->mSubMeshes.begin();
		iter != this->mSubMeshes.end(); ++iter)
	{
		if ((*iter)->GetName() == _name)
			return *iter;
	}

	return NULL;
}
