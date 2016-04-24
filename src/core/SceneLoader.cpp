#include "core/SceneLoader.hpp"

using namespace Robotarium;
using namespace core;
using namespace graphic;
using namespace physic;

SceneLoader::SceneLoader()
{

}

SceneLoader::~SceneLoader()
{

}

void SceneLoader::ReadFromFile(Robotarium::String url)
{

	if(!doc.LoadFile(url.c_str()))
	{
		LogErr << "SceneLoader: " << "An error occured reading """ << url << """" << std::endl;
		return;
	}

	RecurseXML(doc.RootElement());

}


void SceneLoader::RecurseXML(TiXmlElement* elem)
{
	const char* SCENE_GRAPH = "SceneGraph";
	const char* CONSTRAINTS = "Constraints";
	const char* SENSORS = "Sensors";
	const char* ACTUATORS = "Actuators";
	const char* MANAGERS = "Managers";

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		LogInfo << "SceneLoader: " << "XML Space:  " << e->Value() << std::endl;
		if(!stricmp(SCENE_GRAPH, e->Value()))
		{
			RecurseSceneXML(e, 0, graphic::RenderEngine::GetSingleton()->GetScene()->GetRootSceneNode());
		}
		if(!stricmp(CONSTRAINTS, e->Value()))
		{
			RecurseConstraintsXML(e);
		}
		if(!stricmp(SENSORS, e->Value()))
		{
			RecurseSensorsXML(e);
		}
		if(!stricmp(ACTUATORS, e->Value()))
		{
			RecurseActuatorsXML(e);
		}
		if(!stricmp(MANAGERS, e->Value()))
		{
			RecurseManagersXML(e);
		}
	}



}


void SceneLoader::RecurseSceneXML(TiXmlElement* elem, UInt32 depth, Robotarium::graphic::SceneNodePtr& parentSceneNode)
{

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{

		const char* SCENE_NODE = "SceneNode";
		const char* GRAPHIC_NODE = "GraphicNode";
		const char* CAMERA_NODE = "CameraNode";
		const char* RIGIDBODY_NODE = "RigidBody";
		const char* POSITION = "Position";
		const char* ROTATION = "Rotation";
		const char* INERTIAL_PROPS = "InertialProps";
		const char* LOOK_AT_POINT = "LookAtPoint";
		const char* VIEWPORT_SIZE = "ViewportSize";

		if(!stricmp(SCENE_NODE, e->Value()))
		{
			const char* name_attr = e->Attribute("Name");

			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute("ID"));

			Robotarium::graphic::SceneNodePtr 
				temp(new Robotarium::graphic::SceneNode(name_attr, id_attr));

			parentSceneNode->AddNode(temp);

			temp->Load();

			temp->SetPosition(Robotarium::Vec3(0,0,0));
			temp->SetOrientation(Robotarium::Quat(1,0,0,0));

			RecurseSceneXML(e, depth+1, temp);
		}
		else if(!stricmp(CAMERA_NODE, e->Value()))
		{
			const char* name_attr = e->Attribute("Name");

			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute("ID"));

			Robotarium::Real px = 0, py = 0, pz = 0;
			Robotarium::Real lx = 0, ly = 0, lz = 0;
			Robotarium::Real vw = 0, vh = 0;

			for(TiXmlElement* e2 = e->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
			{
				if(!stricmp(POSITION, e2->Value()))
				{
					px = Ogre::StringConverter::parseReal(e2->Attribute("x"));
					py = Ogre::StringConverter::parseReal(e2->Attribute("y"));
					pz = Ogre::StringConverter::parseReal(e2->Attribute("z"));
				}
				else if (!stricmp(LOOK_AT_POINT, e2->Value()))
				{
					lx = Ogre::StringConverter::parseReal(e2->Attribute("x"));
					ly = Ogre::StringConverter::parseReal(e2->Attribute("y"));
					lz = Ogre::StringConverter::parseReal(e2->Attribute("z"));
				}
				else if (!stricmp(VIEWPORT_SIZE, e2->Value()))
				{
					vw = Ogre::StringConverter::parseReal(e2->Attribute("w"));
					vh = Ogre::StringConverter::parseReal(e2->Attribute("h"));
				}
			}

			CameraSceneNodePtr temp(new CameraSceneNode(parentSceneNode, 
				name_attr, id_attr,
				Vec2(vw,vh), Vec3(px,py,pz), Vec3(lx,ly,lz)));

			parentSceneNode->AddNode(temp);

			temp->Load(parentSceneNode);

		}
		else if(!stricmp(GRAPHIC_NODE, e->Value()))
		{
			const char* name_attr = e->Attribute("Name");

			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute("ID"));

			const char* mesh_name_attr = e->Attribute("Mesh");

			GraphicNodePtr temp(new GraphicNode(parentSceneNode, name_attr, mesh_name_attr, id_attr));

			parentSceneNode->AddNode(temp);

			temp->Load(parentSceneNode);

		}
		else if(!stricmp(RIGIDBODY_NODE, e->Value()))
		{
			
			const char* name_attr = e->Attribute("Name");

			const char* shape_attr = e->Attribute("Shape");

			Robotarium::Real mass_attr = Ogre::StringConverter::parseReal(e->Attribute("Mass"));

			Robotarium::Real Ixx_attr = 0;
			Robotarium::Real Iyy_attr = 0;
			Robotarium::Real Izz_attr = 0;
			Robotarium::Real restitution_attr;
			Robotarium::Real friction_attr;
			Robotarium::Real rollingfriction_attr;

			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute("ID"));

			Robotarium::physic::RigidBodyPtr 
				temp(new Robotarium::physic::RigidBody(parentSceneNode, name_attr, id_attr));

			parentSceneNode->AddNode(temp);

			temp->Load(shape_attr, parentSceneNode->GetPosition(), mass_attr);

			if(e->Attribute("Ixx"))
				Ixx_attr = Ogre::StringConverter::parseReal(e->Attribute("Ixx"));

			if(e->Attribute("Iyy"))
				Iyy_attr = Ogre::StringConverter::parseReal(e->Attribute("Iyy"));

			if(e->Attribute("Izz"))
				Izz_attr = Ogre::StringConverter::parseReal(e->Attribute("Izz"));
			
			if(Ixx_attr != 0 && Iyy_attr != 0 && Izz_attr != 0)
				temp->SetLocalInertia(Ixx_attr, Iyy_attr, Izz_attr);

			if(e->Attribute("Restitution"))
			{
				restitution_attr = Ogre::StringConverter::parseReal(e->Attribute("Restitution"));
				temp->SetRestitution(restitution_attr);
			}
			if(e->Attribute("Friction"))
			{
				friction_attr = Ogre::StringConverter::parseReal(e->Attribute("Friction"));
				temp->SetFriction(friction_attr);
			}

			if(e->Attribute("RollingFriction"))
			{
				rollingfriction_attr = Ogre::StringConverter::parseReal(e->Attribute("RollingFriction"));
				temp->SetRollingFriction(friction_attr);
			}
		}
		else if(!stricmp(POSITION, e->Value()))
		{
			Robotarium::Real x = Ogre::StringConverter::parseReal(e->Attribute("x"));
			Robotarium::Real y = Ogre::StringConverter::parseReal(e->Attribute("y"));
			Robotarium::Real z = Ogre::StringConverter::parseReal(e->Attribute("z"));

			parentSceneNode->SetPosition(Robotarium::Vec3(x, y, z));
		}
		else if(!stricmp(ROTATION, e->Value()))
		{
			Robotarium::Real x = Ogre::StringConverter::parseReal(e->Attribute("x"));
			Robotarium::Real y = Ogre::StringConverter::parseReal(e->Attribute("y"));
			Robotarium::Real z = Ogre::StringConverter::parseReal(e->Attribute("z"));
			Robotarium::Real theta = Ogre::StringConverter::parseReal(e->Attribute("theta"));

			parentSceneNode->SetOrientation(theta, Vec3(x, y, z));
			//LogWarn << "x = " << x << ", y = " << y << ", z = " << z << ", theta = " << theta << std::endl;
		}
	}

}


void SceneLoader::RecurseConstraintsXML(TiXmlElement* elem)
{
	const char* REVOLUTE_JOINT = "RevoluteJoint";
	const char* PRISMATIC_JOINT = "PrismaticJoint";
	const char* FASTENER_CONSTRAINT = "Fastener";
	const char* DISABLE_COLLISION = "DisableCollision";
	const char* ID1 = "ID1";
	const char* ID2 = "ID2";
	const char* POSITION = "Position";
	const char* AXIS = "Axis";
	const char* LIMITS = "Limits";

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!stricmp(REVOLUTE_JOINT, e->Value()))
		{
			const char* NAME = "Name";
			const char* ID1 = "ID1";
			const char* ID2 = "ID2";
			const char* SOLVER_ITER = "NumSolverIterations";
			const char* POSITION = "Position";
			const char* AXIS = "Axis";
			const char* LOWER = "Lower";
			const char* UPPER = "Upper";			
			
			const char* name_attr = e->Attribute(NAME);

			Robotarium::UInt32 id1_attr = Ogre::StringConverter::parseInt(e->Attribute(ID1));
			Robotarium::UInt32 id2_attr = Ogre::StringConverter::parseInt(e->Attribute(ID2));

			Robotarium::UInt32 solver_iter_attr = 0;
			if(e->Attribute(SOLVER_ITER))
			{
				solver_iter_attr = Ogre::StringConverter::parseInt(e->Attribute(SOLVER_ITER));

				if(solver_iter_attr == 0)
				{
					LogWarn << "SceneLoader: " << name_attr << ": " <<
						SOLVER_ITER << " attribute can not be set to zero! \
						Default value will be used." << std::endl;
				}
			}
			else
			{
				LogWarn << "SceneLoader: " << name_attr << ": " << SOLVER_ITER <<
							" is not specified! \
							Default value will be used." << std::endl;
			}

			graphic::SceneNodePtr node1 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id1_attr);
			graphic::SceneNodePtr node2 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id2_attr);


			Robotarium::Vec3 pos;
			Robotarium::Vec3 axis;
			Robotarium::Real lower, upper;

			for(TiXmlElement* e_ch = e->FirstChildElement(); e_ch != NULL; e_ch = e_ch->NextSiblingElement())
			{
				if(!stricmp(POSITION, e_ch->Value()))
				{
					pos.x = Ogre::StringConverter::parseReal(e_ch->Attribute("x"));
					pos.y = Ogre::StringConverter::parseReal(e_ch->Attribute("y"));
					pos.z = Ogre::StringConverter::parseReal(e_ch->Attribute("z"));

					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"position set: x=" << 
						pos.x << ", y=" << pos.y << ", z=" << pos.z << "." << std::endl;
				}
				else if(!stricmp(AXIS, e_ch->Value()))
				{
					axis.x = Ogre::StringConverter::parseReal(e_ch->Attribute("x"));
					axis.y = Ogre::StringConverter::parseReal(e_ch->Attribute("y"));
					axis.z = Ogre::StringConverter::parseReal(e_ch->Attribute("z"));

					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"axis set: x=" << 
						axis.x << ", y=" << axis.y <<
						", z=" << axis.z << "." << std::endl;
				}
				else if(!stricmp(LIMITS, e_ch->Value()))
				{
					lower = Ogre::StringConverter::parseReal(e_ch->Attribute(LOWER));
					upper = Ogre::StringConverter::parseReal(e_ch->Attribute(UPPER));

					//joint->SetAxis(2, Robotarium::Vec3(x, y, z));
					
					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"limits set: Lower=" << lower << 
						", Upper=" << upper << std::endl;
				}
			}

			

			physic::RevoluteJointPtr joint(new physic::RevoluteJoint(name_attr, node1, node2, pos, axis));
			
			joint->SetLimits(lower, upper);
			joint->SetNumSolverIterations(solver_iter_attr);

			LogInfo << "SceneLoader: " << name_attr << ": " <<
				" created for ID1=" << node1->GetName() << 
				" & ID2=" << node2->GetName() << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddConstraint(joint);

		}
		else if(!stricmp(PRISMATIC_JOINT, e->Value()))
		{
			const char* NAME = "Name";
			const char* ID1 = "ID1";
			const char* ID2 = "ID2";
			const char* SOLVER_ITER = "NumSolverIterations";
			const char* POSITION = "Position";
			const char* AXIS = "Axis";
			const char* LOWER = "Lower";
			const char* UPPER = "Upper";			
			
			const char* name_attr = e->Attribute(NAME);

			Robotarium::UInt32 id1_attr = Ogre::StringConverter::parseInt(e->Attribute(ID1));
			Robotarium::UInt32 id2_attr = Ogre::StringConverter::parseInt(e->Attribute(ID2));

			Robotarium::UInt32 solver_iter_attr = 0;
			if(e->Attribute(SOLVER_ITER))
			{
				solver_iter_attr = Ogre::StringConverter::parseInt(e->Attribute(SOLVER_ITER));

				if(solver_iter_attr == 0)
				{
					LogWarn << "SceneLoader: " << name_attr << ": " <<
						SOLVER_ITER << " attribute can not be set to zero! \
						Default value will be used." << std::endl;
				}
			}
			else
			{
				LogWarn << "SceneLoader: " << name_attr << ": " << SOLVER_ITER <<
							" is not specified! \
							Default value will be used." << std::endl;
			}

			graphic::SceneNodePtr node1 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id1_attr);
			graphic::SceneNodePtr node2 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id2_attr);


			Robotarium::Vec3 pos;
			Robotarium::Vec3 axis;
			Robotarium::Real lower, upper;

			for(TiXmlElement* e_ch = e->FirstChildElement(); e_ch != NULL; e_ch = e_ch->NextSiblingElement())
			{
				if(!stricmp(POSITION, e_ch->Value()))
				{
					pos.x = Ogre::StringConverter::parseReal(e_ch->Attribute("x"));
					pos.y = Ogre::StringConverter::parseReal(e_ch->Attribute("y"));
					pos.z = Ogre::StringConverter::parseReal(e_ch->Attribute("z"));

					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"position set: x=" << 
						pos.x << ", y=" << pos.y << ", z=" << pos.z << "." << std::endl;
				}
				else if(!stricmp(AXIS, e_ch->Value()))
				{
					axis.x = Ogre::StringConverter::parseReal(e_ch->Attribute("x"));
					axis.y = Ogre::StringConverter::parseReal(e_ch->Attribute("y"));
					axis.z = Ogre::StringConverter::parseReal(e_ch->Attribute("z"));

					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"axis set: x=" << 
						axis.x << ", y=" << axis.y <<
						", z=" << axis.z << "." << std::endl;
				}
				else if(!stricmp(LIMITS, e_ch->Value()))
				{
					lower = Ogre::StringConverter::parseReal(e_ch->Attribute(LOWER));
					upper = Ogre::StringConverter::parseReal(e_ch->Attribute(UPPER));

					//joint->SetAxis(2, Robotarium::Vec3(x, y, z));
					
					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"limits set: Lower=" << lower << 
						", Upper=" << upper << std::endl;
				}
			}

			

			physic::PrismaticJointPtr joint(new physic::PrismaticJoint(name_attr, node1, node2, pos, axis));
			
			joint->SetLimits(lower, upper);
			joint->SetNumSolverIterations(solver_iter_attr);

			LogInfo << "SceneLoader: " << name_attr << ": " <<
				"Joint " << name_attr << 
				" created for ID1=" << node1->GetName() << 
				" & ID2=" << node2->GetName() << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddConstraint(joint);

		}
		else if(!stricmp(FASTENER_CONSTRAINT, e->Value()))
		{
			const char* NAME = "Name";
			const char* ID1 = "ID1";
			const char* ID2 = "ID2";
			const char* SOLVER_ITER = "NumSolverIterations";
			const char* POSITION = "Position";
			const char* AXIS = "Axis";
			
			
			const char* name_attr = e->Attribute(NAME);

			Robotarium::UInt32 id1_attr = Ogre::StringConverter::parseInt(e->Attribute(ID1));
			Robotarium::UInt32 id2_attr = Ogre::StringConverter::parseInt(e->Attribute(ID2));

			Robotarium::UInt32 solver_iter_attr = 0;
			if(e->Attribute(SOLVER_ITER))
			{
				solver_iter_attr = Ogre::StringConverter::parseInt(e->Attribute(SOLVER_ITER));

				if(solver_iter_attr == 0)
				{
					LogWarn << "SceneLoader: " << name_attr << ": " <<
						SOLVER_ITER << " attribute can not be set to zero! \
						Default value will be used." << std::endl;
				}
			}
			else
			{
				LogWarn << "SceneLoader: " << name_attr << ": " << SOLVER_ITER <<
							" is not specified! \
							Default value will be used." << std::endl;
			}


			graphic::SceneNodePtr node1 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id1_attr);
			graphic::SceneNodePtr node2 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id2_attr);


			Robotarium::Vec3 pos;
			Robotarium::Vec3 axis;

			for(TiXmlElement* e_ch = e->FirstChildElement(); e_ch != NULL; e_ch = e_ch->NextSiblingElement())
			{
				if(!stricmp(POSITION, e_ch->Value()))
				{
					pos.x = Ogre::StringConverter::parseReal(e_ch->Attribute("x"));
					pos.y = Ogre::StringConverter::parseReal(e_ch->Attribute("y"));
					pos.z = Ogre::StringConverter::parseReal(e_ch->Attribute("z"));

					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"position set: x=" << 
						pos.x << ", y=" << pos.y << ", z=" << pos.z << "." << std::endl;
				}
				else if(!stricmp(AXIS, e_ch->Value()))
				{
					axis.x = Ogre::StringConverter::parseReal(e_ch->Attribute("x"));
					axis.y = Ogre::StringConverter::parseReal(e_ch->Attribute("y"));
					axis.z = Ogre::StringConverter::parseReal(e_ch->Attribute("z"));

					LogInfo << "SceneLoader: " << name_attr << ": " << 
						"axis set: x=" << 
						axis.x << ", y=" << axis.y << ", z=" << axis.z << "." << std::endl;
				}
			}

			physic::FastenerConstraintPtr constraint(new physic::FastenerConstraint(name_attr, node1, node2, pos, axis));
			
			constraint->SetNumSolverIterations(solver_iter_attr);

			LogInfo << "SceneLoader: " << name_attr << ": " <<
				" created for ID1=" << node1->GetName() << 
				" & ID2=" << node2->GetName() << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddConstraint(constraint);

		}
		else if(!stricmp(DISABLE_COLLISION, e->Value()))
		{
			const char* name_attr = e->Attribute("Name");

			Robotarium::UInt32 id1_attr = Ogre::StringConverter::parseInt(e->Attribute("ID1"));
			Robotarium::UInt32 id2_attr = Ogre::StringConverter::parseInt(e->Attribute("ID2"));

			graphic::SceneNodePtr node1 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id1_attr);

			graphic::SceneNodePtr node2 = Robotarium::graphic::RenderEngine::GetSingleton()->GetScene()->GetSceneNode(id2_attr);			

			physic::DisableCollisionPtr joint(new physic::DisableCollision(name_attr, node1, node2));
			
			LogInfo << "SceneLoader: " << name_attr << " created for ID1=" << node1->GetName() << " & ID2=" << node2->GetName() << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddConstraint(joint);

			//joint->Init();
			//LogInfo << "Joint Initialized." << std::endl;
			//joint->Load();
			//LogInfo << "Joint Loaded." << std::endl;

		}
	}
}

void RecurseConstraintsXML(TiXmlElement* elem, Robotarium::physic::ConstraintPtr)
{
	const char* POSITION = "Position";
	const char* AXIS = "Axis";

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!stricmp(POSITION, e->Value()))
		{
			Robotarium::Real x = Ogre::StringConverter::parseReal(e->Attribute("x"));
			Robotarium::Real y = Ogre::StringConverter::parseReal(e->Attribute("y"));
			Robotarium::Real z = Ogre::StringConverter::parseReal(e->Attribute("z"));
		}
	}
}

void SceneLoader::RecurseSensorsXML(TiXmlElement* elem)
{
	const char* R_JOINT_SENSOR = "RJointSensor";
	const char* P_JOINT_SENSOR = "PJointSensor";
	const char* FORCE_SENSOR = "ForceSensor";
	const char* REMOTE_SENSOR = "RemoteSensor";
	const char* NAME = "Name";
	const char* ID = "ID";
	const char* SOURCE_NAME = "SourceName";

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!stricmp(R_JOINT_SENSOR, e->Value()))
		{
			const char* name_attr = e->Attribute(NAME);
			const char* source_name_attr = e->Attribute(SOURCE_NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::physic::RJointSensorPtr sensor_ptr(new physic::RJointSensor(name_attr, id_attr));


			sensor_ptr->SetSource(boost::static_pointer_cast<Robotarium::physic::RevoluteJoint>
				(Robotarium::physic::PhysicsWorld::GetSingleton()->GetConstraint(source_name_attr)));

			LogInfo << "SceneLoader: " << name_attr << " created with Name=" << name_attr << 
				" & ID=" << id_attr << " & SourceName=" << source_name_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddSensor(sensor_ptr);

		}
		else if(!stricmp(P_JOINT_SENSOR, e->Value()))
		{
			const char* name_attr = e->Attribute(NAME);
			const char* source_name_attr = e->Attribute(SOURCE_NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::physic::PJointSensorPtr sensor_ptr(new physic::PJointSensor(name_attr, id_attr));


			sensor_ptr->SetSource(boost::static_pointer_cast<Robotarium::physic::PrismaticJoint>
				(Robotarium::physic::PhysicsWorld::GetSingleton()->GetConstraint(source_name_attr)));

			LogInfo << "SceneLoader: " << name_attr << " created with Name=" << name_attr << 
				" & ID=" << id_attr << " & SourceName=" << source_name_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddSensor(sensor_ptr);

		}
		else if(!stricmp(FORCE_SENSOR, e->Value()))
		{
			const char* name_attr = e->Attribute(NAME);
			const char* source_name_attr = e->Attribute(SOURCE_NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::physic::ForceSensorPtr sensor_ptr(new physic::ForceSensor(name_attr, id_attr));

			sensor_ptr->SetSource(boost::static_pointer_cast<Robotarium::physic::ForceFeedbackConstraint>
				(Robotarium::physic::PhysicsWorld::GetSingleton()->GetConstraint(source_name_attr)));

			LogInfo << "SceneLoader: " << name_attr << ": created with Name=" << name_attr << 
				" & ID=" << id_attr << " & SourceName=" << source_name_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddSensor(sensor_ptr);

		}
		else if(!stricmp(REMOTE_SENSOR, e->Value()))
		{


			const char* PORT = "Port";
			
			const char* REMOTE_ADDRESS = "RemoteAddress";

			const char* SIGNAL_SIZE = "SignalSize";
			
			const char* name_attr = e->Attribute(NAME);
			
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::UInt32 port_attr = Ogre::StringConverter::parseInt(e->Attribute(PORT));
			
			const char* remote_address_attr = e->Attribute(REMOTE_ADDRESS);

			Robotarium::UInt32 signal_size_attr = Ogre::StringConverter::parseInt(e->Attribute(SIGNAL_SIZE));

			Robotarium::physic::RemoteSensorPtr sensor_ptr(new physic::RemoteSensor(name_attr, id_attr));


			sensor_ptr->SetPort(port_attr);

			sensor_ptr->SetRemoteAddress(remote_address_attr);

			sensor_ptr->SetSignalSize(signal_size_attr);

			LogInfo << "SceneLoader: " << name_attr << " created with Name=" << name_attr << 
				" & ID=" << id_attr << " & RemoteAddress=" << remote_address_attr << 
				" & Port=" << port_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddSensor(sensor_ptr);

		}
	}
}


void SceneLoader::RecurseActuatorsXML(TiXmlElement* elem)
{
	const char* REVOLUTE_JOINT_ACTUATOR = "RJointActuator";
	const char* PRISMATIC_JOINT_ACTUATOR = "RJointActuator";
	const char* REMOTE_ACTUATOR = "RemoteActuator";
	const char* NAME = "Name";
	const char* ID = "ID";
	const char* TARGET_NAME = "TargetName";

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!stricmp(REVOLUTE_JOINT_ACTUATOR, e->Value()))
		{
			const char* name_attr = e->Attribute(NAME);
			const char* target_name_attr = e->Attribute(TARGET_NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::physic::RJointActuatorPtr actuator_ptr(new physic::RJointActuator(name_attr, id_attr));


			actuator_ptr->SetTarget(boost::static_pointer_cast<Robotarium::physic::RevoluteJoint>
				(Robotarium::physic::PhysicsWorld::GetSingleton()->GetConstraint(target_name_attr)));

			LogInfo << "SceneLoader: " << name_attr << " created with Name=" << name_attr << 
				" & ID=" << id_attr << " & TargetName=" << target_name_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddActuator(actuator_ptr);

		}
		else if(!stricmp(PRISMATIC_JOINT_ACTUATOR, e->Value()))
		{
			const char* name_attr = e->Attribute(NAME);
			const char* target_name_attr = e->Attribute(TARGET_NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::physic::PJointActuatorPtr actuator_ptr(new physic::PJointActuator(name_attr, id_attr));


			actuator_ptr->SetTarget(boost::static_pointer_cast<Robotarium::physic::PrismaticJoint>
				(Robotarium::physic::PhysicsWorld::GetSingleton()->GetConstraint(target_name_attr)));

			LogInfo << "SceneLoader: " << name_attr << " created with Name=" << name_attr << 
				" & ID=" << id_attr << " & TargetName=" << target_name_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddActuator(actuator_ptr);

		}
		else if(!stricmp(REMOTE_ACTUATOR, e->Value()))
		{

			const char* PORT = "Port";
			const char* REMOTE_ADDRESS = "RemoteAddress";
			const char* SIGNAL_SIZE = "SignalSize";
			
			const char* name_attr = e->Attribute(NAME);
			
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::UInt32 port_attr = Ogre::StringConverter::parseInt(e->Attribute(PORT));
			
			const char* remote_address_attr = e->Attribute(REMOTE_ADDRESS);
			
			Robotarium::UInt32 signal_size_attr = Ogre::StringConverter::parseInt(e->Attribute(SIGNAL_SIZE));
			
			Robotarium::physic::RemoteActuatorPtr actuator_ptr(new physic::RemoteActuator(name_attr, id_attr));


			actuator_ptr->SetPort(port_attr);

			actuator_ptr->SetRemoteAddress(remote_address_attr);

			actuator_ptr->SetSignalSize(signal_size_attr);


			LogInfo << "SceneLoader: " << name_attr << " created with Name=" << name_attr << 
				" & ID=" << id_attr << " & RemoteAddress=" << remote_address_attr << 
				" & Port=" << port_attr << "." << std::endl;

			PhysicsWorld::GetSingleton()->AddActuator(actuator_ptr);

		}

	}
}

void SceneLoader::RecurseManagersXML(TiXmlElement* elem)
{
	const char* SENSOR_MANAGER = "SensorManager";
	const char* ACTUATOR_MANAGER = "ActuatorManager";
	const char* EXTERNAL_CONTROLLER = "ExternalController";
	const char* CONTROLLER_PLUGIN_MANAGER = "ControllerPluginManager";
	const char* DISPATCH_MANAGER = "DispatchManager";
	const char* NAME = "Name";
	const char* ID = "ID";

	for(TiXmlElement* e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(!stricmp(SENSOR_MANAGER, e->Value()))
		{
			//LogInfo << "SceneLoader: " << "Inside SensorManager." << std::endl;

			const char* name_attr = e->Attribute(NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			LogInfo << "SceneLoader: " << "Got SensorManager attributes." << std::endl;

			Robotarium::physic::SensorManagerPtr sensorManager_ptr(new physic::SensorManager(name_attr, id_attr));

			LogInfo << "SceneLoader: " << "Created SensorManagerPtr." << std::endl;

			const char* SENSOR = "Sensor";

			for(TiXmlElement* e_ch = e->FirstChildElement(); e_ch != NULL; e_ch = e_ch->NextSiblingElement())
			{
				if(!stricmp(SENSOR, e_ch->Value()))
				{

					LogInfo << "SceneLoader: " << "Inside Inside SensorManager." << std::endl;
					
					const char* sensor_name_attr = e_ch->Attribute(NAME);

					Robotarium::physic::SensorPtr sensor = physic::PhysicsWorld::GetSingleton()->GetSensor(sensor_name_attr);

					if(sensor != 0)
					{
						sensorManager_ptr->AddSensor(sensor);
						LogInfo << "SceneLoader: " << "Sensor, " << sensor_name_attr << ", added to the SensorManager, " << name_attr << "." << std::endl;
					}
					
				}
			}

			physic::PhysicsWorld::GetSingleton()->AddManager(sensorManager_ptr);

		}
		else if(!stricmp(ACTUATOR_MANAGER, e->Value()))
		{
			//LogInfo << "Inside ActuatorManager." << std::endl;

			const char* name_attr = e->Attribute(NAME);
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::physic::ActuatorManagerPtr actuatorManager_ptr(new physic::ActuatorManager(name_attr, id_attr));

			const char* ACTUATOR = "Actuator";

			for(TiXmlElement* e_ch = e->FirstChildElement(); e_ch != NULL; e_ch = e_ch->NextSiblingElement())
			{
				if(!stricmp(ACTUATOR, e_ch->Value()))
				{

					const char* actuator_name_attr = e_ch->Attribute(NAME);

					Robotarium::physic::ActuatorPtr actuator = physic::PhysicsWorld::GetSingleton()->GetActuator(actuator_name_attr);

					actuatorManager_ptr->AddActuator(actuator);

					LogInfo << "Actuator, " << actuator_name_attr << ", added to the ActuatorManager, " << name_attr << "." << std::endl;
				}
			}

			physic::PhysicsWorld::GetSingleton()->AddManager(actuatorManager_ptr);

		}
		else if(!stricmp(EXTERNAL_CONTROLLER, e->Value()))
		{
			const char* SOURCE = "Source";
			const char* TARGET = "Target";
			const char* RX_PORT = "RxPort";
			const char* TX_PORT = "TxPort";
			const char* REMOTE_ADDRESS = "RemoteAddress";
			
			const char* name_attr = e->Attribute(NAME);

			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			const char* source_attr = e->Attribute(SOURCE);

			const char* target_attr = e->Attribute(TARGET);

			Robotarium::UInt32 rx_port_attr = Ogre::StringConverter::parseInt(e->Attribute(RX_PORT));
			Robotarium::UInt32 tx_port_attr = Ogre::StringConverter::parseInt(e->Attribute(TX_PORT));
			
			const char* remote_address_attr = e->Attribute(REMOTE_ADDRESS);

			physic::ExternalControllerPtr externalControllerManager_ptr(new physic::ExternalController(name_attr, id_attr));

			physic::SensorManagerPtr source_ptr = boost::static_pointer_cast<physic::SensorManager>
				(physic::PhysicsWorld::GetSingleton()->GetManager(source_attr));

			physic::ActuatorManagerPtr target_ptr = boost::static_pointer_cast<physic::ActuatorManager>
				(physic::PhysicsWorld::GetSingleton()->GetManager(target_attr));

			externalControllerManager_ptr->SetSensorManager(source_ptr);

			externalControllerManager_ptr->SetActuatorManager(target_ptr);

			externalControllerManager_ptr->SetRxPort(rx_port_attr);

			externalControllerManager_ptr->SetTxPort(tx_port_attr);

			externalControllerManager_ptr->SetRemoteAddress(remote_address_attr);

			physic::PhysicsWorld::GetSingleton()->AddManager(externalControllerManager_ptr);
		}
		
		else if(!stricmp(CONTROLLER_PLUGIN_MANAGER, e->Value()))
		{
			const char* SOURCE = "Source";
			const char* TARGET = "Target";
			const char* PLUGIN_PATH = "PluginPath";

			
			const char* name_attr = e->Attribute(NAME);

			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			const char* source_attr = e->Attribute(SOURCE);

			const char* target_attr = e->Attribute(TARGET);

			const char* plugin_path_attr = e->Attribute(PLUGIN_PATH);

			physic::ControllerPluginManagerPtr controllerPluginManager_ptr(new physic::ControllerPluginManager(name_attr, id_attr));

			physic::SensorManagerPtr source_ptr = boost::static_pointer_cast<physic::SensorManager>
				(physic::PhysicsWorld::GetSingleton()->GetManager(source_attr));

			physic::ActuatorManagerPtr target_ptr = boost::static_pointer_cast<physic::ActuatorManager>
				(physic::PhysicsWorld::GetSingleton()->GetManager(target_attr));

			controllerPluginManager_ptr->SetSensorManager(source_ptr);

			controllerPluginManager_ptr->SetActuatorManager(target_ptr);

			controllerPluginManager_ptr->SetControllerPluginPath(plugin_path_attr);

			physic::PhysicsWorld::GetSingleton()->AddManager(controllerPluginManager_ptr);
		}
		else if(!stricmp(DISPATCH_MANAGER, e->Value()))
		{
			const char* PORT = "Port";
			const char* REMOTE_ADDRESS = "RemoteAddress";

			//LogInfo << "Inside DispatchManager." << std::endl;

			const char* name_attr = e->Attribute(NAME);
			
			Robotarium::UInt32 id_attr = Ogre::StringConverter::parseInt(e->Attribute(ID));

			Robotarium::UInt32 port_attr = Ogre::StringConverter::parseInt(e->Attribute(PORT));
			
			const char* remote_address_attr = e->Attribute(REMOTE_ADDRESS);

			Robotarium::physic::DispatchManagerPtr dispatchManager_ptr(new physic::DispatchManager(name_attr, id_attr));

			dispatchManager_ptr->SetPort(port_attr);

			dispatchManager_ptr->SetRemoteAddress(remote_address_attr);

			const char* MANAGER = "Manager";

			for(TiXmlElement* e_ch = e->FirstChildElement(); e_ch != NULL; e_ch = e_ch->NextSiblingElement())
			{
				if(!stricmp(MANAGER, e_ch->Value()))
				{

					const char* manager_name_attr = e_ch->Attribute(NAME);

					Robotarium::core::ManagerPtr manager = 
						physic::PhysicsWorld::GetSingleton()->GetManager(manager_name_attr);

					if((manager->mManagerType != SENSOR_MANAGER_TYPE) && (manager->mManagerType != CONTROLLER_MANAGER_TYPE))
					{
						LogErr << name_attr << ": Specified Manager type does not contain any outputs to be dispatched." << std::endl;
					}
					else
					{
						dispatchManager_ptr->AddManager(manager);
					}

					//actuatorManager_ptr->AddActuator(actuator);

					LogInfo << name_attr << ": " << manager_name_attr << ", added to the output list." << std::endl;
				}
			}

			physic::PhysicsWorld::GetSingleton()->AddManager(dispatchManager_ptr);

		}
	}
}








//<SimulinkController Name="SimCont_01" ID="0" Source="SensorManager_01" Target="ActuatorManager_01"/>









