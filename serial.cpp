/* Copyright (C) 2022 Alessandro Zolli - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: personal@alessandrozolli.com
 */

#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

int open_serial(char* devFile) {

    cout << "Opening serial port...";

    //RDWR
    int serial_port = open(devFile, O_RDWR);

    cout << "Opened!";

    if(serial_port < 0) {
        cout << "Error " << errno << " from open: " << strerror(errno) << endl;
        return 0;
    }

    return serial_port;
}

int write_Serial(int sp, string serialCommand){
    char *msg = new char[serialCommand.length() + 1];
    strcpy(msg, serialCommand.c_str());
    
    cout.flush();
    int b = write(sp, msg, sizeof(msg));
    
    return b;
}

int read_Serial(int sp){
    char read_buf[256];
    int num_bytes = read(sp, &read_buf, sizeof(read_buf));
    cout << read_buf;
    cout.flush();

    return num_bytes;
}

int main(int argc, char **argv){

    struct termios tty;
    int sp = open_serial(argv[1]);

    if(tcgetattr(sp, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB; // Disabling default parity (to enable |= PARENB)
    tty.c_cflag &= ~CSTOPB; // Disabling default two stop bits (to enable |= CSTOPB)
    tty.c_cflag &= ~CSIZE; // Disabling default byte size
    tty.c_cflag |= CS8; // Setting byte = 8 bits (others: 5,6,7)
    //tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON; // Disabling UNIX input canonical mode (processes input by line and not by char)
    tty.c_lflag &= ~ECHO; // Disable echo (loopback of what we write)
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 10;  // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Input and output baud rates
    cfsetispeed(&tty, B9600); //Only number to use custom on GNU/Linux
    cfsetospeed(&tty, B9600);

    if (tcsetattr(sp, TCSANOW, &tty) != 0) {
        cout << "Error " << errno << " from tcsetattr: " << strerror(errno) << endl;
    }
    
    close(sp);
}