#pragma once
#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include "common/Types.hpp"
#include "ManagerOutput.hpp"

namespace Robotarium
{
	namespace core
	{

		typedef enum MANAGER_TYPE_ENUM
		{
			CONSTRAINT_MANAGER_TYPE = 0,
			ACTUATOR_MANAGER_TYPE,
			SENSOR_MANAGER_TYPE,
			CONTROLLER_MANAGER_TYPE,
			DISPATCH_MANAGER_TYPE,
		} MANAGER_TYPE;


		class Manager;

		/// \def ManagerPtr
		/// \brief Shared Pointer to Manager
		typedef boost::shared_ptr<Manager> ManagerPtr;

		/// \def Manager_M
		/// \brief List of Managers
		typedef std::list<ManagerPtr> ManagerList;

		/// \def Manager_MPtr
		/// \brief Pointer to the list of Managers
		typedef boost::shared_ptr<ManagerList> ManagerListPtr;

		class Manager
		{

					/// \brief Constructor.
		public:		Manager(MANAGER_TYPE _type, Robotarium::String _name, Robotarium::Int32 _id);

					/// \brief Destructor.
		public:		~Manager();

					/// \brief Load the Manager.
		public:		virtual void Load() = 0;

					/// \brief Initialize the Manager.
		public:		virtual void Init() = 0;

					/// \brief Update the Manager.
		public:		virtual void Update() = 0;

					/// \brief Determines Managers Type. Should be specified in the derived class
		public:		MANAGER_TYPE mManagerType;

					/// \brief Managers Name
		private:	Robotarium::String mName;

					/// \brief Returns the Managers Name
		public:		Robotarium::String GetName();

					/// \brief Sets the Name of the Manager
		public:		void SetName(Robotarium::String _name);

					/// \brief ID of the Manager
		private:	Robotarium::Int32 mID;

					/// \brief Gets the ID of the Manager
		public:		Robotarium::Int32 GetID();

					/// \brief ManagerOutput
		public:		ManagerOutput mOutput;

		};
	}
}

#endif