#include "rational_number.h"

int main(int argc, char const *argv[])
{
    TRationalNum TRN_1_2(5,2);
    std::cout << TRN_1_2 << " " << TRN_1_2.GetWholePart() << " " << TRN_1_2 << "\n";
    TRationalNum TRN_0;
    TRationalNum TRN_02;
    TRN_02 = TRN_0 = TRN_1_2;
    std::cout << TRN_02 << " " << TRN_0 << " " << TRN_1_2 << "\n";
    std::cout << +TRN_02 << " " << -TRN_0 << " " << TRN_1_2 << "\n";
    TRN_0 += TRN_02;
    TRN_1_2 = TRN_02 + TRN_0;
    std::cout << TRN_02 << " " << TRN_0 << " " << TRN_1_2 << "\n";
    bool fst = TRN_0 == TRN_0;
    bool scnd = TRN_02 == TRN_0;
    std::cout << fst << " " << scnd << "\n";
    std::cout << ++TRN_02 << " " << TRN_0++ << "\n";
    std::cout << TRN_02 << " " << TRN_0 << "\n";
    return 0;
}






















