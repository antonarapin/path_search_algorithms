#ifndef BINARY_HEAP
#define BINARY_HEAP
#include <iostream>

class BinaryHeap{
	private:
		int* heap; //locations shuffled here
		double* in_priorities; //distances
		int* locations;
		int size;
	public:
		BinaryHeap(const double* priorities, int numItems);
		~BinaryHeap();
		virtual int getMin() const;
		virtual void popMin();
		virtual bool contains(int item) const;
		virtual double getPriority(int item) const;
		virtual void decreasePriority(int item, double newPriority);
		virtual int getSize() const;
		virtual int getItem(int pos) const;
		virtual int getPos(int item) const;
		virtual void heapify(int pos);
		virtual int getParent(int pos);
		virtual int getLeft(int pos);
		virtual int getRight(int pos);
		virtual void printHeap();


};
#endif