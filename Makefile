database:  bintree.o database.o  form.o cout_operator.o
	g++  bintree.o database.o form.o cout_operator.o
bintree.o: bintree.cpp bintree.h
	g++ -c bintree.cpp 
database.o: database.cpp database.h
	g++ -c database.cpp
form.o: form.cpp form.h
	g++ -c form.cpp
cout_operator.o : cout_operator.cpp cout_operator.h
	g++ -c cout_operator.cpp
clean:
	rm *.o database
