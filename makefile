# Points to the root of Google Test, relative to where this file is.
GTEST_DIR= ./src/tests/googletest/googletest
# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include
# Flags passed to the C++ compiler.
CXXFLAGS += -std=c++11 -g -Wall -Wextra -pthread
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

#---------------MAIN-------------

./build/cell.o: ./src/lib/cell.cpp ./src/lib/cell.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) cell.cpp -o ../../build/cell.o; 

./build/dice.o: ./src/lib/dice.cpp ./src/lib/dice.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) dice.cpp -o ../../build/dice.o;

./build/white_dice.o: ./src/lib/white_dice.cpp ./src/lib/white_dice.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) white_dice.cpp -o ../../build/white_dice.o;

./build/red_dice.o: ./src/lib/red_dice.cpp ./src/lib/red_dice.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) red_dice.cpp -o ../../build/red_dice.o;

./build/yellow_dice.o: ./src/lib/yellow_dice.cpp ./src/lib/yellow_dice.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) yellow_dice.cpp -o ../../build/yellow_dice.o;

./build/green_dice.o: ./src/lib/green_dice.cpp ./src/lib/green_dice.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) green_dice.cpp -o ../../build/green_dice.o;

./build/p2d.o: ./src/lib/p2d.cpp ./src/lib/p2d.h
	cd src/lib; \
	$(CXX) -c $(CXXFLAGS) p2d.cpp -o ../../build/p2d.o;	

./build/alea_game.o: ./src/alea_game.cpp ./src/alea_game.h 
	cd src; \
	$(CXX) -c $(CXXFLAGS) alea_game.cpp -o ../build/alea_game.o;

./build/search_algorithms.o: ./src/search_algorithms.cpp ./src/search_algorithms.h 
	cd src; \
	$(CXX) -c $(CXXFLAGS) search_algorithms.cpp -o ../build/search_algorithms.o;

level_solver: ./build/p2d.o ./build/cell.o ./build/dice.o ./build/white_dice.o ./build/red_dice.o ./build/yellow_dice.o ./build/green_dice.o ./build/alea_game.o ./build/search_algorithms.o
	cd src; \
	$(CXX) $(CXXFLAGS) level_solver.cpp -o level_solver ../build/p2d.o ../build/cell.o ../build/dice.o ../build/white_dice.o ../build/red_dice.o ../build/yellow_dice.o ../build/green_dice.o ../build/alea_game.o ../build/search_algorithms.o


#---------------TESTS-------------

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) -isystem src/tests/googletest/googletest/include -Isrc/tests/googletest/googletest $(CXXFLAGS) -c src/tests/googletest/googletest/src/gtest-all.cc;

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) -isystem src/tests/googletest/googletest/include -Isrc/tests/googletest/googletest $(CXXFLAGS) -c src/tests/googletest/googletest/src/gtest_main.cc;
	
gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^; \
	mv gtest.a ./src/tests; 

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^;
	
./src/tests/tests.o : ./src/tests/tests.cpp ./build/p2d.o ./build/cell.o ./build/dice.o ./build/white_dice.o ./build/red_dice.o ./build/yellow_dice.o ./build/green_dice.o $(GTEST_HEADERS)
	cd ./src/tests/; \
	$(CXX) -isystem ./googletest/googletest/include $(CXXFLAGS) -c tests.cpp

tests: ./src/tests/tests.o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ ./build/p2d.o ./build/cell.o ./build/dice.o ./build/white_dice.o ./build/red_dice.o ./build/yellow_dice.o ./build/green_dice.o; \
	mv gtest-all.o ./src/tests; \
	mv gtest_main.o ./src/tests; \
	mv gtest_main.a ./src/tests; \
	mv tests ./src/tests;

#---------------COMMANDS-------------

make all: level_solver

run: level_solver ./src/level_solver
	./src/level_solver 

run_tests:	
	./src/tests/tests	

clean:
	rm -f ./build/*.o ./src/level_solver ./src/tests/tests ./src/tests/*.a ./src/tests/*.o
