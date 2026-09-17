#pragma once
#include"lif_neuron.h"

typedef struct
{
    int no_of_input;
    int no_of_neurons;
    LIF_Neuron *neurons;//for this layer only
    float **weights;
}Network_Layer;

Network_Layer initialize_layer(int no_in, int no_out);//for making a lyer dynamically
