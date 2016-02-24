all: linkedlist

FileIO.o:	FileIO.c
			gcc -c FileIO.c

HelperFunctions.o: HelperFunctions.c
			gcc -c HelperFunctions.c

GenericLists.o:	HelperFunctions.o GenericLists.c
			gcc -c GenericLists.c

UserDefined.o:	HelperFunctions.o UserDefined.c
			gcc -c UserDefined.c

linkedlist:	FileIO.o GenericLists.o UserDefined.o HelperFunctions.o listTest.c
		gcc FileIO.o GenericLists.o UserDefined.o HelperFunctions.o listTest.c -o linkedlist

clean:
		rm linkedlist *.o
