
SET(Name "MIECCompiler")
 
SET(srcDir MiniIEC)
SET(Languagefile ${srcDir}/MIEC.atg) 
SET( Sources ${Sources} ${srcDir}/main.cpp ${srcDir}/SymbolFactory.cpp)
SET( cocoNamespace MIEC)

ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Parser.h ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Scanner.h ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir}/Scanner.cpp
                    COMMAND cococpp -frames ${CMAKE_CURRENT_SOURCE_DIR}/CocoLinux ${CMAKE_CURRENT_SOURCE_DIR}/${Languagefile} -o ${CMAKE_CURRENT_SOURCE_DIR}/${srcDir} -namespace ${cocoNamespace}
                    #COMMAND set( Sources ${Sources} Parser.cpp Scanner.cpp PARENT_SCOPE)
                    DEPENDS  ${Languagefile} 
                    COMMENT "Generating source code from XML" )
MESSAGE( ${CMAKE_CURRENT_SOURCE_DIR})

#ADD_CUSTOM_TARGET(RunGenerator DEPENDS generatedfile1 generatedfile2
#	COMMENT "Check for generation")

project(${Name})

set( Sources ${Sources} ${srcDir}/Parser.cpp ${srcDir}/Scanner.cpp)
include_directories( ${srcDir})
add_executable(${Name} ${Sources})
#add_dependencies(${Name} RunGenerator)
