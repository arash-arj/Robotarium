#pragma once
#ifndef __GRAPHIC_NODE_HPP__
#define __GRAPHIC_NODE_HPP__

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

#include "core/Scene.hpp"
#include "core/Node.hpp"

namespace Robotarium
{
	namespace graphic
	{

		class GraphicNode;

		/// \def GraphicNodePtr
		/// \brief Shared pointer to GraphicNode
		typedef boost::shared_ptr<GraphicNode> GraphicNodePtr;


		class GraphicNode : public Robotarium::core::Node //   : public boost::enable_shared_from_this<Node>
		{
					/// \brief Constructor
					/// \param[in] scene Pointer to the parent Scene
					/// \param[in] name Name of the new Node
					/// \param[in] meshName Name of the mesh associated with 
					///			   this GraphicNode. There should be a mesh
					///			   with this name in the resources, otherwise
					///			   will crash when loading.
		public:		GraphicNode(Robotarium::String _name);

					/// \brief Destructor
		public:		~GraphicNode();

					/// \brief Initialize GraphicNode
		public:		virtual void Init();

					/// \brief Load GraphicNode
		public:		virtual void Load();

					/// \brief Update GraphicNode
		public:		virtual void Update();

					/// \brief Terminate GraphicNode
		public:		virtual void Terminate();

					/// \brief Stores the mesh name associated with this GraphicNode
		private:	Robotarium::String mMeshName;

					/// \brief Pointer to the associated Mesh
		private:	Robotarium::common::MeshPtr mMesh;

					/// \brief Returns the pointer to the associated Mesh
		public:		Robotarium::common::MeshPtr GetMeshPtr();

					/// \brief Gets the mesh name associated with this GraphicNode
		public:		Robotarium::String GetMeshName();

					/// \brief Gets the mesh name associated with this GraphicNode
		public:		void SetMeshName(String);

					/// \brief Pointer to the Ogre Entity for this GraphicNode
		private:	Ogre::Entity* mOgreEntity;

					/// \brief Returns pointer to the Entity
		public:		Ogre::Entity* GetOgreEntity();

					/// \brief Pointer to the GraphicNodes Ogre SceneNode
		private:	Ogre::SceneNode* mOgreSceneNode;

					/// \brief Returns the Ogre SceneNode for this GraphicNode
		public:		Ogre::SceneNode* GetOgreSceneNode();

					/// \brief Load the mesh data
		public:		void LoadMesh();

					/// \brief Indicates whether the Mesh name is set for this GraphicNode
		private:	Robotarium::Bool mIsMeshNameSet;

					/// \brief Indicates whether the GraphicNode is Initialized
		private:	Robotarium::Bool mIsInitialized;

					/// \brief Indicates whether the GraphicNode is Loaded
		private:	Robotarium::Bool mIsLoaded;

		};
	}
}
#endif