#pragma once

#include <stdbool.h>

typedef enum
{
    TS_LONG,
    TS_INT,
    TS_SHORT,
    TS_CHAR,
    TS_BOOL
} type_specifier_t;

typedef enum
{
    TM_CONST,
    TM_VOLATILE,
    TM_RESTRICT
} type_modifier_t;

typedef enum
{
    SC_AUTO,
    SC_REGISTER,
    SC_STATIC,
    SC_EXTERN,
    SC_TYPEDEF
} storage_class_t;

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
    storage_class_t storage_class;
    type_modifier_t type_modifiers;
    type_specifier_t type_specifier;
} obj_t;