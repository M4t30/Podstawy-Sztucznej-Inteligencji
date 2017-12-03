#include"Layer.h"

Layer::Layer(int numberOfNeurons, int amountOfDendrites, int amountOfOutputs, double learningCoefficient)
{
	_numberOfNeurons = numberOfNeurons;
	neurons.resize(numberOfNeurons);

	for (int i = 0; i < numberOfNeurons; i++)
		neurons[i].Neuron::Neuron(amountOfDendrites, amountOfOutputs, learningCoefficient);
}

void Layer::changeNeuronWeight(bool testing)
{
	gatherScalarProducts();
	foundMaxScalarProduct(testing);
}

void Layer::gatherScalarProducts()
{
	_scalarProducts.clear();

	for (int i = 0; i < _numberOfNeurons; i++)
		_scalarProducts.push_back(neurons[i].countScalarProduct());
}

void Layer::foundMaxScalarProduct(bool testing)
{
	double tmp = _scalarProducts[0];
	_winnerNeuronIndex = 0;

	for (int i = 1; i < _scalarProducts.size(); i++)
	{
		if (tmp < _scalarProducts[i])
		{
			_winnerNeuronIndex = i;
			tmp = _scalarProducts[i];
		}
	}

	neurons[_winnerNeuronIndex].processOutput();
	if (testing == false)
		neurons[_winnerNeuronIndex].countNewWeights();
}
