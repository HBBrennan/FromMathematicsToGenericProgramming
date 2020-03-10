CXX := clang++
CXXFLAGS := -std=c++2a 

.PHONY: all clean

all: bin/ch4 bin/ch7 bin/ch8

bin/%: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf bin/*
