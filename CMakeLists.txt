
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
MESSAGE( ${SOURCES})

#ADD_CUSTOM_TARGET(RunGenerator DEPENDS generatedfile1 generatedfile2
#	COMMENT "Check for generation")

project(${Name})

# set( Sources ${Sources} ${srcDir}/Parser.cpp ${srcDir}/Scanner.cpp)
include_directories( ${srcDir})
add_executable(${Name} ${SOURCES})
#add_dependencies(${Name} RunGenerator)
