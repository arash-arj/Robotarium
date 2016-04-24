#pragma once

#ifndef __SCENE_LOADER_HPP__
#define __SCENE_LOADER_HPP__

#include "common/Types.hpp"
#include "physics/PhysicsTypes.hpp"
#include "graphic/RenderEngine.hpp"
#include "graphic/Scene.hpp"
#include "graphic/SceneNode.hpp"
#include "graphic/GraphicNode.hpp"
#include "physics/PhysicsWorld.hpp"
#include "physics/RigidBody.hpp"
#include "physics/RevoluteJoint.hpp"
#include "physics/PrismaticJoint.hpp"
#include "physics/FastenerConstraint.hpp"
#include "physics/DisableCollision.hpp"
#include "physics/Sensor.hpp"
#include "physics/RJointSensor.hpp"
#include "physics/PJointSensor.hpp"
#include "physics/ForceSensor.hpp"
#include "physics/RemoteSensor.hpp"
#include "physics/RemoteActuator.hpp"
#include "physics/SensorManager.hpp"
#include "physics/Actuator.hpp"
#include "physics/RJointActuator.hpp"
#include "physics/PJointActuator.hpp"
#include "physics/ActuatorManager.hpp"
#include "physics/ControllerPluginManager.hpp"
#include "thirdparties/ExternalController.hpp"
#include "physics/DispatchManager.hpp"
#include "../extlibs/tinyxml/tinyxml.h"

namespace Robotarium
{
	namespace core
	{
		class SceneLoader
		{
		
		public:		SceneLoader();
		
		
		public:		~SceneLoader();


		public:		void ReadFromFile(Robotarium::String url);


		private:	TiXmlDocument doc;


		private:	void RecurseSceneXML(TiXmlElement*, UInt32, Robotarium::graphic::SceneNodePtr&);

		
		private:	void RecurseSensorsXML(TiXmlElement*);

		
		private:	void RecurseActuatorsXML(TiXmlElement*);


		private:	void RecurseManagersXML(TiXmlElement*);


		private:	void RecurseConstraintsXML(TiXmlElement*);


		private:	void RecurseConstraintsXML(TiXmlElement*, Robotarium::physic::ConstraintPtr);

		
		private:	void RecurseXML(TiXmlElement*);

		};
	}
}
#endif