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

int main()
{
    mpz_class n;
    n = "0";

    int currentMultiplicativePersistence = -1;
    int maxMultiplicativePersistence = 12;

    auto start = std::chrono::high_resolution_clock::now();
    while(currentMultiplicativePersistence < maxMultiplicativePersistence)
    {
        int nMP = per(n);

        if (nMP > currentMultiplicativePersistence)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count();

            std::cout << nMP << " | " << n << " (" << elapsedTime << " ms)\n";
            ++currentMultiplicativePersistence;
        }

        n += 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Total time: " << totalTime << " ms\n";


    return 0;
}
