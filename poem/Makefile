CXX = g++

all:	clean build
build:	 poem.o libshared.so 
	echo "-build-"
	$(CXX) -Wall -o build poem.o 
run:
	./build
poem.o:	poem.cpp 
	echo "-poem.o-"
	$(CXX) -Wall -c -ldl poem.cpp
shared.o: shared.cpp
	echo "-shared.o-"
	$(CXX) -Wall -c -fPIC shared.cpp
libshared.so:	shared.o
	echo "-lib-"
	$(CXX) -Wall -shared -fPIC -o libshared.so shared.o

clean:
	echo "-clean-"
	rm *.o *.so build

