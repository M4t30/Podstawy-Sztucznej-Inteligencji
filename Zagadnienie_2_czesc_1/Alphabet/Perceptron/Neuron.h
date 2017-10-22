#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Neuron
{
public:
	void createInputs(int amountOfDendrites, int amountOfSynapses); 
	void createDendrite() { _dendrites.push_back(0); } 
	void createSynapse(int index) { _synapses[index].push_back(0); } 
	int getDendritesAmount() { return _dendrites.size(); } 
	int getSynapsesAmount() { return _synapses.size(); }
	double getInput(int index) { return _dendrites[index]; } 
	void setInput(int index, double value) { _dendrites[index] = value;	} 
	double getSynapse(int index1, int index2) { return  _synapses[index1][index2]; } 
	void setSynapse(int synapseIndex, int index, double value) { _synapses[synapseIndex][index] = value; } 
	double getSumOfAllInputs(int index) { return _sumOfAllInputs[index]; }
	double* getOutputValue() { return _outputValue; }
	double getOutputValue(int index){ return _outputValue[index]; }
	double processSingleInput(int index, int synapseIndex) { return _dendrites[index] * _synapses[synapseIndex][index]; } 
	void sumOfInputs(); 
	void processOutput(bool secondAlgorithm, bool testing); 
	void countNewWeights(int rightAnswer, int neuronAnswer, int *inputArray, int inputNumber, bool secondAlgorithm);
	
	Neuron(int amountOfDendrites, int amountOfSynapses, double learningCoefficient)
	{
		createInputs(amountOfDendrites, amountOfSynapses);
		_learningCoefficient = learningCoefficient;
		_sumOfAllInputs = new double[amountOfSynapses];
		_outputValue = new double[amountOfSynapses];
	}

private:
	double countFirstWeight();
	vector<double> _dendrites; //inputs
	vector< vector<double> > _synapses; //weights
	double *_sumOfAllInputs;
	double *_outputValue;
	double _learningCoefficient;
	int _size;
};