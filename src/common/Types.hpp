#pragma once

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <string>
#include <stdint.h>
#include "OGRE/Ogre.h"
#include "common/BaseObject.hpp"

#ifdef _WIN32_WINNT
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace Robotarium
{

	typedef enum NODE_TYPE_ENUM
	{
		BASIC_NODE_TYPE = 0,
		SCENE_NODE_TYPE,
		GRAPHIC_NODE_TYPE,
		CAMERA_SCENE_NODE_TYPE,
		RIGID_BODY_NODE_TYPE,
	} NODE_TYPE;


	typedef bool Bool;

	typedef int8_t Int8;
	typedef int16_t Int16;
	typedef int32_t Int32;

	typedef uint8_t UInt8;
	typedef uint16_t UInt16;
	typedef uint32_t UInt32;

	typedef double Real;

	typedef Ogre::Vector2 Vec2;
	typedef Ogre::Vector3 Vec3;
	typedef Ogre::Quaternion Quat;

	typedef Ogre::Matrix4 Trans;

	typedef Ogre::Radian Radian;
	typedef Ogre::Degree Degree;

	typedef std::string String;

	typedef std::vector<Robotarium::Real> Signal;

	namespace core
	{

		class Scene;

		class Node;

		/// \def NodePtr
		/// \brief Shared pointer to Node
		typedef boost::shared_ptr<Node> NodePtr;

		/// \def Node_V
		/// \brief Vector of nodes
		typedef std::vector<NodePtr> NodeVec;

		/// \def Node_VPtr
		/// \brief Pointer to the vector of Nodes
		typedef boost::shared_ptr<NodeVec> NodeVecPtr;


		
		class SceneNode;
		
		/// \def SceneNodePtr
		/// \brief Shared pointer to SceneNode
		typedef boost::shared_ptr<SceneNode> SceneNodePtr;

		/// \def SceneNode_V
		/// \brief Vector of SceneNodes
		typedef std::vector<SceneNodePtr> SceneNodeVec;

		/// \def SceneNodeNode_VPtr
		/// \brief Pointer to vector of SceneNodes
		typedef boost::shared_ptr<SceneNodeVec> SceneNodeVecPtr;
	}


}
#endif