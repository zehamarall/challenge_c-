# 
# Makefile for some Boost testing
#

MY_NAME := stream_server
MY_SRCS := $(wildcard *.cpp)
MY_OBJS := ${MY_SRCS:.cpp=.o}
MY_INCLUDE_DIRS :=
MY_LIBRARY_DIRS := /usr/lib/x86_64-linux-gnu
MY_LIBRARIES := boost_system

CXXFLAGS += $(foreach includedir,$(MY_INCLUDE_DIRS),-I$(includedir))
CXXFLAGS += -g -std=gnu++11
LDFLAGS += $(foreach librarydir,$(MY_LIBRARY_DIRS),-L$(librarydir))
LDLIBS += $(foreach library,$(MY_LIBRARIES),-l$(library))

.PHONY: all clean

all: ${MY_NAME}

$(MY_NAME): $(MY_OBJS)
	$(LINK.cc) $(MY_OBJS) -o $(MY_NAME) $(LDLIBS)

clean:
	@- rm -rf $(MY_OBJS) $(MY_NAME)
