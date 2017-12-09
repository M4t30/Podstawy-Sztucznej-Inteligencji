#include <iostream>
#include <vector>
#include "Layer.h"
#include <time.h>
#include <fstream>
using namespace std;

void setInputValue(Neuron& neuron, vector< vector<double> > inputData, int numberOfEntrances, int inputDataRow);
void learn(Layer& layer, vector< vector<double> > inputData);
void test(Layer& layer, vector< vector<double> > inputData);
void readLearningData(vector< vector<double> > &learningInputData, int numberOfEntrances, int amountOfOutputs);
void readTestingData(vector< vector<double> > &testingInputData, int numberOfEntrances, int amountOfOutputs);

fstream OUTPUT_LEARNING_FILE;
fstream OUTPUT_TESTING_FILE;
fstream OUTPUT_TESTING_NEURON;
fstream LEARNING_DATA;
fstream TESTING_DATA;

int main()
{
	srand(time(NULL));
	vector< vector<double> > learningInputData;
	vector< vector<double> > testingInputData;

	int numberOfNeurons = 20;
	int numberOfEntrances = 20;
	int numberOfOutputs = 1;
	double learningCoefficient = 0.09;
	int numberOfEpochs = 200;
	Layer kohonenNetwork(numberOfNeurons, numberOfEntrances, numberOfOutputs, learningCoefficient, (double)numberOfEpochs);

	readLearningData(learningInputData, numberOfEntrances, numberOfOutputs);
	readTestingData(testingInputData, numberOfEntrances, numberOfOutputs);

	do
	{
		cout << "1. Learn" << endl;
		cout << "2. Test" << endl;
		cout << "3. Exit" << endl;

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			OUTPUT_LEARNING_FILE.open("output_learning_data.txt", ios::out);

			for (int epochNumber = 1, i = 0; i < numberOfEpochs; i++, epochNumber++)
			{
				learn(kohonenNetwork, learningInputData);
				if (epochNumber == 1 || epochNumber == 200)
				OUTPUT_LEARNING_FILE << "EPOCH NUMBER: " << epochNumber << endl;
			}

			break;

		case 2:
			OUTPUT_TESTING_FILE.open("output_testing_data.txt", ios::out);
			OUTPUT_TESTING_NEURON.open("output_testing_neuron.txt", ios::out);
			test(kohonenNetwork, testingInputData);
			break;

		case 3:
			OUTPUT_LEARNING_FILE.close();
			OUTPUT_TESTING_FILE.close();
			return 0;
		}

	} while (true);

	return 0;
}

void setInputValue(Neuron& neuron, vector< vector<double> > inputData, int numberOfEntrances, int row)
{
	for (int i = 0; i < numberOfEntrances; i++)
		neuron.setInput(i, inputData[row][i]);
}

void learn(Layer& layer, vector< vector<double> > inputData)
{
	static int currentIteration = 1;
	for (int inputDataRow = 0; inputDataRow < inputData.size(); inputDataRow++)
	{
		for (int i = 0; i < layer.getNumberOfNeurons(); i++)
		{
			setInputValue(layer.neurons[i], inputData, layer.neurons[i].getInputsAmount(), inputDataRow);
			layer.neurons[i].countScalarProduct();
		}

		layer.changeNeuronWeight(currentIteration, false);
		if (currentIteration == 1 || currentIteration == 200)
		OUTPUT_LEARNING_FILE << inputDataRow << ": " << layer.getWinnerNeuronIndex() << endl;
	}
	currentIteration++;
}

void test(Layer& layer, vector< vector<double> > inputData)
{
	for (int inputDataRow = 0, myDictionary = 0; inputDataRow < inputData.size(); inputDataRow++)
	{
		for (int i = 0; i < layer.getNumberOfNeurons(); i++)
		{
			setInputValue(layer.neurons[i], inputData, layer.neurons[i].getInputsAmount(), inputDataRow);
			layer.neurons[i].countScalarProduct();
		}

		if (inputDataRow == 12 || inputDataRow == 15 || inputDataRow == 16)
			myDictionary++;

		if (inputDataRow == 18)
			myDictionary += 3;
	
		char letter = 'A';
		layer.changeNeuronWeight(0, true);
		OUTPUT_TESTING_FILE << layer.neurons[layer.getWinnerNeuronIndex()].getSumOfAllInputs() << endl;
		OUTPUT_TESTING_NEURON << static_cast<char>(letter + inputDataRow + myDictionary) << " " << layer.getWinnerNeuronIndex() << endl;

	}
}

void readLearningData(vector< vector<double> > &learningInputData, int numberOfEntrances, int amountOfOutputs)
{
	LEARNING_DATA.open("learning_data.txt", ios::in);
	vector<double> row;

	do
	{
		row.clear();

		for (int i = 0; i < numberOfEntrances; i++)
		{
			double inputTmp = 0.0;
			LEARNING_DATA >> (double)inputTmp;
			row.push_back(inputTmp);
		}

		double vectorLength = 0.0;

		for (int i = 0; i < numberOfEntrances; i++)
			vectorLength += pow(row[i], 2);

		vectorLength = sqrt(vectorLength);

		for (int i = 0; i < numberOfEntrances; i++)
			row[i] /= vectorLength;

		learningInputData.push_back(row);

	} while (!LEARNING_DATA.eof());

	LEARNING_DATA.close();
}

void readTestingData(vector< vector<double> > &testingInputData, int numberOfEntrances, int amountOfOutputs)
{
	TESTING_DATA.open("testing_data.txt", ios::in);
	vector<double> row;

	while (!TESTING_DATA.eof())
	{
		row.clear();

		for (int i = 0; i < numberOfEntrances; i++)
		{
			double inputTmp = 0.0;
			TESTING_DATA >> (double)inputTmp;
			row.push_back(inputTmp);
		}

		double vectorLength = 0.0;

		for (int i = 0; i < numberOfEntrances; i++)
			vectorLength += pow(row[i], 2);

		vectorLength = sqrt(vectorLength);

		for (int i = 0; i < numberOfEntrances; i++)
			row[i] /= vectorLength;

		testingInputData.push_back(row);
	}

	TESTING_DATA.close();
}
