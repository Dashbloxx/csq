#pragma once

#include <stdbool.h>

/**
 *  @brief  This struct defines an object. All objects are to contain a label (name), and a pointer, which
 *          points to the value of the object. If it's a function, the pointer points to the start of the code
 *          of the function. Note that the `function` value clarifies whether the object is a function or not.
 */
typedef struct {
    char label[128];
    bool function;
    bool _pointer;
    void *pointer;
    int storage_class;
    int type_modifiers;
    int type_specifier;
} obj_t;