#pragma once
#ifndef __SCENE_NODE_BASE_HPP__
#define __SCENE_NODE_BASE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "common/Types.hpp"
#include "core/Node.hpp"

namespace Robotarium
{
	namespace core
	{
		class SceneNodeBase : public Robotarium::core::Node
		{
					friend class core::Scene;

			/// \brief Constructor
			/// \param[in] scene Pointer to the parent Scene
			/// \param[in] name Name of the new Node
		public:		SceneNodeBase(Robotarium::String);

					/// \brief Destructor
		public:		~SceneNodeBase();

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
#endif