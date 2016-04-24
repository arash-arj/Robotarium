#include "graphic/SceneNode.hpp"

using namespace Robotarium;
using namespace graphic;


SceneNode::SceneNode(String name, UInt32 Id)
	:SceneNodeBase(name, Id)
{
	SetNodeType(SCENE_NODE_TYPE);
	this->SetID(Id);
	this->SetName(name);
	this->SetPosition(Vec3(0,0,0));
}

SceneNode::~SceneNode()
{
}

void SceneNode::Load()
{

	mOgreSceneNode = RenderEngine::GetSingleton()->
		GetScene()->GetOgreSceneMgr()->getRootSceneNode()->createChildSceneNode(GetName());

	this->mAxisDebugShape = boost::shared_ptr<AxisDebugShape>(new AxisDebugShape(this->shared_from_this()));

	//if(parent)
	//{
	//	Ogre::LogManager::getSingleton().logMessage(GetName() + ": Inside if.");
	//	Ogre::LogManager::getSingleton().logMessage(GetName() + RenderEngine::GetSingleton()->
	//		GetScene()->GetOgreSceneMgr()->getRootSceneNode()->getName());
	//}

	//if (parent) // check if this is the RootSceneNode or not
	//{
	//	parent->AddNode(boost::static_pointer_cast<Node>
	//		(boost::make_shared<SceneNode>(*this)));
	//}

	//LoadChildNodes();

}

void SceneNode::Update()
{
	this->mOgreSceneNode->setPosition(mPosition);
	this->mOgreSceneNode->resetOrientation();
	this->mOgreSceneNode->setOrientation(mOrientation);

	this->UpdateChildNodes();
}

Ogre::SceneNode* SceneNode::GetOgreSceneNode()
{
	return mOgreSceneNode;
}

void SceneNode::LoadChildNodes()
{
	NodeMapPtr childNodeMap = GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		switch(nodeIterator->second->GetNodeType())
		{
		case Robotarium::SCENE_NODE_TYPE:
			boost::static_pointer_cast<SceneNodeBase>(nodeIterator->second)->Load();
			break;
		case Robotarium::GRAPHIC_NODE_TYPE:
			boost::static_pointer_cast<GraphicNode>(nodeIterator->second)->Load(shared_from_this());
			break;
		case Robotarium::CAMERA_SCENE_NODE_TYPE:
			boost::static_pointer_cast<CameraSceneNode>(nodeIterator->second)->Load(shared_from_this());
			break;
		}
	}
}


void SceneNode::UpdateChildNodes()
{

	NodeMapPtr childNodeMap = GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();
	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		switch(nodeIterator->second->GetNodeType())
		{
		case Robotarium::CAMERA_SCENE_NODE_TYPE:

			boost::static_pointer_cast<CameraSceneNode>(nodeIterator->second)->Update(GetPosition(), GetOrientation());
			break;
		}
	}
}


void SceneNode::Unload()
{
	mOgreSceneNode->detachAllObjects();

	delete mOgreSceneNode;
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

void SceneNode::SetOrientation(Quat rot)
{
	mOrientation = rot;
}

void SceneNode::SetOrientation(Real angle, Vec3 axis)
{
	mOrientation.FromAngleAxis(Ogre::Radian(angle), axis);
	//this->mOgreSceneNode->setOrientation(mOrientation);
}


Robotarium::Trans SceneNode::GetWorldTransform()
{
	return Trans::IDENTITY;
}

void SceneNode::SetWorldTransform(Robotarium::Vec3 _position, Robotarium::Quat _rotation)
{
	
}