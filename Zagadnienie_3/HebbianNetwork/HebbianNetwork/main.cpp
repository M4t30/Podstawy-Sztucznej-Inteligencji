#include <iostream>
#include <vector>
#include "Layer.h"
#include <time.h>
#include <fstream>
using namespace std;

void setInputValue(Neuron& neuron, vector< vector<double> > inputData, int numberOfOutputs, int numberOfEntrances, int inputDataRow);
void learn(Layer& layer, vector< vector<double> > inputData);
void test(Layer& layer, vector< vector<double> > inputData);
void readLearningData(vector< vector<double> > &learningInputData, int numberOfEntrances, int amountOfOutputs);
void readTestingData(vector< vector<double> > &testingInputData, int numberOfEntrances, int amountOfOutputs);

fstream OUTPUT_LEARNING_FILE;
fstream OUTPUT_TESTING_FILE;
fstream LEARNING_DATA;
fstream TESTING_DATA;

int main()
{
	srand(time(NULL));
	vector< vector<double> > learningInputData;
	vector< vector<double> > testingInputData;

	int numberOfNeurons = 20;
	int numberOfEntrances = 21;
	int numberOfOutputs = 1;
	double learningCoefficient = 0.01;
	double forgettingCoefficient = 0.001;
	Layer hebbianNetwork(numberOfNeurons, numberOfEntrances, numberOfOutputs, learningCoefficient, forgettingCoefficient);
	
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

			for (int epochNumber = 1, i = 0; i < 80; i++, epochNumber++)
			{
				learn(hebbianNetwork, learningInputData);
				OUTPUT_LEARNING_FILE << hebbianNetwork.neurons[2].getSynapse(2) << endl;
				//OUTPUT_LEARNING_FILE << "EPOCH NUMBER: " << epochNumber << endl;
			}

			break;

		case 2:
			OUTPUT_TESTING_FILE.open("output_testing_data.txt", ios::out);
			test(hebbianNetwork, testingInputData);
			break;

		case 3:
			OUTPUT_LEARNING_FILE.close();
			OUTPUT_TESTING_FILE.close();
			return 0;
		}

	} while (true);

	return 0;
}

void setInputValue(Neuron& neuron, vector< vector<double> > inputData, int numberOfOutputs, int numberOfEntrances, int row)
{
	for (int i = 0; i < numberOfEntrances; i++)
		neuron.setInput(i, inputData[row][i]);
}

void learn(Layer& layer, vector< vector<double> > inputData)
{
	for (int inputDataRow = 0; inputDataRow < inputData.size(); inputDataRow++)
	{
		for (int i = 0; i < layer.getNumberOfNeurons(); i++)
		{
			setInputValue(layer.neurons[i], inputData, layer.getNumberOfNeurons(), layer.neurons[i].getDendritesAmount(), inputDataRow);
			layer.neurons[i].sumOfInputs();
			layer.neurons[i].processOutput();
			layer.neurons[i].countNewWeights();
		}
	}
}

void test(Layer& layer, vector< vector<double> > inputData)
{
	for (int inputDataRow = 0; inputDataRow < inputData.size(); inputDataRow++)
	{
		for (int i = 0; i < layer.getNumberOfNeurons(); i++)
		{
			setInputValue(layer.neurons[i], inputData, layer.getNumberOfNeurons(), layer.neurons[i].getDendritesAmount(), inputDataRow);
			layer.neurons[i].sumOfInputs();
			layer.neurons[i].processOutput();
		}

		layer.gatherAnswers();
		
		for (int i = 0; i < layer.getNumberOfNeurons(); i++)
			OUTPUT_TESTING_FILE << layer.neurons[i].getOutputValue() << " ";
		
		OUTPUT_TESTING_FILE << endl;
	}
}

void readLearningData(vector< vector<double> > &learningInputData, int numberOfEntrances, int amountOfOutputs)
{
	LEARNING_DATA.open("learning_data.txt", ios::in);
	vector<double> row;

	do
	{
		row.clear();

		for (int i = 0, inputTmp = 0; i < numberOfEntrances; i++)
		{
			LEARNING_DATA >> inputTmp;
			row.push_back(inputTmp);
		}

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

		for (int i = 0, inputTmp; i < numberOfEntrances; i++)
		{
			TESTING_DATA >> inputTmp;
			row.push_back(inputTmp);
		}

		testingInputData.push_back(row);
	}
	TESTING_DATA.close();
}
