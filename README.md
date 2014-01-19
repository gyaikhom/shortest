# Shortest Path

Implements the following algorithms:

* Dijkstra's shortest path algorithm
* Floyd-Warshall all-pair shortest path algorithm

and applies them to a navigation application.


## Compiling the application

Generate the Cmake files and build the application.

    $ mkdir build
    $ cd build
    $ cmake -G "Unix Makefiles" ..
    $ make

## Usage

    shortest locations.map [source] [destination]

Display this help message if no arguments are provided.

This application implements two approaches to finding out the
shortest path between two landmarks on a locations map:

1) Dijkstra's shortest path algorithm:
    This algorithm allows us to find the shortest path
   between two landmarks: the source and the destination.

   To use this approach, provide four arguments to this
   application, as follows:

        shortest locations.map 2 3

   where, 2 and 3 are respectively the indices of the source
   and the destination landmarks in locations.map. Note that
   indexing beings at zero, and not at one).

   Alternatively, the user may also specify the landmarks by name.
   For instance,

        shortest locations.map "Edinburgh" "Oxford"

2) Floyd-Warshall's all-pair shortest paths algorithm:
   This algorithm allows us to find all of the shortest paths
   between every landmark on the locations.map. It is particularly
   useful when we wish to generate all of the paths for display
   at each of the landmarks.

   To use this approach, invoke the application as follows:

        shortest locations.map
