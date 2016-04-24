#pragma once
#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "common/SingletonT.hpp"
#include "common/Mesh.hpp"
#include "core/SceneNode.hpp"
#include "core/Visitor.hpp"

namespace Robotarium
{
	namespace core
	{
		class Scene : public SingletonT<Robotarium::core::Scene>//  : public boost::enable_shared_from_this<Scene>
		{
			/// \brief Constructor
		public:		Scene(void);

					/// \brief Destructor
		public:		~Scene(void);

		private:	SceneNodePtr mRootSceneNode;

		public:		SceneNodePtr& GetRootSceneNode()
					{
						return mRootSceneNode;
					}

					/// \brief Load the Scene
		public:		void Init();

					/// \brief Initialize the Scene
		public:		void Load();

					/// \brief Update the Whole Scene
		public:		void Update();

					/// \brief Terminate SceneManager
		public:		void Terminate();

					/// \brief Recursive Function to Update Every Node in the Scene
		public:		void UpdateScene(Robotarium::core::NodePtr& startingNode);

					/// \brief Add Node to a specified parent Node
		public:		void AddNode(core::NodePtr _new_node, core::SceneNodePtr _parent_node);

					/// \brief Add Node to a specified parent Node
		public:		void AddNode(core::NodePtr _new_node, Robotarium::String _parent_name);

					/// \brief Add Node to a root Node
		public:		void AddNode(core::NodePtr _new_node);
					
					/// \brief Determines if the Node has a child of specific type (child of first order)
		public:		Robotarium::Bool HasChild(Robotarium::core::NodePtr _node, Robotarium::NODE_TYPE_ENUM _type);

					/// \brief Determines if the Node has any child
		public:		Robotarium::Bool HasChild(Robotarium::core::NodePtr _node);

					/// \brief Returns the first child with specified type
		public:		Robotarium::core::NodePtr GetFirstChild(Robotarium::core::NodePtr, Robotarium::NODE_TYPE_ENUM);

					/// \brief Gets the Node by name
		public:		Robotarium::core::NodePtr GetNode(Robotarium::String _name);

					/// \brief Gets the Node by name, starting from a specific Node
		public:		Robotarium::core::NodePtr GetNode(Robotarium::core::SceneNodePtr _starting_node, Robotarium::String _name);

					/// \brief Dispatches a Visitor to every Node
		public:		void DispatchVisitor(core::Visitor&);

					/// \brief Dispatches a Visitor to every Node
		public:		void DispatchVisitor(core::Visitor&, Robotarium::core::SceneNodePtr);

					/// \brief Dispatches a Visitor to the Nodes with specified type
		public:		void DispatchVisitor(core::Visitor&, NODE_TYPE_ENUM _type);

					/// \brief Dispatches a Visitor to the Nodes with specified type, start from specified SceneNode
		public:		void DispatchVisitor(core::Visitor&, Robotarium::NODE_TYPE_ENUM, Robotarium::core::SceneNodePtr);

					/// \brief Vector of Scene Meshes
		private:	Robotarium::common::MeshVecPtr mMeshVec;
					
					/// \brief Add Mesh to the Scene's Mesh vector
		public:		void AddMesh(Robotarium::common::MeshPtr _mesh_ptr);

					/// \brief Get pointer to Mesh with specified name
		public:		common::MeshPtr GetMesh(Robotarium::String _name);
		};
	}
}
#endif