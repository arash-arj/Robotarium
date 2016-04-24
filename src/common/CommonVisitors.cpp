#include "common/CommonVisitors.hpp"

using namespace Robotarium;
using namespace common;

void InitVisitor::Visit(Robotarium::core::NodePtr _node)
{
  _node->Init();
}

void LoadVisitor::Visit(Robotarium::core::NodePtr _node)
{
  _node->Load();
}
void UpdateVisitor::Visit(Robotarium::core::NodePtr _node)
{
  _node->Update();
}

void TerminateVisitor::Visit(Robotarium::core::NodePtr _node)
{
  _node->Terminate();
}

