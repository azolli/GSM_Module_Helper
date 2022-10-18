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
#include "json.hpp"


namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}


void getConfig(json &configParams){
    ifstream jsonConfig("params.json");
    json conf = json::parse(jsonConfig);
    cout << "Listening on: " << conf["serial"] << endl;
    configParams = conf;

    return;
}

int main()
{
    json configParams;
    getConfig(configParams);

    AT::ATtools t(to_string(configParams["pin"]));

    // CURL *curl;
    // CURLcode res;
    // std::string readBuffer;

    // curl = curl_easy_init();

    // if (curl)
    // {
    //     curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
    //     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    //     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    //     res = curl_easy_perform(curl);
    //     curl_easy_cleanup(curl);

    //     std::cout << readBuffer << std::endl;
    // }

    return 1;
}