add_library(RbmGraphic
  RenderEngine.cpp
  GraphicNode.cpp
  CameraSceneNode.cpp
)
target_link_libraries(RbmGraphic RbmCommon)
target_link_libraries(RbmGraphic RbmCore)