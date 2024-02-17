
SET(Name "MIECCompiler")

set(CMAKE_CXX_STANDARD 20)
SET(srcDir MiniIEC)
SET(Languagefile ${srcDir}/MIEC.atg) 
file(GLOB SOURCES CONFIGURE_DEPENDS "MiniIEC/*.cpp")
file(GLOB SOURCES2 CONFIGURE_DEPENDS "MiniIEC/*/*.cpp")
# file(GLOB SOURCES2 CONFIGURE_DEPENDS "MiniIEC/*/*.h")
SET(SOURCES ${SOURCES} ${SOURCES2})
message(STATUS,${SOURCES2})
SET( cocoNamespace MIEC)

ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Parser.h ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Scanner.h ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Scanner.cpp
                    COMMAND cococpp -frames ${CMAKE_CURRENT_SOURCE_DIR}/Coco ${CMAKE_CURRENT_SOURCE_DIR}/${Languagefile} -o ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir} -namespace ${cocoNamespace}
                    #COMMAND set( Sources ${Sources} Parser.cpp Scanner.cpp PARENT_SCOPE)
                    DEPENDS  ${Languagefile} 
                    COMMENT "Generating source code from XML" )

#ADD_CUSTOM_TARGET(RunGenerator DEPENDS generatedfile1 generatedfile2
#	COMMENT "Check for generation")

project(${Name})

# set( Sources ${Sources} ${srcDir}/Parser.cpp ${srcDir}/Scanner.cpp)
include_directories( ${srcDir})
add_executable(${Name} ${SOURCES})

find_package(Catch2 3 REQUIRED)
file(GLOB TEST_SRC CONFIGURE_DEPENDS "tests/*.cpp")
file(GLOB TEST_SRC2 CONFIGURE_DEPENDS "tests/*/*.cpp")
file(GLOB MAIN CONFIGURE_DEPENDS "MiniIEC/main.cpp")
SET(TEST_SRC ${TEST_SRC} ${TEST_SRC2})
enable_testing()
# These tests can use the Catch2-provided main
list(REMOVE_ITEM SOURCES ${MAIN})
MESSAGE( ${SOURCES})

add_executable(tests ${SOURCES} ${TEST_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE "MiniIEC")
include(CTest)
include(Catch)
catch_discover_tests(tests)
# add_test(TESTS tests)
# # These tests need their own main
# add_executable(custom-main-tests test.cpp test-main.cpp)
# target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)
# #add_dependencies(${Name} RunGenerator)
