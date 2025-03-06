#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector> // double check if i am allowed to include vector
#include <algorithm> // for swap as stated on piazza

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  std::vector<T> _data; // data of the PQ
  int _m; // stores the max number of children of each node
  PComparator _c; // stores the specific comp functor
  void heapify(int idx); // will be used to maintain heap structure later on
  void bubbleUp(int idx); // reverse of heapify
  // might need to add functors here
  // greater than functor is included in <functional>
  // less than functor is inluded in stl and is class default
};

// Add implementation of member functions here - top/pop are implemented later

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : _m(m), _c(c) {} // creates m and c then heap

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator> // I got this function from the heap slides
void Heap<T, PComparator>::bubbleUp(int idx) {
  if(idx==0) return; // if curr is the root, leave
  int parent = (idx - 1) / _m;
  if(_c(_data[idx], _data[parent])) {
    std::swap(_data[idx], _data[parent]);
    bubbleUp(parent);
  }
}


template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  _data.push_back(item); // add to the end of the vector
  // need to add the heap alg using swap()
  /* 0-indexed relations:
  node: i
  parent: (i-1)/m
  child: (m*i) + k + 1
  */
  //use slides for binary then change to m-ary
  // make a trickleup() and trickledown() helper function
  bubbleUp((_data.size()) - 1); // ^^
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return _data.empty(); // if vector is empty return true
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return _data.size();
}


template <typename T, typename PComparator> // I got this function from the heap slides
void Heap<T, PComparator>::heapify(int idx) {
  if ((idx * _m) + 1 >= this->size()) return; // if idx is leaf, leave
  
  int priorityChild = (idx * _m) + 1; // start w/ left
  for(int i=1; i < _m; i++) {
    int otherChild = (idx * _m)+1+i; // loops through children
    if(otherChild < this->size() && _c(_data[otherChild], _data[priorityChild])) { // sees if its smaller than curr smallest
      priorityChild = otherChild;
    }
  }
  if (priorityChild < _data.size() && _c(_data[priorityChild], _data[idx])) {
    std::swap(_data[idx], _data[priorityChild]);
    heapify(priorityChild);
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return _data.front();
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }

  std::swap(_data.front(), _data.back());
  _data.pop_back(); // this swaps first and last elemtn so we can pop highest priority in O(1)
  if(!empty()) { // check post pop
    heapify(0); //calls heapify to bubble down
  }
  
}



#endif

