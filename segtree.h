#ifndef SEGTREE_H
#define SEGTREE_H
#include<iostream>
#include<vector>
template<class T>
struct segtree {

private:

	//Stores the size of segment tree
	int size;
	//Stores the value that is stored in extra leaf nodes of segment tree
	T undefined_nodes_helper;
	//Represents the tree
	T* seg;
	//Stores the functions address which is used to combine the nodesto form the parent node
	T (*function)(T obj1, T obj2);

	//Used to calculate the size of the segment-tree
	void segtree_size(int n)
	{
		size = 1;
		while (size < n)size *= 2;
		size = 2 * size - 1;
		return;
	}

	//A recursive function to help the query function in answering the queries
	T query_helper(int l, int r, int root, int lx, int rx)
	{
		if (lx >= r or rx<=l or l>r)
			return undefined_nodes_helper;

		if (lx >= l and rx <= r)
			return seg[root];

		return function(query_helper(l, r, 2 * root + 1, lx, (lx + rx) / 2), query_helper(l, r, 2 * root + 2, (lx + rx) / 2 , rx));
	}

	//A recursive function to help the query function in answering the queries
	void update_helper(int i, T v, int root, int lx, int rx)
	{
		if (rx - lx == 1) {
			seg[root] = v;
			return;
		}


		int mid = (lx + rx) / 2;
		if (i < mid)
			update_helper(i, v, 2 * root + 1, lx, mid);
		else
			update_helper(i, v, 2 * root + 2, mid, rx);

		seg[root] = function(seg[2 * root + 1], seg[2 * root + 2]);
	}


public:

	//Used to build the tree
	void buildtree(std::vector<T> data, T value, T(* query_function)(T obj1, T obj2))
	{
		int n = data.size();
		segtree_size(n);
		int extra = (size / 2 + 1) - n;
		function = query_function;
		undefined_nodes_helper = value;
		for (int i = size - 1; i >= 0; i--)
		{
			if (extra) {
				seg[i] = value;
				extra--;
			}

			else if (n)
			{
				seg[i] = data[n - 1];
				n--;
			}

			else
			{
				seg[i] = query_function(seg[2 * i + 1], seg[2 * i + 2]);
			}
		}

	}
	//Used to build the tree
	void buildtree(T arr[], int n, T value, T(* query_function)(T obj1, T obj2))
	{
		undefined_nodes_helper = value;
		segtree_size(n);
		seg = new T[size];
		int extra = (size / 2 + 1) - n;
		function = query_function;
		for (int i = size - 1; i >= 0; i--)
		{
			if (extra > 0) {
				seg[i] = value;
				extra--;
			}

			else if (n > 0)
			{
				seg[i] = arr[n - 1];
				n--;
			}

			else
			{
				seg[i] = function(seg[2 * i + 1], seg[2 * i + 2]);
			}
		}

	}

	//To answer the query from l to r
	T query(int l, int r)
	{
		return query_helper(l, r, 0, 0, size / 2 +1);
	}

	//To update the value at index i with v
	void update(int i, T v)
	{
		update_helper(i, v, 0, 0, size / 2 + 1);
	}

	//To print the segment tree
	void print_segtree()
	{
		for (int i = 0; i < size; i++)
			std::cout << seg[i] << "    ";
	}
};
#endif // SEGTREE_H
