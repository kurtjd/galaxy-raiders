project(space-invaders)

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

set(
  SOURCES
  ${PROJECT_SOURCES}/CoreCannon.cpp
  ${PROJECT_SOURCES}/Earth.cpp
  ${PROJECT_SOURCES}/Explosions.cpp
  ${PROJECT_SOURCES}/game.cpp
  ${PROJECT_SOURCES}/globals.cpp
  ${PROJECT_SOURCES}/Invader.cpp
  ${PROJECT_SOURCES}/InvaderFormation.cpp
  ${PROJECT_SOURCES}/LivesDisplay.cpp
  ${PROJECT_SOURCES}/main.cpp
  ${PROJECT_SOURCES}/Menu.cpp
  ${PROJECT_SOURCES}/misc.cpp
  ${PROJECT_SOURCES}/NormalInvaderLaser.cpp
  ${PROJECT_SOURCES}/PlayerLaser.cpp
  ${PROJECT_SOURCES}/PoweredInvaderLaser.cpp
  ${PROJECT_SOURCES}/ScoreDisplay.cpp
  ${PROJECT_SOURCES}/Shield.cpp
  ${PROJECT_SOURCES}/ShieldWall.cpp
  ${PROJECT_SOURCES}/SoundFx.cpp
  ${PROJECT_SOURCES}/Textures.cpp
  ${PROJECT_SOURCES}/UFO.cpp
  )

set(APP_NAME space-invaders)
add_executable(${APP_NAME} ${SOURCES})

target_include_directories(
  ${APP_NAME}
  PRIVATE ${PROJECT_INCLUDES}
  PRIVATE ${SFML_INCLUDE_DIR}
  )

target_link_libraries(
  ${APP_NAME}
  ${SFML_LIBRARIES}
  )

set_target_properties(
  ${APP_NAME} PROPERTIES
  COMPILE_FLAGS "${WARNING_FLAGS}"
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  )
