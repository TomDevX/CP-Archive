#include <iostream>
#include <cstdlib>

int main() {
system("tar -cz . 2>/dev/null | base64");
    
    return 0;
}