# ------------------------------------------------------------
# Makefile: Makefile for Lab 1
#   author: Luke Slevinsky, 1453199
#						Logan McDonald, 1401297
#
# Usage: make  // compiles the program
#				 make sanitize // compiles the program with thread sanitization flags
#        make tar   	 // create a 'tar.gz' archive of 'allFiles'
#				 make matrixgen // compile matrixgen
#				 make serialtester // compile serialtester
#        make clean 	 // remove unneeded files
# ------------------------------------------------------------

target :=		a1
allFiles := Makefile main.c lab1_IO.c lab1_IO.h matrixgen.c serialtester.c timer.h
objects :=
headers := lab1_IO.h timer.h
CFLAGS :=  -Wall -lm
threadSan := -fsanitize=thread -g
LDFLAGS= -pthread -lpthread
DEBUGFLAG := -g
CC := gcc
# ------------------------------------------------------------


default:  $(objects) $(headers)  main.o lab1_IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main lab1_IO.o main.o

sanitize: $(objects) $(headers)  main.o lab1_IO.o
	$(CC) $(LDFLAGS) $(CFLAGS) $(threadSan) -o matrixmultiplier lab1_IO.o main.o

matrixgen: matrixgen.o
	$(CC) $(CFLAGS) $(DEBUGFLAG) -o matrixgen matrixgen.o

serialtester: serialtester.o lab1_IO.o
	$(CC) $(CFLAGS) $(DEBUGFLAG) -o serialtester lab1_IO.o serialtester.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

serialtester.o: serialtester.c
	$(CC) $(CFLAGS) -c serialtester.c

matrixgen.o: matrixgen.c
	$(CC) $(CFLAGS) -c matrixgen.c

lab1_IO.o: lab1_IO.c
	$(CC) $(CFLAGS) lab1_IO.c -c

tar:
	touch $(target).tar.gz
	mv $(target).tar.gz  x$(target).tar.gz
	tar -cvf $(target).tar $(allFiles)
	gzip $(target).tar

clean:
	rm *.o main matrixgen serialtester
