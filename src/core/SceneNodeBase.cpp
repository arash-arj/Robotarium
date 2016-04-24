#include "core/SceneNodeBase.hpp"

using namespace Robotarium;
using namespace core;

SceneNodeBase::SceneNodeBase(String name): 
	Node(name)
{
	this->SetName(name);
	this->SetInitialized(false);
	this->SetLoaded(false);
}

SceneNodeBase::~SceneNodeBase()
{
}

Robotarium::Bool SceneNodeBase::IsLoaded()
{
	return this->mLoaded;
}

Robotarium::Bool SceneNodeBase::IsInitialized()
{
	return this->mInitialized;
}

void SceneNodeBase::SetInitialized(Robotarium::Bool _is_initialized)
{
	this->mInitialized = _is_initialized;
}

void SceneNodeBase::SetLoaded(Robotarium::Bool _is_loaded)
{
	this->mLoaded = _is_loaded;
}
