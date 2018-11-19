#include "BinaryHeap.h"
#include <iostream>
#include <limits>
using namespace std;
BinaryHeap::BinaryHeap(const double* priorities, int numItems){
	heap=new int[numItems];
	size=numItems;
	in_priorities=new double[numItems];
	locations=new int[numItems];
	for(int i =0; i<numItems; i++){
		heap[i]=i;
		in_priorities[i]=priorities[i];
		locations[i]=i;
	}
	for(int i=(size-1); i>=0; i--){
		//cout<<"i is "<<i<<endl;
		this->heapify(i);
	}
	//cout<<" root "<<heap[0]<<endl;
	//cout<<" roots left and right "<<heap[this->getLeft(0)]<<" "<<heap[this->getRight(0)]<<endl;
	//cout<<"left's children "<<heap[this->getLeft(1)]<<" "<<heap[this->getRight(1)]<<endl;
	//cout<<"right's children "<<heap[this->getLeft(2)]<<" "<<heap[this->getRight(2)]<<endl;

}
BinaryHeap::~BinaryHeap(){
	delete[] this->heap;
	delete[] this->locations;
	delete[] in_priorities;
}
int BinaryHeap::getParent(int pos){

	return (pos-1)/2;
}
int BinaryHeap::getLeft(int pos){
	return 2*(pos)+1;
}
int BinaryHeap::getRight(int pos){
	return (2*(pos))+2;
}
void BinaryHeap::heapify(int pos){
	int left_ch=this->getLeft(pos);
	int right_ch=this->getRight(pos);
	int min;
	if(left_ch<(size-1) && (in_priorities[heap[left_ch]]<in_priorities[heap[pos]])){
		min=left_ch;
	} else{
		min=pos;
	}
	if(right_ch<(size-1) && (in_priorities[heap[right_ch]]<in_priorities[heap[min]])){
		min=right_ch;
	}
	if(min!=pos){

		locations[heap[min]]=pos;
		locations[heap[pos]]=min;
		int p1 = heap[min];
		int p2 = heap[pos];
		heap[min]=p2;
		heap[pos]=p1;
		//std::swap(heap[min],heap[pos]);
		//std::swap(this->locations[this->heap[min]],this->locations[this->heap[pos]]);
		
		this->heapify(min);
	}

}
int BinaryHeap::getMin() const{
	return this->heap[0];
}
void BinaryHeap::popMin(){
	//
	locations[heap[size-1]]=locations[heap[0]];
	locations[heap[0]]=numeric_limits<int>::max();
	int p1=heap[0];
	int p2=heap[size-1];
	heap[0]=p2;
	heap[size-1]=p1;
	size-=1;
	//
	this->heapify(0);
}
bool BinaryHeap::contains(int item) const{
	if(this->locations[item]==(numeric_limits<int>::max())){
		return false;
	} else{
		return true;
	}

}
double BinaryHeap::getPriority(int item) const{
	return in_priorities[item];
}
void BinaryHeap::decreasePriority(int item, double newPriority){

	/*int i=0;
	bool found=false;
	while(!found){
		if(heap[i]==item){
			found=true;
		} else{
			i+=1;
		}
	}*/
	//cout<<"check for equality: "<<i<<"  =  "<<this->getPos(item)<<endl;
	int i = this->getPos(item);
	if(newPriority<in_priorities[item]){
		in_priorities[item]=newPriority;
		while(i>0 && in_priorities[heap[this->getParent(i)]]>in_priorities[heap[i]]){
			locations[heap[i]]=this->getParent(i);
			locations[heap[this->getParent(i)]]=i;
			int p1=heap[i];
			int p2=heap[this->getParent(i)];
			heap[i]=p2;
			heap[this->getParent(i)]=p1;
			//std::swap(heap[i],heap[this->getParent(i)]);
		
			i=this->getParent(i);
		}
	}
}
int BinaryHeap::getSize() const{
	return size;
}
int BinaryHeap::getItem(int pos) const{
	return heap[pos];
}
int BinaryHeap::getPos(int item) const{
	return locations[item];
	
}
void BinaryHeap::printHeap(){
	for(int i =0; i<this->size; i++){
		cout<<heap[i]<<"  "<<i<<"  loc  "<<locations[heap[i]]<<endl;
	}
	
}


















