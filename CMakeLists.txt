      # (1)
      cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

      project(NextSim)

      set(CMAKE_MACOSX_RPATH 1)

      # (2)
      option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
      if(WITH_GEANT4_UIVIS)
        find_package(Geant4 REQUIRED ui_all vis_all)
      else()
        find_package(Geant4 REQUIRED)
      endif()

      set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules/)

      find_package(ROOT REQUIRED)
      set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
      
      # (3)      
      include(${Geant4_USE_FILE})
      include_directories(${PROJECT_SOURCE_DIR}/include)
      include_directories(${ROOT_INCLUDE_DIR})
      message(status ${ROOT_INCLUDE_DIR})


     # (4)      
      file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
      file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

      ROOT_GENERATE_DICTIONARY(NEXTSimDict OptPhotonHit.hh ScintHit.hh LINKDEF)

      add_library(NEXTSim SHARED ${PROJECT_SOURCE_DIR}/src/OptPhotonHit.cc ${PROJECT_SOURCE_DIR}/src/ScintHit.cc  NEXTSimDict.cxx)
      target_link_libraries(NEXTSim ${ROOT_LIBRARIES})


      # (5)
      add_executable(neutronDetectorDesign neutronDetectorDesign.cc ${sources} )
      target_link_libraries(neutronDetectorDesign ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} NEXTSim)

      # (6)


      # (7) Left out since it will only be executed locally where built


      # (8) DPL
      #---------------------------------------------------------------------------
      # Create the directory for the Output files
      #
      file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output")

      # (9)
      #---------------------------------------------------------------------------
      #Copy all scripts to the build directory, i.e. the directory in which we
      # build NEXTSim. This is so that we can run the executable directly because it
      # relies on these scripts being in the current working directory.
      #
	set(NEXTSIM_SCRIPTS
      	mac/run.mac
      	mac/vis.mac
        )

      foreach(_script ${NEXTSIM_SCRIPTS})
       configure_file(
          ${PROJECT_SOURCE_DIR}/${_script}
          ${PROJECT_BINARY_DIR}/${_script}
          COPYONLY
          )
      endforeach()
