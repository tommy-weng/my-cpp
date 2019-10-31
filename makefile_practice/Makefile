CCX = g++

target = xx

target: main.o hello.o
	$(CCX) -o $(target)  main.o hello.o

main.o: main.cpp main.hpp
	$(CCX) -c main.cpp

hello.o: hello.cpp
	$(CCX) -c hello.cpp

clean:
	rm *.o $(target) -f
