#include "glut.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <vector>
#include <iostream>
#include "Room.h"
#include "HomeObject.h"


using namespace std;

const double PI = 3.14;

const int HORIZONTAL = 1;
const int VERTICAL = 0;

const int SPACE = 0;
const int WALL = 1;
const int START = 2;
const int TARGET = 3;
const int PATH = 4;
const int VISITED = 5;
const int FRINGE = 6; // GRAY NODES

const int MSZ = 100;

int maze[MSZ][MSZ] = { 0 };

vector <HomeObject> hob;
HomeObject* ph;



// Binary tree
typedef struct tnode {
	int direction;
	Room* pr;
	tnode* left;
	tnode* right;
}TNODE;

TNODE* root = nullptr;

void SetupMaze();
TNODE* BinarySpacePartition(Room* pr);
void AddPassages(TNODE* root);

void init()
{
	glClearColor(0.4, 0, 0.7, 0);// color of window background
								 // setup coordinates system
	glOrtho(-1, 1, -1, 1, -1, 1);
	srand(time(0));
	SetupMaze();

	Room* proom = new Room(new Point2D(0, 0), MSZ, MSZ);

	root = BinarySpacePartition(proom);
	// add passages
	// root contains now all the rooms so we can run AddPassages
	AddPassages(root);

	ph = new HomeObject(new Point2D(rand() % MSZ, rand() % MSZ), "Table");
	//	hob.push_back(*ph);
}

void DrawPassages(TNODE* pt)
{
	int i, j, start, stop;
	// check the direction
	if (pt->direction == HORIZONTAL) // DrawVertical passage
	{
		start = pt->left->pr->getCenter().getRow();
		stop = pt->right->pr->getCenter().getRow();
		for (i = start; i <= stop; i++)
			maze[i][pt->left->pr->getCenter().getCol()] = SPACE;
	}
	else // Draw Horizontal passage
	{
		start = pt->left->pr->getCenter().getCol();
		stop = pt->right->pr->getCenter().getCol();
		for (j = start; j <= stop; j++)
			maze[pt->left->pr->getCenter().getRow()][j] = SPACE;
	}
}

void AddPassages(TNODE* root)
{
	if (root->left != nullptr && right != nullptr) // if partition exists
	{
		AddPassages(root->left);
		AddPassages(root->right);
		DrawPassages(root);
	}
	// else root was not prtitioned
}

void DrawRoom(Room* pr) {
	int i, j;
	int start, stop;
	start = pr->getLeftTop()->getRow();
	stop = start + pr->getHeight();
	// vertical walls
	for (i = start; i <= stop; i++)
	{
		maze[i][pr->getLeftTop()->getCol()] = WALL; // left
		maze[i][pr->getLeftTop()->getCol() + pr->getWidth()] = WALL;
	}
	// horizontal walls
	start = pr->getLeftTop()->getCol();
	stop = pr->getLeftTop()->getCol() + pr->getWidth();
	for (j = start; j <= stop; j++)
	{
		maze[pr->getLeftTop()->getRow()][j] = WALL;
		maze[pr->getLeftTop()->getRow() + pr->getHeight()][j] = WALL;
	}
}

// this is a partition without passages
TNODE* BinarySpacePartition(Room* pr)
{
	int left1, top1, w1, h1, left2, top2, w2, h2;
	TNODE* root = new TNODE;
	root->left = nullptr; // in case that the partition cannot be done
	root->right = nullptr;// both left and right are NULL
	Room* pr1, * pr2; // two future partition rooms
	root->pr = pr;

	DrawRoom(pr);

	// 1. check for stop condition:
	if (pr->getWidth() > MIN_SZ && pr->getHeight() > MIN_SZ) // execute the partition
	{
		// define area in which the point can be taken
		Room area;
		area.setLeftTop(new Point2D(pr->getLeftTop()->getRow() + MIN_SZ / 2, pr->getLeftTop()->getCol() + MIN_SZ / 2));
		area.setWidth(pr->getWidth() - MIN_SZ);
		area.setHeight(pr->getHeight() - MIN_SZ);
		// choose randomly a point inside this area
		Point2D np = area.ChoosePoint();
		// choose direction
		if (rand() % 2 == 0) // the partition is horizontal
		{
			root->direction = HORIZONTAL;
			// room1
			// left-top of first room
			left1 = pr->getLeftTop()->getCol();
			top1 = pr->getLeftTop()->getRow();
			w1 = pr->getWidth();
			h1 = np.getRow() - top1;
			// room2
			left2 = left1;
			top2 = np.getRow();
			w2 = w1;
			h2 = pr->getHeight() - h1;
			pr1 = new Room(new Point2D(top1, left1), w1, h1);
			pr2 = new Room(new Point2D(top2, left2), w2, h2);
			// add leaf nodes to the root
			root->left = BinarySpacePartition(pr1);
			root->right = BinarySpacePartition(pr2);
		}
		else // the partition is vertical
		{
			root->direction = VERTICAL;
			// room1
			// left-top of first room
			left1 = pr->getLeftTop()->getCol();
			top1 = pr->getLeftTop()->getRow();
			w1 = np.getCol() - left1;
			h1 = pr->getHeight();
			// room2
			left2 = np.getCol();
			top2 = top1;
			w2 = pr->getWidth() - w1;
			h2 = h1;
			pr1 = new Room(new Point2D(top1, left1), w1, h1);
			pr2 = new Room(new Point2D(top2, left2), w2, h2);
			// add leaf nodes to the root
			root->left = BinarySpacePartition(pr1);
			root->right = BinarySpacePartition(pr2);
		}
	}
	return root;
}

void SetupMaze()
{
	for (int i = 0; i < MSZ; i++) // outer borders are WALLs
	{
		maze[0][i] = WALL;
		maze[i][0] = WALL;
		maze[MSZ - 1][i] = WALL;
		maze[i][MSZ - 1] = WALL;
	}
}

void DrawObjects()
{
	double x, y;
	double dx, dy; // size of a square
	dx = 2.0 / MSZ;
	dy = 2.0 / MSZ;

	//	auto itr = hob.begin();
	//	while (itr != hob.end())
	{
		//		x = -1 + dx* (itr)->getLocation().getCol();
		//		y = 1 - dy*(itr)->getLocation().getRow();
		x = -1 + dx * ph->getLocation().getCol();
		y = 1 - dy * ph->getLocation().getRow();
		glColor3d(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2d(x, y); // left-top corner
		glVertex2d(x + dx, y); //right-top corner
		glVertex2d(x + dx, y - dy); //right-bottom corner
		glVertex2d(x, y - dy); //left-bottom corner
		glEnd();

		glRasterPos2d(x, y);
		for (int i = 0; i < ph->getName().size(); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, ph->getName().at(i));


	}

}

void DrawMaze()
{
	double x, y;
	double dx, dy; // size of a square

	dx = 2.0 / MSZ;
	dy = 2.0 / MSZ;
	y = 1;
	for (int i = 0; i < MSZ; i++, y -= dy)
	{
		x = -1;
		for (int j = 0; j < MSZ; j++, x += dx)
		{
			switch (maze[i][j]) // set the right color
			{
			case SPACE:
				glColor3d(1, 1, 1); // white
				break;
			case WALL:
				glColor3d(0.3, 0.3, 0.3); // dark gray
				break;
			case START:
				glColor3d(0.2, 0.2, 1); // blue
				break;
			case TARGET:
				glColor3d(1, 0, 0); // red
				break;
			case PATH:
				glColor3d(0, 0.5, 0); // green
				break;
			case VISITED:
				glColor3d(0.3, 0.8, 0.9); // light blue
				break;
			case FRINGE:
				glColor3d(0.8, 0.4, 0.0); // orange

			}// switch
			 // draw square
			glBegin(GL_POLYGON);
			glVertex2d(x, y); // left-top corner
			glVertex2d(x + dx, y); //right-top corner
			glVertex2d(x + dx, y - dy); //right-bottom corner
			glVertex2d(x, y - dy); //left-bottom corner
			glEnd();
		}
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	DrawMaze();
	DrawObjects();

	glutSwapBuffers(); // show all
}

void idle()
{
	glutPostRedisplay();
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("First Example");

	glutDisplayFunc(display); // Repaint function
	glutIdleFunc(idle); // "timer" function

	init();

	glutMainLoop();
}