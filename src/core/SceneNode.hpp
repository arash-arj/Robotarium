#ifndef __SCENE_NODE_HPP__
#define __SCENE_NODE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "core/SceneNodeBase.hpp"

namespace Robotarium
{
	namespace core
	{
		class SceneNode : public SceneNodeBase
		{
					friend class core::Scene;

					/// \brief Constructor
					/// \param[in] name Name of the new Node
					/// \param[in] Id Unique ID of the new Node
		public:		SceneNode(Robotarium::String);

					/// \brief Destructor
		public:		~SceneNode();

					/// \brief Initialize this SceneNode
		public:		void Init();

					/// \brief Load this SceneNode
		public:		void Load();

					/// \brief Update this SceneNode and its children
		public:		void Update();

					/// \brief Terminate this SceneNode
		public:		void Terminate();
					
					/// \brief Returns True if the SceneNode is Initialized
		public:		Robotarium::Bool IsInitialized();

					/// \brief Contains child nodes
		private:	NodeVecPtr mChildNodes;

					/// \brief Returns the pointer to child nodes
		public:		NodeVecPtr& GetChildNodeVec();

					/// \brief Returns the pointer to child nodes
		public:		NodePtr GetChildNode(Robotarium::UInt32 _index);

					/// \brief Returns size of the child node vec
		public:		Robotarium::UInt32 GetNodeVecSize();

					/// \brief Adds a new Node to the child node vec
					/// \param[in] nodePtr Shared pointer to the node
					///			   which is going to be added as child
		protected:	void AddNode(NodePtr _node_ptr);

					/// \brief Set position
		public:		void SetPosition(Real x, Real y, Real z);
					void SetPosition(Vec3 pos);
					
					/// \brief Get position
		public:		Vec3 GetPosition();

					/// \brief Get position
		public:		Quat GetOrientation();

					/// \brief Get position
		public:		Vec3 GetWorldPosition();

					/// \brief Get orientation
		public:		Quat GetWorldOrientation();

					/// \brief Stores position of the camera
		private:	Vec3 mPosition;

					/// \brief Stores rosition of the camera
		private:	Quat mOrientation;

					/// \brief Set orientation
		public:		void SetOrientation(Ogre::Quaternion rot);

					/// \brief Set orientation
		public:		void SetOrientation(Real angle, Vec3 axis);


		public:		void SetWorldTransform(Robotarium::Vec3 _position, Robotarium::Quat _rotation);


		public:		Robotarium::Trans GetWorldTransform();
		
		};
	}
}
#endif