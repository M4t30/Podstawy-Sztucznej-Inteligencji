#pragma once
#include<vector>
#include"Neuron.h"
using namespace std;

class Layer
{
public:
	Layer(int numberOfNeurons, int amountOfDendrites, int amountOfOutputs, double learningCoefficient, double numberOfIterations);
	vector<Neuron> neurons;
	int getNumberOfNeurons() { return _numberOfNeurons; }
	void changeNeuronWeight(double currentIteration, bool testing);
	double getScalarProduct(int index) { return _scalarProducts[index]; }
	void gatherScalarProducts();
	int getWinnerNeuronIndex() { return _winnerNeuronIndex; }

private:
	void foundMaxScalarProduct();
	int _numberOfNeurons;
	vector<double> _scalarProducts;
	int _winnerNeuronIndex;
	double _mapRadius;
	double _timeConstant;
};