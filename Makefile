CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall
SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)
EXECUTABLE = ImageProcessing

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o

cleanall:
	rm -f *.o $(EXECUTABLE)
