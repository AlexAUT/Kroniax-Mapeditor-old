cmake_minimum_required(VERSION 2.8)

project(Kroniax_Mapeditor)

# Set options
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
set(SFML_STATIC_LIBS FALSE CACHE BOOL "Choose whether SFML is linked statically or not.")
set(Kroniax_Mapeditor_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard/runtime libraries? This option must match the one used for SFML.")
    
# Make sure that the runtime library gets link statically
if(Kroniax_Mapeditor_STATIC_STD_LIBS)
	if(NOT SFML_STATIC_LIBS)
		message("\n-> If you check Kroniax_Mapeditor_STATIC_STD_LIBS, you also need to check SFML_STATIC_LIBRARIES.")
		message("-> It would lead to multiple runtime environments which result in undefined behavior.\n")
	elseif(WIN32 AND MSVC)
		# Change all MSVC compiler flags to /MT
		foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
			if(${flag} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
		endforeach()
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		# Note: Doesn't work for TDM compiler, since it's compiling the runtime libs statically by default
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
	endif()
endif()

# Kroniax_Mapeditor uses C++11 features
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")

# Make sure that FindSFML.cmake searches for the static libraries
if(SFML_STATIC_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

# Find SFML
find_package(SFML 2 COMPONENTS graphics window system)

# Output an error if SFML wasn't found
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Add the source files
set(SRC_DIR "include")
set(INC_DIR "include")

set(
	SOURCES
	${INC_DIR}/AwGUI/awMessageBox.hpp
	${INC_DIR}/AwGUI/button.hpp
	${INC_DIR}/AwGUI/dropDownMenu.hpp
	${INC_DIR}/AwGUI/enum.hpp
	${INC_DIR}/AwGUI/gui.hpp
	${INC_DIR}/AwGUI/inputBox.hpp
	${INC_DIR}/AwGUI/layer.hpp
	${INC_DIR}/AwGUI/panel.hpp
	${INC_DIR}/utilities/converter.hpp
	${INC_DIR}/guiActions.hpp
	${INC_DIR}/initGui.hpp
	${INC_DIR}/level.hpp
	${INC_DIR}/levelEditor.hpp
	${INC_DIR}/levelLine.hpp
	${INC_DIR}/scriptManager.hpp
	${SRC_DIR}/AwGUI/awMessageBox.cpp
	${SRC_DIR}/AwGUI/button.cpp
	${SRC_DIR}/AwGUI/dropDownMenu.cpp
	${SRC_DIR}/AwGUI/gui.cpp
	${SRC_DIR}/AwGUI/inputBox.cpp
	${SRC_DIR}/AwGUI/layer.cpp
	${SRC_DIR}/AwGUI/panel.cpp
	${SRC_DIR}/utilities/converter.cpp
	${SRC_DIR}/level.cpp
	${SRC_DIR}/levelEditor.cpp
	${SRC_DIR}/levelLine.cpp
	${SRC_DIR}/scriptManager.cpp
	${SRC_DIR}/../main.cpp
)

# Tell CMake to build a executable 
add_executable(Kroniax_Mapeditor ${SOURCES})

# Link SFML
target_link_libraries(Kroniax_Mapeditor ${SFML_LIBRARIES})

# Install executable
install(TARGETS Kroniax_Mapeditor
		RUNTIME DESTINATION .)

# Install game data
install(DIRECTORY data
		DESTINATION .)

# On Windows install required audio libraries
if(WIN32)
	install(FILES ${SFML_ROOT}/bin/openal32.dll ${SFML_ROOT}/bin/libsndfile-1.dll
			DESTINATION .)
endif()
