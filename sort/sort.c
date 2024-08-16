#include <stdio.h>

void debug_int_arr(int *arr, int left, int right)
{
	if (left >= right)
		return;
	printf("[");
	for (int i = left; i < right; i++)
		printf("%d, ", arr[i]);
	printf("]\n");
}

void merge(int *arr, int left, int mid, int right)
{
	// printf("Entering merge...\nLeft: %d, Right: %d\n", left, right);
	int i, j;

	int len1 = mid - left;
	int len2 = right - mid;

	int L[len1], R[len2];

	for (i = 0; i < len1; i++)
		L[i] = arr[left + i];
	for (i = 0; i < len2; i++)
		R[i] = arr[mid + i];
	// debug_int_arr(L, 0, len1);
	// debug_int_arr(R, 0, len2);

	debug_int_arr(L, 0, len1);
	debug_int_arr(R, 0, len2);
	i = j = 0;
	int k = left;

	while (i < len1 && j < len2)
	{
		if (L[i] < R[j])
		{
			arr[k] = L[i];
			i++;
		} else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < len1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < len2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

int *mergesort(int *items, int left, int right)
{
	// debug_int_arr(items, left, right);
	// printf("Left: %d, Right: %d\n", left, right);
	if (left < right)
	{
		int mid = (right + left) / 2;
		if (right - left > 1)
		{
			mergesort(items, left, mid);
			mergesort(items, mid, right);
		}
		merge(items, left, mid, right);
		debug_int_arr(items, left, right);
	}
	return items;
}


int main(void)
{
	int items[] = {1, 5, 4, 7, 8, 2, 3, 10, 4};
	printf("%lu\n", sizeof items);
	printf("%p\n", items);
	int item_size =(sizeof items) / sizeof(int);
	int *result = mergesort(items, 0, item_size);
	// debug_int_arr(result, 0, item_size);
}
