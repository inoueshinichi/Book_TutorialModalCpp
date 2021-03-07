#include "../all.hpp"

using namespace std;

int main(int, char**)
{
    //////////
    // 数学定数
    //////////

    // ネイピア数e
    double e_d = numbers::e;
    std::cout << "e: " << e_d << std::endl;
    float e_f = numbers::e_v<float>;

    // eに対する底2のlog
    double log2e_d = numbers::log2e;
    std::cout << "log2e: " << log2e_d << std::endl;
    float log2e_f = numbers::log2e_v<float>;

    // eに対する底10のlog
    double log10e_d = numbers::log10e;
    std::cout << "log10e: " << log10e_d << std::endl;
    float log10e_f = numbers::log10e_v<float>;

    // 円周率π
    double pi_d = numbers::pi;
    std::cout << "pi: " << pi_d << std::endl;
    float pi_f = numbers::pi_v<float>;

    // 円周率πの逆数1/π
    double inv_pi_d = numbers::inv_pi;
    std::cout << "inv_pi: " << inv_pi_d << std::endl;
    float inv_pi_f = numbers::inv_pi_v<float>;

    // 円周率πの平方根逆数1/√π
    double inv_sqrtpi_d = numbers::inv_sqrtpi;
    std::cout << "inv_sqrtpi: " << inv_sqrtpi_d << std::endl;
    float inv_sqrtpi_f = numbers::inv_sqrtpi_v<float>;

    // 2の自然対数ln(2)
    double ln2_d = numbers::ln2;
    std::cout << "log2: " << ln2_d << std::endl;
    float ln2_f = numbers:ln2_v<float>;

    // 10の自然対数ln(10)
    double ln10_d = numbers::ln10;
    std::cout << "log10: " << ln10_d << std::endl;
    float ln10_f = numbers::ln10_v<float>;

    // 2の平方根√2
    double sqrt2_d = numbers::sqrt2;
    std::cout << "sqrt2: " << sqrt2_d << std::endl;
    float sqrt2_f = numbers::sqrt2_v<float>;

    // 3の平方根√3
    double sqrt3_d = numbers::sqrt3;
    std::cout << "sqrt3: " << sqrt3_d << std::endl;
    float sqrt3_f = numbers::sqrt3_v<float>;

    // 3の平方根の逆数1/√3
    double inv_sqrt3_d = numbers::inv_sqrt3;
    std::cout << "inv_sqrt3: " << inv_sqrt3_d << std::endl;
    float inv_sqrt3_f = numbers::inv_sqrt3_v<float>;

    // オイラー定数γ
    double eular_gamma_d = numbers::egamma;
    std::cout << "eular_gamma: " << eular_gamma_d << std::endl;
    float eular_gamma_f = numbers::egamma_v<float>;

    // 黄金比φ
    double phi_d = numbers::phi;
    std::cout << "phi: " << phi_d << std::endl;
    float phi_f = numbers::phi_v<float>;

}