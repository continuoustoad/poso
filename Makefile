
SRC_DIR = src

dev: $(SRC_DIR)/main.cpp $(SRC_DIR)/*.hpp
	g++ -I"$(SRC_DIR)" "$(SRC_DIR)/main.cpp" -o main -std=c++17
