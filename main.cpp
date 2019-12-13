#include <iostream>
#include <string>

void per(long long n)
{
    int step = 0;
    std::string nString = std::to_string(n);

   std:: cout << nString << "\n";
    while (nString.length() > 1)
    {
        long long m = 1;
        for(auto c : nString)
        {
            m *= (c - '0');
        }
        nString = std::to_string(m);
        std::cout << nString << "\n";
        ++step;
    }

    std::cout << "TOTAL STEP: " << step << "\n";
}

int main()
{
    per(277777788888899);
    return 0;
}
