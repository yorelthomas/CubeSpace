#ifndef MATRIX_H
#define MATRIX_H

#ifdef WIN32
#include "windows.h"
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#define MAT_WIDTH 5
#define MAT_HEIGHT 10
#define MAT_DEPTH 5

struct MatrixLocation
{
	int x;
	int y;
	int z;
};

class Matrix
{
	private:
		int loc[MAT_WIDTH][MAT_HEIGHT][MAT_DEPTH];
		// active cube matrix location
		MatrixLocation activeCube;
		int score;
		
	public:
		Matrix();		
		int isSet(int,int,int);
		void set(int,int,int);
		bool moveDown();
		bool drop();
		void moveLeft();
		void moveRight();
		void moveOut();
		void moveIn();
		void setActiveCube(int, int, int);
		void clearRows();
		void lowerFloaters(char);
		void SetTitleBar();
		int GetScore() { return score; }
		void SetScore(int s) { score = s; }
		void ZeroMatrix();
};


#endif