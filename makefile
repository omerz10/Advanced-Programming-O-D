# name David Nakash, Omer Zucker
# id 203752902, 200876548

a.out: compileAll
	g++ *.o 
	rm -f *.o

compileAll: src/*.h src/*.cpp
	g++ -IHeaders/ -c src/*.cpp
run:
	./a.out
