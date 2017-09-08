#因为我们使用的新版本，所以最低要求是2.8.11  
cmake_minimum_required( VERSION 2.8.11 )  
project( qtvtk )  
  
#这句话是我们刚才标记添加的内容  
set(CMAKE_INCLUDE_CURRENT_DIR ON)  
  
#这两句是VTK的内容，没什么说的  
find_package( VTK REQUIRED )  
include( ${VTK_USE_FILE} )  
  
#这句话是刚才标价添加的  
find_package(Qt5Widgets)  
#这个include是根据东灵博客的内容  
include_directories(${PROJECT_SOURCE_DIR}  
                    ${CMAKE_CURRENT_BINARY_DIR}  
                    ${VTK_DIR})  
  
#这片的内容是设置MOC翻译的内容，我们只需要将东灵博客的QT4改成QT5就可以  
SET( PROJECT_SRCS  
    main.cpp  
    qtvtk.cpp  
    qtvtk.h  
    )  
SET( PROJECT_UIS  
    qtvtk.ui  
)  
SET( PROJECT_MOC_HDRS  
  qtvtk.h  
)  
QT5_WRAP_UI( PROJECT_UIS_H  
             ${PROJECT_UIS}  
           )  
QT5_WRAP_CPP( PROJECT_MOC_SRCS  
              ${PROJECT_MOC_HDRS}  
            )  
  
#这句话就是添加可执行文件了  
ADD_EXECUTABLE( qtvtk  
                ${PROJECT_SRCS}  
                ${PROJECT_UIS_H}  
                ${PROJECT_MOC_SRCS}  
              )  
  
#这边我们要包含的东西就是vtk和QT5各自需要包含的头文件  
TARGET_LINK_LIBRARIES ( qtvtk  
  ${VTK_LIBRARIES}  
  Qt5::Widgets  
  ) 