/* Copyright (C) 2022 Alessandro Zolli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: personal@alessandrozolli.com
 */

#include <iostream>

namespace AT
{
    class ATtools
    {

    private:
        std::string pin;

    public:

        ATtools(std::string PIN)
        {
            pin = PIN;
        }
        void sendMessage()
        {
            std::cout << "Sending message"
                      << "\n";
        };
        void httpRequest()
        {
            std::cout << "Making HTTP request"
                      << "\n";
        };
    };
};