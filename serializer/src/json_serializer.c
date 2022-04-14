#include "json_serializer.h"

void initialize_json_data(json_data_t* json_data) {
    if (json_data == NULL)
        return;

    char* data_alloc = calloc(DEFAULT_LENGTH, sizeof(char));

    if (data_alloc) {
        json_data->data_string = data_alloc;
        json_data->data_capacity = DEFAULT_LENGTH;

        memcpy(&json_data->data_string[0], begin_json, strlen(begin_json) * sizeof(char));
        json_data->current_data_item = strlen(begin_json);
    }
}

void destruct_json_data(json_data_t* json_data) {
    if (json_data == NULL)
        return;

    free(json_data->data_string);
    json_data->current_data_item = 0;
    json_data->data_capacity = 0;
}

void add_json_float_object(json_data_t* json_data, const char* tag, double json_value, _Bool end_of_json) {
    if (json_data == NULL)
        return;

    char string_converter[DEFAULT_STR_LENGTH];

    sprintf(string_converter, "\"%s\": %f,", tag, json_value);

    move_data_json_buffer(json_data, string_converter, end_of_json);
}

void add_json_int_object(json_data_t* json_data, const char* tag, int json_value, _Bool end_of_json) {
    if (json_data == NULL)
        return;

    char string_converter[DEFAULT_STR_LENGTH];

    sprintf(string_converter, "\"%s\": %d,", tag, json_value);

    move_data_json_buffer(json_data, string_converter, end_of_json);
}

void add_json_str_object(json_data_t* json_data, const char* tag, const char* json_value, _Bool end_of_json) {
    if (json_data == NULL)
        return;

    char string_converter[DEFAULT_STR_LENGTH];

    sprintf(string_converter, "\"%s\": \"%s\",", tag, json_value);

    move_data_json_buffer(json_data, string_converter, end_of_json);
}

void move_data_json_buffer(json_data_t* json_data, const char* data_to_add, _Bool end_of_json) {
    if (json_data == NULL)
        return;

    if ((json_data->current_data_item + strlen(data_to_add)) < json_data->data_capacity) {
        memcpy(&json_data->data_string[json_data->current_data_item], data_to_add, strlen(data_to_add) * sizeof(char));

        json_data->current_data_item += strlen(data_to_add);
    }
    else {
        char* new_data_alloc = realloc(json_data->data_string, GROWTH_FACTOR * json_data->data_capacity);

        if (new_data_alloc) {
            json_data->data_string = new_data_alloc;
            json_data->data_capacity *= GROWTH_FACTOR;

            memcpy(&json_data->data_string[json_data->current_data_item], data_to_add, strlen(data_to_add) * sizeof(char));

            json_data->current_data_item += strlen(data_to_add);
        }
    }

    if (end_of_json)
        memcpy(&json_data->data_string[json_data->current_data_item - 1], end_json, strlen(end_json) * sizeof(char));
}
