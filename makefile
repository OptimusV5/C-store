VPATH = src

db : main.o fileException.o fileOpenException.o load.o query.o
	g++ -o db main.o fileException.o fileOpenException.o load.o query.o

main.o : main.cpp load.h query.h fileException.h fileOpenException.h
	g++ -c src/main.cpp 
load.o : load.cpp load.h fileOpenException.h
	g++ -c src/load.cpp 
query.o : query.cpp query.h
	g++ -c src/query.cpp 
fileOpenException.o : fileOpenException.cpp fileOpenException.h fileException.h
	g++ -c src/fileOpenException.cpp 
fileException.o : fileException.h fileException.cpp
	g++ -c src/fileException.cpp 

clean :
	rm db main.o fileException.o fileOpenException.o load.o query.o
