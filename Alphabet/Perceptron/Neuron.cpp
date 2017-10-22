#include "Neuron.h"
#include <time.h>
#include <math.h>

void Neuron::createInputs(int amountOfDendrites, int amountOfSynapses) 
{
	double weight = countFirstWeight();
	vector<double> row;
	
	for (int i = 0; i < amountOfSynapses; i++)
	{
		row.clear();
		for (int j = 0; j < amountOfDendrites; j++)
		{
			if (i == 0)
			{
				_dendrites.push_back(0);
			}

			row.push_back(countFirstWeight());
		}
		_synapses.push_back(row);
	}
}

void Neuron::sumOfInputs()
{
	double *sum = new double[getSynapsesAmount()];

	for (int i = 0; i < getSynapsesAmount(); i++)
	{
		sum[i] = 0;

		for (int j = 0; j < getDendritesAmount(); j++)
		{
			sum[i] += processSingleInput(j, i);
		}
		
		_sumOfAllInputs[i] = sum[i];
	}
}

void Neuron::processOutput(bool secondAlgorithm, bool testing) 
{
	if (secondAlgorithm == false || testing == true)
	{
		for (int i = 0; i < getSynapsesAmount(); i++)
		{
			if (_sumOfAllInputs[i] > 0)
			{
				_outputValue[i] = 1;
			}

			else
			{
				_outputValue[i] = 0;
			}
		}
	}

	else // second algorithm
	{
		double functionCoefficient = 1;
		for (int i = 0; i < getSynapsesAmount(); i++)
		{
			_outputValue[i] = (1.0 / (1.0 + (exp(-functionCoefficient * _sumOfAllInputs[i]))));
		}
	}
}

void Neuron::countNewWeights(int rightAnswer, int neuronAnswer, int* inputArray, int inputNumber, bool secondAlgorithm)
{
	if (secondAlgorithm == false)
	{
		_synapses[inputNumber][0] += _learningCoefficient * (rightAnswer - neuronAnswer);

		for (int j = 1; j < getDendritesAmount(); j++)
		{
			_synapses[inputNumber][j] += _learningCoefficient * (rightAnswer - neuronAnswer) * inputArray[j];
		}
	}

	else // second algorithm
	{
		_synapses[inputNumber][0] += _learningCoefficient * (rightAnswer - _outputValue[inputNumber]);

		for (int j = 1; j < getDendritesAmount(); j++)
		{
			_synapses[inputNumber][j] += _learningCoefficient * (rightAnswer - _outputValue[inputNumber] ) * (_outputValue[inputNumber] * (1 - _outputValue[inputNumber])) *inputArray[j];
		}
	}
}

//private methods

double Neuron::countFirstWeight()
{
	double max = 1.0;
	double min = -1.0;
	double weight = ((double(rand()) / double(RAND_MAX)) * (max - min)) + min;
	return weight;
}