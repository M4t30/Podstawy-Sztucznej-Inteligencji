#include"Layer.h"

Layer::Layer(int numberOfNeurons, int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double inertiaCoefficient)
{
	_numberOfNeurons = numberOfNeurons;
	_learningCoefficient = learningCoefficient;

	neurons.resize(numberOfNeurons);

	for (int i = 0; i < numberOfNeurons; i++)
		neurons[i].Neuron::Neuron(amountOfDendrites, amountOfOutputs, _learningCoefficient, inertiaCoefficient);
}

void Layer::gatherAnswers()
{
	_answers.clear();

	for (int i = 0; i < _numberOfNeurons; i++)
		_answers.push_back(neurons[i].getOutputValue());
}