#pragma once
#include<vector>
#include"Neuron.h"
using namespace std;

class Layer
{
public:
	Layer(int numberOfNeurons, int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double forgettingCoefficient);
	vector<Neuron> neurons;
	int getNumberOfNeurons() { return _numberOfNeurons; }
	void gatherAnswers();
	vector<double> getAnswers() { return _answers; }
	double getAnswer(int index) { return _answers[index]; }

private:
	int _numberOfNeurons;
	vector<double> _answers;
};