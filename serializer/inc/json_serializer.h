#ifndef JSON_JSON_SERIALIZER_H
#define JSON_JSON_SERIALIZER_H

#define DEFAULT_LENGTH (0x55)
#define DEFAULT_STR_LENGTH (0x40)
#define GROWTH_FACTOR (0x02)

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static const char* begin_json = "{";
static const char* end_json = "}";

typedef struct json_data {
    char* data_string;
    size_t current_data_item;
    size_t data_capacity;
} json_data_t;

extern void initialize_json_data(json_data_t* json_data);
extern void destruct_json_data(json_data_t* json_data);

extern void add_json_float_object(json_data_t* json_data, const char* tag, double json_value, _Bool end_of_json);
extern void add_json_int_object(json_data_t* json_data, const char* tag, int json_value, _Bool end_of_json);
extern void add_json_str_object(json_data_t* json_data, const char* tag, const char* json_value, _Bool end_of_json);

extern void move_data_json_buffer(json_data_t* json_data, const char* data_to_add, _Bool end_of_json); // Helper function to add json objects.

#endif
