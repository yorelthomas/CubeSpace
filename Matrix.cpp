#include "matrix.h"

Matrix::Matrix()
{
	score = 0;
	ZeroMatrix();
}

void Matrix::ZeroMatrix()
{
	for(int i = 0; i < MAT_WIDTH; ++i)
		for(int j = 0; j < MAT_HEIGHT; ++j)
			for(int k = 0; k < MAT_DEPTH; ++k)
				loc[i][j][k] = 0;
}

int Matrix::isSet(int x, int y, int z)
{
	//return the value(color) stored in the matrix at x,y,z
	//if the value is 0, it is not set and therefore
	//no cube is located there
	return(loc[x][y][z]);	
}

void Matrix::set(int x, int y, int z)
{
	int color;
	
//	srand( (unsigned)time(NULL) );//seed the rand num generator

	color = rand()%6+1; //0=no cube, 1 = red, 2=green, 3=blue,
					    //4=yellow, 5=cyan, 6=magenta

	setActiveCube(x,y,z);

	//arrays are zero based so subtract one
	--x;
	--y;
	--z;

	loc[x][y][z] = color;
}

void Matrix::moveLeft()
{
	int temp;

	//cube can only be moved if it is not at rest
	if( (activeCube.x > 0) && (activeCube.y != 0) &&
		(loc[activeCube.x][activeCube.y-1][activeCube.z] == 0) )
	{
		//move cube left if the space is not already occupied
		if(loc[activeCube.x-1][activeCube.y][activeCube.z]== 0)
		{
			//store the color value of the cube and move it
			temp = loc[activeCube.x][activeCube.y][activeCube.z];
			loc[activeCube.x][activeCube.y][activeCube.z] = 0;
			activeCube.x = activeCube.x - 1;
			loc[activeCube.x][activeCube.y][activeCube.z] = temp;
		}
	}
}

void Matrix::moveRight()
{
	int temp;

	//cube can only be moved if it is not at rest
	if( (activeCube.x < 4) && (activeCube.y != 0) &&
		(loc[activeCube.x][activeCube.y-1][activeCube.z] == 0) )
	{
		//store the color value of the cube and move it
		if(loc[activeCube.x+1][activeCube.y][activeCube.z]== 0)
		{
			temp = loc[activeCube.x][activeCube.y][activeCube.z];
			loc[activeCube.x][activeCube.y][activeCube.z] = 0;
			activeCube.x = activeCube.x + 1;
			loc[activeCube.x][activeCube.y][activeCube.z] = temp;
		}
	}
}

void Matrix::moveIn()
{
	int temp;

	//cube can only be moved if it is not at rest
	if( (activeCube.z < 4) && (activeCube.y != 0) &&
		(loc[activeCube.x][activeCube.y-1][activeCube.z] == 0) )
	{
		//store the color value of the cube and move it
		if(loc[activeCube.x][activeCube.y][activeCube.z+1]== 0)
		{
			temp = loc[activeCube.x][activeCube.y][activeCube.z];
			loc[activeCube.x][activeCube.y][activeCube.z] = 0;
			activeCube.z = activeCube.z + 1;
			loc[activeCube.x][activeCube.y][activeCube.z] = temp;
		}
	}
}

void Matrix::moveOut()
{
	int temp;

	//cube can only be moved if it is not at rest
	if( (activeCube.z > 0) && (activeCube.y != 0) &&
		(loc[activeCube.x][activeCube.y-1][activeCube.z] == 0) )
	{
		//store the color value of the cube and move it
		if(loc[activeCube.x][activeCube.y][activeCube.z-1]== 0)
		{
			temp = loc[activeCube.x][activeCube.y][activeCube.z];
			loc[activeCube.x][activeCube.y][activeCube.z] = 0;
			activeCube.z = activeCube.z - 1;
			loc[activeCube.x][activeCube.y][activeCube.z] = temp;
		}
	}
}

void Matrix::lowerFloaters(char rowDir)
{
	const MatrixLocation tempLoc = activeCube;
	int startHeight = 1 + activeCube.y;

	//go through evey location above the row that was cleared
	//and drop all of the cubes
	for(int j = 0; j < MAT_WIDTH; ++j)
	{
		for(int i = startHeight; i < MAT_HEIGHT; ++i)
		{
			if(rowDir == 'x')
			{
				//activeCube.x = activeCube.x;
				activeCube.y = i;
				activeCube.z = j;

			}
			else // rowDir == 'z'
			{
				activeCube.x = j;
				activeCube.y = i;
				//activeCube.z = activeCube.z;
			}

			//if there is a cube in the spot, drop it
			if(loc[activeCube.x][activeCube.y][activeCube.z])
				drop();
		}
	}

	activeCube = tempLoc;
}


void Matrix::SetTitleBar()
{
	char scorePhrase[50];

	sprintf(scorePhrase,
		"Cube Space                     Score: %i", score);
	glutSetWindowTitle(scorePhrase);
}


void Matrix::clearRows()
{
	int oldScore = score;
	int color;

	for(int y=0; y<MAT_HEIGHT; ++y)
	{
		for(int x=0; x<MAT_WIDTH; ++x)
		{
			//for a given value of x, if all cells along z are set
			// to the same color, then clear the row
//			if(loc[x][y][0] && loc[x][y][1] && loc[x][y][2] && loc[x][y][3] && loc[x][y][4])
			color = loc[activeCube.x][activeCube.y][activeCube.z];
			if( color == loc[x][y][0] &&
				color == loc[x][y][1] &&
				color == loc[x][y][2] &&
				color == loc[x][y][3] &&
				color == loc[x][y][4]
			  )
			{
				//increase the score by the values in the row
				score += 10 * loc[x][y][0];
				score += 10 * loc[x][y][1];
				score += 10 * loc[x][y][2];
				score += 10 * loc[x][y][3];
				score += 10 * loc[x][y][4];

				loc[x][y][0] = 0;
				loc[x][y][1] = 0;
				loc[x][y][2] = 0;
				loc[x][y][3] = 0;
				loc[x][y][4] = 0;

				lowerFloaters('x');
			}
		}

		for(int z=0; z<MAT_WIDTH; ++z)
		{
			//for a given value of z, if all cells along x are set
			//to the same color, then clear the row
//			if(loc[0][y][z] && loc[1][y][z] && loc[2][y][z] && loc[3][y][z] && loc[4][y][z])
			color = loc[activeCube.x][activeCube.y][activeCube.z];
			if( color == loc[0][y][z] &&
				color == loc[1][y][z] &&
				color == loc[2][y][z] &&
				color == loc[3][y][z] &&
				color == loc[4][y][z]
			  )
			{
				//increase the score by the values in the row
				score += 10 * loc[0][y][z];
				score += 10 * loc[1][y][z];
				score += 10 * loc[2][y][z];
				score += 10 * loc[3][y][z];
				score += 10 * loc[4][y][z];

				loc[0][y][z] = 0;
				loc[1][y][z] = 0;
				loc[2][y][z] = 0;
				loc[3][y][z] = 0;
				loc[4][y][z] = 0;

				lowerFloaters('z');
			}
		}
	} //end of y loop

	//clear stacks of 5
	for( int z = 0; z < MAT_WIDTH; ++z)
		for(int x = 0; x < MAT_WIDTH; ++x)
			for(y = 0; y < (MAT_HEIGHT-4); ++y)
			{
				color = loc[activeCube.x][activeCube.y][activeCube.z];
				if( color == loc[x][y+0][z] &&
					color == loc[x][y+1][z] &&
					color == loc[x][y+2][z] &&
					color == loc[x][y+3][z] &&
					color == loc[x][y+4][z]
				  )
				{
					score += 5 * loc[x][y][z];
					score += 5 * loc[x][y+1][z];
					score += 5 * loc[x][y+2][z];
					score += 5 * loc[x][y+3][z];
					score += 5 * loc[x][y+4][z];

					loc[x][y][z] = 0;
					loc[x][y+1][z] = 0;
					loc[x][y+2][z] = 0;
					loc[x][y+3][z] = 0;
					loc[x][y+4][z] = 0;

//					const MatrixLocation tempLoc = activeCube;
//					for (int yy = y+5; yy < MAT_HEIGHT; ++YY)
//					{
//						SetActiveCube(activeCube.x, yy, activeCube.z);
//						drop();
//					}
//					activeCube = tempLoc;
				}
			}

	if(oldScore != score)
		SetTitleBar();
}

bool Matrix::moveDown()
{
	int temp = 0;
	int lowestOpenSpot = 0;

	//find the lowest empty spot in the current column
	while(loc[activeCube.x][lowestOpenSpot][activeCube.z])
	{
		++lowestOpenSpot;
		if(lowestOpenSpot >= MAT_HEIGHT)
			return false; //game over		
	}

	//if the active cube is not immediately above the lowest
	//spot, then lower the cube by one cell
	if(activeCube.y > lowestOpenSpot)
	{
		temp = loc[activeCube.x][activeCube.y][activeCube.z];
		loc[activeCube.x][activeCube.y][activeCube.z] = 0;
		activeCube.y = activeCube.y - 1;
		loc[activeCube.x][activeCube.y][activeCube.z] = temp;
	}
	else //start a new cube
	{
		//clear any completed rows
		clearRows();
		set(3,10,3);
	}

	return true;
}

bool Matrix::drop()
{
	int temp = 0;
	int lowestOpenSpot = 0;

	while(loc[activeCube.x][lowestOpenSpot][activeCube.z])
	{
		++lowestOpenSpot;
		if(lowestOpenSpot >= MAT_HEIGHT)
			return false; //game over
	}

	//if the cube is not at the lowest open spot, drop it to the lowest spot
	if(activeCube.y > lowestOpenSpot)
	{
		temp = loc[activeCube.x][activeCube.y][activeCube.z]; //save the color value
		loc[activeCube.x][activeCube.y][activeCube.z] = 0;
		activeCube.y = lowestOpenSpot;
		loc[activeCube.x][activeCube.y][activeCube.z] = temp; //restore the color
	}
//	else
//	{
//		//check for completed rows, then start a new cube
//		clearRows();
//		set(3,10,3);
//	}
	return true;
}

void Matrix::setActiveCube(int xx, int yy, int zz)
{
	activeCube.x = (--xx);
	activeCube.y = (--yy);
	activeCube.z = (--zz);
}
