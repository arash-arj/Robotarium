#pragma once
#ifndef __CAMERA_NODE_HPP__
#define __CAMERA_NODE_HPP__

#include <vector>
#include <string>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "core/Scene.hpp"
#include "core/SceneNode.hpp"
#include "core/SceneNodeBase.hpp"
#include "core/Visitor.hpp"
#include "graphic/WindowFactory.hpp"


namespace Robotarium
{
	namespace graphic
	{
		class CameraSceneNode;
		
		/// \def CameraSceneNodePtr
		/// \brief Shared pointer to CameraSceneNode
		typedef boost::shared_ptr<CameraSceneNode> CameraSceneNodePtr;

		class CameraSceneNode : public Robotarium::core::SceneNode//   : public boost::enable_shared_from_this<Node>
		{
					/// \brief Constructor
					/// \param[in] scene Pointer to the parent Scene
					/// \param[in] name Name of the new Node
					/// \param[in] meshName Name of the mesh associated with 
					///			   this GraphicNode. There should be a mesh
					///			   with this name in the resources, otherwise
					///			   will crash when loading.
		public:		CameraSceneNode(core::SceneNodePtr& parent, String name, String HWND, Vec2 viewportSize, Vec3 position, Vec3 lapPoint);


		public:		CameraSceneNode(core::SceneNodePtr& parent, String name, Vec2 viewportSize, Vec3 position, Vec3 lapPoint);

					/// \brief Destructor
		public:		~CameraSceneNode();

					/// \brief Loads the CameraSceneNode. This method creates 
					///	the actual Ogre CameraSceneNode and should be called 
					/// after RenderEngine is loaded and initialized.
		public:		void Load(core::SceneNodePtr& parent);

					/// \brief Load this CameraSceneNode
		public:		void Load();

					/// \brief Load this CameraSceneNodes children
		private:	void LoadChildNodes();

					/// \brief Unload this CameraSceneNode
		public:		void Unload();

					/// \brief Update this CameraSceneNode and its children
		public:		void Update();

					/// \brief Update this CameraSceneNodes children
		private:	void UpdateChildNodes();

					/// \brief Sets the look-at-point of the CameraSceneNode
		public:		void SetLookAtPoint(Vec3 lap);

					/// \brief Sets the field of view for the CameraSceneNode
		public:		void SetFOV(Real fov);

					/// \brief Pointer to the viewport
		private:	Ogre::Viewport* mViewport;

					/// \brief Pointer to the Ogre CameraSceneNode
		private:	Ogre::Camera * mCamera;

					/// \brief Pointer to the Ogre RenderWindow
		private:	Ogre::RenderWindow * mRenderWindow;

					/// \brief Pointer to corresponding Ogre SceneNode
		private:	Ogre::SceneNode* mOgreSceneNode;

					/// \brief Stores viewport dimension sizes for 
					///	current CameraSceneNode.
		private:	Vec2 mViewportSize;

					/// \brief Stores coordinates of look at point of the
					///	CameraSceneNode relative to its parent node.
		private:	Vec3 mLapPoint;

					/// \brief Stores the target hwnd for CameraSceneNodes output.
		private:	String mHWND;

		};
	}
}
#endif