# Path-Algorithms  
C project in visual studio 2022 using OpenGL , showcasing popular path algorithms.

## config
https://github.com/cohenyuval315/Path-Algorithms/blob/main/Graphics/main.cpp   
```code
bool INIT_MAZE = true;  // Default=True - Show the maze in the console
bool INIT_GRAPH = true;  // Default=True - Show the graph and its nodes in the console, cannot be used with INIT_MAZE (MAZE overides)
```

## Features:
- using context menu , you can choose the path algorithm
  
---

### **Maze**: 
1. Breadth-first search:  
  - unknown target position.
  - searching through all tiles at each depth level before continuing to the next depth level.
2. Depth-first search:
  - unknown target position.
  - search though the deepest depth level tile along each branch before backtracking.
3. Best-first search:
  - known target position.
  - greedily prioritize tiles by target poisiton from a starting point ,and search though all tiles at each depth level before continuing to the next depth level.
4. Astar:
  - known target position.
  - explore tiles by considering multiple paths from a starting point to a target ,and selects the shortest path based on heuristic estimates.
---
    
### **Graph**
1. Uniform Cost Search:
  - variant of Dijkstra's algorithm.
  - explores the graph by considering paths with the lowest cumulative cost from the starting point to each node.
---

---
# Preview
### Maze:
- in the video , you cant see the context menu , at first i used bf then dfs then astar

https://github.com/cohenyuval315/Path-Algorithms/assets/61754002/2d67ccae-1551-42bd-bd13-f6a42780101c


## Graph:

https://github.com/cohenyuval315/Path-Algorithms/assets/61754002/b6d7665a-eac7-4319-9824-97c46622fa1d



