add_library(RbmCore
  Manager.cpp 
  Scene.cpp
  Node.cpp
  SceneNode.cpp
  SceneNodeBase.cpp
  Visitor.cpp
  )
target_link_libraries(RbmCore RbmCommon)
#set_target_properties(RbmCore PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/)