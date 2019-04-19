## Disjoint Set Data Structure

### About
The disjoint set data structure is useful in situations arising from having collections of items partitioned into one or more disjoint sets that must tracked. 

The primary operations provied by a disjoint set are:

1.  Initialize:  Given the number of items this operation intializes the data structure with each item in a unique set. Each of N sets will have size of 1 and parent pointer to itself.
2.  Find:  Given an item this operation locates the parent of that item.  For a newly initialized.
3.  Union:  Given two items this operation joins the smaller set with the larget set to create a single set.

#### Reference Implementation Details
The reference implementation, in disjoint-set.h, accepts a single template parameter as the data type for items in the sets - this defaults to int.

The public members available to consuming clients are:
1. ctor - Accepts an integer that specifies the total number of items in the collection - each item is then in its own set.
2. find - Accepts a single parameter as the set for which to locate a parent, i.e. given parameter X this member returns the parent of X.  On initializtion in the ctor each set is its own parent.
3. union\_sets - Accepts two parameters which specifies the two set in which to join.  The smaller set is joined to the larger set and the parent of the smaller is updated to the larger.
4. same\_set - Accepts two paramters with which this method returns a boolean to indicate if those are in the same set.
5. largest\_set
### Uses
1.  Kruskal's algorithm to find the minimum spanning tree of a graph with weighted edges.
2.  Largest group of friends problem (see test case in main.cc)
