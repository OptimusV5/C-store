db : main.o fileException.o fileOpenException.o load.o query.o
	cc -o edit main.o fileException.o fileOpenException.o load.o query.o

main.o : main.cpp load.h query.h fileException.h fileOpenException.h
	cc -c main.cpp
load.o : load.cpp load.h fileOpenException.h
	cc -c load.cpp
query.o : query.cpp query.h
	cc -c query.cpp
fileOpenException.o : fileOpenException.cpp fileOpenException.h fileException.h
	cc -c fileOpenException.cpp
fileException.o : fileException.h fileException.cpp
	cc -c fileException.cpp
