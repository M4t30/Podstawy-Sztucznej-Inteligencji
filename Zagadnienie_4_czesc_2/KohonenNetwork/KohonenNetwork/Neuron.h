#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Neuron
{
public:
	void createInputs(int amountOfDendrites, int amountOfSynapses);
	void createInput() { _inputs.push_back(0); }
	void createWeight(int index) { _weights.push_back(0); }
	int getInputsAmount() { return _inputs.size(); }
	int getWeightsAmount() { return _weights.size(); }
	double getInput(int index) { return _inputs[index]; }
	void setInput(int index, double value) { _inputs[index] = value; }
	double getSynapse(int index) { return  _weights[index]; }
	void setSynapse(int index, double value) { _weights[index] = value; }
	double getSumOfAllInputs() { return _sumOfAllInputs; }
	double getOutputValue() { return _outputValue; }
	double processSingleInput(int index) { return _inputs[index] * _weights[index]; }
	void processOutput();
	void countNewWeights();
	double countScalarProduct();
	void countNeighbourhoodRadius(double mapRadius, double currentIteration, double timeConstant);
	double getNeighbourhoodRadius() { return _neighbourhoodRadius; }
	void setNeighbourhoodRadius(double neighbourhoodRadius) {_neighbourhoodRadius = neighbourhoodRadius; }
	void setDistance(double distance) { _distance = distance; }
	Neuron();
	Neuron(int amountOfDendrites, int amountOfOutputs, double learningCoefficient);

private:
	double countFirstWeight();
	void countNeighbourhoodFunction();
	void normalizeWeights();
	vector<double> _inputs;
	vector<double> _weights;
	double _sumOfAllInputs;
	double _outputValue;
	double _learningCoefficient;
	double _neighbourhoodFunctionValue;
	double _distance;
	double _neighbourhoodRadius;
};
