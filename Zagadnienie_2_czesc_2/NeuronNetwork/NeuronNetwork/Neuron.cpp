#include "Neuron.h"
#include <time.h>
#include <math.h>

Neuron::Neuron()
{
	_dendrites.resize(0);
	_synapses.resize(0);
	_previousWeights.resize(0);
	_sumOfAllInputs = 0;
	_outputValue = 0;
	_learningCoefficient = 0;
	_inertiaCoefficient = 0;
}

Neuron::Neuron(int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double inertiaCoefficient)
{
	createInputs(amountOfDendrites, amountOfOutputs);
	_learningCoefficient = learningCoefficient;
	_inertiaCoefficient = inertiaCoefficient;
	_sumOfAllInputs = 0;
	_outputValue = 0;
}

void Neuron::createInputs(int amountOfDendrites, int amountOfOutputs)
{
	double weight = _countFirstWeight();

	for (int j = 0; j < amountOfDendrites; j++)
	{
		_dendrites.push_back(0);
		_previousWeights.push_back(0);
		_synapses.push_back(_countFirstWeight());
	}
}

void Neuron::sumOfInputs()
{
	_sumOfAllInputs = 0.0;

	for (int i = 0; i < getDendritesAmount(); i++)		
		_sumOfAllInputs += processSingleInput(i);
}

void Neuron::processOutput(bool testing)
{
	if (testing == true)
	{
		if (_sumOfAllInputs > 0)	
			_outputValue = 1;
			
		else
			_outputValue = 0;	
	}

	else
	{
		double beta = 2.0;
		_outputValue = (1.0 / (1.0 + (exp(-beta * _sumOfAllInputs))));
	}
}

void Neuron::countNewWeights()
{
	for (int i = 0; i < getDendritesAmount(); i++)
		_synapses[i] += _inertiaCoefficient * _learningCoefficient * _errorSignal * (_outputValue * (1 - _outputValue) * _dendrites[i]);
}

//private methods
double Neuron::_countFirstWeight()
{
	double max = 0.5;
	double min = -0.5;
	double weight = ((double(rand()) / double(RAND_MAX)) * (max - min)) + min;
	return weight;
}