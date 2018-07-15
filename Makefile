## Compiler
CXX = g++

## Compiler Flags
## -g			Debugging enable
## -Wall		Shows all warnings
## -std=c++0x		Compile with C++11 standards (using beta flag because C4 machines use gcc 4.4.7)
CXXFLAGS  = -g -Wall -std=c++0x

## Build target  
TARGET = det

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

clean:
	$(RM) $(TARGET) input.txt output.txt
