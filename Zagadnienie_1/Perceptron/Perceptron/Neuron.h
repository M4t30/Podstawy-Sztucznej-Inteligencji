#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Neuron
{
public:
	void createInputs(int amount); 
	void createDendrite() { _dendrites.push_back(0); } 
	void createSynapse() { _synapses.push_back(0); } 
	int getDendritesAmount() { return _dendrites.size(); } 
	double getInput(int index) { return _dendrites[index]; } 
	void setInput(int index, double value) { _dendrites[index] = value;	} 
	double getSynapse(int index) { return  _synapses[index]; } 
	void setSynapse(int index, double value) { _synapses[index] = value; } 
	double getSumOfAllInputs() { return _sumOfAllInputs; }
	int getOutputValue(){ return _outputValue; }
	double processSingleInput(int index) { return _dendrites[index] * _synapses[index]; } 
	void sumOfInputs(); 
	int processOutput(); 
	void countNewWeights(int rightAnswer, int neuronAnswer, int *inputArray);
	
	Neuron(int amount, double learningCoefficient)
	{
		createInputs(amount);
		_learningCoefficient = learningCoefficient;
	}

private:
	double countFirstWeight();
	vector<double> _dendrites; //inputs
	vector<double> _synapses; //weights
	double _sumOfAllInputs;
	int _outputValue;
	double _learningCoefficient;
	int _size;
};