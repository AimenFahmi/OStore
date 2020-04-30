//
// Created by Aimen Fahmi on 2020-04-17.
//

#include "Memory_Error_Handler.h"

void *malloc_safe_mode(int size) {
    void *allocated_memory = malloc(size);
    if (allocated_memory == NULL) {
        printf("[-] Memory allocation failed\n");
        exit(-1);
    }
    return allocated_memory;
}
