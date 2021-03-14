#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>

using namespace std::chrono;

/*
* merge function to combine two parts that have been separated before
* while sorting them
*/
std::vector<int> merge(std::vector<int> leftPart, std::vector<int> rightPart)
{
	std::vector<int> result;
	while (leftPart.size() > 0 && rightPart.size() > 0)
	{
		if (leftPart.front() <= rightPart.front())
		{
			result.push_back(leftPart.front());
			leftPart.erase(leftPart.begin());
		}
		else
		{
			result.push_back(rightPart.front());
			rightPart.erase(rightPart.begin());
		}
	}
	if (leftPart.size() > 0)
	{
		while (leftPart.size() > 0)
		{
			result.push_back(leftPart.front());
			leftPart.erase(leftPart.begin());
		}
	}
	if (rightPart.size() > 0)
	{
		while (rightPart.size() > 0)
		{
			result.push_back(rightPart.front());
			rightPart.erase(rightPart.begin());
		}
	}
	return result;
}
/*
* mergeSort function that recursively calls itself to devide vector
* into two parts from left to the middle
* from middle to the right
* COMPLEXITY O(n*logn) time and O(n) space
*/
std::vector<int> mergeSort(std::vector<int> toSort)
{
	if (toSort.size() <= 1)
	{
		return toSort;
	}
	int middle;
	std::vector<int> leftPart, rightPart, result;
	middle = toSort.size() / 2;
	for (int i = 0; i < middle; i++)
	{
		leftPart.push_back(toSort[i]);
	}
	for (int i = middle; i < toSort.size(); i++)
	{
		rightPart.push_back(toSort[i]);
	}

	leftPart = mergeSort(leftPart);
	rightPart = mergeSort(rightPart);
	result = merge(leftPart, rightPart);

	return result;

}
/*
* bubbleSort function that switches every two consecutive numbers
* if left one is greater than the right one
* COMPLEXITY O(n^2) time and O(1) space since it doesn't use any sup space
*/
std::vector<int> bubbleSort(std::vector<int> toSort)
{
	for (int i = 0; i < toSort.size() - 1; i++)
	{
		for (int j = 0; j < toSort.size() - 1 - i; j++)
		{
			if (toSort[j] > toSort[j + 1])
			{
				std::swap(toSort[j], toSort[j + 1]);

			}
		}
	}
	return toSort;
}

std::vector<int> countSort(std::vector<int> toSort)
{
	int n;
	n = toSort.size();

	int maxValue;
	maxValue = toSort[0];
	
	for (int i = 1; i < n; i++)
	{
		if (toSort[i] > maxValue)
		{
			maxValue = toSort[i];
		}
	}
	
	std::vector<int> counting(maxValue + 1,0);

	for (int i = 0; i < n; i++)
	{
		counting[toSort[i]] = counting[toSort[i]] + 1;
	
	}
	std::vector<int> result;
	for (int i = 0; i <= maxValue; i++)
	{
		while (counting[i] != 0)
		{
			result.push_back(i);
			counting[i]--;
		}
	}
	return result;
}

void sortBuckets(std::vector<int>& bucket_to_sort)
{
	int pivot, j;
	for (int i = 1; i < bucket_to_sort.size(); i++)
	{
		pivot = bucket_to_sort[i];
		j = i - 1;

		while (j >= 0 && pivot < bucket_to_sort[j])
		{
			bucket_to_sort[j + 1] = bucket_to_sort[j];
			j = j - 1;
		}
		bucket_to_sort[j + 1] = pivot;
	}
}



//bucketsort
std::vector<int> bucketSort(std::vector<int> toSort)
{
	std::vector<int> result;
	int n;
	int maxValue;
	maxValue = *max_element(toSort.begin(), toSort.end());
	n = toSort.size();
	//create a vector of vectors of size n to minimize operations in insertion (sortBuckets) sort which has complexity O(n^2)
	std::vector<std::vector<int>> buckets(n);
	for (int i = 0; i < n; i++)
	{	
		int bucketIndex;
		
		bucketIndex = (toSort[i] * n) / (maxValue + 1);
		buckets[bucketIndex].push_back(toSort[i]);
	}
	for (int i = 0; i < n; i++)
	{
		if (buckets[i].size() == 0)
		{
			continue;
		}
		else
		{
			sortBuckets(buckets[i]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (buckets[i].size() == 0)
		{
			continue;
		}
		else
		{
			for (int j = 0; j < buckets[i].size(); j++)
			{
				result.push_back(buckets[i][j]);
			}
		}
	}
	return result;
}

std::vector<int> cocktailShakerSort(std::vector<int> toSort)
{
	bool switched = true;
	int startIndex = 0;
	int endIndex = toSort.size() - 1;

	while (switched == true)
	{
		switched = false;

		for (int i = startIndex; i < endIndex; i++)
		{
			if (toSort[i] > toSort[i + 1])
			{
				std::swap(toSort[i], toSort[i + 1]);
				switched = true;
			}
		}

		if (switched == false)
		{
			break;
		}

		switched = false;

		endIndex--;

		for (int i = endIndex; i > startIndex; i--)
		{
			if (toSort[i] < toSort[i - 1])
			{
				std::swap(toSort[i], toSort[i - 1]);
				switched = true;
			}
		}

		startIndex++;
	}

	return toSort;
}

bool checkIfSorted(std::vector<int> sorted)
{
	bool notSorted = false;
	for (int i = 0; i < sorted.size()-1; i++)
	{
		if (sorted[i] > sorted[i + 1])
		{
			notSorted = true;
		}
	}

	return notSorted;
}

std::vector<int> randomlyGenerated(int size, int maxValue)
{
	std::vector<int> v;

	srand(time(0));

	for (int k = 0; k < size; k++)
	{
		v.push_back(rand() % maxValue + 1);
	}

	return v;
}

std::vector<int> theSameNumber(int size, int maxValue)
{
	std::vector<int> v(size,maxValue);

	return v;
}


std::vector<int> alreadySorted(int size)
{
	std::vector<int> v(size, 0);
	for (int i = 0; i < size - 1; i++)
	{
		v[i] = i;
	}

	return v;
}


std::vector<int> reversedSorted(int size, int maxValue)
{
	std::vector<int> v(size, 0);

	for (int i = v.size() - 1; i > 0; i--)
	{
		v[i] = maxValue;
		maxValue--;
	}

	return v;
}


int main()
{
	/*
	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v3;
	std::vector<int> v4;
	std::vector<int> v5;
	v1 = cocktailShakerSort(v1);

	for (int i = 0; i < v1.size(); i++)
	{
		std::cout << v1[i] << " ";
	}
	*/  

	std::ifstream file ("TextFile2.txt");
	std::string Str;
	std::vector<int> vectorInput;

	while (file >> Str)
	{
		vectorInput.push_back(std::stoi(Str));
	}
	file.close();

	

	std::cout << "Test #1: Randomly filled vectors \n\n";

	

	for (int j = 1; j < 13; j = j + 2)
	{
		int size = vectorInput[j];
		int maxNumber = vectorInput[j + 1];
		std::vector<int> v;

		v = randomlyGenerated(size, maxNumber);

		std::cout << "For the size of " << size << " and maximum value of " << maxNumber << " (prints 0 if sorted correctly)" <<"\n";


		std::vector<int> v1;
		std::vector<int> v2;
		std::vector<int> v3;
		std::vector<int> v4;
		std::vector<int> v5;

		auto start1 = high_resolution_clock::now();

		v1 = mergeSort(v);

		auto stop1 = high_resolution_clock::now();

		auto duration1 = duration_cast<microseconds>(stop1 - start1);
		std::cout <<"Merge Sort: "<< duration1.count() << " microseconds ";
		std::cout << checkIfSorted(v1)<< "\n";

		auto start2 = high_resolution_clock::now();

		v2 = bubbleSort(v);

		auto stop2 = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(stop2 - start2);
		std::cout << "Bubble Sort: " << duration2.count() << " microseconds ";

		std::cout << checkIfSorted(v2) << "\n";

		auto start3 = high_resolution_clock::now();

		v3 = countSort(v);

		auto stop3 = high_resolution_clock::now();
		auto duration3 = duration_cast<microseconds>(stop3 - start3);

		std::cout << "Count Sort: " << duration3.count() << " microseconds ";
		std::cout << checkIfSorted(v3) << "\n";

		auto start4 = high_resolution_clock::now();

		v4 = bucketSort(v);

		auto stop4 = high_resolution_clock::now();
		auto duration4 = duration_cast<microseconds>(stop4 - start4);

		std::cout <<"Bucket Sort: " << duration4.count() << " microseconds ";
		std::cout << checkIfSorted(v4) << "\n";

		auto start5 = high_resolution_clock::now();

		v5 = cocktailShakerSort(v);

		auto stop5 = high_resolution_clock::now();
		auto duration5 = duration_cast<microseconds>(stop5 - start5);

		std::cout << "Cocktail Shaker Sort: " << duration5.count() << " microseconds ";
		std::cout << checkIfSorted(v5) << "\n";


		std::cout << "\n\n";
			
	} 

	std::cout << "Test #2: Vectors filled with the same number! \n\n";


	for (int j = 1; j < 13; j = j + 2)
	{
		int size = vectorInput[j];
		int maxNumber = vectorInput[j + 1];
		std::vector<int> v;

		v = theSameNumber(size, maxNumber);

		std::cout << "For the size of " << size << " and the only number of " << maxNumber << " (prints 0 if sorted correctly)" <<"\n";


		std::vector<int> v1;
		std::vector<int> v2;
		std::vector<int> v3;
		std::vector<int> v4;
		std::vector<int> v5;

		auto start1 = high_resolution_clock::now();

		v1 = mergeSort(v);

		auto stop1 = high_resolution_clock::now();

		auto duration1 = duration_cast<microseconds>(stop1 - start1);
		std::cout <<"Merge Sort: "<< duration1.count() << " microseconds ";
		std::cout << checkIfSorted(v1)<< "\n";

		auto start2 = high_resolution_clock::now();

		v2 = bubbleSort(v);

		auto stop2 = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(stop2 - start2);
		std::cout << "Bubble Sort: " << duration2.count() << " microseconds ";

		std::cout << checkIfSorted(v2) << "\n";

		auto start3 = high_resolution_clock::now();

		v3 = countSort(v);

		auto stop3 = high_resolution_clock::now();
		auto duration3 = duration_cast<microseconds>(stop3 - start3);

		std::cout << "Count Sort: " << duration3.count() << " microseconds ";
		std::cout << checkIfSorted(v3) << "\n";

		auto start4 = high_resolution_clock::now();

		v4 = bucketSort(v);

		auto stop4 = high_resolution_clock::now();
		auto duration4 = duration_cast<microseconds>(stop4 - start4);

		std::cout << "Bucket Sort: " << duration4.count() << " microseconds ";
		std::cout << checkIfSorted(v4) << "\n";

		auto start5 = high_resolution_clock::now();

		v5 = cocktailShakerSort(v);

		auto stop5 = high_resolution_clock::now();
		auto duration5 = duration_cast<microseconds>(stop5 - start5);

		std::cout << "Cocktail Shaker Sort: " << duration5.count() << " microseconds ";
		std::cout << checkIfSorted(v5) << "\n";


		std::cout << "\n\n";
			
	} 

	std::cout<< "Test #3: Vectors that are already sorted! \n\n";

	for (int j = 1; j < 13; j = j + 2)
{
	int size = vectorInput[j];
	int maxNumber = vectorInput[j + 1];
	std::vector<int> v;

	v = alreadySorted(size);

	std::cout << "For the size of " << size << " (prints 0 if sorted correctly)" << "\n";


	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v3;
	std::vector<int> v4;
	std::vector<int> v5;

	auto start1 = high_resolution_clock::now();

	v1 = mergeSort(v);

	auto stop1 = high_resolution_clock::now();

	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	std::cout <<"Merge Sort: "<< duration1.count() << " microseconds ";
	std::cout << checkIfSorted(v1) << "\n";

	auto start2 = high_resolution_clock::now();

	v2 = bubbleSort(v);

	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	std::cout << "Bubble Sort: " << duration2.count() << " microseconds ";

	std::cout << checkIfSorted(v2) << "\n";

	auto start3 = high_resolution_clock::now();

	v3 = countSort(v);

	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast<microseconds>(stop3 - start3);

	std::cout << "Count Sort: " << duration3.count() << " microseconds ";
	std::cout << checkIfSorted(v3) << "\n";

	auto start4 = high_resolution_clock::now();

	v4 = bucketSort(v);

	auto stop4 = high_resolution_clock::now();
	auto duration4 = duration_cast<microseconds>(stop4 - start4);

	std::cout << "Bucket Sort: " << duration4.count() << " microseconds ";
	std::cout << checkIfSorted(v4) << "\n";

	auto start5 = high_resolution_clock::now();

	v5 = cocktailShakerSort(v);

	auto stop5 = high_resolution_clock::now();
	auto duration5 = duration_cast<microseconds>(stop5 - start5);

	std::cout << "Cocktail Shaker Sort: " << duration5.count() << " microseconds ";
	std::cout << checkIfSorted(v5) << "\n";


	std::cout << "\n\n";

}

	std::cout << "Test #4: Vectors that are already sorted, but backwards! \n\n";

	for (int j = 1; j < 13; j = j + 2)
	{
		int size = vectorInput[j];
		int maxNumber = vectorInput[j + 1];
		std::vector<int> v;

		v = reversedSorted(size, maxNumber);

		std::cout << "For the size of " << size << " (prints 0 if sorted correctly)" << "\n";


		std::vector<int> v1;
		std::vector<int> v2;
		std::vector<int> v3;
		std::vector<int> v4;
		std::vector<int> v5;

		auto start1 = high_resolution_clock::now();

		v1 = mergeSort(v);

		auto stop1 = high_resolution_clock::now();

		auto duration1 = duration_cast<microseconds>(stop1 - start1);
		std::cout <<"Merge Sort: "<< duration1.count() << " microseconds ";
		std::cout << checkIfSorted(v1) << "\n";

		auto start2 = high_resolution_clock::now();

		v2 = bubbleSort(v);

		auto stop2 = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(stop2 - start2);
		std::cout << "Bubble Sort: " << duration2.count() << " microseconds ";

		std::cout << checkIfSorted(v2) << "\n";

		auto start3 = high_resolution_clock::now();

		v3 = countSort(v);

		auto stop3 = high_resolution_clock::now();
		auto duration3 = duration_cast<microseconds>(stop3 - start3);

		std::cout << "Count Sort: " << duration3.count() << " microseconds ";
		std::cout << checkIfSorted(v3) << "\n";

		auto start4 = high_resolution_clock::now();

		v4 = bucketSort(v);

		auto stop4 = high_resolution_clock::now();
		auto duration4 = duration_cast<microseconds>(stop4 - start4);

		std::cout << "Bucket Sort: " << duration4.count() << " microseconds ";
		std::cout << checkIfSorted(v4) << "\n";

		auto start5 = high_resolution_clock::now();

		v5 = cocktailShakerSort(v);

		auto stop5 = high_resolution_clock::now();
		auto duration5 = duration_cast<microseconds>(stop5 - start5);

		std::cout << "Cocktail Shaker Sort: " << duration5.count() << " microseconds ";
		std::cout << checkIfSorted(v5) << "\n";


		std::cout << "\n\n";

	}
}

