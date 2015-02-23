CXX = clang++
CXXFLAGS += -std=c++11 -Wall
LDLIBS += -lGL -lglut

all: test
