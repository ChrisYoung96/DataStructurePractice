// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int a[101], n;

/*
冒泡排序基本思想：
假设对一个乱序序列进行升序排序
则首先将序列的第一个元素与第二个元素进行比较，如果第二个元素比第一个元素小
则交换位置；然后第二个元素再和第三个元素进行比较，如果第二个元素比第三个元素小，则交换位置；
以此类推，直到第n-1个元素和第n个元素进行比较。
上述过程就是冒泡排序的第一趟排序，其结果就是，序列中最大的元素被换到了最后一个位置（大数沉底）。
之后进行第二趟，对前n-1个元素进行上述过程。以此类推直到排序完毕
时间复杂度为O(n^2)
*/
void bubbleSort(int a[], int len) {
	int i, j,temp;
	for (i = 0; i < len-1; i++) {
		for (j = 0; j < len - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}

	}
}

/*
快速排序
详细讲解请看链接
http://wiki.jikexueyuan.com/project/easy-learn-algorithm/fast-sort.html
简单概述：
在整个序列中寻找一个基数（参考标准，也叫枢轴），然后分别从左边开始找到找到第一个比基数大的数，从右边找到第一个比基数小的数，交换。然后继续做相似操作，直到遍历一遍。
第一趟快排，结果是该序列中，比这个基数小的都在基数的左边
比这个基数大的都在基数的右边。
之后再对这个基数的左右两部分进行相似操作，直到结束。
时间复杂度O(logn)
*/
void quickSort(int left, int right) {
	int i, j, temp, base;// i:从序列最左端前进的哨兵，j:从序列最右端前进的哨兵；temp:交换值用的中间变量；base：基数
	
	//递归出口
	if (left > right) {
		return;
	}

	base = a[left];//将选定的基数存放到base中，作为参考
	//两个哨兵就位
	i = left;
	j = right;

	//开始排序
	while (i!=j) {
		//这里要注意开始的顺序，如果这个基数偏左那么就右边先开始，如果偏右那就左边先开始
		while (a[j] >=base&&i < j) {//如果右边右边的数比基数小，哨兵j停止前进，等待和i交换
			j--;
		}
		//从左边开始找
		while (a[i] <=base&&i < j) {
			i++;
		}

		//找到后交换
		if (i < j) {
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}

	//基数去到该去的位置
	a[left] = a[i];
	a[i] = base;

	
	quickSort(left, i - 1);//递归处理左边
	quickSort(j + 1, right);//递归处理右边

}


/*
选择排序
算法思想
将待排序序列分为两部分，一部分为有序序列，另一部分为无序序列。
第一趟：从a[0]到a[n-1]中找到最小的数a[i]，然后将a[i]与a[0]交换
第二趟：从a[1]到a[n-1]中找到最小的数a[j]，然后将a[j]与a[1]交换
第三趟：从a[2]到a[n-1]中找到最小的数a[k],然后将a[k]与a[2]交换 ……
时间复杂度：
O(n^2)
*/
void chooseSort(int a[], int len) {
	int min, i, j, temp,min_index;
	
	for ( i = 0; i < len - 1; i++) {
		min = a[i];
		min_index = i;
		for ( j = i; j < len - 1; j++) {
			if (a[j] < min) {
				min_index = j;
				min = a[j];
			}
		}
		if (min_index != i) {
			temp = a[min_index];
			a[min_index] = a[i];
			a[i] = temp;
		}

	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	quickSort(0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
    return 0;
}

