build:
	rm -f program.exe
	g++ -g -std=c++11 -Wall main.cpp -o program.exe

test01:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test01.cpp -o program.exe

test02:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test02.cpp -o program.exe
	
test10:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test10.cpp -o program.exe

test04:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test04.cpp -o program.exe

test05:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test05.cpp -o program.exe
	
test07:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test07.cpp -o program.exe	
	
test08:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test08.cpp -o program.exe
	
test011:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test011.cpp -o program.exe	
	
testall:
	rm -f program.exe
	g++ -g -std=c++11 -Wall maincatch.cpp test*.cpp -o program.exe
	
run:
	./program.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.exe
