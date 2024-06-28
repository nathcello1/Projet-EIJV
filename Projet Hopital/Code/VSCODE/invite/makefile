invite: main.o affichage.o operation.o SQL.o
	gcc -o invite  main.o affichage.o operation.o SQL.o $(shell mysql_config --libs) $(shell mysql_config --cflags) 

main.o: main.c affichage.h
	gcc -c main.c

affichage.o: affichage.c operation.h
	gcc -c affichage.c

operation.o: operation.c SQL.h
	gcc -c operation.c

SQL.o: SQL.c
	gcc -c SQL.c