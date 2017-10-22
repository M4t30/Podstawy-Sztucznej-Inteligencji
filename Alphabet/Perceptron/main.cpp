#include <iostream>
#include <vector>
#include "Neuron.h"
#include <time.h>
#include <fstream>
using namespace std;

void setInputValue(Neuron& neuron, bool testing, int numberOfEntrances, int numberOfWeights, bool secondAlgorithm);
void learn(Neuron& neuron, bool testing, int numberOfEntrances, int numberOfWeights, bool secondAlgorithm);

fstream OUTPUT_LEARNING_FILE;
fstream OUTPUT_TESTING_FILE;
fstream OUTPUT_LEARNING_SECOND_ALGORITHM_FILE;
fstream OUTPUT_TESTING_SECOND_ALGORITHM_FILE;
fstream LEARNING_DATA;
fstream TESTING_DATA;
double E_F;
double E_F_TESTING;
double E;
double E_TESTING;
int BAD_ANSWERS_AMOUNT;
int TOTAL_BAD_ANSWERS_AMOUNT;
int RIGHT_ANSWERS_AMOUNT;
int TOTAL_RIGHT_ANSWERS_AMOUNT;
int CORRECT_ANSWER[2];

int main()
{
	srand(time(NULL));
	int numberOfEntrances = 21;
	int numberOfWeights = 2;
	Neuron neuron(numberOfEntrances, numberOfWeights, 1);
	LEARNING_DATA.open("learning_data.txt", ios::in);
	TESTING_DATA.open("testing_data.txt", ios::in);
	OUTPUT_LEARNING_FILE.open("output_learning_data.txt", ios::out);
	OUTPUT_LEARNING_SECOND_ALGORITHM_FILE.open("output_learning_second_algorithm_data.txt", ios::out);

	do
	{
		cout << "1. Learn" << endl;
		cout << "2. Test" << endl;
		cout << "3. Learn (second algorithm)" << endl;
		cout << "4. Test (second algorithm)" << endl;
		cout << "5. Exit" << endl;

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMOUNT = 0;
			TOTAL_BAD_ANSWERS_AMOUNT = 0;
			TOTAL_RIGHT_ANSWERS_AMOUNT = 0;
			int numberOfEpochs;
			cout << "Enter number of epochs: " << endl;
			cin >> numberOfEpochs;
			OUTPUT_LEARNING_FILE << "NEW EPOCH NUMBER: 1" << endl;
			for (int i = 1, epochNumber = 1; i <= numberOfEpochs * 20; i++)
			{
				learn(neuron, false, numberOfEntrances, numberOfWeights, false);

				if (i % 20 == 0)
				{
					epochNumber++;
					LEARNING_DATA.clear();
					LEARNING_DATA.seekg(0, ios::beg);
					OUTPUT_LEARNING_FILE << "Bad answers amount: " << BAD_ANSWERS_AMOUNT << endl;
					OUTPUT_LEARNING_FILE << "Right answers amount: " << RIGHT_ANSWERS_AMOUNT << endl;
					OUTPUT_LEARNING_FILE << "EF: " << E_F << endl;
					E_F = 0;

					if (epochNumber <= numberOfEpochs)
					{
						OUTPUT_LEARNING_FILE << "NEW EPOCH NUMBER: " << epochNumber << endl;
					}

					TOTAL_BAD_ANSWERS_AMOUNT += BAD_ANSWERS_AMOUNT;
					TOTAL_RIGHT_ANSWERS_AMOUNT += RIGHT_ANSWERS_AMOUNT;
					RIGHT_ANSWERS_AMOUNT = 0;
					BAD_ANSWERS_AMOUNT = 0;
				}
			}

			OUTPUT_LEARNING_FILE << "\nTotal bad answers amount: " << TOTAL_BAD_ANSWERS_AMOUNT << endl;
			OUTPUT_LEARNING_FILE << "Total right answers amount: " << TOTAL_RIGHT_ANSWERS_AMOUNT << endl;
			break;

		case 2:
			OUTPUT_TESTING_FILE.open("output_testing_data.txt", ios::out);
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMOUNT = 0;
			E_F_TESTING = 0;
			
			for (int i = 0; i < 20; i++)
			{
				learn(neuron, true, numberOfEntrances, numberOfWeights, false);
			}

			OUTPUT_TESTING_FILE << "Bad answers amount: " << BAD_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_FILE << "Right answers amount: " << RIGHT_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_FILE << "E: " << E_F_TESTING << endl;
			break;

		case 3:
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMOUNT = 0;
			TOTAL_BAD_ANSWERS_AMOUNT = 0;
			TOTAL_RIGHT_ANSWERS_AMOUNT = 0;
			cout << "Enter number of epochs: " << endl;
			cin >> numberOfEpochs;
			OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << "NEW EPOCH NUMBER: 1" << endl;

			for (int i = 1, epochNumber = 1; i <= numberOfEpochs * 20; i++)
			{
				learn(neuron, false, numberOfEntrances, numberOfWeights, true);

				if (i % 20 == 0)
				{
					OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << "E: " << E << endl;
					E = 0;
					epochNumber++;
					LEARNING_DATA.clear();
					LEARNING_DATA.seekg(0, ios::beg);
					
					if (epochNumber <= numberOfEpochs)
					{
						OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << "NEW EPOCH NUMBER: " << epochNumber << endl;
					}

					TOTAL_BAD_ANSWERS_AMOUNT += BAD_ANSWERS_AMOUNT;
					TOTAL_RIGHT_ANSWERS_AMOUNT += RIGHT_ANSWERS_AMOUNT;
					RIGHT_ANSWERS_AMOUNT = 0;
					BAD_ANSWERS_AMOUNT = 0;
				}
			}

			break;

		case 4:
			OUTPUT_TESTING_SECOND_ALGORITHM_FILE.open("output_testing_second_algorithm_data.txt", ios::out);
			BAD_ANSWERS_AMOUNT = 0;
			RIGHT_ANSWERS_AMOUNT = 0;
			E_TESTING = 0;

			for (int i = 0; i < 20; i++)
			{
				learn(neuron, true, numberOfEntrances, numberOfWeights, true);
			}

			OUTPUT_TESTING_SECOND_ALGORITHM_FILE << "Bad answers amount: " << BAD_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_SECOND_ALGORITHM_FILE << "Right answers amount: " << RIGHT_ANSWERS_AMOUNT << endl;
			OUTPUT_TESTING_SECOND_ALGORITHM_FILE << "E: " << E_TESTING << endl;
			break;

		case 5:
			OUTPUT_LEARNING_FILE.close();
			OUTPUT_TESTING_FILE.close();
			OUTPUT_LEARNING_SECOND_ALGORITHM_FILE.close();
			OUTPUT_TESTING_SECOND_ALGORITHM_FILE.close();
			LEARNING_DATA.close();
			TESTING_DATA.close();

			return 0;
		}

	} while (true);

	return 0;
}

void setInputValue(Neuron& neuron, bool testing, int numberOfEntrances, int numberOfWeights, bool secondAlgorithm)
{
	if (testing == false)
	{
		int* inputs = new int[numberOfEntrances];
		int* answers = new int[numberOfWeights];
		
		if (secondAlgorithm == false)
		{
			for (int i = 0; i < numberOfEntrances; i++)
			{
				LEARNING_DATA >> inputs[i];
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				LEARNING_DATA >> answers[i];
			}

			for (int i = 0; i < numberOfEntrances; i++)
			{
				neuron.setInput(i, inputs[i]);
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				CORRECT_ANSWER[i] = answers[i];
			}

			OUTPUT_LEARNING_FILE << "IN: ";

			for (int i = 0; i < numberOfEntrances; i++)
			{
				OUTPUT_LEARNING_FILE << neuron.getInput(i) << " ";
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				OUTPUT_LEARNING_FILE << " RA: " << CORRECT_ANSWER[i];
			}
		}

		else
		{
			for (int i = 0; i < numberOfEntrances; i++)
			{
				LEARNING_DATA >> inputs[i];
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				LEARNING_DATA >> answers[i];
			}

			for (int i = 0; i < numberOfEntrances; i++)
			{
				neuron.setInput(i, inputs[i]);
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				CORRECT_ANSWER[i] = answers[i];
			}

			OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << "IN: ";

			for (int i = 0; i < numberOfEntrances; i++)
			{
				OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << neuron.getInput(i) << " ";
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << " RA: " << CORRECT_ANSWER[i];
			}
		}

		delete inputs;
		delete answers;
	}

	else
	{
		int* inputs = new int[numberOfEntrances];
		int* answers = new int[numberOfWeights];

		if (secondAlgorithm == false)
		{
			for (int i = 0; i < numberOfEntrances; i++)//load input
			{
				TESTING_DATA >> inputs[i];
			}

			for (int i = 0; i < numberOfWeights; i++)//load correct answers
			{
				TESTING_DATA >> answers[i];
			}

			for (int i = 0; i < numberOfEntrances; i++)//set neuron inputs
			{
				neuron.setInput(i, inputs[i]);
			}

			for (int i = 0; i < numberOfWeights; i++)//set correct answer
			{
				CORRECT_ANSWER[i] = answers[i];
			}

			OUTPUT_TESTING_FILE << "IN: ";

			for (int i = 0; i < numberOfEntrances; i++)
			{
				OUTPUT_TESTING_FILE << neuron.getInput(i) << " ";
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				OUTPUT_TESTING_FILE << " RA: " << CORRECT_ANSWER[i];
			}
		}

		else
		{
			for (int i = 0; i < numberOfEntrances; i++)//load input
			{
				TESTING_DATA >> inputs[i];
			}

			for (int i = 0; i < numberOfWeights; i++)//load correct answers
			{
				TESTING_DATA >> answers[i];
			}

			for (int i = 0; i < numberOfEntrances; i++)//set neuron inputs
			{
				neuron.setInput(i, inputs[i]);
			}

			for (int i = 0; i < numberOfWeights; i++)//set correct answer
			{
				CORRECT_ANSWER[i] = answers[i];
			}

				OUTPUT_TESTING_SECOND_ALGORITHM_FILE << "IN: ";

			for (int i = 0; i < numberOfEntrances; i++)
			{
				OUTPUT_TESTING_SECOND_ALGORITHM_FILE << neuron.getInput(i) << " ";
			}

			for (int i = 0; i < numberOfWeights; i++)
			{
				OUTPUT_TESTING_SECOND_ALGORITHM_FILE << " RA: " << CORRECT_ANSWER[i];
			}
		}

		delete inputs;
		delete answers;
	}
}

void learn(Neuron& neuron, bool testing, int numberOfEntrances, int numberOfWeights, bool secondAlgorithm)
{
	setInputValue(neuron, testing, numberOfEntrances, numberOfWeights, secondAlgorithm);
	neuron.sumOfInputs();
	neuron.processOutput(secondAlgorithm, testing);
	double* neuronAnswer = neuron.getOutputValue();

	int* inputArray = new int[numberOfEntrances];

	for (int i = 0; i < numberOfEntrances; i++)
	{
		inputArray[i] = neuron.getInput(i);
	}

	for (int i = 0; i < numberOfWeights; i++)
	{
		if (neuronAnswer[i]) //neuron answer = 1
		{
			if (CORRECT_ANSWER[i] == 0)
			{
				BAD_ANSWERS_AMOUNT++;
				if (testing == false)
				{
					neuron.countNewWeights(CORRECT_ANSWER[i], neuronAnswer[i], inputArray, i, secondAlgorithm);
					if (secondAlgorithm == false)
					{
						E_F += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_LEARNING_FILE << " A: 1 - NEW WEIGHTS";
					}

					else
					{
						E += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << " NEW WEIGHTS";
					}

				}

				else
				{
					if (secondAlgorithm == false)
					{
						E_F_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_FILE << " A: 1 -";
					}

					else
					{
						E_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_SECOND_ALGORITHM_FILE << " A: 1 -";
					}
				}
			}

			else
			{
				RIGHT_ANSWERS_AMOUNT++;

				if (testing == false)
				{
					if (secondAlgorithm == false)
					{
						E_F += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_LEARNING_FILE << " A: 1 + KEEPING WEIGHTS";
					}

					else
					{
						neuron.countNewWeights(CORRECT_ANSWER[i], neuronAnswer[i], inputArray, i, secondAlgorithm);
						OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << " NEW WEIGHTS";
						E += 0.5* pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
					}
				}

				else
				{
					if (secondAlgorithm == false)
					{
						E_F_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_FILE << " A: 1 +";
					}

					else
					{
						E_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_SECOND_ALGORITHM_FILE << " A: 1 +";
					}
				}
			}
		}

		else //neuron answer = 0
		{
			if (CORRECT_ANSWER[i] == 1)
			{
				BAD_ANSWERS_AMOUNT++;

				if (testing == false)
				{
					neuron.countNewWeights(CORRECT_ANSWER[i], neuronAnswer[i], inputArray, i, secondAlgorithm);
					
					if (secondAlgorithm == false)
					{
						E_F += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_LEARNING_FILE << " A: 0 - NEW WEIGHTS";
					}

					else
					{
						E += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << " A: 0 - NEW WEIGHTS";
					}
				}

				else // testing == true
				{
					if (secondAlgorithm == false)
					{
						E_F_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_FILE << " A: 0 -";
					}

					else
					{
						E_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_SECOND_ALGORITHM_FILE << " A: 0 -";
					}
				}
			}

			else
			{
				RIGHT_ANSWERS_AMOUNT++;

				if (testing == false)
				{
					if (secondAlgorithm == false)
					{
						E_F += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_LEARNING_FILE << " A: 0 + KEEPING WEIGHTS";
					}

					else
					{
						neuron.countNewWeights(CORRECT_ANSWER[i], neuronAnswer[i], inputArray, i, secondAlgorithm);
						OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << " A: 0 + NEW WEIGHTS";
						E += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
					}
				}

				else
				{
					if (secondAlgorithm == false)
					{
						E_F_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_FILE << " A: 0 +";
					}

					else
					{
						E_TESTING += 0.5 * pow(((double)CORRECT_ANSWER[i] - neuron.getOutputValue(i)), 2);
						OUTPUT_TESTING_SECOND_ALGORITHM_FILE << " A: 0 +";
					}
				}
			}
		}

		if (i == (numberOfWeights - 1))// file formatting
		{
			if (testing == false)
			{
				if (secondAlgorithm == false)
				{
					OUTPUT_LEARNING_FILE << endl;
				}

				else
				{
					OUTPUT_LEARNING_SECOND_ALGORITHM_FILE << endl;
				}
			}

			else
			{
				if (secondAlgorithm == false)
				{
					OUTPUT_TESTING_FILE << endl;
				}

				else
				{
					OUTPUT_TESTING_SECOND_ALGORITHM_FILE << endl;
				}
			}
		}
	}
}