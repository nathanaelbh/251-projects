build:
	rm -f program.exe
	g++ -g -std=c++11 -Wall main.cpp -o program.exe

test:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test01.cpp -o program.exe

test2:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test02.cpp -o program.exe

test3:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test03.cpp -o program.exe
	
testall:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test*.cpp -o program.exe
	
run:
	./program.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./program.exe
