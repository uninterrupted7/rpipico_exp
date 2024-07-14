#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int main() {
    int serial_port = open("/dev/ttyACM0", 9600);
    
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return 1;
    }

    struct termios tty;

    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    // Set Baud Rate
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Setting other Port Stuff
    tty.c_cflag &= ~PARENB; // Make 8n1
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~CRTSCTS;       // No flow control
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    // Allocate memory for read buffer
    char read_buf [256];
    int read_int;
    while (1) {
        memset(&read_buf, '\0', sizeof(read_buf));

        // Read bytes. The read() function will return the number of bytes read, or -1 on error
        int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
        // Convert the received data to an integer
        int received_value = atoi(read_buf);

        if (num_bytes < 0) {
            printf("Error reading: %s", strerror(errno));
            return 1;
        }

        // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
        // print it to the screen like this!)
        if (num_bytes > 0) {
            printf("Read %i bytes. Received message: %s\n", num_bytes, read_buf);
        }

        printf("%i\n",received_value);
    }

    close(serial_port);
    return 0; // success
}