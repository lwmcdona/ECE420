# ------------------------------------------------------------
# Makefile: Makefile for Lab 3
#   author: Luke Slevinsky, 1453199
#						Logan McDonald, 1401297
#
# Usage: make  // compiles the program
#				 make main1 // compiles the serial program
#				 make main2 // compiles the 1st parallel iteration
#				 make main3 // compiles the 2st parallel iteration
#				 make main4 // compiles the 3rd parallel iteration
#				 make main5 // compiles the 4th parallel iteration
#				 make serialtester // compiles the serialtester
#				 make datagen // compiles the datagen
#        make tar   	 // create a 'tar.gz' archive of 'allFiles'
#        make clean 	 // remove unneeded files
# ------------------------------------------------------------

target := lab3
allFiles := Makefile timer.h datagen.c Lab3IO.c Lab3IO.h serialtester.c main.c main1.c main2.c main3.c main4.c main5.c
objects :=
headers := timer.h Lab3IO.h
CFLAGS :=  -Wall -lm
threadSan := -fsanitize=thread -g
LDFLAGS= -fopenmp
DEBUGFLAG := -ggdb
CC := gcc
# ------------------------------------------------------------

default: $(headers) main.o Lab3IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main main.o Lab3IO.o

main1: $(headers) main1.o Lab3IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main1 main1.o Lab3IO.o

main2: $(headers) main2.o Lab3IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main2 main2.o Lab3IO.o

main3: $(headers) main3.o Lab3IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main3 main3.o Lab3IO.o

main4: $(headers) main4.o Lab3IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main4 main4.o Lab3IO.o

main5: $(headers) main5.o Lab3IO.o
	$(CC) $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS) -o main5 main5.o Lab3IO.o

serialtester: serialtester.o Lab3IO.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o serialtester serialtester.o Lab3IO.o -lm

datagen: datagen.o Lab3IO.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o datagen datagen.o Lab3IO.o

main.o: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) main.c -c

main1.o: main1.c
	$(CC) $(LDFLAGS) $(CFLAGS) main1.c -c

main2.o: main2.c
	$(CC) $(LDFLAGS) $(CFLAGS) main2.c -c

main3.o: main3.c
	$(CC) $(LDFLAGS) $(CFLAGS) main3.c -c

main4.o: main4.c
	$(CC) $(LDFLAGS) $(CFLAGS) main4.c -c

main5.o: main5.c
	$(CC) $(LDFLAGS) $(CFLAGS) main5.c -c

datagen.o: datagen.c
	$(CC) $(CFLAGS) datagen.c -c

serialtester.o: serialtester.c
	$(CC) $(CFLAGS) serialtester.c -c

Lab3IO.o: Lab3IO.c
	$(CC) $(CFLAGS) Lab3IO.c -c

tar:
	touch $(target).tar.gz
	mv $(target).tar.gz  x$(target).tar.gz
	tar -cvf $(target).tar $(allFiles)
	gzip $(target).tar

clean:
	rm *.o main main1 main2 main3 main4 serialtester datagen
