template<typename T>
class PriorityQueue {

	T* m_data[300];  // as we have only 256 characters in keyboard 
	int m_size;

public:
	PriorityQueue() {
		m_size = 0;
	}
	int getsize() {
		return m_size;
	}
	bool isEmpty() {
		return m_size == 0;
	}
	T* getmin() {
		if (isEmpty()) {
			//cout << "Empty Queue" << endl;
			return nullptr;
		}
		return m_data[0];
	}

private:
	void swap(T** data1, T** data2) {
		T* temp = *data1;
		*data1 = *data2;
		*data2 = temp;
	}

public:

	void insert(T* element) {

		m_data[m_size] = element;
		++m_size;
		int childindex = m_size - 1;

		while (childindex > 0) {
			int parentindex = (childindex - 1) / 2;
			if (m_data[childindex]->frequency < m_data[parentindex]->frequency) {
				swap(&m_data[childindex], &m_data[parentindex]);
			}
			else {
				break;
			}
			childindex = parentindex;
		}
	}
	void removeMin() {

		T* ans = m_data[0];
		m_data[0] = m_data[m_size - 1];
		--m_size;

		// downfy heap;
		int parentindex = 0;
		int leftchildindex = 2 * parentindex + 1;
		int rightchildindex = 2 * parentindex + 2;

		while (leftchildindex < m_size) {  // if not left child then 100% No right child;
			int minindex = parentindex;
			if (m_data[minindex]->frequency > m_data[leftchildindex]->frequency) {
				minindex = leftchildindex;
			}
			if (rightchildindex < m_size && m_data[rightchildindex]->frequency < m_data[minindex]->frequency) {
				minindex = rightchildindex;
			}
			if (minindex == parentindex) {
				break;
			}
			swap(&m_data[minindex], &m_data[parentindex]);

			parentindex = minindex;
			leftchildindex = 2 * parentindex + 1;
			rightchildindex = 2 * parentindex + 2;
		}
	}
};