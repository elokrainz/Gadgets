/************************************************************************
* Description:	float radix sort & (unsigned) int radix sort impletement by C++
* Version:		1.0
* Date:			2015/06/28
* Author:		Elokrainz Zhang
* Email:		Elokrainz@gmail.com
************************************************************************/
#include<algorithm>

namespace Elokrainz
{
	template <typename type>
	void radix_unit_sort(type *arr, type *sorted_arr, unsigned int *bin, const int &len, const unsigned int &radix, const unsigned int &mask, const unsigned int shift)
	{
		int i = 0;
		memset(bin, 0x00, sizeof(int)*radix);

		for(i = 0; i < len; ++i)  ++bin[(arr[i]>>shift)&mask];		// count

		for(i = 1; i < radix; ++i)  bin[i] += bin[i-1];				// calc the indx

		for(i = len-1; i >= 0; --i)  sorted_arr[--bin[(arr[i]>>shift)&mask]] = arr[i];	// assign number to array
	}
	void radix_unit_sort_sign(int *arr, int *sorted_arr, unsigned int *bin, const int &len, const unsigned int &radix, const unsigned int &mask, const unsigned int shift)
	{
		int i = 0;
		memset(bin, 0x00, sizeof(int)*radix);

		for(i = 0; i < len; ++i)  ++bin[(arr[i]>>shift)&mask];		// count

		for(i = 1+(radix>>1); i < radix; ++i) bin[i] += bin[i-1];	// negative numbers
		bin[0] += bin[radix-1];
		for(i = 1; i <= (radix>>1); ++i) bin[i] += bin[i-1];		// positive numbers

		for(i = len-1; i >= 0; --i)  sorted_arr[--bin[(arr[i]>>shift)&mask]] = arr[i];	// assign number to array
	}
	
	void radix_sort(unsigned int *arr, const int len)
	{
		if( nullptr == arr || len < 2 ) return;

		const unsigned int RADIX = 256;
		const unsigned int MASK = RADIX-1;
		
		unsigned int bin[RADIX];
		unsigned int *sorted_arr = new unsigned int [len];

		//  0- 7 bits
		radix_unit_sort(arr, sorted_arr, bin, len, RADIX, MASK, 0);
		//  8-15 bits
		radix_unit_sort(sorted_arr, arr, bin, len, RADIX, MASK, 8);
		// 16-23 bits
		radix_unit_sort(arr, sorted_arr, bin, len, RADIX, MASK, 16);
		// 24-31 bits
		radix_unit_sort(sorted_arr, arr, bin, len, RADIX, MASK, 24);

		delete [] sorted_arr;
	}
	
	void radix_sort(int *arr, const int len)
	{
		if( nullptr == arr || len < 2 ) return;

		const unsigned int RADIX = 256;
		const unsigned int MASK = RADIX-1;
		
		unsigned int bin[RADIX];
		int *sorted_arr = new int [len];

		//  0- 7 bits
		radix_unit_sort(arr, sorted_arr, bin, len, RADIX, MASK, 0);
		//  8-15 bits
		radix_unit_sort(sorted_arr, arr, bin, len, RADIX, MASK, 8);
		// 16-23 bits
		radix_unit_sort(arr, sorted_arr, bin, len, RADIX, MASK, 16);
		// 24-31 bits
		radix_unit_sort_sign(sorted_arr, arr, bin, len, RADIX, MASK, 24);

		delete [] sorted_arr;
	}
	
	void radix_sort(float *arr, const int len)
	{
		if( nullptr == arr || len < 2 ) return;

		// binary convert float to int ( binary copy )
	    int *int_arr = new int[len];
	    for(int i = 0; i < len; ++i)
	        int_arr[i] = *reinterpret_cast<int*>(&arr[i]);
	    // using radix sort for int
	    radix_sort(int_arr, len);

		// binary convert int to float ( binary copy )
	    for(int i = 0; i < len; ++i)
	        arr[i] = *reinterpret_cast<float*>(&int_arr[i]);

	    // since the bigger the negative exponent, the smaller the number is. Should reverse all negative numbers  
	    int left = -1, right = 0;
	    for(right = 0; right < len; ++right) if(arr[right] >= 0) break;
		while(++left < --right) std::swap(arr[left], arr[right]);

	    delete [] int_arr;
	}
}
