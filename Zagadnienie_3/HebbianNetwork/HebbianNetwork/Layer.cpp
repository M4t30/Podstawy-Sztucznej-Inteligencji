#include"Layer.h"

Layer::Layer(int numberOfNeurons, int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double forgettingCoefficient)
{
	_numberOfNeurons = numberOfNeurons;
	neurons.resize(numberOfNeurons);

	for (int i = 0; i < numberOfNeurons; i++)
		neurons[i].Neuron::Neuron(amountOfDendrites, amountOfOutputs, learningCoefficient, forgettingCoefficient);
}

void Layer::gatherAnswers()
{
	_answers.clear();

	for (int i = 0; i < _numberOfNeurons; i++)
		_answers.push_back(neurons[i].getOutputValue());
}