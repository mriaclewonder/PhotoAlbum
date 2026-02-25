# 指定所需CMake的最低版本，确保使用兼容的命令和特性
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本，并声明使用的语言为C++
project(PhotoAlbum VERSION 0.1 LANGUAGES CXX)

# 启用Qt的自动UI处理：编译时自动调用uic处理.ui文件
set(CMAKE_AUTOUIC ON)

# 启用Qt的自动MOC处理：编译时自动调用moc处理含有Q_OBJECT的头文件
set(CMAKE_AUTOMOC ON)

# 启用Qt的自动RCC处理：编译时自动调用rcc处理.qrc资源文件
set(CMAKE_AUTORCC ON)

# 设置C++标准为17，并强制要求编译器支持该标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt库，先尝试Qt6再尝试Qt5，必须找到Widgets组件
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

# 根据上面找到的Qt主版本号，再次查找对应版本的Widgets组件
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 定义项目的源文件列表，包含主函数、主窗口实现、头文件和UI文件
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# 根据Qt主版本选择不同的可执行文件生成方式
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # Qt6使用qt_add_executable命令创建可执行文件，MANUAL_FINALIZATION表示手动控制最终化步骤
    qt_add_executable(PhotoAlbum
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    # 如果是Android平台，可以在这里设置Android包源目录（示例注释）
    # set_property(TARGET PhotoAlbum APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #              ${CMAKE_CURRENT_SOURCE_DIR}/android)
else()
    # Qt5的处理：如果是Android，则创建共享库；否则创建普通可执行文件
    if(ANDROID)
        add_library(PhotoAlbum SHARED
            ${PROJECT_SOURCES}
        )
        # 如果是Android，可以在这里设置Android包源目录（示例注释）
        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PhotoAlbum
            ${PROJECT_SOURCES}
            rc.qrc
        )
    endif()
endif()

# 链接Qt的Widgets模块到目标PhotoAlbum
target_link_libraries(PhotoAlbum PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 对于iOS/macOS，设置bundle标识符（仅Qt版本低于6.1.0时需要手动指定）
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PhotoAlbum)
endif()

# 设置目标属性：bundle标识符、版本信息、是否为macOS bundle、是否为Windows GUI应用
set_target_properties(PhotoAlbum PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 包含GNU安装目录定义，用于后续安装路径
include(GNUInstallDirs)

# 安装目标：bundle（macOS）放到当前目录，库文件放到标准库目录，可执行文件放到标准bin目录
install(TARGETS PhotoAlbum
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 如果使用的是Qt6，则执行可执行文件的最终化（例如处理Android的部署）
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PhotoAlbum)
endif()

