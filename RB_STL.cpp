#include <bits/stdc++.h>
#define MAX 5000000
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	double elapsed_secs;
	clock_t begin;
	clock_t end;
	set<int> RB;

	int temp;

	begin = clock();
	for(int i=1;i<=MAX;i++)
	{
		cin >> temp;
		RB.insert(temp);
	}
	end = clock();

	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;
	return 0;
}