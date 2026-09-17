#include<stdio.h>
#include<stdlib.h>



typedef struct 
{
    float current_voltage;
    float threshold;
    float decay_rate;
}LIF_Neuron;


int update_neuron(LIF_Neuron* neuron, float input_voltage)
{
    neuron->current_voltage= (neuron->current_voltage * neuron->decay_rate) + input_voltage; //U=U*B+X
    if(neuron->current_voltage>= neuron->threshold)
    {
        neuron->current_voltage=0.0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int no_of_neurons=10;
    LIF_Neuron* layer=(LIF_Neuron*) malloc (no_of_neurons * sizeof(LIF_Neuron));  
   
   for(int i=0;i<no_of_neurons;i++)
   { 
     layer[i].current_voltage=0.0;
     layer[i].decay_rate=0.9;
     layer[i].threshold=1.0;
   }
    
   int no_of_input=5;
   float inputs[5]={1.0,0.0,1.0,0.0,1.0};// just how many inuts each neuron gets

   float attention_scores[10] = {2.0, 2.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0};// for gate of attention


   float weights[no_of_input][no_of_neurons];//make 2d arr of weight
   for(int i=0;i<no_of_input;i++)//
   {
    for(int j=0;j<no_of_neurons;j++)//putting them in
    {
        weights[i][j]=(i+j) * 0.05;//random weight to test out
    }
   }

    for(int i=0;i<=20;i++)
    { 
        printf("step %d spikes:[",i);
       for(int j=0;j<no_of_neurons;j++)
       { 
         float incoming_voltage=0.0;
         for(int i=0;i<no_of_input;i++)
         {
            incoming_voltage= (inputs[i] *  weights[i][j]) + incoming_voltage;
         } 
         
         incoming_voltage=incoming_voltage * attention_scores[j];// multiplying by attention scores to get the gate

         int spike=update_neuron(&layer[j],incoming_voltage);
         printf("%d",spike);
       }
       printf("]\n");
    }


    free(layer);
}