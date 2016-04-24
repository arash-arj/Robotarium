#include "core/SceneNode.hpp"

using namespace Robotarium;
using namespace core;


SceneNode::SceneNode(Robotarium::String name)
	:SceneNodeBase(name), mChildNodes(new NodeVec())
{
	SetNodeType(SCENE_NODE_TYPE);
	this->SetName(name);
	this->SetPosition(Vec3::ZERO);
	this->SetOrientation(Quat::IDENTITY);
	this->mParent = 0;
}

SceneNode::~SceneNode()
{
}

void SceneNode::Init()
{

}

void SceneNode::Load()
{

}

void SceneNode::Update()
{

}


void SceneNode::Terminate()
{

}

void SceneNode::SetPosition(Vec3 pos)
{
	mPosition = pos;
}

Vec3 SceneNode::GetPosition()
{
	return mPosition;
}

Quat SceneNode::GetOrientation()
{
	return mOrientation;
}

Vec3 SceneNode::GetWorldPosition()
{
	if(!mParent)
	{
		return Robotarium::Vec3::ZERO;
	}
	else
	{
		return this->mParent->GetWorldPosition() + 
			this->mParent->GetWorldOrientation().Inverse()*mPosition;
	}
}

Quat SceneNode::GetWorldOrientation()
{
	if(!mParent)
	{
		return Quat::IDENTITY;
	}
	else
	{
		return (mOrientation)*(this->mParent->GetWorldOrientation());
	}
}

void SceneNode::SetOrientation(Quat rot)
{
	mOrientation = rot;
}

void SceneNode::SetOrientation(Real angle, Vec3 axis)
{
	mOrientation.FromAngleAxis(Ogre::Radian(angle), axis);
}

NodeVecPtr& SceneNode::GetChildNodeVec()
{
	return mChildNodes;
}

void SceneNode::AddNode(NodePtr _nodePtr)
{
	mChildNodes->insert(mChildNodes->end(), _nodePtr);
}

Robotarium::UInt32 SceneNode::GetNodeVecSize()
{
	return mChildNodes->size();
}

NodePtr SceneNode::GetChildNode(Robotarium::UInt32 _index)
{
	if(_index > this->mChildNodes->size())
	{
		std::cout << "Specified index out of bounds!" << std::endl;
		return 0;
	}
	return this->mChildNodes->at(_index);
}