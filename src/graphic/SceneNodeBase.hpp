#pragma once
//#ifndef __SCENE_NODE_BASE_HPP__
//#define __SCENE_NODE_BASE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "core/Node.hpp"

namespace Robotarium
{
	namespace core
	{
		class SceneNodeBase : public Node	//: public boost::enable_shared_from_this<Node>
		{
			/// \brief Constructor
			/// \param[in] scene Pointer to the parent Scene
			/// \param[in] name Name of the new Node
		public:		SceneNodeBase(String);

					/// \brief Destructor
		public:		~SceneNodeBase();

					/// \brief Load this SceneNode and its children
		public:		virtual void Load() = 0;

					/// \brief Load this SceneNode's children
		private:	virtual void LoadChildNodes() = 0;

					/// \brief Update this SceneNode and its children
		public:		virtual void Update() = 0;

					/// \brief Update this SceneNode's children
		private:	virtual void UpdateChildNodes() = 0;

					/// \brief Terminate this SceneNode and its children
		//public:		virtual void Terminate();

					/// \brief Determines if the SceneNode is Loaded
		private:	Robotarium::Bool mLoaded;

					/// \brief Determines if the SceneNode is Initialized
		private:	Robotarium::Bool mInitialized;

					/// \brief Returns True if the SceneNode is Loaded
		public:		Robotarium::Bool IsLoaded();

					/// \brief Returns True if the SceneNode is Initialized
		public:		Robotarium::Bool IsInitialized();

					/// \brief Marks the SceneNode is Loaded
		public:		void SetLoaded(Robotarium::Bool _is_loaded);

					/// \brief Marks the SceneNode is Initialized
		public:		void SetInitialized(Robotarium::Bool _is_initialized);



		};
	}
}
//#endif