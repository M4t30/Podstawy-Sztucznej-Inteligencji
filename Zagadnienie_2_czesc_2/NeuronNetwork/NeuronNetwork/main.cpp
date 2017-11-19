#include <iostream>
#include <vector>
#include "Layer.h"
#include <time.h>
#include <fstream>
using namespace std;

void setInputValue(Neuron& neuron, vector< vector<int> > inputData, vector< vector<double> > neuronAnswers, int numberOfOutputs, int numberOfEntrances, int numberOfLayer, int inputDataRow);
void learn(vector<Layer>& layers, vector< vector<int> > inputData);
void backpropagationFunction(vector<Layer>& layers);
void test(vector<Layer>& layers, vector< vector<int> > inputData);
void readLearningData(vector< vector<int> > &learningInputData, int numberOfEntrances, int amountOfOutputs);
void readTestingData(vector< vector<int> > &testingInputData, int numberOfEntrances, int amountOfOutputs);

fstream OUTPUT_LEARNING_FILE;
fstream OUTPUT_TESTING_FILE;
fstream LEARNING_DATA;
fstream TESTING_DATA;
double E;
double E_MAX = 0.5;
double E_TESTING;
int BAD_ANSWERS_AMOUNT;
int TOTAL_BAD_ANSWERS_AMOUNT;
int RIGHT_ANSWERS_AMOUNT;
int TOTAL_RIGHT_ANSWERS_AMOUNT;
int NUMBER_OF_CORRECT_ANSWERS;
int *CORRECT_ANSWERS;

int main()
{
	srand(time(NULL));
	vector<Layer> layers;
	vector< vector<int> > learningInputData;
	vector< vector<int> > testingInputData;
	vector< vector<double> > neuronAnswers;

	int numberOfNeuronsInFirstLayer = 20;
	int numberOfNeuronsInSecondLayer = 10;
	int numberOfNeuronsInThirdLayer = 20;
	int numberOfEntrancesInFirstLayer = 21;
	int numberOfEntrancesInSecondLayer = 21;
	int numberOfEntrancesInThirdLayer = 11;
	int numberOfOutputs = 1;
	double learningCoefficient = 0.8;
	double inertiaCoefficient = 1.4;
	
	layers.push_back(Layer::Layer(numberOfNeuronsInFirstLayer, numberOfEntrancesInFirstLayer, numberOfOutputs, learningCoefficient, inertiaCoefficient));
	layers.push_back(Layer::Layer(numberOfNeuronsInSecondLayer, numberOfEntrancesInSecondLayer, numberOfOutputs, learningCoefficient, inertiaCoefficient));
	layers.push_back(Layer::Layer(numberOfNeuronsInThirdLayer, numberOfEntrancesInThirdLayer, numberOfOutputs, learningCoefficient, inertiaCoefficient));

	readLearningData(learningInputData, numberOfEntrancesInFirstLayer, numberOfOutputs);
	readTestingData(testingInputData, numberOfEntrancesInFirstLayer, numberOfOutputs);

	CORRECT_ANSWERS = new int[NUMBER_OF_CORRECT_ANSWERS];

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
			
			for (int epochNumber = 1; ;)
			{
				learn(layers, learningInputData);
				OUTPUT_LEARNING_FILE << "EPOCH NUMBER: " << epochNumber << " E: " << E << endl;
				if (E < E_MAX)
					break;

				epochNumber++;

				E = 0;
			}

			break;

		case 2:
			OUTPUT_TESTING_FILE.open("output_testing_data.txt", ios::out);
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMOUNT = 0;
			E_TESTING = 0;
			test(layers, testingInputData);
			OUTPUT_TESTING_FILE << "Bad answers amount: " << BAD_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_FILE << "Right answers amount: " << RIGHT_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_FILE << "E: " << E_TESTING << endl;
			break;

		case 3:
			OUTPUT_LEARNING_FILE.close();
			OUTPUT_TESTING_FILE.close();
			return 0;
		}

	} while (true);

	return 0;
}

void setInputValue(Neuron& neuron, vector< vector<int> > inputData, vector<double> neuronAnswers, int numberOfOutputs, int numberOfEntrances, int numberOfLayer, int row)
{
	for (int i = 0; i < numberOfEntrances; i++)
	{
		if (numberOfLayer == 0)
			neuron.setInput(i, inputData[row][i]);

		else
		{
			if (i == 0)
				neuron.setInput(i, 1);

			else
				neuron.setInput(i, neuronAnswers[i - 1]);
		}
	}

	if (numberOfLayer == 2)
	{
		for (int i = 0, j = (inputData[0].size() - numberOfOutputs); i < NUMBER_OF_CORRECT_ANSWERS; i++, j++)
			CORRECT_ANSWERS[i] = inputData[row][j];
	}
}

void backpropagationFunction(vector<Layer>& layers)
{
	for (int layerIndex = (layers.size() - 1); layerIndex >= 0; layerIndex--)
	{
		for (int i = 0; i < layers[layerIndex].getNumberOfNeurons(); i++)
		{
			if (layerIndex == (layers.size() - 1))
				layers[layerIndex].neurons[i].setErrorSignal(CORRECT_ANSWERS[i] - layers[layerIndex].neurons[i].getOutputValue());

			else
			{
				double errorSignal = 0.0;

				for (int j = 0; j < layers[layerIndex + 1].getNumberOfNeurons(); j++)
					errorSignal += layers[layerIndex + 1].neurons[j].getErrorSignal() * layers[layerIndex + 1].neurons[j].getSynapse(i + 1);

 				layers[layerIndex].neurons[i].setErrorSignal(errorSignal);
			}
		}
	}
}

void learn(vector<Layer>& layers, vector< vector<int> > inputData)
{
	for (int inputDataRow = 0; inputDataRow < inputData.size(); inputDataRow++)
	{
		for (int layerIndex = 0; layerIndex < layers.size(); layerIndex++)
		{
			for (int i = 0; i < layers[layerIndex].getNumberOfNeurons(); i++)
			{
				setInputValue(layers[layerIndex].neurons[i], inputData, layers[(layerIndex > 0) ? (layerIndex - 1) : 0].getAnswers(), layers[layerIndex].getNumberOfNeurons(), layers[layerIndex].neurons[i].getDendritesAmount(), layerIndex, inputDataRow);
				layers[layerIndex].neurons[i].sumOfInputs();
				layers[layerIndex].neurons[i].processOutput(false);
			}
			layers[layerIndex].gatherAnswers();

			if (layerIndex == (layers.size() - 1))
				for (int i = 0; i < layers[layers.size() - 1].getNumberOfNeurons(); i++)
					E += 0.5 * pow(((double)CORRECT_ANSWERS[i] - layers[layers.size() - 1].getAnswer(i)), 2);
		}


		backpropagationFunction(layers);

		for (int layerIndex = 0; layerIndex < layers.size(); layerIndex++)
			for (int i = 0; i < layers[layerIndex].getNumberOfNeurons(); i++)
				layers[layerIndex].neurons[i].countNewWeights();
	}
}

void test(vector<Layer>& layers, vector< vector<int> > inputData)
{
	for (int inputDataRow = 0; inputDataRow < inputData.size(); inputDataRow++)
	{
		for (int layerIndex = 0; layerIndex < layers.size(); layerIndex++)
		{
			for (int i = 0; i < layers[layerIndex].getNumberOfNeurons(); i++)
			{
				setInputValue(layers[layerIndex].neurons[i], inputData, layers[(layerIndex > 0) ? (layerIndex - 1) : 0].getAnswers(), layers[layerIndex].getNumberOfNeurons(), layers[layerIndex].neurons[i].getDendritesAmount(), layerIndex, inputDataRow);
				layers[layerIndex].neurons[i].sumOfInputs();
				if (layerIndex != (layers.size() - 1))
					layers[layerIndex].neurons[i].processOutput(false);

				else
					layers[layerIndex].neurons[i].processOutput(true);
			}

			layers[layerIndex].gatherAnswers();
		}

		for (int i = 0; i < layers[layers.size() - 1].getNumberOfNeurons(); i++)
		{
			if (layers[layers.size() - 1].getAnswer(i) == CORRECT_ANSWERS[i])
			{
				RIGHT_ANSWERS_AMOUNT++;
				E_TESTING += 0.5 * pow(((double)CORRECT_ANSWERS[i] - layers[layers.size() - 1].getAnswer(i)), 2);
				OUTPUT_TESTING_FILE << layers[layers.size() - 1].neurons[i].getOutputValue() << " + ";
			}

			else
			{
				BAD_ANSWERS_AMOUNT++;
				E_TESTING += 0.5 * pow(((double)CORRECT_ANSWERS[i] - layers[layers.size() - 1].getAnswer(i)), 2);
				OUTPUT_TESTING_FILE << layers[layers.size() - 1].neurons[i].getOutputValue() << " - ";
			}
		}

		OUTPUT_TESTING_FILE << endl;
	}
}

void readLearningData(vector< vector<int> > &learningInputData, int numberOfEntrances, int amountOfOutputs)
{
	LEARNING_DATA.open("learning_data.txt", ios::in);
	vector<int> row;

	do 
	{
		row.clear();

		for (int i = 0, inputTmp = 0; i < numberOfEntrances; i++)
		{
			LEARNING_DATA >> inputTmp;
			row.push_back(inputTmp);
		}

		for (int i = 0, answerTmp; i < (numberOfEntrances - 1); i++)
		{
			LEARNING_DATA >> answerTmp;
			row.push_back(answerTmp);
		}

		learningInputData.push_back(row);
	}while (!LEARNING_DATA.eof());

	NUMBER_OF_CORRECT_ANSWERS = row.size() / 2;

	LEARNING_DATA.close();
}

void readTestingData(vector< vector<int> > &testingInputData, int numberOfEntrances, int amountOfOutputs)
{
	TESTING_DATA.open("testing_data.txt", ios::in);
	vector<int> row;

	while (!TESTING_DATA.eof())
	{
		row.clear();

		for (int i = 0, inputTmp; i < numberOfEntrances; i++)
		{
			TESTING_DATA >> inputTmp;
			row.push_back(inputTmp);
		}

		for (int i = 0, answerTmp; i < (numberOfEntrances - 1); i++)
		{
			TESTING_DATA >> answerTmp;
			row.push_back(answerTmp);
		}

		testingInputData.push_back(row);
	}
	TESTING_DATA.close();
}
