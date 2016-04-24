
#include "graphic/RenderEngine.hpp"

using namespace Robotarium;
using namespace graphic;

RenderEngine::RenderEngine(void)
{
	this->logManager = NULL;
	this->mOgreRoot = NULL;
	this->initialized = false;
	this->loaded = false;
}

RenderEngine::~RenderEngine(void)
{

}

void RenderEngine::Load()//WindowFactoryPtr _windowfactory)
{
	this->Load(NULL);
}

void RenderEngine::Load(WindowFactoryPtr _windowfactory)
{
	if(this->loaded)
	{
		LogErr << "RenderEngine is Already Loaded!" << std::endl;
		return;
	}
	if (!this->mOgreRoot)
	{

		this->mWindowFactory = _windowfactory;

		// Make the root
		try
		{
			this->mOgreRoot = new Ogre::Root();
		}
		catch(Ogre::Exception &e)
		{
			return;
		}
		
		// Setup the available resources
		this->SetupResources();

		//// Create a new log manager and prevent output from going to stdout
		//this->logManager = new Ogre::LogManager();

		//std::string logPath = "./GraphicsEngine.log";

		//this->logManager->createLog(logPath, true, false, false);
		Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_LOW);

		// Setup the rendering system, and create the context
		this->SetupRenderSystem();

	}

	this->loaded = true;

	LogInfo << "RenderEngine Loaded." << std::endl;
}

void RenderEngine::Init()
{
	if(this->initialized)
	{
		LogErr << "RenderEngine is Already Initialized!" << std::endl;
		return;
	}

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// init the resources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(
		Ogre::TFO_ANISOTROPIC);

	//rendering::Material::CreateMaterials();

	//for (unsigned int i = 0; i < this->scenes.size(); i++)
	//	this->scenes[i]->Init();

	this->initialized = true;
	
	mOgreSceneManager = RenderEngine::GetSingleton()->GetOgreRoot()->createSceneManager(Ogre::ST_GENERIC);
	
	LogInfo << "RenderEngine Initialized." << std::endl;
}

void RenderEngine::Terminate()
{
	delete this->mOgreRoot;
}

void RenderEngine::SetupRenderSystem()
{
	Ogre::RenderSystem *renderSys;
	const Ogre::RenderSystemList *rsList;

	// Set parameters of render system (window size, etc.)
	rsList = &(this->mOgreRoot->getAvailableRenderers());

	int c = 0;

	renderSys = NULL;

	do
	{
		if (c == static_cast<int>(rsList->size()))
			break;

		renderSys = rsList->at(c);
		c++;
	}
	while (renderSys &&
		renderSys->getName().compare("OpenGL Rendering Subsystem") != 0);
		//renderSys->getName().compare("Direct3D9 Rendering Subsystem") != 0);
		

	if (renderSys == NULL)
	{
		return;
	}

	this->mOgreRoot->setRenderSystem(renderSys);

	renderSys->setConfigOption("Full Screen", "No");

	renderSys->setConfigOption("Video Mode", "640 x 480 @ 32-bit colour");

	renderSys->setConfigOption("RTT Preferred Mode", "FBO");

	renderSys->setConfigOption("FSAA", "0");

	renderSys->setConfigOption("VSync", "Yes");
	
	mOgreRoot->initialise(false);

	LogInfo << "Root Initialized."  << std::endl;

	Ogre::NameValuePairList misc;
	misc["externalWindowHandle"] = "0";

	Ogre::RenderWindow* target = mOgreRoot->createRenderWindow("Robotarium", 320, 240, false, &misc);
	

	//target->setHidden(true);
}


void RenderEngine::SetupResources()
{
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);

		}
	}

}

void RenderEngine::RunRenderLoop()
{
	//this->root->_fireFrameStarted();
	//this->root->_fireFrameRenderingQueued();
	//this->root->_fireFrameEnded();
	this->mOgreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
			LogInfo << "Creating Light" << std::endl;

		Ogre::Light *light = this->mOgreSceneManager->createLight("light1");

		LogInfo << "Setting Light Position" << std::endl;

		light->setPosition(0,10,10);

	mThread = boost::thread(&RenderEngine::RenderLoopWorker, this);
	//mThread.join();
	LogInfo << "Renderer Thread Spawned." << std::endl;
}

//ScenePtr& RenderEngine::CreateScene(const std::string &_name)
//{
//	//mScene = boost::make_shared<Robotarium::graphic::Scene>();
//	//mScene = ScenePtr(new Scene());
//
//
//
//	//static const char * matName = "main_grid_mat";
// //   Ogre::MaterialPtr mtl = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(matName);
// //   mtl->setReceiveShadows(false);
// //   mtl->setSceneBlending( Ogre::SBT_TRANSPARENT_ALPHA );
// //   mtl->setDepthBias( 0.1, 0 );
// //   Ogre::TextureUnitState * tu = mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
// //   assert( tu );
// //   tu->setColourOperationEx( Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE );
// //   mtl->getTechnique(0)->setLightingEnabled(false);
//
//
//	//// create ManualObject
//	//Ogre::ManualObject* manual = mScene->GetOgreSceneMgr()->createManualObject("main_grid");
//	//Ogre::ColourValue c(0.5, 0.5, 0.5);
//	//Ogre::ColourValue c1(0.7, 0.7, 0.7);
//	//// specify the material (by name) and rendering type
//	//manual->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);
//
//	//// define start and end point
//	//for (int i = -5; i <= 5; i++)
//	//{
//	//	manual->position(i, 0, -5);
//	//	if(i!=0) manual->colour(c); else manual->colour(c1);
//	//	manual->position(i, 0, 5);
//	//	if(i!=0) manual->colour(c); else manual->colour(c1);
//	//}
//
//	//for (int i = -5; i <= 5; i++)
//	//{
//	//	manual->position(-5, 0, i);
//	//	if(i!=0) manual->colour(c); else manual->colour(c1);
//	//	manual->position(5, 0, i);
//	//	if(i!=0) manual->colour(c); else manual->colour(c1);
//	//}
//	//// tell Ogre, your definition has finished
//	//manual->end();
//
//	//// add ManualObject to the RootSceneNode (so it will be visible)
//	//mScene->GetOgreSceneMgr()->getRootSceneNode()->attachObject(manual);
//	////mScene->Load();
//	//return mScene;
//	return 0;
//}

Ogre::Root* RenderEngine::GetOgreRoot()
{
	return this->mOgreRoot;
}

Ogre::SceneManager *RenderEngine::GetOgreSceneManager()
{
	return mOgreSceneManager;
}


void RenderEngine::RenderLoopWorker()
{
	mOgreRoot->getRenderSystem()->_initRenderTargets();

	Robotarium::common::UpdateVisitor camera_update_visitor;

	for(;;)
	{
		//this->GetScene()->Update();
		Robotarium::core::Scene::GetSingleton()->DispatchVisitor(camera_update_visitor, Robotarium::CAMERA_SCENE_NODE_TYPE);
		
		Ogre::WindowEventUtilities::messagePump();

        if(!mOgreRoot->_fireFrameStarted())
			LogErr << "An Error Occured While Trying to Render Next Frame!" << std::endl;

        mOgreRoot->getRenderSystem()->_updateAllRenderTargets();

        if(!mOgreRoot->_fireFrameEnded())
			LogErr << "An Error Occured While Trying to Render Next Frame!" << std::endl;

		boost::this_thread::sleep(boost::posix_time::milliseconds(16));
	}
}


Robotarium::String RenderEngine::CreateNewWindow(Robotarium::Vec2 _viewportsize,
						Robotarium::String _name)
{
	if(this->mWindowFactory)
	{
		return this->mWindowFactory->CreateNewWindow(_viewportsize, _name);
	}
	
	return "0";
}