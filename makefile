mad_dices: cell.o dice.o white_dice.o
	g++ mad_dices.cpp -o mad_dices cell.o dice.o white_dice.o

cell.o: cell.cpp cell.h
	g++ -c cell.cpp

dice.o: dice.cpp dice.h
	g++ -c dice.cpp

white_dice.o: white_dice.cpp white_dice.h
	g++ -c white_dice.cpp

run:
	./mad_dices

clean:
	rm –f *.o mad_dices *~