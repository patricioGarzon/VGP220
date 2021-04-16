#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

//Name: Patricio Garzon	
//StudentId: 2032567

int fibArray[10];
int RecursiveMultiplication(int a, int b);
int NonRecursiveFibonacci(int n);
int PrintFibonacciLessThan15(int n);
int printRecursiveFactorialLessThan50(int n);
int DynamicProgrammingFunc(int n);

int main(int argc, char* argv[])
{
	for (int x = 0; x < 10; x++) {
		fibArray[x] = -1;
	}
	//Tests:
	std::cout << RecursiveMultiplication(2, 5) << std::endl; // Expected result: 10

	std::cout << NonRecursiveFibonacci(5) << std::endl; //Expected result: 5

	PrintFibonacciLessThan15(7) ; //Expected result: 0 1 1 2 3 5 8 13
	
	std::cout << std::endl;// ->Adding an extra line

	printRecursiveFactorialLessThan50(10);//Expected result: 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
	std::cout << printRecursiveFactorialLessThan50(10) << std::endl;
	return 0;
}

int RecursiveMultiplication(int a, int b)
{
	//TODO: Write a recursive function to multiply two positive integers
	//without using the operator *
	//You can use addition(+), subtraction(-) and bitShifting(<< or >>), but you
	//should minimize the number of those operations.
	if (b > 1) {
		
		return a + RecursiveMultiplication(a,b-1);
	}
	else {
		return a;
	}
	
}

int NonRecursiveFibonacci(int n)
{
	//TODO: Convert the recursive fibonacci that we did in class
	//to a non recursive method, using a bottom-up approach.
	assert(n >= 0);
	int fib = 0;
	for (int i = 0; i < n-1; i++) {
		if (i != 0) {
			fib = i + (i - 1);
		}
	}
	return fib;
}

int PrintFibonacciLessThan15(int n)
{
	//TODO: Create a method that will print all the fibonacci sequence
	//less than 15. The way that you should print is:
	//PrintFibonacciLessThan15(7) -> "0 1 1 2 3 5 8 13". You just need to print what is between "".
	//Don't forget that is less than 15, so use assert if the method is being used outside the
	//boundaries of the function.
	
	
	assert(n >= 0);
	if (fibArray[n] < 0  ) {
		
		if (n <= 1) {
			//fix error for printing the second int of the array first
			//get array[0] value first then print the first two values already acquired
			fibArray[n] = n;
			if (n == 1 && fibArray[0] != -1) {
				cout << fibArray[n] << " ";
			}
			else if (n == 0) {
				cout << fibArray[n] << " ";
				cout << fibArray[n+1] << " ";
			}
			
			
		}
		else {
			fibArray[n] = PrintFibonacciLessThan15(n - 2) + PrintFibonacciLessThan15(n - 1);
			cout << fibArray[n] << " ";
		}
		
	}
	

	return fibArray[n];
}

int printRecursiveFactorialLessThan50(int n)
{
	//TODO: Create a method that will print recursive
	//the factorial multiplication format of a number that is less than 50.
	//ASSERT that this function will be used in a correct way.
	//As an example:
	//printRecursiveFactorialLessThan50(10) -> "10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1"
	//The function just prints what is between "".
	if (n > 1) {

		return  n * printRecursiveFactorialLessThan50(n - 1);
	}
	else {
		return 1;
	}
	
}

//TODO: Show with dynamic programming, the results and calls for DynamicProgrammingFunc(10)
//Identify repeated calls. This question you can do in a piece of paper drawing the calls
//and results and saving an image on your git repo.
int DynamicProgrammingFunc(int n)
{
	if (n < 5)
	{
		return n - 2;
	}

	return DynamicProgrammingFunc(n - 3) - (DynamicProgrammingFunc(n - 1) * DynamicProgrammingFunc(n - 2));
}