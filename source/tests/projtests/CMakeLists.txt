#ADD_SUBDIRECTORY(Mocks)
FILE (GLOB TEST_SOURCES *.cpp 
	  Mocks/*.cpp)
enable_testing()
INCLUDE_DIRECTORIES (${gtest_SOURCE_DIR}/include 
					${gtest_SOURCE_DIR} 
					${gmock_SOURCE_DIR}/include 
					${PROJECT_SOURCE_DIR}/source/proj
					${PROJECT_BINARY_DIR}/source/proj 
					Mocks)
ADD_EXECUTABLE (Test${GB_PROJECT_NAME}-bin ${TEST_SOURCES})

TARGET_LINK_LIBRARIES (Test${GB_PROJECT_NAME}-bin ${GB_PROJECT_NAME}-lib gtest gtest_main gmock) 

ADD_TEST( Test${GB_PROJECT_NAME}-bin Test${GB_PROJECT_NAME}-bin )
ADD_CUSTOM_COMMAND(TARGET Test${GB_PROJECT_NAME}-bin POST_BUILD COMMAND ${PROJECT_BINARY_DIR}/Test${GB_PROJECT_NAME}-bin)
