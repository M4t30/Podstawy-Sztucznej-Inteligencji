#include "Neuron.h"
#include <time.h>

void Neuron::createInputs(int amount) 
{
	double weight = countFirstWeight();

	for (int i = 0; i < amount; i++)
	{
		_dendrites.push_back(0);
		_synapses.push_back(countFirstWeight());
	}
}

void Neuron::sumOfInputs()
{
	if (getDendritesAmount() == 0) 
	{
		return;
	}

	else
	{
		double sum = 0;

		for (int i = 0; i < getDendritesAmount(); i++)
		{
			sum += processSingleInput(i);
		}
		
		_sumOfAllInputs = sum;
	}
}

int Neuron::processOutput() 
{
	if (getDendritesAmount() == 0) 
	{
		return -1;
	}

	else
	{
		if (_sumOfAllInputs > 0)
		{
			_outputValue = 1;
			return _outputValue;
		}

		else
		{
			_outputValue = 0;
			return _outputValue;
		}
	}
}

void Neuron::countNewWeights(int rightAnswer, int neuronAnswer, int* inputArray)
{
	_synapses[0] += _learningCoefficient * (rightAnswer - neuronAnswer);

	for (int i = 1; i < getDendritesAmount(); i++)
	{
		_synapses[i] += _learningCoefficient * (rightAnswer - neuronAnswer) * inputArray[i-1];
	}
}

//private methods

double Neuron::countFirstWeight()
{
	double weight = ((double)rand() / (RAND_MAX));
	return weight;
}