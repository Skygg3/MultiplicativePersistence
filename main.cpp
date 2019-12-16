// C++ Standard Library
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <execution>
#include <sstream>

// MPIR
#include <mpirxx.h>

#include "timer.h"

/**
 * @brief Calculated the multiplicative persistence of a number
 * @param number    Input number
 * @return  Multiplicative persistence of the given number
 */
int multiplicativePersistence(const mpz_class &number)
{
    std::string nString = number.get_str();

    int requiredSteps = 0;
    while (nString.length() > 1)
    {
        mpz_class m;
        m = 1;

        for(const auto c : nString)
        {
            if(c == '0') return requiredSteps + 1;
            m *= (c - '0');
        }
        nString = m.get_str();
        ++requiredSteps;
    }

    return requiredSteps;
}

/**
 * @brief Utility function to create a std::string formed by the repetition of another std::string
 * @param toRepeat  String to repeat
 * @param nRepeat   Number of repetition
 * @return  Repeated string
 */
std::string repeatString(const std::string &toRepeat, int nRepeat)
{
    std::string output;

    for(int i = 0; i < nRepeat; ++i)
    {
        output += toRepeat;
    }

    return output;
}

/**
 * @brief Transforms a number in normalised form into a natural form
 * @param normalisedNumber  A number in normalised form
 * @return Input number in natural form
 */
std::string normalisedToNatural(const std::string &normalisedNumber)
{
    int nb2 = 0;
    int nb3 = 0;
    int nb4 = 0;
    int nb5 = 0;
    int nb6 = 0;
    int nb7 = 0;
    int nb8 = 0;
    int nb9 = 0;

    // Analyze the number
    for(auto c : normalisedNumber)
    {
        switch (c) {
            case '2':
                ++nb2;
                break;
            case '3':
                ++nb3;
                break;
            case '5':
                ++nb5;
                break;
            case '7':
                ++nb7;
                break;
        }
    }

    // Replace any three 2s with 8
    nb8 = nb2 / 3;
    nb2 -= 3 * nb8;

    // Replace any two 3s with 9
    nb9 = nb3 / 2;
    nb3 -= 2 * nb9;

    // Replace any 2 and 3 with 6
    nb6 = std::min(nb2, nb3);
    nb2 -= nb6;
    nb3 -= nb6;

    // Replace any two 2s with 4
    nb4 = nb2 / 2;
    nb2 -= 2 * nb4;

    // Sort the digits of the result into ascending order and return it
    std::string output;
    output += repeatString("2", nb2);
    output += repeatString("3", nb3);
    output += repeatString("4", nb4);
    output += repeatString("5", nb5);
    output += repeatString("6", nb6);
    output += repeatString("7", nb7);
    output += repeatString("8", nb8);
    output += repeatString("9", nb9);

    return output;
}

/**
 * @brief Constructs a normalised number
 * @param nb2   Number of 2 in the number
 * @param nb3   Number of 3 in the number
 * @param nb5   Number of 5 in the number
 * @param nb7   Number of 7 in the number
 * @return      The normalised number defined by the parameters
 */
std::string constructNormalisedNumber(int nb2, int nb3, int nb5, int nb7)
{
    return repeatString("2", nb2) + repeatString("3", nb3) + repeatString("5", nb5) + repeatString("7", nb7);
}


int main()
{
    // Size of the numbers to test
    int minDigits = 1;
    int maxDigits = 200;

    Timer timer;

    timer.start();
    for(int nDigits = minDigits; nDigits <= maxDigits; ++nDigits)
    {
        // Creates a vector containing all possible number of 2 in the number
        std::vector<int> n2Vector;
        for(int k = nDigits; k >= 0; --k)
        {
            n2Vector.push_back(k);
        }

        // Start calculation in multiple thread
        std::for_each(
            std::execution::par_unseq,
            n2Vector.begin(),
            n2Vector.end(),
            [&](const auto &n2)
            {
            for(int n3 = nDigits - n2; n3 >= 0; --n3)
            {
                if(n2 == 0)
                {
                    for(int n5 = nDigits - n2 - n3; n5 >= 0; --n5)
                    {
                        int n7 = nDigits - n2 - n3 - n5;

                        mpz_class number;
                        number = constructNormalisedNumber(n2, n3, n5, n7);
                        int numberMP = multiplicativePersistence(number);

                        if (numberMP >= 10)
                        {
                            // Store the output in a std::stringstream to cout it to prevent threads from writing at the same time
                            std::stringstream stream;
                            stream << numberMP << " | " << normalisedToNatural(number.get_str()) << " (" << timer.elapsedMilliseconds() << " ms)\n";
                            std::cout << stream.str();
                        }
                    }
                }
                else {
                    int n5 = 0;
                    int n7 = nDigits - n2 - n3 - n5;

                    mpz_class number;
                    number = constructNormalisedNumber(n2, n3, n5, n7);
                    int numberMP = multiplicativePersistence(number);

                    if (numberMP >= 10)
                    {
                        // Store the output in a std::stringstream to cout it to prevent threads from writing at the same time
                        std::stringstream stream;
                        stream << numberMP << " | " << normalisedToNatural(number.get_str()) << " (" << timer.elapsedMilliseconds() << " ms)\n";
                        std::cout << stream.str();
                    }
                }

            }
            });

        std::cout << "Checked " << nDigits << " digits numbers in " << timer.elapsedMilliseconds() << " ms\n";
    }

    return 0;
}
