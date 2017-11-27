#include "Neuron.h"
#include <time.h>
#include <math.h>

Neuron::Neuron()
{
	_dendrites.resize(0);
	_synapses.resize(0);
	_sumOfAllInputs = 0.0;
	_outputValue = 0.0;
	_learningCoefficient = 0.0;
	_forgettingCoefficient = 0.0;
}

Neuron::Neuron(int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double forgettingCoefficient)
{
	createInputs(amountOfDendrites, amountOfOutputs);
	_learningCoefficient = learningCoefficient;
	_forgettingCoefficient = forgettingCoefficient;
	_sumOfAllInputs = 0.0;
	_outputValue = 0.0;
}

void Neuron::createInputs(int amountOfDendrites, int amountOfOutputs)
{
	for (int j = 0; j < amountOfDendrites; j++)
	{
		_dendrites.push_back(0);
		_synapses.push_back(_countFirstWeight());
	}
}

void Neuron::sumOfInputs()
{
	_sumOfAllInputs = 0.0;

	for (int i = 0; i < getDendritesAmount(); i++)
		_sumOfAllInputs += processSingleInput(i);
}

void Neuron::processOutput()
{
	if (_sumOfAllInputs > 0)
		_outputValue = 1.0;

	else
		_outputValue = 0.0;
}

void Neuron::countNewWeights()
{
	for (int i = 0; i < getDendritesAmount(); i++)
		_synapses[i] = _synapses[i] * (1.0 - _forgettingCoefficient) + _learningCoefficient * _dendrites[i] * _outputValue;
}

//private methods
double Neuron::_countFirstWeight()
{
	double max = 1.0;
	double min = -1.0;
	double weight = ((double(rand()) / double(RAND_MAX)) * (max - min)) + min;
	return weight;
}