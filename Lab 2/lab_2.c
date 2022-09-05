#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIMUM_SIZE_OF_ARRAY 20

int is_prime(int number_to_be_checked)
{
    //Checks if the number_to_be_checked is prime or not. Returns 1 if it is prime, 0 otherwise.
    if (number_to_be_checked < 2) return 0;
    if (number_to_be_checked == 2) return 1;
    if (number_to_be_checked % 2 == 0) return 0;
    int possible_divisor;
    possible_divisor = 3;
    while (possible_divisor * possible_divisor <= number_to_be_checked)
    {
        if (number_to_be_checked % possible_divisor == 0) return 0;
        possible_divisor += 2;
    }
    return 1;
}
int main()
{
        int list_of_numbers[MAXIMUM_SIZE_OF_ARRAY] = {0};
        int length_of_the_list, index = 0;
        int maximum_length_of_subsequence = 0, current_length_of_subsequence = 0, first_index_in_subsequence = 0, difference_between_2_consecutive_numbers;
        char input_string[6];
        
        //read the numbers until the occurrence of the word 'exit'
        scanf("%s", input_string);
        input_string[strlen(input_string)] = 0;  //the string has to finish with 0 (Null)
        while (strcmp(input_string, "exit") != 0)
        {
                //atoi converts the number which was read with the char format into an integer 
                list_of_numbers[index] = atoi(input_string);        //put in the array the number converted into integer
                index++;                          //move to the next element
                scanf("%s", input_string);       //read the next string (until it is equal with 'exit')
                input_string[strlen(input_string)] = 0;
        }
        length_of_the_list = index;
        
        /*
        finding the longest susequence with the given property and the index from which the subsequence starts in
the array to be able to print the subsequence later
        */
        index = 0;
        while (index < length_of_the_list - 1)
        {
            difference_between_2_consecutive_numbers = list_of_numbers[index + 1] - list_of_numbers[index];
            if (is_prime(difference_between_2_consecutive_numbers) == 1)
                    current_length_of_subsequence += 1;     //if the difference is a prime number, we count it by increasing the current length of the subsequence
            else if (current_length_of_subsequence >= maximum_length_of_subsequence)            //else the current element in the array intrerupts the subsequence. so we have to check if the length of the found subsequence is greater than the maximum one
                {
                    maximum_length_of_subsequence = current_length_of_subsequence;
                    first_index_in_subsequence = index - current_length_of_subsequence;
                    current_length_of_subsequence = 0;                       //reinitialize the current lenght
                }
            index++;    //move to the next element
        }

        if (current_length_of_subsequence >= maximum_length_of_subsequence)            //for the last element, if it was an element of a good subsequence, the comparation hasn't been made  
        {
            maximum_length_of_subsequence = current_length_of_subsequence;
            first_index_in_subsequence = index - current_length_of_subsequence;
        }

        //in the max lenght, the last element of the subsequence was not counted. so:
        maximum_length_of_subsequence = maximum_length_of_subsequence + 1;

        //now we print the found subsequence which has max_lenght elements. 
        index = 1;
        while (index <= maximum_length_of_subsequence)
        {
            printf("%d ", list_of_numbers[first_index_in_subsequence]);
            first_index_in_subsequence++;
            index++;
        }

    return 0;
}
