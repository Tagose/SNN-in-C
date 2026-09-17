#include"stdp.h"
#include<math.h>

void stdp(float *weights,int input_spike_time,int output_spike_time)
{
    //if no spike->nothing to do
    if(input_spike_time==-1 || output_spike_time==-1)
    {
        return;
    }

    int dt=output_spike_time-input_spike_time;//calculate delta time(which means difference between time of output and input for those who dont know what that means including me for example )

    float A_plus=0.05;//how much to increase strength by(go plus ultra by making this be 2)
    float A_minus=0.05;//yes i made it seperate and didnt just use A for both plus and minus shuttup

    float tau=5.0;//the tau(ik fancy right) is the time window for how long it remembers

    if(dt>0)//basically input gives output then increase weight...i think....i dunno maths man
    {
        *weights+= A_plus * (exp((-dt/tau)));
    }
    else if(dt<0)//if dt<0 then nothing happened wehn input was given hence decrease the connection here obv
    {
        *weights-= A_minus * (exp((dt/tau)));
    }

    //now we have slight thing to do.WEights cant be aboce 1 and under 0 so put a check for that
    if(*weights>1.0)
    {   *weights=1.0;}
    if(*weights<0.0)
    {*weights=0.0;}
    
       
}