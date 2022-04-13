# JSON serializer

This is a lightweight JSON serializer written in C. The implementation is quite lightweight, and can find application within microcontrollers, for example. In my case I have used this implementation on the ATmega328P microcontroller among others. The aim was to transmit different values of I2C sensors, whereby the values should be easily and universally deserialized.

Since a dynamic buffer is used, the first thing you need to do is call the function `initialize_json_data`. Then you can add tags with, for example, the function `add_json_float_object`. Note the use of the `end_of_json` parameter. If you want to name the end of a JSON object, this value must be `true`, otherwise `false`. If the JSON serializer is no longer used, you have to clear the buffer independently by calling `destruct_json_data`.

An application can be generated as follows:

```c
json_data_t data;

initialize_json_data(&data);

add_json_float_object(&data, "Temperature", 34, false);
add_json_int_object(&data, "Firmware", 1, false);
add_json_str_object(&data, "SensorType", "BMP280", false);

printf("Data: %s\n", data.data_string);

destruct_json_data(&data);
```
