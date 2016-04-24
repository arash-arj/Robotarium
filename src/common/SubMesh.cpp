#include "common/Mesh.hpp"

using namespace Robotarium;
using namespace common;


SubMesh::SubMesh()
{
}

SubMesh::~SubMesh()
{
}

void SubMesh::SetName(const Robotarium::String &_name)
{
	this->mName = _name;
}

Robotarium::String SubMesh::GetName() const
{
	return this->mName;
}

void SubMesh::AddIndex(Robotarium::UInt32 _index)
{
	this->mIndices.push_back(_index);
}

Robotarium::UInt32 SubMesh::GetIndex(Robotarium::UInt32 _i) const
{
	if (_i >= this->mIndices.size())
	{
		LogErr << "Index out of bounds!" << std::endl;
		return 0;
	}

	return this->mIndices[_i];
}


void SubMesh::AddVertex(const Robotarium::Vec3 &_vertex)
{
	this->mVertices.push_back(_vertex);
}

void SubMesh::AddVertex(double _x, double _y, double _z)
{
	this->mVertices.push_back(Robotarium::Vec3(_x, _y, _z));
}

void SubMesh::AddTexCoord(double _u, double _v)
{
	this->mTexCoords.push_back(Robotarium::Vec2(_u, _v));
}

void SubMesh::AddTexCoord(const Robotarium::Vec2 &_tex_coord)
{
	this->mTexCoords.push_back(_tex_coord);
}

void SubMesh::AddNormal(const Robotarium::Vec3 &_normal)
{
	this->mNormals.push_back(_normal);
}

void SubMesh::AddNormal(double _x, double _y, double _z)
{
	this->mNormals.push_back(Robotarium::Vec3(_x, _y, _z));
}


Robotarium::Vec3 SubMesh::GetVertex(Robotarium::UInt32 _i) const
{
	if (_i >= this->mVertices.size())
	{
		LogErr << "Index out of bounds!" << std::endl;
		return Robotarium::Vec3::ZERO;
	}

	return this->mVertices[_i];
}


void SubMesh::SetVertex(Robotarium::UInt32 _i, const Robotarium::Vec3 &_vertex)
{
	if (_i >= this->mVertices.size())
	{
		LogErr << "Index out of bounds!" << std::endl;
		return;
	}

	this->mVertices[_i] = _vertex;
}


Robotarium::Vec3 SubMesh::GetNormal(Robotarium::UInt32 _i) const
{
	if (_i >= this->mNormals.size())
	{
		LogErr << "Index out of bounds!" << std::endl;
		return Robotarium::Vec3::ZERO;
	}

	return this->mNormals[_i];
}

void SubMesh::SetNormal(Robotarium::UInt32 _i, const Robotarium::Vec3 &_normal)
{
	if (_i >= this->mNormals.size())
	{
		LogErr << "Index out of bounds!" << std::endl;
		return;
	}

	this->mVertices[_i] = _normal;
}

Robotarium::UInt32 SubMesh::GetVertexCount() const
{
	return this->mVertices.size();
}

Robotarium::UInt32 SubMesh::GetNormalCount() const
{
	return this->mNormals.size();
}

Robotarium::UInt32 SubMesh::GetIndexCount() const
{
	return this->mIndices.size();
}

Robotarium::UInt32 SubMesh::GetTexCoordCount() const
{
	return this->mTexCoords.size();
}

void SubMesh::FillArrays(float **_vertArr, int **_indArr) const
{
	if (this->mVertices.empty() || this->mIndices.empty())
		LogErr << "No vertices or indices" << std::endl;

	std::vector< Robotarium::Vec3 >::const_iterator viter;
	std::vector< unsigned int >::const_iterator iiter;
	unsigned int i;

	if (*_vertArr)
		delete [] *_vertArr;

	if (*_indArr)
		delete [] *_indArr;

	*_vertArr = new float[this->mVertices.size() * 3];
	*_indArr = new int[this->mIndices.size()];

	for (viter = this->mVertices.begin(), i = 0; viter != this->mVertices.end();
		++viter)
	{
		(*_vertArr)[i++] = static_cast<float>((*viter).x);
		(*_vertArr)[i++] = static_cast<float>((*viter).y);
		(*_vertArr)[i++] = static_cast<float>((*viter).z);
	}

	for (iiter = this->mIndices.begin(), i = 0;
		iiter != this->mIndices.end(); ++iiter)
		(*_indArr)[i++] = (*iiter);
}



void SubMesh::FillArrays2(float **_vertArr, uint32_t **_indArr) const
{
	//if (this->mVertices.empty() || this->mIndices.empty())
	//	LogErr << "No vertices or indices" << std::endl;

	//std::vector< Robotarium::Vec3 >::const_iterator viter;
	//std::vector< unsigned int >::const_iterator iiter;
	//unsigned int i;

	//if (*_vertArr)
	//	delete [] *_vertArr;

	//if (*_indArr)
	//	delete [] *_indArr;

	//*_vertArr = new float[this->GetVertexCount() * 8];
	//*_indArr = new uint32_t[this->GetIndexCount()];


	for (unsigned int v = 0, i = 0; v < this->mVertices.size(); v++)
	{
		(*_vertArr)[i++] = static_cast<float>(mVertices[v].x);
		(*_vertArr)[i++] = static_cast<float>(mVertices[v].y);
		(*_vertArr)[i++] = static_cast<float>(mVertices[v].z);

		if(this->GetNormalCount() > 0)
		{
			(*_vertArr)[i++] = static_cast<float>(mNormals[v].x);
			(*_vertArr)[i++] = static_cast<float>(mNormals[v].y);
			(*_vertArr)[i++] = static_cast<float>(mNormals[v].z);
		}

		if(this->GetTexCoordCount() > 0)
		{
			(*_vertArr)[i++] = static_cast<float>(mTexCoords[v].x);
			(*_vertArr)[i++] = static_cast<float>(mTexCoords[v].y);
		}
	}

	for (unsigned int v = 0, i = 0; v < this->GetIndexCount(); v++)
	{
        (*_indArr)[i++] = this->GetIndex(v);
	}
	//for (iiter = this->mIndices.begin(), i = 0;
	//	iiter != this->mIndices.end(); ++iiter)
	//	(*_indArr)[i++] = (*iiter);
}


void SubMesh::Scale(double _factor)
{
	for (std::vector<Robotarium::Vec3>::iterator iter = this->mVertices.begin();
		iter != this->mVertices.end(); ++iter)
	{
		(*iter) *= _factor;
	}
}

void SubMesh::SetScale(const Robotarium::Vec3 &_factor)
{
	for (std::vector<Robotarium::Vec3>::iterator iter = this->mVertices.begin();
		iter != this->mVertices.end(); ++iter)
	{
		(*iter).x *= _factor.x;
		(*iter).y *= _factor.y;
		(*iter).z *= _factor.z;
	}
}

void SubMesh::Translate(const Robotarium::Vec3 &_vec)
{
	for (std::vector<Robotarium::Vec3>::iterator iter = this->mVertices.begin();
		iter != this->mVertices.end(); ++iter)
	{
		(*iter) += _vec;
	}
}

