#include "graphic/CameraSceneNode.hpp"
#include "graphic/RenderEngine.hpp"

using namespace Robotarium;
using namespace core;
using namespace graphic;

//NoCullFrustum.h
class NoCullFrustum: public Ogre::Frustum{
public:
   NoCullFrustum(){}
   ~NoCullFrustum(){}
   bool isVisible(const Ogre::AxisAlignedBox &bound, Ogre::FrustumPlane *culledBy=0) const{return true;}
   bool isVisible(const Ogre::Sphere &bound, Ogre::FrustumPlane *culledBy=0) const{return true;}
   bool isVisible(const Ogre::Vector3 &vert, Ogre::FrustumPlane *culledBy=0) const{return true;}
};

CameraSceneNode::CameraSceneNode(core::SceneNodePtr& parent, String name, String HWND, Vec2 viewportSize, Vec3 position, Vec3 lapPoint)
	:SceneNode(name), mHWND(HWND), 
	mViewportSize(viewportSize), mLapPoint(lapPoint)
{
	SetNodeType(CAMERA_SCENE_NODE_TYPE);

	this->SetName(name);
	this->SetParent(parent);
	this->SetPosition(position);
}

CameraSceneNode::CameraSceneNode(core::SceneNodePtr& parent, String name, Vec2 viewportSize, Vec3 position, Vec3 lapPoint)
	:SceneNode(name), mViewportSize(viewportSize), mLapPoint(lapPoint)
{
	SetNodeType(CAMERA_SCENE_NODE_TYPE);

	this->SetName(name);
	this->SetParent(parent);
	this->SetPosition(position);

	this->mHWND = RenderEngine::GetSingleton()->CreateNewWindow(mViewportSize, this->GetName());

}

CameraSceneNode::~CameraSceneNode()
{
}

void CameraSceneNode::Load(SceneNodePtr& parent)
{

	Ogre::NameValuePairList params;
    
    params["externalWindowHandle"] = "0";//mHWND;

	mRenderWindow = Ogre::Root::getSingleton().
		createRenderWindow(GetName() , mViewportSize.x, mViewportSize.y, false);

	Ogre::SceneManager* mOgreSceneMgr = RenderEngine::GetSingleton()->GetOgreSceneManager();

	mCamera = mOgreSceneMgr->createCamera(GetName());


	mOgreSceneNode = mOgreSceneMgr->getRootSceneNode()->createChildSceneNode(GetName());

	mOgreSceneNode->attachObject(mCamera);

	mCamera->setNearClipDistance(0.001);

	mCamera->setCullingFrustum(new NoCullFrustum());

	// Create one viewport, entire window
	mViewport = mRenderWindow->addViewport(mCamera, 1);

	mViewport->setBackgroundColour(Ogre::ColourValue(0.2,0.2,0.2));

	mViewport->setAutoUpdated( true ); 
    mViewport->setClearEveryFrame( true ); 

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(mViewport->getActualWidth())/Real(mViewport->getActualHeight()));

	SetLookAtPoint(mLapPoint);

	this->SetLoaded(true);
	this->SetInitialized(true);
	/*Robotarium::graphic::RenderEngine::GetSingleton()->GetOgreRoot()->getRenderSystem()->_initRenderTargets();*/
}

void CameraSceneNode::Load()
{
	//Load(GetParent());
}

void CameraSceneNode::Update()
{
	if(this->IsLoaded())
	{
		mOgreSceneNode->setPosition(this->GetWorldPosition());
		mOgreSceneNode->setOrientation(this->GetWorldOrientation());
		try
		{
				mRenderWindow->update();
		}
		catch(int i){}
		//this->mParentPosition = this->GetParent()->GetPosition();
		//this->mParentOrientation = this->GetParent()->GetOrientation();
		//this->SetPosition(this->mPosition);
		//this->SetOrientation(this->mOrientation);
	}
}

void CameraSceneNode::LoadChildNodes()
{
}

void CameraSceneNode::UpdateChildNodes()
{
}

//void CameraSceneNode::SetPosition(Real x, Real y, Real z)
//{
//	mPosition.x = x;
//	mPosition.y = y;
//	mPosition.z = z;
//	mOgreSceneNode->setPosition(mParentPosition + mParentOrientation*mPosition);
//}
//
//void CameraSceneNode::SetPosition(Vec3 pos)
//{
//	mPosition = pos;
//	mOgreSceneNode->setPosition(mParentPosition + mParentOrientation*mPosition);
//}
//
//Vec3 CameraSceneNode::GetPosition()
//{
//	return mPosition;
//}
//
//void CameraSceneNode::SetOrientation(Quat rot)
//{
//	mOrientation = rot;
//	mOgreSceneNode->setOrientation(mParentOrientation*mOrientation);
//}
//
//void CameraSceneNode::SetOrientation(Real angle, Vec3 axis)
//{
//	mOrientation.FromAngleAxis(Ogre::Radian(angle), axis);
//	mOgreSceneNode->setOrientation(mParentOrientation*mOrientation);
//}

void CameraSceneNode::SetLookAtPoint(Vec3 lap)
{
	//mOgreSceneNode->lookAt(lap, Ogre::Node::TS_WORLD);

	Vec3 z = -(lap - GetPosition()); z.normalise(); // z
	Vec3 x = z.crossProduct(Vec3::NEGATIVE_UNIT_Y); x.normalise(); // x
	Vec3 y = -x.crossProduct(z); y.normalise(); // y

	Ogre::Matrix3 R;
	R.FromAxes(x, y, z);

	Quat q; q.FromRotationMatrix(R);
	mOgreSceneNode->setOrientation(q);

	this->SetOrientation(mOgreSceneNode->getOrientation()*this->GetParent()->GetOrientation().Inverse());
}
