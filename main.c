#include <stdio.h>

#include "json_serializer.h"

int main() {
    json_data_t data;

    initialize_json_data(&data);

    add_json_float_object(&data, "Temperature", 34, false);
    add_json_float_object(&data, "Light", 1223, false);
    add_json_float_object(&data, "Wind", 21, false);
    add_json_int_object(&data, "Firmware", 1, false);
    add_json_str_object(&data, "SensorType", "BMP280", false);
    add_json_float_object(&data, "Altitude", 344, true);

    printf("Data: %s\n", data.data_string);

    destruct_json_data(&data);

    return EXIT_SUCCESS;
}
