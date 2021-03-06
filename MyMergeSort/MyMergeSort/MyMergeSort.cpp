// MyMergeSort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

/*
归并排序
算法思想：
归并排序采用了“分治”的算法思想，所谓“分”，既将问题分(divide)成一些小的问题然后递归求解，
而治(conquer)的阶段则将分的阶段得到的各答案"修补"在一起
归并排序在"分"的阶段是将无序的序列不断划分成更小的子序列，直到每个子序列中只有一个元素，然后将相邻的两个子序列进行大小的比较
归并排序在"治"的阶段是将已经排好序的子序列进行合并，合并成一个更长的有序子序列
以此类推，知道整个序列有序
*/




/*
归并排序“治”的部分
temp[]临时数组用来存储合并好的有序子序列
leftstart为左子序列的第一个元素下标
rightend为右子序列的最后一个元素的下标
mid为将整个序列一分为二后，左子序列的最后一个元素的下标
*/
void divideAndSort(int a[], int leftstart, int mid, int rightend, int temp[]) {
	int i = leftstart,j=mid+1;//i指向左子序列的第一个元素，j指向右子序列的第一个元素
	int t = 0;//用于指向temp[]中的元素
	//将两个子序列进行合并
	while (i <= mid && j <= rightend) {
		if (a[i] <= a[j]) {//如果左边的比右边的小，则将左边的装入temp[]
			temp[t] = a[i];
			t++;
			i++;
		}
		else {//否则将右边的装入temp[]
			temp[t++] = a[j++];
		}
	}

	//左右子序列的长度存在不相等的情况，因此，若最后左子序列有剩余，直接装入temp[]
	while (i <= mid) {
		temp[t++] = a[i++];
	}
	//同理
	while (j <= rightend) {
		temp[t++] = a[j]++;
	}

	t = 0;
	//将排序好的部分重新填入原数组
	while (leftstart <= rightend) {
		a[leftstart++] = temp[t++];
	}
}

/*
归并算法
start为数组的第一个元素的下标
end为数组的第二个元素的下标
*/
void mergesort(int a[], int start, int end, int temp[]) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergesort(a, start, mid, temp);//左边归并排序，使得左子序列有序
		mergesort(a, mid + 1, end, temp);//右边归并排序，使得右子序列有序
		divideAndSort(a, start, mid, end, temp);//将两个有序子序列合并操作
	}
}



int main()
{
	int n;
	cin >> n;
	int a[101], temp[101];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	mergesort(a, 0, n - 1, temp);
	for (int i = 0; i < n; i++) {
		cout << a[i];
	}
    return 0;
}

