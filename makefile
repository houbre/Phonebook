phonebook: main.o phone.o
        gcc -o phonebook main.o phone.o

main.o: main.c PHONE_RECORD.h
        gcc -c main.c

phone.o: phone.c PHONE_RECORD.h
        gcc -c phone.c
