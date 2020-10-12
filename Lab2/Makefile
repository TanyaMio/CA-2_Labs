all : main.o calculator.a
	g++ main.o calculator.a -o main

main.o : main.cpp
	g++ -c main.cpp

calculator.o : calculator.cpp
	g++ -c calculator.cpp

calculator.a : calculator.o
	ar rvs calculator.a calculator.o

clean:
	rm *.o main