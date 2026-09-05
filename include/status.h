#ifndef STATUS
#define STATUS
#include <stdio.h>

typedef enum Status {
    NO_ERROR,
    ALLOCATION_ERROR,
    FILE_NOT_FOUND,
    NULL_POINTER,
    ITEM_NOT_FOUND,
    READ_ERROR,
    ITEM_FOUND,
    ITEM_ALREADY_EXIST
} Status;


static inline void status_print(Status status) {
    switch (status) {
        case NO_ERROR:
            printf("NO_ERROR\n");
            break;
        case ALLOCATION_ERROR:
            printf("ALLOCATION_ERROR\n");
            break;
        case FILE_NOT_FOUND:
            printf("FILE_NOT_FOUND\n");
            break;
        case NULL_POINTER:
            printf("NULL_POINTER\n");
            break;
        case ITEM_NOT_FOUND:
            printf("ITEM_NOT_FOUND\n");
            break;
        case READ_ERROR:
            printf("READ_ERROR\n");
            break;
        case ITEM_FOUND:
            printf("ITEM_FOUND\n");
            break;
        case ITEM_ALREADY_EXIST:
            printf("ITEM_ALREADY_EXIST\n");
            break;
        default:
            printf("UNKNOWN_STATUS\n");
            break;
    }

}

#endif
