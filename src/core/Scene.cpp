#include "core/Scene.hpp"

using namespace Robotarium;
using namespace core;

Scene::Scene(void) : mRootSceneNode(new SceneNode("RootNode"))
{
	this->mMeshVec = boost::make_shared<common::MeshVec>();
	//std::cout << typeid(*this).hash_code() << std::endl;
	//mSceneMgr = RenderEngine::GetSingleton()->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
}

Scene::~Scene(void)
{
}

void Scene::Init()
{
	mRootSceneNode->Init();
}

void Scene::Load()
{

	mRootSceneNode->Load();

	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0,0,0));
	
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
	
}

void Scene::Terminate()
{
}


void Scene::Update()
{
	
}

void Scene::UpdateScene(NodePtr& startingNode)
{
	
}

Robotarium::Bool Scene::HasChild(Robotarium::core::NodePtr _node, Robotarium::NODE_TYPE_ENUM _type)
{
	return false;
}


Robotarium::Bool Scene::HasChild(Robotarium::core::NodePtr _node)
{
	return false;
}


NodePtr Scene::GetFirstChild(NodePtr _node, Robotarium::NODE_TYPE_ENUM _type)
{
	return false;
}

NodePtr Scene::GetNode(Robotarium::String _name)
{
	return this->GetNode(Scene::GetSingleton()->GetRootSceneNode(), _name);
}

NodePtr Scene::GetNode(Robotarium::core::SceneNodePtr _starting_node, Robotarium::String _name)
{
	//std::cout << typeid(*this).hash_code() << std::endl;
	//std::cout << _starting_node->GetName() << std::endl;

	NodeVecPtr node_vec = _starting_node->GetChildNodeVec();
	int last_ind = node_vec->size() - 1;

	for(int i = 0; i <= last_ind; i++)
	{
		if(node_vec->at(i)->GetName() == _name)
		{
			return node_vec->at(i);
		}

		if(node_vec->at(i)->GetNodeType() == Robotarium::SCENE_NODE_TYPE)
		{
			NodePtr _node = GetNode(boost::static_pointer_cast<SceneNode>(node_vec->at(i)), _name);

			if(_node != 0)
			{
				return _node;
			}
		}

	}
	return 0;
}

void Scene::DispatchVisitor(core::Visitor& _visitor)
{
	DispatchVisitor(_visitor, Scene::GetSingleton()->GetRootSceneNode());
}

void Scene::DispatchVisitor(
	core::Visitor& _visitor, 
	Robotarium::core::SceneNodePtr _starting_node)
{
	NodeVecPtr node_vec = _starting_node->GetChildNodeVec();
	int last_ind = node_vec->size() - 1;

	for(int i = 0; i <= last_ind; i++)
	{
		_visitor.Visit(node_vec->at(i));

		if(node_vec->at(i)->GetNodeType() == Robotarium::SCENE_NODE_TYPE)
		{
			DispatchVisitor(_visitor, boost::static_pointer_cast<SceneNode>(node_vec->at(i)));
		}
	}
}

void Scene::DispatchVisitor(core::Visitor& _visitor, NODE_TYPE_ENUM _type)
{
	DispatchVisitor(_visitor, _type, Scene::GetSingleton()->GetRootSceneNode());
}

void Scene::DispatchVisitor(
	core::Visitor& _visitor, 
	Robotarium::NODE_TYPE_ENUM _type, 
	Robotarium::core::SceneNodePtr _starting_node)
{
	NodeVecPtr node_vec = _starting_node->GetChildNodeVec();
	int last_ind = node_vec->size() - 1;

	for(int i = 0; i <= last_ind; i++)
	{
		if(node_vec->at(i)->GetNodeType() == _type)
		{
			_visitor.Visit(node_vec->at(i));
		}

		if(node_vec->at(i)->GetNodeType() == Robotarium::SCENE_NODE_TYPE)
		{
			DispatchVisitor(_visitor, _type, boost::static_pointer_cast<SceneNode>(node_vec->at(i)));
		}
	}
}

void Scene::AddNode(core::NodePtr _new_node, Robotarium::String _parent_name)
{
	core::NodePtr parent_node = Scene::GetSingleton()->GetNode(_parent_name);
	core::SceneNodePtr parent = 0;

	if(parent_node == 0) // parent_node not found
	{
		std::cout << "Specified parent not found!" << std::endl;
		return;
	}

	if(parent_node->GetNodeType() == Robotarium::SCENE_NODE_TYPE)
	{
		parent = boost::static_pointer_cast<core::SceneNode>(parent_node);
	}
	else
	{
		std::cout << "Specified parent," << _parent_name 
			<< ", should be of type SceneNode!" << std::endl;
		return;
	}

	core::NodePtr search_res = Scene::GetSingleton()->GetNode(_new_node->GetName());

	if(search_res != 0) // name already exists
	{
		std::cout << "Name already exists!" << std::endl;
		return;
	}



	parent->AddNode(_new_node);
	_new_node->SetParent(parent);
}

void Scene::AddNode(core::NodePtr _new_node, core::SceneNodePtr _parent_node)
{
	if(_parent_node == 0) // _parent_node not initialized
	{
		std::cout << "Specified parent Node has not been initialized!" << std::endl;
		return;
	}

	_parent_node->AddNode(_new_node);
	_new_node->SetParent(_parent_node);
}

void Scene::AddNode(core::NodePtr _new_node)
{
	core::SceneNodePtr parent_node = Scene::GetSingleton()->GetRootSceneNode();

	core::NodePtr search_res = Scene::GetSingleton()->GetNode(_new_node->GetName());

	if(search_res != 0) // name already exists
	{
		std::cout << "Name already exists!" << std::endl;
		return;
	}

	parent_node->AddNode(_new_node);
	_new_node->SetParent(parent_node);
}

//void Scene::AddMesh(Robotarium::String _name, Robotarium::String _mesh_path)
//{
//	std::ifstream file (_mesh_path.c_str(), std::ifstream::in | std::ifstream::binary);
//	
//	if (!file)
//	{
//		LogErr << "File " + _mesh_path + " not found." << std::endl;
//		return;
//	}
//	
//	Ogre::DataStreamPtr stream (OGRE_NEW Ogre::FileStreamDataStream (&file, false));
//	
//	Ogre::MeshPtr pMesh = Ogre::MeshManager::getSingleton().createManual(
//		_name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//	
//	Ogre::MeshSerializer meshSerializer;
//	
//	meshSerializer.importMesh(stream, pMesh.getPointer());
//	
//	common::Mesh* raw_mesh_ptr = static_cast<common::Mesh*>(pMesh.getPointer());
//	
//	Robotarium::common::MeshPtr mesh_ptr(raw_mesh_ptr);
//	
//	this->AddMesh(mesh_ptr);
//	
//}

void Scene::AddMesh(Robotarium::common::MeshPtr _mesh_ptr)
{
	this->mMeshVec->insert(this->mMeshVec->begin(), _mesh_ptr);
	
	LogInfo << this->mMeshVec->at(0)->GetName() << std::endl;
	LogInfo << this->mMeshVec->at(0)->GetSubMeshCount() << std::endl;
}


Robotarium::common::MeshPtr Scene::GetMesh(Robotarium::String _name)
{
	for(int i = 0; i < mMeshVec->size(); i++)
	{
		if(mMeshVec->at(i)->GetName() == _name)
			return mMeshVec->at(i);
	}

	LogErr << "Mesh with name: " << _name << " not found!" << std::endl;

	return 0;
}