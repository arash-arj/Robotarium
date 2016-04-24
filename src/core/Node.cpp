#include "core/Node.hpp"
#include "core/SceneNode.hpp"

using namespace Robotarium;
using namespace core;

Node::Node(String name)
{
	SetNodeType(BASIC_NODE_TYPE);
	mName = name;
}

Node::~Node()
{
}

Robotarium::String Node::GetName()
{
	return this->mName;
}

void Node::SetName(Robotarium::String _name)
{
	this->mName = _name;
}

void Node::SetNodeType(NODE_TYPE _type)
{
	type = _type;
}

NODE_TYPE Node::GetNodeType()
{
	return type;
}

SceneNodePtr Node::GetParent()
{
	return this->mParent;
}

void Node::SetParent(SceneNodePtr _parent_node)
{
	this->mParent = _parent_node;
}
