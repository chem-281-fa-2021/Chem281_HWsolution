#include "Soda.h"
#include <iostream>
#include <map>

using namespace std;
using namespace Soda;

//context functions
std::map<std::string, Action> operation_map { {"p", press}, {"q", insert}, {"e", quit}, {"reload", reload}, };

void SodaMachine::setState(State *newState){
    currentState = newState;
}
SodaMachine::SodaMachine(State *initalState, int num_soda) : currentState(initalState), count(num_soda) {}

int SodaMachine::contextInterface(std::string custom_operation){
    std::string instruction = "Enter q for insert quarter, p for push button and e to quit the machine\n Please reinput\n";
    if(operation_map.find(custom_operation) == operation_map.end()){
        std::cout << instruction;
        return 0;
    }
    else{
        Action myac = operation_map[custom_operation];
        if (myac != quit){
            double result = currentState->handle(&myac);
            if(result != 0){
                cout<<"Machine failed\n";
                return 1;
            }
            return 0;
        }else{
            cout<<"Thanks for using Soda Machine!\n";
            return 1;

        }
    }
    return 0;
}

//Base State functions and AbstractStateFactory functions
void State::SetTransitionTable(State **tT)
{
    transitionTable = tT;
}
void State::setContext(AbstractContext * ac)
{
    context = ac;
}
void AbstractStateFactory::setContext(AbstractContext * ac, State **table)
{
    for (int k = 0; k < num_states; k++)
    {
        table[k]->setContext(ac);
    }
}
void AbstractStateFactory::desctruct(State **table)
{
    if (table != NULL)
    {
        for (int k = 0; k < num_states; k++)
        {
            if (table[k] != NULL)
                delete table[k];
        }
        delete table;
    }
}

std::string Invlaid_operation = "Invalid operation. Please reinput!\n";
// Derived state functions for Problem1
double Idle::handle(Action *eventData)
{
    switch (*eventData)
    {
    case insert:
        this->context->setState(this->transitionTable[1]);
        break;
    case press:
        cout << "Insert Quarter" << endl;
        break;
    default:
        cout<< Invlaid_operation;
    }
    return 0;
}
double Ready::handle(Action *eventData)
{
    switch (*eventData)
    {
    // case insert:
    //     this->context->setState(this->transitionTable[1]);
    //     break;
    
    case press:
        {cout << "Delivering" << endl;
        int left = this->context->getcount();
        if(left == 0){
            cout << "is Empty" << endl;
            this->context->setState(this->transitionTable[2]);
        }else{
            cout << "is Idle" << endl;
            this->context->setState(this->transitionTable[0]);
            this->context->decreasecount();
        }
        break;}
    default:
        cout<< Invlaid_operation;
    }
    return 0;
}
double Empty::handle(Action *eventData)
{
    switch (*eventData)
    {
    case reload:
        {cout<< "Please input reload number and return\n";
        string str_num_soda;
        getline(std::cin, str_num_soda);
        int num_soda = stoi(str_num_soda);
        this->context->setcount(num_soda);
        cout<< "LOADED\n";
        this->context->setState(this->transitionTable[0]);
        break;}
    default:
        cout<< "machine is empty\n";
    }
    return 0;
}

State **Poblem1_factory::createStates()
{
    State **table = new State *[num_states];
    table[0] = new Idle();
    table[1] = new Ready();
    table[2] = new Empty();
    for (int k = 0; k < num_states; k++)
    {
        table[k]->SetTransitionTable(table);
    }
    return table;
}



// Derived state functions for Problem 2
double Idle2::handle(Action *eventData)
{
    int left_sode = this->context->getcount();
    switch (*eventData)
    {
    case insert:
        if(left_sode >0)
            this->context->setState(this->transitionTable[1]);
        else
            this->context->setState(this->transitionTable[3]);
        break;
    case press:
        if(left_sode >0)
            cout << "Insert Quarter" << endl;
        else{
            this->context->setState(this->transitionTable[2]);
            cout << "is Empty now." << endl;
        }
        break;
    default:
        cout<< Invlaid_operation;
    }
    return 0;
}
double Overloaded::handle(Action *eventData)
{
    switch (*eventData)
    {
    case insert:
        cout << " 2 quarters ejectected" << endl;
        break;
    default:
        cout << "quarter ejectected" << endl;
        break;
    }
    int left_sode = this->context->getcount();
    if(left_sode >0)
        this->context->setState(this->transitionTable[1]);
    if(left_sode == 0)
        this->context->setState(this->transitionTable[2]);
    if(left_sode < 0)
        return 1;

    return 0;
}
double Ready2::handle(Action *eventData)
{
    switch (*eventData)
    {
    case insert:
        this->context->setState(this->transitionTable[3]);
        cout << "Overloaded" << endl;
        break;
    case press:
        {
        cout << "Delivering" << endl;
        this->context->decreasecount();
        int left = this->context->getcount();
        if(left == 0){
            this->context->setState(this->transitionTable[2]);
            cout << "is Empty now." << endl;
        }else{
            cout << "is Idle" << endl;
            this->context->setState(this->transitionTable[0]);
        }
        break;}
    default:
        cout<< Invlaid_operation;
    }
    return 0;
}
double Empty2::handle(Action *eventData)
{
    switch (*eventData)
    {
    case insert:
        this->context->setState(this->transitionTable[3]);
        cout << "is Empty. Overloaded" << endl;
        break;
    case reload:
        {cout<< "Please input reload number and return\n";
        string str_num_soda;
        getline(std::cin, str_num_soda);
        int num_soda = stoi(str_num_soda);
        this->context->setcount(num_soda);
        cout<< "LOADED\n";
        this->context->setState(this->transitionTable[0]);
        break;}
    default:
        cout<< "machine is empty\n";
    }
    return 0;
}

State **Poblem2_factory::createStates()
{
    State **table = new State *[num_states];
    table[0] = new Idle2();
    table[1] = new Ready2();
    table[2] = new Empty2();
    table[3] = new Overloaded();
    for (int k = 0; k < num_states; k++)
    {
        table[k]->SetTransitionTable(table);
    }
    return table;
}