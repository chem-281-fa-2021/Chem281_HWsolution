#if !defined SODA_H
#define SODA_H
#include <string>

namespace Soda
{
    enum Action {insert, press, reload, quit};
    class State;

    class AbstractContext
    {
    public:
        virtual void setState(State *newState)=0; // change state object
        virtual void decreasecount()=0; // change some variable
        virtual void setcount(int count)=0; // change some variable
        virtual int getcount()=0; // get some variable
    };

    class SodaMachine : public AbstractContext
    {
    public:
        SodaMachine(State *initalState, int num_soda);
        int contextInterface(std::string custom_operation);                // receive messages from clients
        virtual void setState(State *newState); // change state object
        virtual void decreasecount() {count--;}; // change some variable
        virtual void setcount(int count_in) {count = count_in;} // change some variable
        virtual int getcount(){return count;} // get some variable
    private:
        State *currentState;
        int count;
    };

    class State
    {
    public:
        State(){}
        void setContext(AbstractContext * ac);
        void SetTransitionTable(State **transitonTable);
        virtual double handle(Action *eventData) = 0;

    protected:
        AbstractContext *context;
        State **transitionTable;
    };

    class AbstractStateFactory
    {
    public:
        AbstractStateFactory(int num): num_states(num){}
        virtual State **createStates()=0;
        void setContext(AbstractContext * ac, State **createStates);
        void desctruct(State **createStates);
        const int num_states;
    };

    class Idle : public State{
        virtual double handle(Action *eventData);
    };
    class Ready : public State{
        virtual double handle(Action *eventData);
    };
    class Empty : public State{
        virtual double handle(Action *eventData);
    };
    class Poblem1_factory : public AbstractStateFactory
    {
    public:
        virtual State **createStates();
        Poblem1_factory(): AbstractStateFactory(3){}
    };

    
    class Idle2 : public State{
        virtual double handle(Action *eventData);
    };
    class Ready2 : public State{
        virtual double handle(Action *eventData);
    };
    class Empty2 : public State{
        virtual double handle(Action *eventData);
    };
    class Overloaded : public State{
        virtual double handle(Action *eventData);
    };
    class Poblem2_factory : public AbstractStateFactory
    {
    public:
        virtual State **createStates();
        Poblem2_factory(): AbstractStateFactory(4){}
    };

  
}
#endif // SODA_H