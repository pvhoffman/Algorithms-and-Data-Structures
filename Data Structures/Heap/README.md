## Heap Data Structure
#### About
A heap is an efficient implementation of a priority queue which maintains a partial - weak - ordering and exposes operations to insert, extract the 'top' element, and determine the number of elements contained.  The 'top' element can represent the minimum value in a min-heap or the maximum value in a max-heap.  As the 'top' value is extracted, or popped, the heap is partially reordered in O(n log n) time. Maintaining a partial ordering on insertion requires O(n log n) time.

The most objectively interesting aspect of a heap is the internal representation of a binary tree using an array or vector.


#### Reference Implementation Details
The reference implementation, in heap.h, accepts two class template parameters:
1.  The data type stored in the heap.
2.  A comparison policy class implementation which determines the heap order, e.g. min-heap or max-heap.
The second template parameter defaults to a min-heap.

An integer min-heap could be aliased thusly:
    using IntegerMinHeap = pvh::heap<int, pvh::heap_compare_min>;

An integer max-heap could be aliased thusly:
    using IntegerMaxHeap = pvh::heap<int, pvh::heap_compare_max>;

The public members available to consuming clients are:
*  insert - Accepts a single parameter of the type specified in the first template parameter and does not return a value. Executes in O(n log n) time to maintain partial ordering.
*  top - Returns the minimum or maximum value, depending upon the second template parameter, and throws an exception of type pvh::heap\_empty\_exception if the heap contains no elements.  After return from this method the size of the heap is decreased by one. Executes in O(n log n) time to maintain partial ordering.
*  size - Returns the number of elements in the heap. Executes in O(1) time.

### Some Uses
The general use case for the heap data structure is in the form of a priority queue.
1.  Thread scheduling.
2.  Shortest path finding algorithms for graphs with weighted edges (Dijkstra).
3.  Load balancing.
4.  Busiest network nodes.
5.  Heapsort.







