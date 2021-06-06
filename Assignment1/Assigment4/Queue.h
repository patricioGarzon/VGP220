#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue 
{
public:
	Queue();
	~Queue();

	//ERROR: -5: You are overflowing the buffer

	//Inserts the data in the queue.
	void Enqueue(T data) {
		if (!isEmpty()) {
			if (mCurrentSize < mCapacity) {
				mData[mCurrentSize] = data;
				mCurrentSize++;
			}
			else {
				std::cout << "queu is full";
			}
		}
		else {
			mData[mCurrentSize] = data;
			rear++;
			mCurrentSize++;
		}
	}
	
	//ERROR: -5 .You are just advancing with iterators without a managed memory.
	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output) {
		if (!isEmpty()) {
			output = mData[front];
			front++;
			return true;
		}
		else {
			return false;
		}
	}
	
	//Returns true if queue is empty, false otherwise
	bool isEmpty() {
		if (mCurrentSize != 0) {
			return false;
		}
		else {
			return true;
		}
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue() {
		for (int x = front; x < mCurrentSize; x++) {
			std::cout << "data: " << mData[x] << std::endl;
		}
	}
private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;
};

template<typename T>
 Queue<T>::Queue()
{
	front = 0;
	rear = 0;
	mCapacity = 10;
	mCurrentSize = 0;
	mData = new T[mCapacity];
}

 //ERROR: -2 Dangling pointers. mData = nullptr;
template<typename T>
inline Queue<T>::~Queue()
{
	delete[] mData;
}
