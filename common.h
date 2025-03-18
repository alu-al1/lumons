#ifndef COMMON_H
#define COMMON_H

typedef struct {
    int is_owner; // if set - it should be safe to free resp if presented 
    int cnt;
    void** resp;
    // int rescnt;
    int ok;
} BRLEV_Result;

#endif // GLUE_H
