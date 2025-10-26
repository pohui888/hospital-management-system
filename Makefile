# Makefile

CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -g
LDLIBS     :=
TARGET     := main

SRC_DIRS   := src/ambulance-dispatch src/emergency-department src/medical-supply src/patient-admission
SRCS       := $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS))) main.cpp
OBJS       := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
