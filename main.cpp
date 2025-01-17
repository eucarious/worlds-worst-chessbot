#include "shakki.h"
#include "asema.h"
#include <iostream>


int main() {

    Asema board;

    int a;
    int b;

    board.print();
    board.find_king(wK, a, b);

    std::cout << a << ", " << b;


	std::cout << "\n\n";

    board.clear();
    board.find_king(bK, a, b);

    
    std::cout << a << ", " << b;

    return 0;

};