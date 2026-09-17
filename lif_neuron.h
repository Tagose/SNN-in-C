#pragma once


typedef struct 
{
    float current_voltage;
    float threshold;
    float decay_rate;
    int last_spike_time;//for time keeping of last spike fire duh
    int refractory_cd_time_left;//keeps tab for the neurons cooldowndown time..then its free to ult again
}LIF_Neuron;


int update_neuron(LIF_Neuron* neuron, float input_voltage,int current_step);

