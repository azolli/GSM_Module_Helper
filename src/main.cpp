/* Copyright (C) 2022 Alessandro Zolli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: personal@alessandrozolli.com
 */

#include "AT.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <curl/curl.h>
#include "../libs/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;

void getConfig(json &configParams)
{
    ifstream jsonConfig("./config/params.json");
    json conf = json::parse(jsonConfig);
    configParams = conf;

    return;
}

int main()
{
    json configParams;
    getConfig(configParams);

    AT::ATtools atools("1234", "/dev/cu.usbmodem114301");
    atools.sendMessage();
    atools.closeSerial();

    return 1;
}