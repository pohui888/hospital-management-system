# Makefile

CXX        := g++
CXXFLAGS   := -std=c++17 -Wall -g
LDLIBS     :=
TARGET     := main

SRC_DIRS   := src/ambulance-dispatcher src/emergency-department src/patient-admission src/medical-supply-manager/controllers/SupplyManager src/medical-supply-manager/FileHandler src/medical-supply-manager/MedicalSupplyMenuHandler src/medical-supply-manager/models/Supply src/medical-supply-manager/models/SupplyStack src/medical-supply-manager/utils
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
