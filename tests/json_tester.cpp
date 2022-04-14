#include <gtest/gtest.h> // Include the 'gtest' facilities.
#include <gmock/gmock.h> // Include the 'gmock' facilities.

// This test is written in C++. Indicate to the compiler that we are also using C components (from the JSON serializer).
extern "C" {
    #include <json_serializer.h> // Include our 'json_serializer' header.
}

using ::testing::StrEq;

// Vector for providing basic values for the JSON tester. It contains a tag, together with a floating point value.
static std::vector<std::pair<std::string, float>> get_float_json_tags() {
    return {
        {"Temperature", 23.445},
        {"Pressure", 1002.33},
        {"Light", 344.5},
        {"RSSI", 344},
        {"Volt", 3.44}
    };
}

// Vector for providing basic values for the JSON tester. It contains a tag, together with an integer value.
static std::vector<std::pair<std::string, int>> get_int_json_tags() {
    return {
        {"FanMode", 3},
        {"ControlStats", 344},
        {"BrokerEnable", 1},
        {"TimeEnable", 1},
        {"StackMode", 232}
    };
}

// Vector for providing basic values for the JSON serializer. It contains a tag, together with a textual value.
static std::vector<std::pair<std::string, std::string>> get_str_json_tags() {
    return {
        {"Salary", "none"},
        {"Shutdown", "on"},
        {"macOS", "12.3"},
        {"iOS", "15.4"},
        {"watchOS", "8.4"}
    };
}

// First test, we are testing dynamic allocation.
TEST (json_serializer_test, dynamic_allocation) {
    json_data_t json_data; // The type for the JSON data.
    initialize_json_data(&json_data); // Allocate memory for the JSON buffer.

    ASSERT_NE(json_data.data_string, nullptr) << "Allocating dynamic memory for the buffer failed!"; // Check if the values are not equal. If you have not a null pointer, memory is allocated for the buffer.

    destruct_json_data(&json_data); // Deallocate the memory.
}

// Second test, we are testing floating point JSON serialization.
TEST (json_serializer_test, float_object) {
    json_data_t json_data; // The type for the JSON data.
    initialize_json_data(&json_data); // Allocate memory for the JSON buffer.

    // Add some objects to the JSON data structure (in this case 'json_data'):
    add_json_float_object(&json_data, get_float_json_tags()[0].first.c_str(), get_float_json_tags()[0].second, false);
    add_json_float_object(&json_data, get_float_json_tags()[1].first.c_str(), get_float_json_tags()[1].second, false);
    add_json_float_object(&json_data, get_float_json_tags()[2].first.c_str(), get_float_json_tags()[2].second, false);
    add_json_float_object(&json_data, get_float_json_tags()[3].first.c_str(), get_float_json_tags()[3].second, true);

    ASSERT_THAT(std::string(json_data.data_string), StrEq("{\"Temperature\": 23.445000,\"Pressure\": 1002.330017,\"Light\": 344.500000,\"RSSI\": 344.000000}")) << "The serialized JSON object is not right!"; // Assert the two string for equality.

    destruct_json_data(&json_data); // Deallocate the memory.
}

// Third test, we are testing integer JSON serialization.
TEST (json_serializer_test, int_object) {
    json_data_t json_data; // The type for the JSON data.
    initialize_json_data(&json_data); // Allocate memory for the JSON buffer.

    // Add some objects to the JSON data structure (in this case 'json_data'):
    add_json_int_object(&json_data, get_int_json_tags()[0].first.c_str(), get_int_json_tags()[0].second, false);
    add_json_int_object(&json_data, get_int_json_tags()[1].first.c_str(), get_int_json_tags()[1].second, false);
    add_json_int_object(&json_data, get_int_json_tags()[2].first.c_str(), get_int_json_tags()[2].second, false);
    add_json_int_object(&json_data, get_int_json_tags()[3].first.c_str(), get_int_json_tags()[3].second, true);

    ASSERT_THAT(std::string(json_data.data_string), StrEq("{\"FanMode\": 3,\"ControlStats\": 344,\"BrokerEnable\": 1,\"TimeEnable\": 1}")) << "The serialized JSON object is not right!"; // Assert the two string for equality.

    destruct_json_data(&json_data); // Deallocate the memory.
}

// Fourth test, we are testing string JSON serialization.
TEST (json_serializer_test, string_object) {
    json_data_t json_data; // The type for the JSON data.
    initialize_json_data(&json_data); // Allocate memory for the JSON buffer.

    // Add some objects to the JSON data structure (in this case 'json_data'):
    add_json_str_object(&json_data, get_str_json_tags()[0].first.c_str(), get_str_json_tags()[0].second.c_str(), false);
    add_json_str_object(&json_data, get_str_json_tags()[1].first.c_str(), get_str_json_tags()[1].second.c_str(), false);
    add_json_str_object(&json_data, get_str_json_tags()[2].first.c_str(), get_str_json_tags()[2].second.c_str(), false);
    add_json_str_object(&json_data, get_str_json_tags()[3].first.c_str(), get_str_json_tags()[3].second.c_str(), true);

    ASSERT_THAT(std::string(json_data.data_string), StrEq("{\"Salary\": \"none\",\"Shutdown\": \"on\",\"macOS\": \"12.3\",\"iOS\": \"15.4\"}")) << "The serialized JSON object is not right!"; // Assert the two string for equality.

    destruct_json_data(&json_data); // Deallocate the memory.
}

// The fifth test, serializing multiple object for JSON.
TEST (json_serializer_test, mixed_object) {
    json_data_t json_data; // The type for the JSON data.
    initialize_json_data(&json_data); // Allocate memory for the JSON buffer.

    // Add some objects to the JSON data structure (in this case 'json_data'):
    add_json_int_object(&json_data, get_int_json_tags()[2].first.c_str(), get_int_json_tags()[2].second, false);
    add_json_float_object(&json_data, get_float_json_tags()[4].first.c_str(), get_float_json_tags()[4].second, false);
    add_json_float_object(&json_data, get_float_json_tags()[0].first.c_str(), get_float_json_tags()[0].second, false);
    add_json_str_object(&json_data, get_str_json_tags()[4].first.c_str(), get_str_json_tags()[4].second.c_str(), false);
    add_json_str_object(&json_data, get_str_json_tags()[3].first.c_str(), get_str_json_tags()[3].second.c_str(), false);
    add_json_int_object(&json_data, get_int_json_tags()[2].first.c_str(), get_int_json_tags()[2].second, true);

    ASSERT_THAT(std::string(json_data.data_string), StrEq("{\"BrokerEnable\": 1,\"Volt\": 3.440000,\"Temperature\": 23.445000,\"watchOS\": \"8.4\",\"iOS\": \"15.4\",\"BrokerEnable\": 1}")) << "The serialized JSON object is not right!"; // Assert the two string for equality.

    destruct_json_data(&json_data); // Deallocate the memory.
}
