#ifndef STATUS_H
#define STATUS_H

typedef enum Status {
    NO_ERROR,
    ALLOCATION_ERROR,
    FILE_NOT_FOUND,
    NULL_POINTER,
    ITEM_NOT_FOUND,
    READ_ERROR,
    ITEM_FOUND,
    ITEM_ALREADY_EXIST,
    ARRAY_FULL,
    STRING_EMPTY,
} Status;


void status_print(Status status);

#endif
