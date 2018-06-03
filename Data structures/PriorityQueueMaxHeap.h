#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H
#include <exception>

template <typename TValue, typename TPriority = int>
class PriorityQueueMaxHeap
{
  public:
	template <typename _TValue = TValue, typename _TPriority = TPriority>
	struct Node
	{
		//Fields
		_TValue value;
		_TPriority priority;

		//Constructor & destructor section
		Node() {}
		Node(_TValue _value, _TPriority _priority) : value(_value), priority(_priority) {}
	};

  private:
	//Fields
	using NodeType = Node<TValue, TPriority>;
	NodeType *arr;
	bool highPriorityFirst = true;

	std::size_t size = 0;
	std::size_t maxSize = 0;

	//Methods
	void heapify_up()
	{
		std::size_t currParentIndex, currentIndex = size;

		while ((currParentIndex = (currentIndex - 1) / 2) <= maxSize)
		{
			if (highPriorityFirst)
			{
				if (arr[currParentIndex].priority < arr[currentIndex].priority)
					std::swap(arr[currParentIndex], arr[currentIndex]);
				else
					break;
			}
			else
			{
				if (arr[currParentIndex].priority > arr[currentIndex].priority)
					std::swap(arr[currParentIndex], arr[currentIndex]);
				else
					break;
			}

			currentIndex = currParentIndex;
		}
	}
	void heapify_down()
	{
		std::size_t currParentIndex, lChildIndex, rChildIndex;
		std::size_t biggerChild_index;

		for (int i = 0;; i++)
		{
			if (!i)
				currParentIndex = 0;

			lChildIndex = 2 * currParentIndex + 1;
			rChildIndex = 2 * currParentIndex + 2;

			if (lChildIndex < size)
			{
				if (highPriorityFirst)
				{
					if (rChildIndex < size)
						if (arr[lChildIndex].priority > arr[rChildIndex].priority)
							biggerChild_index = lChildIndex;
						else
							biggerChild_index = rChildIndex;
					else
						biggerChild_index = lChildIndex;
				}
				else
				{
					if (rChildIndex < size)
						if (arr[lChildIndex].priority < arr[rChildIndex].priority)
							biggerChild_index = lChildIndex;
						else
							biggerChild_index = rChildIndex;
					else
						biggerChild_index = lChildIndex;
				}
			}
			else
				break;

			if (highPriorityFirst)
			{
				if (arr[currParentIndex].priority < arr[biggerChild_index].priority)
					std::swap(arr[currParentIndex], arr[biggerChild_index]);
				else
					break;
			}
			else
			{
				if (arr[currParentIndex].priority > arr[biggerChild_index].priority)
					std::swap(arr[currParentIndex], arr[biggerChild_index]);
				else
					break;
			}

			currParentIndex = biggerChild_index;
		}
	}
	void allocateArr()
	{
		if (maxSize > 0)
			arr = new NodeType[maxSize];
	}

  public:
	//Inline functions
	inline std::size_t getMaxSize() const { return maxSize; }
	inline bool isEmpty() const { return (size > 0) ? false : true; }

	//Copy constructor
	PriorityQueueMaxHeap(const PriorityQueueMaxHeap<TValue, TPriority> &other)
	{
		if (this->maxSize != other.maxSize)
		{
			clear();
			maxSize = other.maxSize;

			allocateArr();
		}
		size = other.size;
		for (int i = 0; i < size; i++)
			arr[i] = other.arr[i];
	}

	PriorityQueueMaxHeap(unsigned _maxSize = 0, bool _highPriorityFirst = true) : maxSize(_maxSize),
																				  highPriorityFirst(_highPriorityFirst)
	{
		allocateArr();
	}

	void push(TValue value, TPriority priority)
	{
		if (size >= maxSize)
			throw std::out_of_range("Heap overflow! Reached max size!");
		arr[size] = NodeType(value, priority);
		heapify_up();
		++size;
	}
	NodeType pop()
	{
		if (isEmpty())
			throw std::out_of_range("Heap is empty! Out of range in .pop()");

		std::swap(arr[0], arr[--size]);

		heapify_down();
		return arr[size];
	}

	void show()
	{
		if (isEmpty())
		{
			std::cout << "Heap is empty!" << std::endl;
			return;
		}

		std::cout << "Priority\tValue" << std::endl;
		for (int i = 0; i < size; i++)
			std::cout << arr[i].priority << "\t" << arr[i].value << std::endl;
	}

	void clear()
	{
		if (isEmpty() && maxSize)
			return;

		size = 0;
		maxSize = 0;
		delete[] arr;
	}
};

#endif