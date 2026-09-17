#include <stdlib.h>
#include <stdio.h>
#include "layer.h"

float get_random_weight() 
{
    return ((float)rand() / (float)RAND_MAX);
}//for random weights


Network_Layer initialize_layer(int no_in, int no_out) 
{
    Network_Layer layer;
    layer.no_of_input = no_in;
    layer.no_of_neurons = no_out;


    // Allocate Memory for the Neurons 
    layer.neurons = malloc (no_out * sizeof *layer.neurons);  //allocating memory for struct
    if (layer.neurons == NULL) 
    {
        printf("ERROR: Memory allocation failed for neurons!\n");
        exit(1);
    }

    //  //initializing the U(membrane pot),B(decar rate)  and  some threshold....all arbitrary rn ofc
    for(int i=0;i<no_out;i++)
      { 
           layer.neurons[i].current_voltage=0.0;
           layer.neurons[i].decay_rate=0.99;
           layer.neurons[i].threshold=0.1;
           layer.neurons[i].last_spike_time=-1;//condition for not firing
           layer.neurons[i].refractory_cd_time_left=0;//gotta have this or malloc causes garbago number dump
      }

    // Allocate Memory for the Weights
    layer.weights = malloc(no_in * sizeof *layer.weights);
    if (layer.weights == NULL) 
    {
        printf("ERROR: Memory allocation failed for weight rows :(\n");
        exit(1);
    }

    for (int i = 0; i < no_in; i++) {
        layer.weights[i] = malloc(no_out * sizeof(*layer.weights[i]));
        if (layer.weights[i] == NULL) {
            printf("ERROR: Memory allocation failed for weight columns!\n");
            exit(1);
        }
        
        // Initialize synapses with a small random starting weight (e.g., 0.0 to 0.1)
        for (int j = 0; j < no_out; j++) {
            layer.weights[i][j] = get_random_weight() * 0.1;
        }
    }
    return layer;
}
