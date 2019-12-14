#include <iostream>
#include <string>

#include <mpirxx.h>

void per(mpz_class n)
{
    int step = 0;

    std::string nString = n.get_str();
    std:: cout << nString << "\n";

    while (nString.length() > 1)
    {
        mpz_class m;
        m = 1;

        for(auto c : nString)
        {
            m *= (c - '0');
        }
        nString = m.get_str();
        std::cout << nString << "\n";
        ++step;
    }

    std::cout << "TOTAL STEP: " << step << "\n";
}

int main()
{
    mpz_class n;
    n = "277777788888899999999999999999999";

    per(n);

    return 0;
}
