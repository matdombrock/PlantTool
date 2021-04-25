/*
Define device state variables
*/
#ifndef State_H
#define State_H
class State{
    public:
        int btn = 0;
        int capRead = 0;
        int prRead = 0;
        int mode = 0;

        float humidity=0;
        float temp=0;
        float tempF=0;
        float heatIndexF=0;
        float heatIndex=0;
};
#endif