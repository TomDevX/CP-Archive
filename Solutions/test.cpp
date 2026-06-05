#include <iostream>
#include <numbers> // Required for mathematical constants

int main() {
    // Double precision constant
    double golden_ratio = std::numbers::phi; 
    std::cout << "Golden Ratio: " << golden_ratio << "\n";
    
    // Float precision variant
    float golden_ratio_f = std::numbers::phi_v<float>;
    return 0;
}
