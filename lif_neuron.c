#include "lif_neuron.h"

int update_neuron(LIF_Neuron* neuron, float input_voltage,int current_step)
{
    if(neuron->refractory_cd_time_left>0)
    {
        neuron->refractory_cd_time_left--;
        neuron->current_voltage=0.0;
        return 0;
    }

    //voltage accumulation
    neuron->current_voltage= (neuron->current_voltage * neuron->decay_rate) + input_voltage; //U=U*B+X
    
    
    if(neuron->current_voltage>= neuron->threshold)
    {
        neuron->current_voltage=0.0;//reset to 0 afterit fired once
        neuron->last_spike_time=current_step;//remembering the spike time we are currently on
        neuron->refractory_cd_time_left=5;//reset timer back to 5 bih
        return 1;//its a spike

    }
    else
    {
        return 0;
    }
}