# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++11

# Source files
SRCS = Add.cpp Div.cpp Mul.cpp Operation.cpp OperationFactory.cpp Sub.cpp test.cpp

# Header files
HEADERS = Add.h Div.h Mul.h Operation.h OperationFactory.h Sub.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = test

# Default target
all: $(EXEC)

# Link the object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile the .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean

