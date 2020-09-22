#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include <curl/curl.h>
#include <cJSON.h>
#include "data_interface.h"

char buffer[1024];

int main()
{
    get_json_data(buffer, "http://date.jsontest.com/");

    return 0;
}