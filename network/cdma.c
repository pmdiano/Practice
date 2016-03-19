#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Flow of the program:
 * 1. main process reads 4 chip sequence (8 bits each) from stdin
 * 2. main process reads 4 bits input signal from stdin
 * 3. main process forks off 4 pairs of transmitter-receiver processes
 * 4. main process opens 4 pipes, each pipe for one pair
 * 5. main process write chip sequences to each pipe
 * 6. each transmitter and receiver reads its chip sequence
 * 7. main process writes the 1-bit signal to each pipe
 * 8. each transmitter receives its signal
 * 9. each transmitter computes its signal to be transmitted, write to pipe
 * 10. main process receives signal from each transmitter, add them
 * 11. main process write the total signal to each pipe
 * 12. each receiver reads the signal from its pipe, decode it, and print it
 */

#define CHANNEL_NUMBER 4

int transmitter_pids[CHANNEL_NUMBER];
int receiver_pids[CHANNEL_NUMBER];
int pipes[CHANNEL_NUMBER][2];

int main(int argc, char *argv[])
{
    // TODO
    return 0;
}
