// Example program
#include <iostream>
#include <string>
#include "Soda.h"

using namespace std;
using namespace Soda;

int main()
{
    std::string instruction = "Enter q for insert quarter, p for push button and e to quit the machine\n Please input\n";

    std::string custom_operation;
    std::cout << instruction;

    // Choose the problem
    // AbstractStateFactory *fac = new Poblem1_factory;
    AbstractStateFactory *fac = new Poblem2_factory;
    State ** table = fac->createStates();
    SodaMachine amachine(table[0], 0);
    AbstractContext* pmachine = &amachine;
    fac->setContext(pmachine, table);
    Action a = insert;
    // table[0]->handle(&a);
    for(int i_index = 0; i_index <= 100; i_index++){
        getline(std::cin, custom_operation);
        int continueornot = amachine.contextInterface(custom_operation);
        if(continueornot == 1)
            break;
    }
    fac->desctruct( table);
    return 0;
}