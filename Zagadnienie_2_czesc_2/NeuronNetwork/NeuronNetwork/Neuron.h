#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Neuron
{
public:
	void createInputs(int amountOfDendrites, int amountOfSynapses);
	void createDendrite() { _dendrites.push_back(0); }
	void createSynapse(int index) { _synapses.push_back(0); }
	int getDendritesAmount() { return _dendrites.size(); }
	int getSynapsesAmount() { return _synapses.size(); }
	double getInput(int index) { return _dendrites[index]; }
	void setInput(int index, double value) { _dendrites[index] = value; }
	double getSynapse(int index) { return  _synapses[index]; }
	void setSynapse(int index, double value) { _synapses[index] = value; }
	double getSumOfAllInputs() { return _sumOfAllInputs; }
	double getOutputValue() { return _outputValue; }
	double processSingleInput(int index) { return _dendrites[index] * _synapses[index]; }
	void sumOfInputs();
	void processOutput(bool testing);
	void countNewWeights();
	void setErrorSignal(double errorSignal) { _errorSignal = errorSignal; }
	double getErrorSignal() { return _errorSignal; }

	Neuron();
	Neuron(int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double inertiaCoefficient);

private:
	double _countFirstWeight();
	vector<double> _dendrites; //inputs
	vector<double> _synapses; //weights
	vector<double> _previousWeights;
	double _sumOfAllInputs;
	double _outputValue;
	double _learningCoefficient;
	double _inertiaCoefficient;
	double _errorSignal;
};
