CXX       = clang++
CXXFLAGS += -std=c++11 -Wall \
            $(shell pkg-config --cflags glfw3)
LDLIBS   += $(shell pkg-config --libs   glfw3) -lGL

all: test
