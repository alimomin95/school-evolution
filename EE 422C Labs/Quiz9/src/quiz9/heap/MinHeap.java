/*
 * EE422C Quiz 9 submission by
 * Ali Ziyaan Momin
 * 16470
 * AZM259
 */

package quiz9.heap;

public class MinHeap {
	int size;
	int[] queue = new int[100];// we assume the heap will have no more
								// than 100 elements.


	int getLeftChildIndex(int nodeIndex) {
		return 2 * nodeIndex + 1;
	}

	int getRightChildIndex(int nodeIndex) {
		return 2 * nodeIndex + 2;
	}

	int getParentIndex(int nodeIndex) {
		return (nodeIndex - 1) / 2;
	}

	private void siftUp(int nodeIndex) {
		int parentIndex, tmp;
		if (nodeIndex != 0) {
			parentIndex = getParentIndex(nodeIndex);
			if (queue[parentIndex] > queue[nodeIndex]) {
				tmp = queue[parentIndex];
				queue[parentIndex] = queue[nodeIndex];
				queue[nodeIndex] = tmp;
				siftUp(parentIndex);
			}
		}
	}

	private void siftDown(int nodeIndex) {
		int leftChildIndex, rightChildIndex, minIndex, tmp;
		leftChildIndex = getLeftChildIndex(nodeIndex);
		rightChildIndex = getRightChildIndex(nodeIndex);
		if (rightChildIndex >= size) {
			if (leftChildIndex >= size)
				return;
			else
				minIndex = leftChildIndex;
		} else {
			if (queue[leftChildIndex] <= queue[rightChildIndex])
				minIndex = leftChildIndex;
			else
				minIndex = rightChildIndex;
		}
		if (queue[nodeIndex] > queue[minIndex]) {
			tmp = queue[minIndex];
			queue[minIndex] = queue[nodeIndex];
			queue[nodeIndex] = tmp;
			siftDown(minIndex);
		}
	}

	/**
	 * Inserts the specified element into this MinHeap.
	 */

	public void insert(int value) {
		if (size == queue.length)
			return;
		else {
			size++;
			queue[size - 1] = value;
			siftUp(size - 1);
		}
	}

	public void add(int value) {
		insert(value);
	}

	public void heapSort() {
		// TODO implement this method using iteration
		int start = queue[size - 1];
		while(start >= 0){
			siftDown(start);
			start = queue[size - 1];
		}
	}

	public void remove(int o) {
		// TODO you are not required to implement this method using iteration.
		// But you will get 5 points bonus if you implement it successfully.
		if (size == 0)
			return;
		else {
			queue[0] = queue[size - 1];
			size--;
			if (size > 0)
				siftDown(0);
		}
	}
}
