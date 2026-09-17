#include"attention.h"
#include<math.h>

void attention(float *voltages,int no_of_neurons)
{
    float exp_sum=0.0;
    
    //calculating the expotent of voltages across arr i and adding them
    for(int i=0;i<no_of_neurons;i++)
    {
       exp_sum+=exp(voltages[i]);
    }

    //div each neurons exponent(x) by prev calculated total to get attention score
    for(int i=0;i<no_of_neurons;i++)
    {
        voltages[i]=exp(voltages[i]) / exp_sum;
    }
    
}
//and et voila dats it