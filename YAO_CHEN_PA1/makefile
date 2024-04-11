main: main.o
	g++ main.o -o main
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o
	rm main
run: main
	./main
