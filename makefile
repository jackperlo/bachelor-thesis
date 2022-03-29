mad_dices: ./build/cell.o ./build/dice.o ./build/white_dice.o
	cd src; \
	g++ mad_dices.cpp -o mad_dices ../build/cell.o ../build/dice.o ../build/white_dice.o

./build/cell.o: ./src/lib/cell.cpp ./src/lib/cell.h
	cd src/lib; \
	g++ -c cell.cpp -o ../../build/cell.o; 

./build/dice.o: ./src/lib/dice.cpp ./src/lib/dice.h
	cd src/lib; \
	g++ -c dice.cpp -o ../../build/dice.o;

./build/white_dice.o: ./src/lib/white_dice.cpp ./src/lib/white_dice.h
	cd src/lib; \
	g++ -c white_dice.cpp -o ../../build/white_dice.o;

make all: mad_dices

run:
	./src/mad_dices

clean:
	rm ./build/*.o ./src/mad_dices ./src/tests/tests

tests: ./build/cell.o ./build/dice.o ./build/white_dice.o
	cd src/tests; \
	g++ tests.cpp -o testsExecutable ../../build/cell.o ../../build/dice.o ../../build/white_dice.o;
run_tests:	
	./src/tests/tests