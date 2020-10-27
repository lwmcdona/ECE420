# ------------------------------------------------------------
# Makefile: Makefile for Lab 4
#   author: Luke Slevinsky, 1453199
#						Logan McDonald, 1401297
#
# Usage: make  // compiles the main parallel program
#				 make main1        // compiles the serial version
#				 make main2        // compiles the 1st parallel iteration
#				 make main3        // compiles the 2st parallel iteration
#				 make serialtester // compiles the serialtester
#				 make datatrim     // compiles the datatrimmer
#        make tar   	     // create a 'tar.gz' archive of 'allFiles'
#        make clean 	     // remove unneeded files
# ------------------------------------------------------------

target := lab4
allFiles := Makefile timer.h main.c main1.c main2.c main3.c datatrim.c serialtester.c web-Stanford.txt Lab4_IO.c Lab4_IO.h
objects :=
headers := timer.h Lab4_IO.h
CFLAGS :=  -Wall -lm
threadSan := -fsanitize=thread -g
LDFLAGS=
DEBUGFLAG := -ggdb
CC := mpicc
# ------------------------------------------------------------

default: $(headers) main.o Lab4_IO.o
	$(CC) -o main main.o Lab4_IO.o $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS)

main1: $(headers) main1.o Lab4_IO.o
	$(CC)  -o main1 main1.o Lab4_IO.o $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS)

main2: $(headers) main2.o Lab4_IO.o
	$(CC) -o main2 main2.o Lab4_IO.o $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS)

main3: $(headers) main3.o Lab4_IO.o
	$(CC) -o main3 main3.o Lab4_IO.o $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS)

serialtester: serialtester.o Lab4_IO.o
	$(CC) -o serialtester serialtester.o Lab4_IO.o $(LDFLAGS) $(CFLAGS)

datatrim: datatrim.o
	$(CC) -o datatrim datatrim.o $(LDFLAGS) $(CFLAGS)

main.o: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) main.c -c

main1.o: main1.c
	$(CC) $(LDFLAGS) $(CFLAGS) main1.c -c

main2.o: main2.c
	$(CC) $(LDFLAGS) $(CFLAGS) main2.c -c

main3.o: main3.c
	$(CC) $(LDFLAGS) $(CFLAGS) main3.c -c

datatrim.o: datatrim.c
	$(CC) $(CFLAGS) datatrim.c -c

serialtester.o: serialtester.c
	$(CC) $(CFLAGS) serialtester.c -c

Lab4_IO.o: Lab4_IO.c
	$(CC) $(CFLAGS) Lab4_IO.c -c

tar:
	touch $(target).tar.gz
	mv $(target).tar.gz  x$(target).tar.gz
	tar -cvf $(target).tar $(allFiles)
	gzip $(target).tar

clean:
	rm *.o main main1 main2 main3 serialtester datatrim
