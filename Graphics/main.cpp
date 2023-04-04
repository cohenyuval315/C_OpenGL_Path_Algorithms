
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include <vector>
#include "Cell.h"
#include <iostream>
#include "Vertex.h"
#include "Edge.h"
#include <queue>
#include <vector>
#include "CompareVertices.h"
#include "DistanceCompareCells.h"
#include "RootDistanceCompareCells.h"
#include "Definitions.h"
#include "Node.h"
#include "CompareNodes.h"


using namespace std;


typedef enum {
	MAZE_BFS,
	MAZE_DFS,
	MAZE_BESTFS,
	MAZE_ASTAR,
	GRAPH_UCS,
	GRAPH_ASTAR,
	PUZZLE_ASTAR,
} RunOption;


const int NUM_VERTICES = 800;
const int NUM_EDGES = 1200;
Vertex vertices[NUM_VERTICES];
Edge edges[NUM_EDGES];


bool INIT_MAZE = true;
bool INIT_GRAPH = true;
bool INIT_PUZZLE = true;




int maze[MSZ][MSZ] = {0};

bool isFin = false, isRun = false;
bool runMazeBFS = false, runMazeDFS = false, runGraphUCS = false,runMazeBestFS = false, runMazeAStar = false, runPuzzleAStar = false;

vector <Cell*> grays;
priority_queue <Vertex*, vector<Vertex*>, CompareVertices> pq;
DistanceCompareCells cmp;
RootDistanceCompareCells rcmp;

priority_queue <Cell*, vector<Cell*>, DistanceCompareCells> pq_maze;
priority_queue <Cell*, vector<Cell*>, RootDistanceCompareCells> a_star_pq_maze;


Node* pn = new Node();


priority_queue <Cell*, vector<Cell*>, DistanceCompareCells> create_pq_maze(DistanceCompareCells cmp) {
	priority_queue <Cell*, vector<Cell*>, DistanceCompareCells> pq_maze(cmp);
	return pq_maze;
}

priority_queue <Cell*, vector<Cell*>, RootDistanceCompareCells> create_a_star_pq_maze(RootDistanceCompareCells rcmp) {
	priority_queue <Cell*, vector<Cell*>, RootDistanceCompareCells> a_star_pq_maze(rcmp);
	return a_star_pq_maze;
}

void InitMaze();
void InitGraph();
void InitPuzzle();


void StopIteration() {
	if (isFin) {
		return;
	}
	runMazeAStar = false;
	runMazeBestFS = false;
	runMazeBFS = false;
	runMazeDFS = false;
	runGraphUCS = false;
	runPuzzleAStar = false;
	
	cout << "stopped iterations \n";
}

void init()
{
	srand(time(0));
	//glClearColor(1, 1.1, 1.1, 1);// color of window background
	//glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system

	
	if (INIT_MAZE) {
		glClearColor(1, 1.1, 1.1, 1);// color of window background
		glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system
		InitMaze();
	}
	else if (INIT_GRAPH) {
		glClearColor(1, 1.1, 1.1, 1);// color of window background
		glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system
		InitGraph();
	}
	else if (INIT_PUZZLE) {
		glClearColor(1, 1, 1, 0);// color of window background
		glOrtho(0, 4, 4, 0, -1, 1); 
	}
	
}

void Run(RunOption runOption) {
	StopIteration();
	std::string str;
	str = "running ";

	switch (runOption) {
	case MAZE_BFS:
		runMazeBFS = true;
		str.append("BFS");
		break;
	case MAZE_DFS:
		runMazeDFS = true;
		str.append("DFS");
		break;
	case GRAPH_UCS:
		runGraphUCS = true;
		str.append("UCS");
		break;
	case MAZE_BESTFS:
		runMazeBestFS = true;
		if (isRun) {
			runMazeBestFS = false;
			str.append(" can only be from start with this algorithm : ");
		}
		str.append("Best FS");
		break;
	case MAZE_ASTAR:
		runMazeAStar = true;
		str.append("Astar");
		break;
	case PUZZLE_ASTAR:
		runPuzzleAStar = true;
		str.append("A star in maze");
		break;
	}
	str.append("\n");

	if (!isFin) {
		cout << str;
	}
	isRun = true;
}


void SolutionFound(bool found) {
	StopIteration();
	isFin = true;
	if (found) {
		cout << "The solution been found\n";
	}
	else {
		cout << "The solution not been found\n";
	}
	cout << " FINISH ,please close \n";
}

void RestorePath(Cell* pc)
{
	while (pc->getParent() != nullptr)
	{
		maze[pc->getRow()][pc->getColumn()] = PATH;
		pc = pc->getParent();
	}
}



//---- PUZZLE ------

void InitPuzzle() {
	pn->draw();
}

void DrawPuzzle() {
	pn->draw();
}

bool PuzzleCheckNeighbor(Node* pCurrent, int direction,
	priority_queue <Node*, vector<Node*>, CompareNodes>& pq, vector<Node>& grays, vector<Node>& blacks)
{
	Node* pNeighbor;
	pNeighbor = new Node(pCurrent, direction);
	return false;
}

void PuzzleRunAStar()
{
	bool solutionFound = false;
	Node* pCurrent;
	priority_queue <Node*, vector<Node*>, CompareNodes> puzzle_pq;
	vector<Node> grays;
	vector<Node> blacks;
	vector<Node>::iterator itGray;

	// prepare pq and grays
	puzzle_pq.push(pn);
	grays.push_back(*pn);


	while (!puzzle_pq.empty() && !solutionFound)
	{
		pCurrent = puzzle_pq.top();
		puzzle_pq.pop();
		// paint pCurrent black
		itGray = find(grays.begin(), grays.end(), *pCurrent); // must be based on oprator ==
		if (itGray == grays.end())
		{
			cout << "ERROR! pCurrent wasn't found in grays \n";
			return;
		}
		else // pCurrent was found
			grays.erase(itGray);
		blacks.push_back(*pCurrent);
		// check neighbors of pCurrent
		// top neighbor
		if (pCurrent->getEmptyRow() > 0)
			solutionFound = PuzzleCheckNeighbor(pCurrent, UP, puzzle_pq, grays, blacks);
		if (!solutionFound && pCurrent->getEmptyRow() < BSZ - 1)
			solutionFound = PuzzleCheckNeighbor(pCurrent, DOWN, puzzle_pq, grays, blacks);
		if (!solutionFound && pCurrent->getEmptyCol() > 0)
			solutionFound = PuzzleCheckNeighbor(pCurrent, LEFT, puzzle_pq, grays, blacks);
		if (!solutionFound && pCurrent->getEmptyCol() < BSZ - 1)
			solutionFound = PuzzleCheckNeighbor(pCurrent, RIGHT, puzzle_pq, grays, blacks);

	}


}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// xx and yy are the cell coordinates
		double xx = 4 * x / (double)W;
		double yy = 4 * y / (double)H;
		if (pn->isAdjacent((int)yy, (int)xx))
			pn->exchangeCells((int)yy, (int)xx);

	}
}

// ----------------


//---- GRAPH ------

double Distance(int index1, int index2)
{
	int x1, y1, x2, y2;

	x1 = vertices[index1].getX();
	y1 = vertices[index1].getY();

	x2 = vertices[index2].getX();
	y2 = vertices[index2].getY();

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void InitGraph()
{
	int i;
	int index1, index2;
	int MAX_DIST = 11;
	// setup Vertices

	for (i = 0; i < NUM_VERTICES; i++)
	{
		vertices[i].setX(2 + rand() % (MSZ - 2));
		vertices[i].setY(2 + rand() % (MSZ - 2));
	}
	// setup Edges

	for (i = 0; i < NUM_EDGES; i++)
	{
		do {
			index1 = rand() % NUM_VERTICES;
			index2 = rand() % NUM_VERTICES;
		} while (Distance(index1, index2) > MAX_DIST);

		edges[i].setVertex1(&vertices[index1]);
		edges[i].setVertex2(&vertices[index2]);
		edges[i].setCost(Distance(index1, index2));
		vertices[index1].addOutgoingEdge(&edges[i]);
		vertices[index2].addOutgoingEdge(&edges[i]);

	}


	vertices[0].setColor(START);
	vertices[0].setG(0);

	pq.push(&vertices[0]); // prepare Priority Queue

	vertices[1].setColor(WHITE_TARGET);

}

void DrawGraph()
{
	// show vertices
	int i;

	for (i = 0; i < NUM_EDGES; i++)
		edges[i].draw();

	for (i = 0; i < NUM_VERTICES; i++)
		vertices[i].draw();
}

void BuildFont() {
	HFONT hFont;
	GLuint fontBaes = glGenLists(256);
	hFont = CreateFont(-0.5, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DECORATIVE, "VictorianD");

}

void UpdatePQ(Vertex* pNeighbor, Vertex* parent, double cost)
{
	// start extracting Vertices from PQ until we find pn
	// then update G of pn and push back all the Vertices that were extracted

	vector<Vertex*> temp;
	Vertex* pn;
	while (!pq.empty() && pq.top() != pNeighbor)
	{
		temp.push_back(pq.top());
		pq.pop();
	}
	if (pq.empty())
	{
		cout << "ERROR. Can't find gray in PQ\n";
		exit(1);
	}
	else // pNeighbor is now at top of PQ
	{
		pn = pq.top();
		pq.pop();
		pn->setG(cost + parent->getG());
		pn->setParent(parent);
		pq.push(pn);

		while (!temp.empty())
		{
			pq.push(temp.back());
			temp.pop_back();
		}
	}
}

void CheckNeighborInGraph(Vertex* pCurrent, Vertex* pNeighbor, double cost)
{
	switch (pNeighbor->getColor())
	{
	case WHITE:
		pNeighbor->setColor(GRAY);
		pNeighbor->setParent(pCurrent);
		pNeighbor->setG(cost + pCurrent->getG());
		pq.push(pNeighbor);
		break;
	case GRAY:
	case GRAY_TARGET:
		if (pNeighbor->getG() > cost + pCurrent->getG()) // update new info
			UpdatePQ(pNeighbor, pCurrent, cost);
		break;
	case WHITE_TARGET:
		pNeighbor->setColor(GRAY_TARGET);
		pNeighbor->setParent(pCurrent);
		pNeighbor->setG(cost + pCurrent->getG());
		pq.push(pNeighbor);
		break;
	}
}

void RestorePathInGraph(Vertex* pv)
{
	pv = pv->getParent();
	while (pv->getParent() != nullptr)
	{
		pv->setColor(PATH);
		pv = pv->getParent();
	}
}

void RunUCSIterationGraph()
{
	Vertex* pCurrent;
	Vertex* pNeighbor;
	vector<Edge*> outgoing;
	if (pq.empty())
	{
		runGraphUCS = false; // stop running UCS
		cout << "No solution\n";
		return;
	}
	else // pq is not empty
	{
		pCurrent = pq.top();
		if (pCurrent->getColor() == GRAY_TARGET)
		{
			runGraphUCS = false; // stop running UCS
			cout << "The solution has been found\n";
			RestorePathInGraph(pCurrent);
			return;
		}
		pCurrent->setColor(BLACK);
		pq.pop();
		// Now check the neighbors of pCurrent
		outgoing = pCurrent->getOutgoing();
		for (auto it : outgoing)
		{ // find the neighbors of pCurrent
			if (it->getVertex1() == pCurrent)
				pNeighbor = it->getVertex2();
			else pNeighbor = it->getVertex1();
			CheckNeighborInGraph(pCurrent, pNeighbor, it->getCost());
		}

	}
}

// ----------------




//---- MAZE ------

void InitMaze()
{
	int i, j;
	
	// creating frame walls 
	for (i = 0; i < MSZ; i++)
	{
		maze[0][i] = WALL;
		maze[MSZ - 1][i] = WALL;
		maze[i][0] = WALL;
		maze[i][MSZ - 1] = WALL;
	}
	// random walls
	for (i = 1; i < MSZ - 1; i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			if (i % 2 == 0) // mostly spaces = no wall
			{
				if (rand() % 100 < 80)
					maze[i][j] = SPACE;
				else
					maze[i][j] = WALL;
			}
			else //  mostly walls
			{
				if (rand() % 100 < 60)
					maze[i][j] = WALL;
				else
					maze[i][j] = SPACE;
			}
		}
	// set START and TARGET
	int start_x = MSZ / 2;
	int start_y = MSZ / 2;
	maze[start_x][start_y] = START;

	// add start Cell to grays
	Cell* pc = new Cell(start_x, start_y, nullptr);
	

	int target_x = rand() % MSZ;
	int target_y = rand() % MSZ;
	maze[target_x][target_y] = TARGET;

	cmp.setTarget(target_x, target_y);
	rcmp.setTarget(target_x, target_y);
	rcmp.setStart(start_x, start_y);

	grays.push_back(pc);
	
	pq_maze = create_pq_maze(cmp);
	pq_maze.push(pc);

	a_star_pq_maze = create_a_star_pq_maze(rcmp);
	a_star_pq_maze.push(pc);
	
}

void DrawMaze()
{
	int i, j;

	for (i = 0;i < MSZ;i++)
		for (j = 0; j < MSZ; j++)
		{
			switch (maze[i][j])
			{
			case SPACE:
				glColor3d(0.9, 0.9, 0.9); // light gray
				break;
			case WALL:
				glColor3d(0.3, 0.3, 0.3); // dark gray
				break;
			case START:
				glColor3d(0.5, 0.5, 0.9); // blue
				break;
			case TARGET:
				glColor3d(0, 1, 0); // green
				break;
			case BLACK:
				glColor3d(0.7, 1, 0.7); // light green
				break;
			case GRAY:
				glColor3d(1, 0.3, 0); // orange
				break;
			case PATH:
				glColor3d(0.8, 0.5, 1); // purple
				break;
			}
			// draw square
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j + 1, i);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j, i + 1);
			glEnd();
		}

}

void CheckNeighbor(int row, int column, Cell* pcurrent)
{
	if (maze[row][column] == TARGET)
	{
		SolutionFound(true);
		RestorePath(pcurrent);
	}
	else // maze[row][column] is WHITE
	{
		Cell* pn = new Cell(row, column, pcurrent);

		// paint this neighbor gray
		grays.push_back(pn);
		pq_maze.push(pn);
		a_star_pq_maze.push(pn);
		maze[row][column] = GRAY;
	}
}

void RunBFSIteration()
{
	Cell* pcurrent;
	int r, c;
	if (grays.empty()) // no solution exists
	{
		SolutionFound(false);
		return;
	}
	else // grays is not empty
	{
		pcurrent = *grays.begin();
		r = pcurrent->getRow();
		c = pcurrent->getColumn();
		maze[r][c] = BLACK; // paint it black
		grays.erase(grays.begin());

		if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET)
			CheckNeighbor(r + 1, c, pcurrent);
		// DOWN
		if (runMazeBFS && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET))
			CheckNeighbor(r - 1, c, pcurrent);
		// LEFT
		if (runMazeBFS && (maze[r][c - 1] == SPACE || maze[r][c - 1] == TARGET))
			CheckNeighbor(r , c- 1, pcurrent);
		// RIGHT
		if (runMazeBFS && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET))
			CheckNeighbor(r, c + 1, pcurrent);

	}
}

void RunDFSIteration() 
{
	Cell* pcurrent;
	int r, c;

	if (grays.empty())
	{
		SolutionFound(false);
		return;
	}
	else
	{
		pcurrent = grays.back(); // DFS uses STACK
		r = pcurrent->getRow();
		c = pcurrent->getColumn();
		maze[r][c] = BLACK; // paint it black
		grays.pop_back();

		// check neighbors (use random direction)
		int directions[4] = { -1,-1,-1,-1 };
		int dir,place;
		for (dir = 0; dir < 4; dir++)
		{
			do {
				place = rand() % 4;
			} while (directions[place] != -1);
			directions[place] = dir;
		}

		for (int i = 0; i < 4; i++)
		{
			if (runMazeDFS)
			{
				switch (directions[i])
				{
				case 0: // up
					if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET)
						CheckNeighbor(r + 1, c, pcurrent);
					break;
				case 1: // down
					if (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET)
						CheckNeighbor(r - 1, c, pcurrent);
					break;
				case 2: // left
					if (maze[r ][c- 1] == SPACE || maze[r ][c- 1] == TARGET)
						CheckNeighbor(r , c- 1, pcurrent);
					break;
				case 3: // right
					if (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET)
						CheckNeighbor(r, c + 1, pcurrent);
					break;

				}
			}
		}
	}
}

void RunUCSIteration2()
{
	Cell* pcurrent;
	int r, c;

	if (grays.empty())
	{
		SolutionFound(false);
		return;
	}
	else
	{
		pcurrent = grays.back(); // DFS uses STACK
		r = pcurrent->getRow();
		c = pcurrent->getColumn();
		maze[r][c] = BLACK; // paint it black
		grays.pop_back();

		// check neighbors (use random direction)
		int directions[4] = { -1,-1,-1,-1 };
		int dir, place;
		for (dir = 0; dir < 4; dir++)
		{
			do {
				place = rand() % 4;
			} while (directions[place] != -1);
			directions[place] = dir;
		}

		for (int i = 0; i < 4; i++)
		{
			if (runMazeDFS)
			{
				switch (directions[i])
				{
				case 0: // up
					if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET)
						CheckNeighbor(r + 1, c, pcurrent);
					break;
				case 1: // down
					if (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET)
						CheckNeighbor(r - 1, c, pcurrent);
					break;
				case 2: // left
					if (maze[r][c - 1] == SPACE || maze[r][c - 1] == TARGET)
						CheckNeighbor(r, c - 1, pcurrent);
					break;
				case 3: // right
					if (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET)
						CheckNeighbor(r, c + 1, pcurrent);
					break;

				}
			}
		}
	}
}


void RunAStarIteration() {
	
	Cell* pcurrent;
	int r, c;
	if (a_star_pq_maze.empty()) {
		SolutionFound(false);
		return;
	}
	else {
		pcurrent = a_star_pq_maze.top();
		r = pcurrent->getRow();
		c = pcurrent->getColumn();
		a_star_pq_maze.pop();
		maze[r][c] = BLACK;
		if (runMazeAStar && maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET)
			CheckNeighbor(r + 1, c, pcurrent);
		if (runMazeAStar && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET))
			CheckNeighbor(r - 1, c, pcurrent);
		if (runMazeAStar && (maze[r][c - 1] == SPACE || maze[r][c - 1] == TARGET))
			CheckNeighbor(r, c - 1, pcurrent);
		if (runMazeAStar && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET))
			CheckNeighbor(r, c + 1, pcurrent);
	}

}

void RunBestFirstSearchIteration() {
	Cell* pcurrent;

	if (pq_maze.empty())
	{	
		runMazeBestFS = false;
		SolutionFound(false);
		return;
	}
	else
	{
		pcurrent = pq_maze.top();
		int r = pcurrent->getRow();
		int c = pcurrent->getColumn();

		maze[r][c] = BLACK;
		pq_maze.pop();

		if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET)
			CheckNeighbor(r + 1, c, pcurrent);
		if (runMazeBestFS && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET))
			CheckNeighbor(r - 1, c, pcurrent);
		if (runMazeBestFS && (maze[r][c - 1] == SPACE || maze[r][c - 1] == TARGET))
			CheckNeighbor(r, c - 1, pcurrent);
		if (runMazeBestFS && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET))
			CheckNeighbor(r, c + 1, pcurrent);

	}
}


// ----------------




//---- GRAPHICS -----

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	if (INIT_MAZE) {
		DrawMaze();
	}
	else if (INIT_GRAPH) {
		DrawGraph();
	}
	else if (INIT_PUZZLE) {
		DrawPuzzle();
	}
	
	glutSwapBuffers(); // show all
}

void idle()
{
	if (isFin) {
		return;
	}
	if (runMazeBFS) {
		RunBFSIteration();
	}
	else if (runMazeDFS) {
		RunDFSIteration();
	}
	else if (runGraphUCS) {
		RunUCSIterationGraph();
	}
	else if (runMazeBestFS) {
		RunBestFirstSearchIteration();
	}
	else if (runPuzzleAStar) {
		pn->computeH();
		pn->setG(0);
		pn->computeF();
		PuzzleRunAStar();
	}
	else if (runMazeAStar) {
		RunAStarIteration();
	}

	glutPostRedisplay();
}

void menu(int choice) {
	switch (choice) {
	case 0:
		StopIteration();
		break;
	case 1: 
		Run(MAZE_BFS);
		break;
	case 2:
		Run(MAZE_DFS);
		break;
	case 3:
		Run(MAZE_BESTFS);
		break;
	case 4:
		Run(MAZE_ASTAR);
		break;
	case 5: 
		Run(GRAPH_UCS);
		break;
	case 6:
		Run(PUZZLE_ASTAR);
		break;
	}




}





int main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Title");

	glutDisplayFunc(display); //  refresh function
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	// menu
	glutCreateMenu(menu);
	if (INIT_MAZE) {
		glutAddMenuEntry("Run BFS", 1);
		glutAddMenuEntry("Run DFS", 2);
		glutAddMenuEntry("Run BestFS", 3);
		glutAddMenuEntry("Run Astar", 4);
		glutAddMenuEntry("Stop", 0);
	}
	else if (INIT_GRAPH) {
		glutAddMenuEntry("Run UCS", 5);
		glutAddMenuEntry("Stop", 0);
	}
	else if (INIT_PUZZLE) {
		glutAddMenuEntry("Solve Puzzle", 6);
		glutAddMenuEntry("Stop", 0);
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
	return 0;
}