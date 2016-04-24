#include "graphic/Scene.hpp"

using namespace Robotarium;
using namespace graphic;

Scene::Scene(void) : mRootSceneNode(new SceneNode("RootNode", 1)), mCameraMap(new CameraMap())
{
	mSceneMgr = RenderEngine::GetSingleton()->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
}

Scene::~Scene(void)
{
}

void Scene::Load()
{

	mRootSceneNode->Load();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0,0,0));
	
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
	
}

Ogre::SceneManager * Scene::GetOgreSceneMgr()
{
	return this->mSceneMgr;
}

CameraMapPtr& Scene::GetCameraMap()
{
	return mCameraMap;
}

void Scene::AddCamera(CameraPtr& camera)
{
	(*mCameraMap)[camera->GetID()] = camera;
	//camera->Load();
}

UInt32 Scene::GetCameraMapSize()
{
	return this->mCameraMap->size();
}

void Scene::LoadAllCameras()
{
	
	for (UInt32 i = 1; i <= this->GetCameraMapSize(); i++)
	{
		(*this->GetCameraMap())[i]->Load();
	}

}

void Scene::Terminate()
{
}


void Scene::Update()
{
	UpdateScene(Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode());
}

void Scene::UpdateScene(Robotarium::graphic::SceneNodePtr& startingNode)
{

	startingNode->Update();

	NodeMapPtr& childNodeMap = startingNode->GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();

	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		if (nodeIterator->second->GetNodeType() == SCENE_NODE_TYPE)
		{
			UpdateScene(boost::static_pointer_cast<SceneNode>(nodeIterator->second));
		}

		if (nodeIterator->second->GetNodeType() == RIGID_BODY_NODE_TYPE)
		{
			//startingNode->Update();
		}
	}

}

SceneNodePtr Scene::GetSceneNode_by_ID(UInt32 _id, SceneNodePtr startingNode)
{
	SceneNodePtr res;

	NodeMapPtr& childNodeMap = startingNode->GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();

	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		if ((nodeIterator->second->GetID() == _id) && 
			(nodeIterator->second->GetNodeType() == SCENE_NODE_TYPE))
		{
			return boost::static_pointer_cast<SceneNode>(nodeIterator->second);
		}

		if (nodeIterator->second->GetNodeType() == SCENE_NODE_TYPE)
		{
			if (res = GetSceneNode_by_ID(_id, boost::static_pointer_cast
					<SceneNode>(nodeIterator->second)))
			{
				return res;
			}
		}
	}
	return NULL;
}


SceneNodePtr Scene::GetSceneNode(Robotarium::UInt32 _id)
{
	return GetSceneNode_by_ID(_id, 
		RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode());
}

Robotarium::Bool Scene::HasChild(Robotarium::graphic::SceneNodePtr _node, Robotarium::NODE_TYPE_ENUM _type)
{
	NodeMapPtr& childNodeMap = _node->GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();

	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		if (nodeIterator->second->GetNodeType() == _type)
			return true;
	}
	return false;
}


Robotarium::Bool Scene::HasChild(Robotarium::graphic::SceneNodePtr _node)
{
	if (_node->GetChildNodeMap()->size() > 0)
		return true;

	return false;
}


Robotarium::NodePtr Scene::GetFirstChild(Robotarium::graphic::SceneNodePtr _node, Robotarium::NODE_TYPE_ENUM _type)
{
	NodeMapPtr& childNodeMap = _node->GetChildNodeMap();

	NodeMap::const_iterator nodeIterator = childNodeMap->begin();

	NodeMap::const_iterator nodeIteratorEnd = childNodeMap->end();

	for(;nodeIterator != nodeIteratorEnd ; ++nodeIterator)
	{
		if (nodeIterator->second->GetNodeType() == _type)
			return nodeIterator->second;
	}
	return false;
}