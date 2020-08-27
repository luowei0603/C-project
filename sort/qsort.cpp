#include<iostream>
using namespace std;

void qsort(int *a, int start, int end)
{
	if(start >= end){
		return;
	}
	int i = start;
	int j = end;
	int tmp = a[start];
	while (i < j) {
		while (i < j && a[j] >= tmp) {
			j--;
		} 
		a[i] = a[j];
		while (i<j && a[i] <= tmp) {
			i++;
		}
		a[j] = a[i];
	}
	a[i] = tmp;
	
	qsort(a, start, i - 1);
	qsort(a, i + 1, end);
} 

int main()
{
	int a[] = {3, 2, 1, 8, 6, 3, 4};
	qsort(a, 0 , sizeof(a) / sizeof(int) -1);
	for(int i = 0; i < sizeof(a) / sizeof(int); i++){
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
