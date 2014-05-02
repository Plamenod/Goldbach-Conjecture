#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

bool binary_search(vector<int>& prime_numbers, int left_bound, int right_bound, int target, int& mid)
{
	while(left_bound <= right_bound)
	{
		mid = (left_bound + right_bound)/2;
		if(prime_numbers[mid] > target)
		{
			right_bound = mid-1;
		}
		else if(prime_numbers[mid] < target)
		{
			left_bound = mid + 1;
		}
		else
		{
			if(prime_numbers[mid] == target)
				return true;
		}
	}
	return false;
}

vector<int> all_primes(int target)
{
	bool* visited = new bool[target];
	memset(visited, true, sizeof(bool)*target);
	vector<int> primes;
	for(int i = 2; i<target; ++i)
	{
		if(visited[i])
		{
			primes.push_back(i);
			for(int j=2; i*j < target; ++j)
			{
				visited[i*j] = false;
			}
		}
	}
	delete [] visited;
	return primes;
}

vector<pair<int, int> > goldbach(int compare_number)
{
	vector<int> prime_numbers = all_primes(compare_number);
	vector<pair<int, int> > result;
	int size = prime_numbers.size();
	int current_result;
	for(int i=0; i<size-1; ++i)
	{
		if(binary_search(prime_numbers, i, size-1, compare_number - prime_numbers[i], current_result))
		{
			result.push_back(make_pair( prime_numbers[i], prime_numbers[current_result]));
		}
	}
	return result;
}


int main()
{
	int n;
	scanf("%d", &n);
	vector<pair<int, int>> tuples = goldbach(n);
	if(!tuples.empty())
		printf("%d", n);
	for(auto iter: tuples)
	{
		printf(" = %ld + %ld", iter.first, iter.second);
	}
	printf("\n");

	return 0;
}
