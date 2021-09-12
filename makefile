myText: myText.o
	gcc -g -Wall -ansi -pedantic myText.o -o myText
myText.o: myText.c info.h
	gcc -c myText.c -o myText.o
  