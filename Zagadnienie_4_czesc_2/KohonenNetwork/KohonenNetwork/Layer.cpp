#include"Layer.h"

Layer::Layer(int numberOfNeurons, int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double numberOfIterations)
{
	_numberOfNeurons = numberOfNeurons;
	neurons.resize(numberOfNeurons);
	_mapRadius = (double)numberOfNeurons;
	_timeConstant = numberOfIterations / _mapRadius;

	for (int i = 0; i < numberOfNeurons; i++)
		neurons[i].Neuron::Neuron(amountOfDendrites, amountOfOutputs, learningCoefficient);
}

void Layer::changeNeuronWeight(double currentIteration, bool testing)
{
	gatherScalarProducts();
	foundMaxScalarProduct();
	neurons[_winnerNeuronIndex].processOutput();
	if (testing == false)
	{
		neurons[_winnerNeuronIndex].countNeighbourhoodRadius(_mapRadius, currentIteration, _timeConstant);
		int radius = neurons[_winnerNeuronIndex].getNeighbourhoodRadius();
		int leftBorderNeuronIndex = 0;
		int rightBorderNeuronIndex = 0;

		if (_winnerNeuronIndex - radius < 0)
			leftBorderNeuronIndex = 0;

		else
			leftBorderNeuronIndex = _winnerNeuronIndex - radius;

		if (_winnerNeuronIndex + radius >= _numberOfNeurons)
			rightBorderNeuronIndex = _numberOfNeurons - 1;

		else
			rightBorderNeuronIndex = _winnerNeuronIndex + radius;

		for (int i = leftBorderNeuronIndex; i < rightBorderNeuronIndex; i++)
		{
			neurons[i].setDistance((i < _winnerNeuronIndex) ? (_winnerNeuronIndex - i) : (i - _winnerNeuronIndex));
			neurons[i].setNeighbourhoodRadius(neurons[_winnerNeuronIndex].getNeighbourhoodRadius());
			neurons[i].countNewWeights();
		}
	}
}

void Layer::gatherScalarProducts()
{
	_scalarProducts.clear();

	for (int i = 0; i < _numberOfNeurons; i++)
		_scalarProducts.push_back(neurons[i].countScalarProduct());
}

void Layer::foundMaxScalarProduct()
{
	double tmp = _scalarProducts[0];
	_winnerNeuronIndex = 0;

	for (int i = 1; i < _scalarProducts.size(); i++)
	{
		if (tmp > _scalarProducts[i])
		{
			_winnerNeuronIndex = i;
			tmp = _scalarProducts[i];
		}
	}
}
