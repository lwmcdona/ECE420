# ------------------------------------------------------------
# Makefile: Makefile for Lab 5
#   author: Luke Slevinsky, 1453199
#						Logan McDonald, 1401297
#
# Usage: make  // compiles the main parallel program
#				 make datatrim     // compiles the datatrimmer
#        make tar   	     // create a 'tar.gz' archive of 'allFiles'
#        make clean 	     // remove unneeded files
# ------------------------------------------------------------

target := lab5
allFiles := Makefile datatrim.c web-Stanford.txt
objects :=
headers :=
CFLAGS :=  -Wall -lm
threadSan := -fsanitize=thread -g
LDFLAGS=
DEBUGFLAG := -ggdb
CC := mpicc
# ------------------------------------------------------------

default: $(headers)
	$(CC) -o main $(LDFLAGS) $(DEBUGFLAG) $(CFLAGS)

datatrim: datatrim.o
	$(CC) -o datatrim datatrim.o $(LDFLAGS) $(CFLAGS)

main.o: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) main.c -c

datatrim.o: datatrim.c
	$(CC) $(CFLAGS) datatrim.c -c

tar:
	touch $(target).tar.gz
	mv $(target).tar.gz  x$(target).tar.gz
	tar -cvf $(target).tar $(allFiles)
	gzip $(target).tar

clean:
	rm *.o main main1 main2 main3 serialtester datatrim
