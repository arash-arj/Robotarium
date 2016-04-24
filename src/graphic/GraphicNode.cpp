#include "graphic/GraphicNode.hpp"
#include "graphic/RenderEngine.hpp"

using namespace Robotarium;
using namespace graphic;

GraphicNode::GraphicNode(Robotarium::String _name)
	: Node(_name)
{

	SetNodeType(GRAPHIC_NODE_TYPE);

	mIsMeshNameSet = false;
	mIsInitialized = false;
	mIsLoaded = false;

	this->SetName(_name);

	LogInfo << GetName() << " (GraphicNode) : Created Successfully." << std::endl;

}

GraphicNode::~GraphicNode()
{
}

Robotarium::String GraphicNode::GetMeshName()
{
	if(mIsMeshNameSet)
		return mMeshName;
	else
		return "";
}

void GraphicNode::SetMeshName(String meshName)
{
	this->mMeshName = meshName;
	mIsMeshNameSet = true;
}


void GraphicNode::Init()
{
	if(!mIsMeshNameSet)
	{
		LogErr << GetName() << ": Mesh name not set!" << std::endl;
		return;
	}

	Ogre::SceneManager* sceneMgr = RenderEngine::GetSingleton()->GetOgreSceneManager();

	if(sceneMgr->hasSceneNode(GetParent()->GetName()))
	{
		mOgreSceneNode = sceneMgr->getSceneNode(GetParent()->GetName());
	}
	else
	{
		mOgreSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(this->GetParent()->GetName());
	}

	mIsInitialized = true;

	LogInfo << GetName() << " (GraphicNode) : Initialized Successfully." << std::endl;
}

void GraphicNode::Load()
{

	if(!mIsInitialized)
	{
		LogErr << GetName() << ": Should be first Initialized!" << std::endl;
		return;
	}

	LoadMesh();
	mIsLoaded = true;

	LogInfo << GetName() << " (GraphicNode) : Loaded Successfully." << std::endl;

}

void GraphicNode::Update()
{
	this->GetOgreSceneNode()->setPosition(this->GetParent()->GetWorldPosition());
	this->GetOgreSceneNode()->setOrientation(this->GetParent()->GetWorldOrientation().Inverse());
}

Ogre::Entity* GraphicNode::GetOgreEntity()
{
	return mOgreEntity;
}


Ogre::SceneNode* GraphicNode::GetOgreSceneNode()
{
	return this->mOgreSceneNode;
}

void GraphicNode::Terminate()
{

}


void GraphicNode::LoadMesh()
{
	//common::MeshPtr _mesh = core::Scene::GetSingleton()->GetMesh(this->GetMeshName());

	//if(!_mesh)
	//{
	//	LogErr << "Mesh not found!" << std::endl;
	//	return;
	//}

	common::MeshPtr _mesh = core::Scene::GetSingleton()->GetMesh(this->GetMeshName());


	Ogre::MeshPtr ogre_mesh = Ogre::MeshManager::getSingleton().createManual(
		this->GetMeshName(),
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	for(Robotarium::UInt32 _sm_index = 0; _sm_index < _mesh->GetSubMeshCount(); _sm_index++)
	{
		Ogre::SubMesh *sub_mesh = ogre_mesh->createSubMesh();//this->GetMeshName() + "_" + Ogre::StringConverter::toString(_sm_index));
		sub_mesh->useSharedVertices = false;

		sub_mesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;

		sub_mesh->vertexData = new Ogre::VertexData;

		Ogre::VertexDeclaration *vertexDeclaration = sub_mesh->vertexData->vertexDeclaration;

		Ogre::HardwareVertexBufferSharedPtr  vertexBuffer;

		Ogre::HardwareIndexBufferSharedPtr   indexBuffer;

		size_t offset=0;
		

		vertexDeclaration = sub_mesh->vertexData->vertexDeclaration;


		{
			vertexDeclaration->addElement(0,offset,Ogre::VET_FLOAT3,Ogre::VES_POSITION);
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		}

		if(_mesh->GetSubMesh(_sm_index)->GetNormalCount() > 0)
		{
			vertexDeclaration->addElement(0,offset,Ogre::VET_FLOAT3,Ogre::VES_NORMAL);
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
		}

		if(_mesh->GetSubMesh(_sm_index)->GetTexCoordCount() > 0)
		{
			vertexDeclaration->addElement(0,offset,Ogre::VET_FLOAT2,Ogre::VES_TEXTURE_COORDINATES);
			offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
		}

		//// Make vertex buffer 
		sub_mesh->vertexData->vertexCount = _mesh->GetSubMesh(_sm_index)->GetVertexCount();

		vertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			vertexDeclaration->getVertexSize(0),
			_mesh->GetSubMesh(_sm_index)->GetVertexCount(),
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

		sub_mesh->vertexData->vertexBufferBinding->setBinding(0, vertexBuffer);

		float *vData = NULL;
		uint32_t *iData = NULL;

		vData = static_cast<float*>(vertexBuffer->lock(
			Ogre::HardwareBuffer::HBL_DISCARD));



		//// Make index buffer

		sub_mesh->indexData->indexCount = _mesh->GetSubMesh(_sm_index)->GetIndexCount();

		sub_mesh->indexData->indexBuffer =
			Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
			Ogre::HardwareIndexBuffer::IT_32BIT,
			sub_mesh->indexData->indexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,
			false);

		indexBuffer = sub_mesh->indexData->indexBuffer;

		iData = static_cast<uint32_t*>(
			indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));


		///// Write the actual mesh data, vertex/index
		_mesh->GetSubMesh(_sm_index)->FillArrays2(&vData, &iData);

		vertexBuffer->unlock();
		indexBuffer->unlock();

	}

	/*ogre_mesh->clone(this->GetMeshName(),
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);*/
	// I don't get real AABB from object, this is ok for probe 
	ogre_mesh->_setBounds(Ogre::AxisAlignedBox(-100,-100,-100,100,100,100), false);
	ogre_mesh->load();


	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
      "Test/ColourTest", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_AMBIENT);


	Ogre::SceneManager* sceneMgr = RenderEngine::GetSingleton()->GetOgreSceneManager();
	
	mOgreEntity = sceneMgr->createEntity(GetName(), ogre_mesh);

	mOgreSceneNode->attachObject(mOgreEntity);

	mOgreEntity->setMaterial(material);

}