/* Copyright (C) 2022 Alessandro Zolli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: personal@alessandrozolli.com
 */

#include <iostream>
#include "serial.cpp"

namespace AT
{
    class ATtools
    {

    private:
        int sp;

    public:
        ATtools(std::string PIN, char *devPath)
        {
            sp = configureSerialPort(devPath);
            int bWritten = write_Serial(sp, "AT+CPIN="+PIN);
            if(bWritten > 0){
                read_Serial(sp);
            }
        }
        void call()
        {
            int bWritten = write_Serial(sp, "ATD");
            if(bWritten > 0){
                read_Serial(sp);
            }
        }
        void sendMessage()
        {
            int bWritten = write_Serial(sp, "ATA");
            if(bWritten > 0){
                read_Serial(sp);
            }
        }
        void httpRequest()
        {
            std::cout << "Making HTTP request"
                      << "\n";
        }
        void closeSerial(){
            close(sp);
        }
    };
};