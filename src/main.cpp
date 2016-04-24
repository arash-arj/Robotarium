#include "common/MeshLoader.hpp"
#include "core/SceneNode.hpp"
#include "core/Scene.hpp"
#include "graphic/RenderEngine.hpp"
#include "graphic/GraphicNode.hpp"
#include "graphic/CameraSceneNode.hpp"
#include <iostream>

using namespace Robotarium;
using namespace core;
using namespace graphic;

int main()
{
	core::Scene* scene = Scene::GetSingleton();
	graphic::RenderEngine* render_engine = graphic::RenderEngine::GetSingleton();
	Robotarium::String _path = "";

	SceneNodePtr node1(new SceneNode("node1"));
	SceneNodePtr node2(new SceneNode("node2"));
	SceneNodePtr node3(new SceneNode("node3"));
	SceneNodePtr node4(new SceneNode("node4"));

	scene->AddNode(node1);
	scene->AddNode(node2);

	scene->AddNode(node3, "node1");
	scene->AddNode(node4, "node3");

	node3->SetPosition(Vec3(1,0,0));
	node4->SetPosition(Vec3(0,1,0));
	node4->SetOrientation(1.5707963267948966192313216916398, Vec3(-1,0,0));

	scene->AddMesh(common::MeshLoader::Import(_path + "monkey.blend", "Mesh1"));
	scene->GetMesh("Mesh1")->GetSubMesh(0)->Scale(0.5);
	render_engine->Load();
	render_engine->Init();

	GraphicNodePtr gnode1(new GraphicNode("gM1"));

	scene->AddNode(gnode1, "node4");

	gnode1->SetMeshName("Mesh1");

	gnode1->Init();
	gnode1->Load();
	


	CameraSceneNodePtr cam1(new CameraSceneNode(
		scene->GetRootSceneNode(), 
		"cam1", 
		Vec2(500,500),
		Vec3(5,5,5),
		Vec3(0,0,0)
		));

	scene->AddNode(cam1);

	cam1->Init();
	cam1->Load();

	render_engine->RunRenderLoop();
	
	std::cout << "Hi!\n";

	double theta = 0;
	while(1)
	{
		theta += 0.05;
		node1->SetOrientation(theta, Vec3(0,1,0));
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		gnode1->Update();
	};
	return 0;
}
