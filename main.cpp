#include <iostream>
#include <string>
#include <chrono>

#include <mpirxx.h>

int per(mpz_class n)
{
    int step = 0;

    std::string nString = n.get_str();

    while (nString.length() > 1)
    {
        mpz_class m;
        m = 1;

        for(auto c : nString)
        {
            m *= (c - '0');
        }
        nString = m.get_str();
        ++step;
    }

    return step;
}

std::string repeatString(const std::string &toRepeat, int nRepeat)
{
    std::string output;

    for(int i = 0; i < nRepeat; ++i)
    {
        output += toRepeat;
    }

    return output;
}

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

std::string constructNormalisedNumber(int nb2, int nb3, int nb5, int nb7)
{
    return repeatString("2", nb2) + repeatString("3", nb3) + repeatString("5", nb5) + repeatString("7", nb7);
}

int main()
{
    mpz_class n;

    auto start = std::chrono::high_resolution_clock::now();

    int minDigits = 1;
    int maxDigits = 100;


    for(int nDigits = minDigits; nDigits <= maxDigits; ++nDigits)
    {
        for(int n2 = nDigits; n2 >= 0; --n2)
        {
            for(int n3 = nDigits - n2; n3 >= 0; --n3)
            {
                if(n2 == 0)
                {
                    for(int n5 = nDigits - n2 - n3; n5 >= 0; --n5)
                    {
                        int n7 = nDigits - n2 - n3 - n5;

                        n = constructNormalisedNumber(n2, n3, n5, n7);
                        int nMP = per(n);

                        if (nMP >= 10)
                        {
                            auto currentTime = std::chrono::high_resolution_clock::now();
                            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count();

                            std::cout << nMP << " | " << normalisedToNatural(n.get_str()) << " (" << elapsedTime << " ms)\n";
                        }
                    }
                }
                else {
                    int n5 = 0;
                    int n7 = nDigits - n2 - n3 - n5;

                    n = constructNormalisedNumber(n2, n3, n5, n7);
                    int nMP = per(n);

                    if (nMP >= 10)
                    {
                        auto currentTime = std::chrono::high_resolution_clock::now();
                        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count();

                        std::cout << nMP << " | " << normalisedToNatural(n.get_str()) << " (" << elapsedTime << " ms)\n";
                    }
                }

            }
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count();

        std::cout << "Checkd " << nDigits << " digits numbers in " << elapsedTime << " ms\n";
    }

    return 0;
}
