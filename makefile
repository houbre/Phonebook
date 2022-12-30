phonebook: main.o phone.o
        gcc -o phonebook main.o phone.o

main.o: main.c phone_record.h
        gcc -c main.c

phone.o: phone.c phone_record.h
        gcc -c phone.c
