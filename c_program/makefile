# Makefile

CXX				= g++
TARGET			= soeasy
CURRENT_PATH 	:= ./
SRC_PATH		= $(wildcard ./src/*.cpp)
INCLUDE_PATH 	= -I${CURRENT_PATH}/include/
OBJS			= $(SRCS:.cpp=.o)
LIB_PATH 		= -L${CURRENT_PATH}/lib/

all :
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(LIB_PATH) $(INCLUDE_PATH) $(SRC_PATH) 