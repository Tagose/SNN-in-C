#include"encoder.h"
#include<stdlib.h>

int generate_poisson_spike(float intensity)
{
	//generate random float betweeen 1.0 and 0.0
	float random_choice=(float)rand() / (float)RAND_MAX;
 	
	
	//if intensity more than randmo number, we fire
	if(intensity>random_choice)
		{
		  return 1;}
	else
		return 0;
}
