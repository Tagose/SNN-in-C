#include<stdio.h>
#include<stdlib.h>
#include"lif_neuron.h"
#include"attention.h"
#include"stdp.h"
#include<time.h>
#include"encoder.h"
#include "mnist_loader.h"
#include"layer.h"

int main()
{
    //int no_of_neurons=100;//lets assume for now ok
    //int no_of_input=784;//yes arbitrary for now shuttup 


   /*  LIF_Neuron *layer=malloc (no_of_neurons * sizeof *layer);  //allocating memory for struct
   
   //initializing the U(membrane pot),B(decar rate)  and  some threshold....all arbitrary rn ofc
    for(int i=0;i<no_of_neurons;i++)
      { 
       layer[i].current_voltage=0.0;
       layer[i].decay_rate=0.99;
       layer[i].threshold=0.1;
       layer[i].last_spike_time=-1;//condition for not firing
       layer[i].refractory_cd_time_left=0;//gotta have this or malloc causes garbago number dump
      }
    
  
   //float inputs[5]={1.0,0.0,1.0,0.0,1.0};// just how many inuts each neuron gets
   //float attention_scores[10] = {2.0, 2.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0};// for gate of attention(basically attention score..u just want attention u dont want my heeeart)
   */
   srand(time(NULL));

   //float pixel_intensities[5]={0.9,0.8,0.1,0.2,0.9};//for now a 5 pixel image
   //float weights[no_of_input][no_of_neurons];//make 2d arr of weight
   //int input_spike_time[5]={-1,-1,-1,-1,-1};//tracks spike firing initial
   
   int no_of_layers = 2;
   int layer_sizes[] = {784, 100, 10};
   
   
   //declareing and initializing the layer
   Network_Layer multiple_layer[no_of_layers];
    printf("------------------------ Initializing Spiking Neural Network ------------------------\n");
    for (int l = 0; l < no_of_layers; l++) {
        multiple_layer[l] = initialize_layer(layer_sizes[l], layer_sizes[l+1]);
        printf("Layer %d initialized: %d Inputs -> %d Neurons\n", l, multiple_layer[l].no_of_input, multiple_layer[l].no_of_neurons);
    }
   

   float pixel_intensities[784];
   int input_spike_time[784];
   
    //Initialize the spike array using the dynamic struct variable
    for(int i = 0; i < multiple_layer[0].no_of_input; i++) 
    {
      input_spike_time[i] = -1;
    }


   //load 
   int label = -1;
   if (load_mnist_image("mnist_test.csv", 2, pixel_intensities, &label) == 0) 
   {
    printf("--- Successfully loaded MNIST Digit: %d ---\n", label);
    } 
    else
     {
       printf("Failed to load image. Check filepath!\n");
       return 1;
     }



   /*float **weights = malloc(no_of_input * sizeof(float *));
   for (int i = 0; i < no_of_input; i++) 
      {
       weights[i] = malloc(no_of_neurons * sizeof(float));
        for(int j = 0; j < no_of_neurons; j++) 
          {
           // weight can be random between 1 and 0 as always
           weights[i][j] = ((float)rand() / (float)RAND_MAX) * 0.5;
          }
      }
   */ 
   int current_inputs = multiple_layer[0].no_of_input;
   int current_neurons = multiple_layer[0].no_of_neurons;

   //main loop where main big league stuff happens
    for(int step=0;step<=50;step++)//time frame naoya style(like animation consider each step as a time frame )
    { 
       printf("step %d spikes:[",step);
       float current_spikes[current_inputs]; // Holds the 1s and 0s for this specific step

       for(int i=0;i<current_inputs;i++)
       {
        current_spikes[i]=(float)generate_poisson_spike(pixel_intensities[i]);
        if(current_spikes[i]>0)//if voltage isnt 0 then reord its time
        {
          input_spike_time[i]=step;
        }
       }

       float pre_attention_voltage[current_neurons];//array holds incoming volt before attention applied
       for(int temp=0;temp<current_neurons;temp++)
       {pre_attention_voltage[temp]=0;}

       for(int j=0;j<current_neurons;j++)//the loop iterates through all neurons of the layer
       {  
         //using synaptic weight adjustment for the incoming volt/input
         for(int i=0;i<current_inputs;i++)
         {
            pre_attention_voltage[j]+= (current_spikes[i] * multiple_layer[0].weights[i][j]) ;//adjusting happens (input * weight + incoming voltage)
         } 
       }

       //quick swap attention(can switxh lets say softmax to smthg else easily now)
       attention(pre_attention_voltage,current_neurons);



       for(int j=0;j<current_neurons;j++)
       {
         int spike=update_neuron(&multiple_layer[0].neurons[j],pre_attention_voltage[j],step);//calling update neuron for the actual LIF part
         printf("%d",spike);

         for(int i=0;i<current_inputs;i++)//adjust weights to learn basically
         {
          stdp(&multiple_layer[0].weights[i][j],input_spike_time[i],multiple_layer[0].neurons[j].last_spike_time);
         }
       }


       printf("]\n");
    }



    /*for (int i = 0; i < no_of_input; i++) 
    {
      free(weights[i]);
        
    }
    free(weights);
    //freeing mem is important id almost forgotten lol
    free(layer);
    */
  for (int l = 0; l<no_of_layers; l++) {
        // Free the columns
        for (int i = 0; i < multiple_layer[l].no_of_input; i++) {
            free(multiple_layer[l].weights[i]);
        }
        // Free the row pointers 
        free(multiple_layer[l].weights);
        // Free the neurons
        free(multiple_layer[l].neurons);
    }

    printf("Network memory fired successfully and there were no leaks :)\n");
    return 0;
}

