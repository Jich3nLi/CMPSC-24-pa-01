# Makefile for PA01 Card Game
# Author: Peter Li

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Executables
EXEC_SET = game_set
EXEC_BST = game

# Source files
SRC_SET = main_set.cpp card.cpp card_list.cpp
SRC_BST = main.cpp card.cpp card_list.cpp

# Header files
HEADERS = card.h card_list.h

# Default target
all: $(EXEC_SET) $(EXEC_BST)

# Build game_set (using std::set / custom BST if needed)
$(EXEC_SET): $(SRC_SET) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_SET) $(SRC_SET)

# Build game (using custom BST)
$(EXEC_BST): $(SRC_BST) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_BST) $(SRC_BST)

# Clean object files and executables
clean:
	rm -f $(EXEC_SET) $(EXEC_BST) *.o

.PHONY: all clean

