cmake_minimum_required(VERSION 4.0)
set(VITASDK "$ENV{VITASDK}")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(Minecraft_beta_1.7.3)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Minecraft beta 1.7.3")
set(VITA_TITLEID  "VSDK00002")
set(VITA_VERSION  "01.00")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wl,-Map=output.map")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

include_directories(src/loader)
include_directories(src/common)
include_directories(src/frame)
include_directories(src/interpreter)
include_directories(src)

add_executable(${PROJECT_NAME}
  src/main.c
  src/util.c
  src/heap.c
  src/method_area.c
  src/init.c
  src/frame/frame.c
  src/frame/stacks.c
  src/interpreter/runtime.c
  src/loader/attributes.c
  src/loader/constant_pool.c
  src/loader/fields.c
  src/loader/interfaces.c
  src/loader/loader.c
  src/loader/method.c
  src/common/debugScreen.c
)

target_link_libraries(${PROJECT_NAME}
  SceDisplay_stub
  SceCtrl_stub
  SceCamera_stub
  SceLibKernel_stub
  SceDisplay_stub   
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE test/Add.class Add.class
  FILE test/JvmTest.class JvmTest.class
)
