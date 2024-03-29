// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <windows.h>

using namespace std;

int size_input,i,j,k,input,minnum,maxnum,sum;
int o, p, q;

int list[50],s[50],h[50];
double f[50];

void printHistogram(double arr[], int arr2[], int arr3[], int n, int n1);
int count(int number, int array[], int length);
int arraySum(int a[], int n);

int main()
{	
	cout << "Input : "; 
	i = 0;
	while ((input = getchar()) != 10 && i < 50) {
		list[i++] = input - '0';
	}
	size_input = i;

	//min max of list input
	maxnum = *max_element(begin(list), list + size_input);
	minnum = *min_element(begin(list), list + size_input);
	cout << "min : " << minnum << " max : " << maxnum;

	//event space
	j = 0;
	cout << "\nEvent space :\n";
	for (i = minnum; i <= maxnum; i++)
	{	
		s[j] = i;
		cout << s[j] << " ";
		j++;
		k = j; 
	}

	//histogram
	j = 0;
	cout << "\nHistogram :\n";
	for (i = 0; i < k; i++) {
		h[j] = count(s[i], list, size_input);
		cout << h[j] << " ";
		j++;
	}

	//probability density function
	cout << "\nProbability Density :\n";
	int n = sizeof(h) / sizeof(h[0]);
	sum = arraySum(h, n);
	j = 0;
	for (i = 0; i < k; i++) {
		f[j] = (double)h[i] / (double)sum;
		cout << f[j] << " ";
		j++;
	}

	//remove duplicate
	int m = k;
	int l;
	for (i = 0; i<m; i++)
	{
		for (j = i + 1; j<m; j++)
		{
			//If any duplicate found */
			if (f[i] == f[j])
			{
				// Delete the current duplicate element
				for (l = j; l < m; l++)
				{
					f[l] = f[l + 1];
				}

				//Decrement size after removing duplicate element
				m--;

				// If shifting of elements occur then don't increment j
				j--;
			}
		}
	}

	cout << "\n";
	for (i = 0; i < m; i++) {
		cout << f[i] << " ";

	}

	printHistogram(f,s,h,k,m);

	while (1);
	
    return 0;
}

int count(int number, int array[], int length) {
	if (length == 0) return 0;
	return (number == *array) + count(number, array + 1, length - 1);
}

void printHistogram(double arr[], int arr2[], int arr3[], int n, int n1)
{
	//min & max of probability density
	double maxEle = *max_element(arr, arr + n1);
	double minEle = *min_element(arr, arr + n1);
	double maxH = *max_element(arr3, arr3 + n);
	double minH = *min_element(arr3, arr3 + n);
	cout << "\nmin : " << minEle << " max : " << maxEle;
	cout << "\nmin : " << minH << " max : " << maxH;

	cout << "\n\n";
	cout << n1;
	cout << "\n";
	sort(arr, arr + n1);
	for (int i = 0; i < n1; i++){
		cout << arr[i] << " ";
	}
	
	cout << "\n\n";

	int t = n1 - 1;
	for (int i = n; i >= 1; i--) {
		cout.width(5);
		cout << right << i <<  " | ";
		for (int j = 1-1; j < n; j++) {
			// if array of element is greater 
			// then array it print x 
			if (arr3[j] >= i)
				cout << " x ";

			// else print blank spaces 
			else
				cout << "   ";
		}
		cout << "\n";
		t--;
	}

	// print last line denoted by ---- 
	for (int i = 0; i < n + 10; i++)
		cout << "---";

	cout << "\n";
	cout << "        ";

	for (int i = 0; i < n; i++) {
		cout.width(2); // width for a number 
		cout << right << arr2[i] << " ";
	}
}

int arraySum(int a[], int n)
{
	int initial_sum = 0;
	return accumulate(a, a + n, initial_sum);
}