## Compiler
CXX = g++

## Compiler Flags
## -g			Debugging enable
## -Wall		Shows all warnings
## --std=c++11	Compile with C++11 standards
CXXFLAGS  = -g -Wall

## Build target  
TARGET = det

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	$(RM) $(TARGET)
