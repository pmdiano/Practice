/**
 * 
 * Compter Networks 5th Edition, Tanenbaum
 * 
 * Chapter 1, Introduction, problem 37
 * 
 * Write a program that implements message flow from the top layer to the
 * bottom layer of the 7-layer protocol model. Your program should include
 * a separate protocol func- tion for each layer. Protocol headers are
 * sequence up to 64 characters. Each protocol function has two parameters:
 * a message passed from the higher layer protocol (a char buffer) and the
 * size of the message. This function attaches its header in front of the
 * message, prints the new message on the standard output, and then invokes
 * the protocol function of the lower-layer protocol. Program input is an
 * application message (a se- quence of 80 characters or less).
 * 
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

void application_layer_send(char *buffer, int len);
void presentation_layer_send(char *buffer, int len);
void session_layer_send(char *buffer, int len);
void transport_layer_send(char *buffer, int len);
void network_layer_send(char *buffer, int len);
void datalink_layer_send(char *buffer, int len);
void physical_layer_send(char *buffer, int len);

char* attach_header(char *buffer, char *header, int *len2) {
    int len = strlen(buffer);
    int hlen = strlen(header);
    *len2 = len + hlen;

    char *buffer2 = (char*)malloc(*len2 + 1);
    memcpy(buffer2, header, hlen);
    memcpy(buffer2 + hlen, buffer, len);
    buffer2[*len2] = '\0';

    return buffer2;
}

void application_layer_send(char *buffer, int len) {
    static char header[] = "application_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    presentation_layer_send(buffer2, len2);
    free(buffer2);
}

void presentation_layer_send(char *buffer, int len) {
    char header[] = "presentation_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    session_layer_send(buffer2, len2);
    free(buffer2);
}

void session_layer_send(char *buffer, int len) {
    char header[] = "session_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    transport_layer_send(buffer2, len2);
    free(buffer2);
}

void transport_layer_send(char *buffer, int len) {
    char header[] = "transport_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    network_layer_send(buffer2, len2);
    free(buffer2);
}

void network_layer_send(char *buffer, int len) {
    char header[] = "network_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    datalink_layer_send(buffer2, len2);
    free(buffer2);
}

void datalink_layer_send(char *buffer, int len) {
    char header[] = "datalink_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    physical_layer_send(buffer2, len2);
    free(buffer2);
}

void physical_layer_send(char *buffer, int len) {
    char header[] = "physical_layer_header;";
    assert(strlen(buffer) == len);

    int len2 = 0;
    char *buffer2 = attach_header(buffer, header, &len2);
    printf("%s\n", buffer2);

    free(buffer2);
}

void application_routine() {
    char message[] = "Hello World!";
    application_layer_send(message, strlen(message));
}

int main(int argc, char *argv[]) {
    application_routine();
    return 0;
}
