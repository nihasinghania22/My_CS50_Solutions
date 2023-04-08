#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{


// check there is only 1 arguments and it is a number else returns instructions
    if (argc == 2 && isdigit(*argv[1]))
        
    {

        int k = atoi(argv[1]); // get the ceasar KEY value convert into integar

        string STR = get_string("plaintext: "); // get text
        printf("ciphertext: "); // print out cipher


        for (int i = 0, n = strlen(STR) ; i < n; i++)
        {
            // checking if it is lowercase 97 = a to 112 = z and if it + 13 characters along.
            if (STR[i] >= 'a' && STR[i] <= 'z')
            {
                printf("%c", (((STR[i] - 'a') + k) % 26) + 'a'); // print out lowercase with key
            } // if it it between uppercase A and C
            else if (STR[i] >= 'A' && STR[i] <= 'Z')
            {
                printf("%c", (((STR[i] - 'A') + k) % 26) + 'A'); // print out uppercase with key
            }

            else

            {
                printf("%c", STR[i]);
            }
        }

        printf("\n");
        return 0;
    }

    else
    {
        printf("Usage: ./caesar k\n");
        return 1;

    }

}