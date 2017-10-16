#include <iostream>
#include <vector>
#include "Neuron.h"
#include <time.h>
#include <fstream>
using namespace std;

void setInputValue(Neuron& neuron, bool testing);
void learn(Neuron& neuron, bool testing);

fstream OUTPUT_LEARNING_FILE;
fstream OUTPUT_TESTING_FILE;
fstream LEARNING_DATA;
fstream TESTING_DATA;
int BAD_ANSWERS_AMOUNT;
int RIGHT_ANSWERS_AMMOUNT;
int CORRECT_ANSWER;

int main()
{
	srand(time(NULL));
	Neuron neuron(3, 0.00999);
	OUTPUT_LEARNING_FILE.open("output_learning_data.txt", ios::out);
	OUTPUT_TESTING_FILE.open("output_testing_data.txt", ios::out);
	LEARNING_DATA.open("learning_data.txt", ios::in);
	TESTING_DATA.open("testing_data.txt", ios::in);

	do
	{
		cout << "1. Learn" << endl;
		cout << "2. Test " << endl;
		cout << "3. Exit" << endl;

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			int loopIteration;
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMMOUNT = 0;
			cout << "Enter number of loops: " << endl;
			cin >> loopIteration;
			
			for (int i = 0; i < loopIteration; i++)
			{
				learn(neuron, false);
			}

			OUTPUT_LEARNING_FILE << "Bad answers amount: " << BAD_ANSWERS_AMOUNT << endl;
			OUTPUT_LEARNING_FILE << "Right answers amount: " << RIGHT_ANSWERS_AMMOUNT << endl;
			break;

		case 2:
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMMOUNT = 0;
			
			for (int i = 0; i < 50; i++)
			{
				learn(neuron, true);
			}

			OUTPUT_TESTING_FILE << "Bad answers amount: " << BAD_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_FILE << "Right answers amount: " << RIGHT_ANSWERS_AMMOUNT << endl;
			break;

		case 3:
			OUTPUT_LEARNING_FILE.close();
			OUTPUT_TESTING_FILE.close();
			TESTING_DATA.close();
			LEARNING_DATA.close();

			return 0;
		}
	} while (true);

	return 0;
}

void setInputValue(Neuron& neuron, bool testing)
{
	if (testing == false)
	{
		int input1, input2, input3, answer;
		LEARNING_DATA >> input1;
		LEARNING_DATA >> input2;
		LEARNING_DATA >> input3;
		LEARNING_DATA >> answer;

		neuron.setInput(0, input1);
		neuron.setInput(1, input2);
		neuron.setInput(2, input3);
		CORRECT_ANSWER = answer;

		OUTPUT_LEARNING_FILE << "IN 0b: " << neuron.getInput(0);
		OUTPUT_LEARNING_FILE << " IN 1: " << neuron.getInput(1);
		OUTPUT_LEARNING_FILE << " IN 2: " << neuron.getInput(2);
		OUTPUT_LEARNING_FILE << " RA: " << CORRECT_ANSWER;
	}

	else
	{
		int input1, input2, input3, answer;
		TESTING_DATA >> input1;
		TESTING_DATA >> input2;
		TESTING_DATA >> input3;
		TESTING_DATA >> answer;

		neuron.setInput(0, input1);
		neuron.setInput(1, input2);
		neuron.setInput(2, input3);
		CORRECT_ANSWER = answer;

		OUTPUT_TESTING_FILE << "IN 0b: " << neuron.getInput(0);
		OUTPUT_TESTING_FILE << " IN 1: " << neuron.getInput(1);
		OUTPUT_TESTING_FILE << " IN 2: " << neuron.getInput(2);
		OUTPUT_TESTING_FILE << " RA: " << CORRECT_ANSWER;
	}
}

void learn(Neuron& neuron, bool testing)
{
	setInputValue(neuron, testing);
	neuron.sumOfInputs();
	int neuronAnswer = neuron.processOutput();
	int *inputArray = new int[2];
	inputArray[0] = neuron.getInput(1);
	inputArray[1] = neuron.getInput(2);

	if (neuronAnswer) //neuron answer = 1
	{
		if (CORRECT_ANSWER == 0)
		{
			BAD_ANSWERS_AMOUNT++;
			if (testing == false)
			{
				OUTPUT_LEARNING_FILE << " A: 1";
				neuron.countNewWeights(CORRECT_ANSWER, neuronAnswer, inputArray);
				OUTPUT_LEARNING_FILE << " -" << " CHANGING WEIGHTS: " << neuron.getSynapse(0) << " " << neuron.getSynapse(1) << " " << neuron.getSynapse(2) << endl;
			}

			else
			{
				OUTPUT_TESTING_FILE << " A: 1 -" << endl;
			}

		}

		else
		{
			RIGHT_ANSWERS_AMMOUNT++;

			if (testing == false)
			{
				OUTPUT_LEARNING_FILE << " A: 1";
				OUTPUT_LEARNING_FILE << " +" << " KEEPING  WEIGHTS: " << neuron.getSynapse(0) << " " << neuron.getSynapse(1) << " " << neuron.getSynapse(2) << endl;
			}

			else
			{
				OUTPUT_TESTING_FILE << " A: 1 +" << endl;
			}
		}
	}

	else //neuron answer = 0
	{
		if (CORRECT_ANSWER == 1)
		{
			BAD_ANSWERS_AMOUNT++;
	
			if (testing == false)
			{
				OUTPUT_LEARNING_FILE << " A: 0";
				neuron.countNewWeights(CORRECT_ANSWER, neuronAnswer, inputArray);
				OUTPUT_LEARNING_FILE << " -" << " CHANGING WEIGHTS: " << neuron.getSynapse(0) << " " << neuron.getSynapse(1) << " " << neuron.getSynapse(2) << endl;
			}

			else
			{
				OUTPUT_TESTING_FILE << " A: 0 -" << endl;
			}
		}

		else
		{
			RIGHT_ANSWERS_AMMOUNT++;
		
			if (testing == false)
			{
				OUTPUT_LEARNING_FILE << " A: 0";
				OUTPUT_LEARNING_FILE << " +" << " KEEPING  WEIGHTS: " << neuron.getSynapse(0) << " " << neuron.getSynapse(1) << " " << neuron.getSynapse(2) << endl;
			}

			else
			{
				OUTPUT_TESTING_FILE << " A: 0 +" << endl;
			}
		}
	}
}