## Graph Data Structure

### About
A graph data structure is composed of edge connected vertices. The edges may be directed, i.e. one way, and/or weighted, i.e. implication of a per edge cost when traversing from one vertex to another.
#### Reference Implementation Details
The reference implementation, in graph.h, contains the following classes:
* vertex:  Represents a single vertex object in a graph.  This class accepts one template parameter as the identity type, which in most cases is an integer.  However the identity type could be any type such as a lat/lon pair, a person's name as a string, an object the parameters that represent a physical address, etc. This class has only one field:  id.
* edge: Represents the connection of two vertices.  This class accepts one template parameter as the identity type for the vertices the edge instance connects.  This class has three fields: (1) A source vertex. (2) A destination vertex.  (3) A weight which would be used to represent the cost to traverse the edge.
* graph:  Represents a graph comprised of edge connected vertices that need not necessirily be a fully connected graph. The core of the graph class is impletemented with a policy type for an adjacency list. The vertices are stored in an unordered\_map with the vertex as the key and a vector of edges of the value - the first edge in each item in the vector is the same of the key value, i.e. the edge source vertex in each edge in the vector is the same as the unordered\_map key.  The graph exposed an add\_edge method to connect two vertices and an access operator [] to access of type pair<vertex, vector<edge>> by identity type.

### Uses
The uses for graphs are limited only by one's imagination however graph traversal via BFS and DFS are the most common approaches to solving graph related problems.  The Algorithms section of this repository will have algorithm implementations using instances of this graph class (coming soon).

