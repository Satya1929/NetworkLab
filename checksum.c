#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find the One's complement
// of the given binary string
void Ones_complement(char *data)
{
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '0')
            data[i] = '1';
        else
            data[i] = '0';
    }
}

// Function to return the checksum value of
// the given string when divided in K size blocks
void checkSum(char *data, int block_size, char *result)
{
    // Check data size is divisible by block_size
    // Otherwise add '0' front of the data
    int n = strlen(data);
    if (n % block_size != 0) {
        int pad_size = block_size - (n % block_size);
        for (int i = 0; i < pad_size; i++) {
            memmove(data+1, data, strlen(data)+1);
            data[0] = '0';
        }
    }

    // Binary addition of all blocks with carry
    // First block of data stored in result variable
    strncpy(result, data, block_size);
    result[block_size] = '\0';

    // Loop to calculate the block
    // wise addition of data
    for (int i = block_size; i < n; i += block_size) {

        // Stores the data of the next block
        char next_block[block_size+1];
        strncpy(next_block, data+i, block_size);
        next_block[block_size] = '\0';

        // Stores the binary addition of two blocks
        char additions[block_size+1];
        int sum = 0, carry = 0;

        // Loop to calculate the binary addition of
        // the current two blocks of k size
        for (int k = block_size - 1; k >= 0; k--) {
            sum += (next_block[k] - '0')
                + (result[k] - '0');
            carry = sum / 2;
            if (sum == 0) {
                additions[k] = '0';
                sum = carry;
            }
            else if (sum == 1) {
                additions[k] = '1';
                sum = carry;
            }
            else if (sum == 2) {
                additions[k] = '0';
                sum = carry;
            }
            else {
                additions[k] = '1';
                sum = carry;
            }
        }
        additions[block_size] = '\0';

        // After binary add of two blocks with carry,
        // if carry is 1 then apply binary addition
        char final[block_size+1];

        if (carry == 1) {
            for (int l = block_size - 1; l >= 0; l--) {
                if (carry == 0) {
                    final[l] = additions[l];
                }
                else if (((additions[l] - '0') + carry) % 2 == 0) {
                    final[l] = '0';
                    carry = 1;
                }
                else {
                    final[l] = '1';
                    carry = 0;
                }
            }
            final[block_size] = '\0';
            strcpy(result, final);
        }
        else {
            strcpy(result, additions);
        }
    }

    // Return One's complements of result value
    // which represents the required checksum value
    Ones_complement(result);
}

// Function to check if the received message
// is same as the senders message
int checker(char *sent_message, char *rec_message, int block_size)
{
    // Checksum Value of the senders message
    char sender_checksum[block_size+1];
    checkSum(sent_message, block_size, sender_checksum);

    // Checksum value for the receivers message
    char receiver_checksum[block_size+1];
    char combined_message[strlen(rec_message) + strlen(sender_checksum) + 1];
    strcpy(combined_message, rec_message);
    strcat(combined_message, sender_checksum);
    checkSum(combined_message, block_size, receiver_checksum);

    // If receivers checksum value is 0
    for (int i = 0; i < block_size; i++) {
        if (receiver_checksum[i] != '0') {
            return 0;
        }
    }
    return 1;
}

// Driver Code
int main()
{
    char sent_message[] = "10000101011000111001010011101101";
    char recv_message[] = "10000101011000111001010011101101";
    int block_size = 8;
    char sender_checksum[block_size+1];

checkSum(sent_message, block_size, sender_checksum);

    //the initial mssg from sender's side is sender's mssg
    printf("Sender's mssg , without chksum is : %s\n", sent_message);

    //generate checksum for error detection by receiver in received mssg
    printf("Checksum for sender's mssg (mssg+checksum send hoga) is : %s\n", sender_checksum);

    //the final mssg received by receiver = received mssg (sender's mssg + may/may not have erro)
    printf("Received mssg is (may/maynot have error , have to check) : %s\n", recv_message);

    //receiver side - mssg validation
    if (checker(sent_message, recv_message, block_size)) {
        printf("No Error in mssg received from sender\n");
    }
    else {
        printf("Error in mssg received from sender\n");
    }

    return 0;
}