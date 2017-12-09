#include "Neuron.h"
#include <time.h>
#include <math.h>

Neuron::Neuron()
{
	_inputs.resize(0);
	_weights.resize(0);
	_sumOfAllInputs = 0.0;
	_outputValue = 0.0;
	_learningCoefficient = 0.0;
}

Neuron::Neuron(int amountOfDendrites, int amountOfOutputs, double learningCoefficient)
{
	createInputs(amountOfDendrites, amountOfOutputs);
	normalizeWeights();
	_learningCoefficient = learningCoefficient;
	_sumOfAllInputs = 0.0;
	_outputValue = 0.0;
}

void Neuron::createInputs(int amountOfDendrites, int amountOfOutputs)
{
	for (int j = 0; j < amountOfDendrites; j++)
	{
		_inputs.push_back(0);
		_weights.push_back(countFirstWeight());
	}
}

double Neuron::countScalarProduct()
{
	_sumOfAllInputs = 0.0;

	for (int i = 0; i < getInputsAmount(); i++)
		_sumOfAllInputs += pow(_inputs[i] - _weights[i],2);

	_sumOfAllInputs = sqrt(_sumOfAllInputs);
	return _sumOfAllInputs;
}

void Neuron::processOutput()
{
	double beta = 1.0;
	_outputValue = (1.0 / (1.0 + (exp(-beta * _sumOfAllInputs))));
}

void Neuron::countNewWeights()
{
	countNeighbourhoodFunction();
	for (int i = 0; i < getWeightsAmount(); i++)
		_weights[i] = _weights[i] + (_learningCoefficient * _neighbourhoodFunctionValue * (_inputs[i] - _weights[i]));

	normalizeWeights();
}

void Neuron::countNeighbourhoodRadius(double mapRadius, double currentIteration, double timeConstant)
{
	_neighbourhoodRadius = mapRadius * exp(-currentIteration / timeConstant);
}

//private methods

void Neuron::countNeighbourhoodFunction()
{
	_neighbourhoodFunctionValue = exp(pow(-_distance,2) / (2 * pow(_neighbourhoodRadius,2)));
}

double Neuron::countFirstWeight()
{
	double max = 1.0;
	double min = 0.0;
	double weight = ((double(rand()) / double(RAND_MAX)) * (max - min)) + min;
	return weight;
}

void Neuron::normalizeWeights()
{
	double vectorLength = 0.0;

	for (int i = 0; i < getWeightsAmount(); i++)
		vectorLength += pow(_weights[i], 2);

	vectorLength = sqrt(vectorLength);

	for (int i = 0; i < getWeightsAmount(); i++)
		_weights[i] /= vectorLength;
}