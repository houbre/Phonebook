struct PHONE_RECORD {
        char name[50];
        char birthdate[12];
        char phone[15];
     };;

//extern the struct for mini5phone.c and mini5main.c
extern struct PHONE_RECORD phonebook[10];
