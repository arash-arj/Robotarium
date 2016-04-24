#include "core/Manager.hpp"

using namespace Robotarium;
using namespace core;

core::Manager::Manager(MANAGER_TYPE _type, Robotarium::String _name, Robotarium::Int32 _id)
{
	this->mManagerType = _type;
	this->mName = _name;
	this->mID = _id;
}

core::Manager::~Manager()
{
}

Robotarium::String core::Manager::GetName()
{
	return this->mName;
}

void core::Manager::SetName(Robotarium::String _name)
{
	this->mName = _name;
}

Robotarium::Int32 core::Manager::GetID()
{
	return this->mID;
}