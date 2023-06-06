#include <iostream>

#include <vector>

using namespace std;

vector<int> vt;

int tmp[100000];

void merge(int start, int end)
{
	int mid = (start + end) / 2;
	int i = start;
	int j = mid+1;
	int k = start;
	while(1)
	{
		if(i == mid+1)
			break;
		if(j == end+1)
			break;
		if(vt[i] < vt[j])
		{
			tmp[k] = vt[i];
			i ++;
			k ++;
		}
		else
		{
			tmp[k] = vt[j];
			j ++;
			k ++;
		}
	}
	if(i == mid+1)
	{
		while(j != end+1)
		{
			tmp[k] = vt[j];
			j ++;
			k ++;
		}
	}
	else
	{
		while(i != mid+1)
		{
			tmp[k] = vt[i];
			i ++;
			k ++;
		}
	}
	for(int i = start; i <= end; i ++)
	{
		vt[i] = tmp[i];
	}
}


void merge_sort(int start, int end)
{
	if(start == end)
		return ;
	int mid = (start + end) / 2;
	merge_sort(start, mid);
	merge_sort(mid+1, end);
	merge(start, end);
}

int main(int argc, char **argv)
{
	for(int i = 100; i >= 0; i --)
		vt.push_back(i);
	
	for(int i = 0; i <= 50; i ++)
		vt[i] = i * 30;
	for(int i = 50; i <= 100; i ++)
		vt[i] = i * -30;
	merge_sort(0, 100);
	for(int i = 0; i < vt.size(); i ++)
		cout << vt[i] << " ";
	cout << endl;
}