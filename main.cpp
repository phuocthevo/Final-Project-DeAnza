//The “objects” in a “park” are represented by any characters except ‘0’. The matrix should
//be dynamically allocated. Output shows the object number and its area.
// Method: iterative
// Written by THE VO

#include<iostream>
#include<fstream>
#include<iomanip>
#include"Stack.h"
#include"Location.h"
#include"Queue.h"

using namespace std;

void display(Queue<int>*);
Queue<int>* processArr(char**, bool**&, int&, int&);
char** intputfile(bool**&, int&, int&);
void deleteData(bool**&, char**&, Queue<int>*,int);

int main()
{
	int row, column;
	bool** check = 0;
	char** inputArr = intputfile(check,row, column); 
	Queue<int>* total = processArr(inputArr, check, row, column);

	display(total);
	deleteData(check, inputArr, total, row);
	system("pause");
	return 0;
}

// deleteData: release memory and delete all pointer
void deleteData(bool**& check, char**&inputArr, Queue<int>* total,int row)
{
	for (int i = 0; i < row; i++) {
		delete[] check[i];
		delete[] inputArr[i];
	}
	delete check;
	delete inputArr;
}

// Display: dpslay object and its area 
void display(Queue<int>* total)
{
	for (int i = 1; !total->isEmpty(); i++)
	{
		int area;
		total->dequeue(area);
		cout << "Object #" << i << ": " << area << " square";
		if (area != 1) cout << "s";
		cout << endl;
	}
}
// inputfile: input data from the text file into 2D array
// input: check: bool**, a(row), b(column): int
//output: inputarr: char** ( store data from .txt file)
char** intputfile(bool**& check, int& a, int& b)
{
	ifstream input("test.txt");
	char data;
	int row, column;;
	char** inputArr;
	if (input.fail())
	{
		cout << "Unable to input file";
		return 0;
	}
	else
	{
		input >> row >> column;
		a = row;
		b = column;

		inputArr = new char*[row];
		check = new bool*[row];
		
		// create 2D array with pointer
		for (int i = 0; i < row; i++) {
			inputArr[i] = new char[column];
			check[i] = new bool[column];
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				input >> data;
				inputArr[i][j] = data;
				check[i][j] = false; 
			}
		}
	}
	return inputArr;
}
//processArr: run over the inputArr 2D array count for the number of object and its area
// change check=true for the visited location, store the object in queue 
//input: inputArr: char** check: bool**, a(row), b(column): int
//output:  total: Queue<int>*
Queue<int>* processArr(char** inputArr, bool**&check, int& row, int& column){

	Queue<int>* total = new Queue<int>();
	int count = 0;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){

			if (inputArr[i][j] != '0' && !check[i][j]){
				check[i][j] = true;
				Stack<Location>* findNode = new Stack<Location>();
				findNode->push(Location(i, j));
				count = 0;
				// check the data 
				while (!findNode->isEmpty()){
					count++;
					Location temp;
					findNode->pop(temp);
					if (inputArr[temp.getX()][temp.getY() + 1] != '0'&&!check[temp.getX()][temp.getY() + 1]){
						check[temp.getX()][temp.getY() + 1] = true;
						findNode->push(Location(temp.getX(), temp.getY() + 1));
					}
					if (inputArr[temp.getX()][temp.getY() - 1] != '0'&&!check[temp.getX()][temp.getY() - 1]){
						check[temp.getX()][temp.getY() - 1] = true;
						findNode->push(Location(temp.getX(), temp.getY() - 1));
					}
					if (inputArr[temp.getX() + 1][temp.getY()] != '0'&&!check[temp.getX() + 1][temp.getY()]){
						check[temp.getX() + 1][temp.getY()] = true;
						findNode->push(Location(temp.getX() + 1, temp.getY()));
					}
					if (inputArr[temp.getX() - 1][temp.getY()] != '0'&&!check[temp.getX() - 1][temp.getY()]){
						check[temp.getX() - 1][temp.getY()] = true;
						findNode->push(Location(temp.getX() - 1, temp.getY()));
					}
				}
				total->enqueue(count);
			}
		}
	}
	return total;
}
