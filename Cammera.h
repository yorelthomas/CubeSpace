#ifndef CAMMERA_H
#define CAMMERA_H

#define PI 3.14159


class Camera
{
	private:
		GLfloat x, y, z;
		float angle; //radians
		float radius;
		bool radiusLimiter;
		bool heightLimiter;
		float maxRadius, minRadius;
		float maxHeight, minHeight;

	public:
		// angle in radians
		// positive z axis coming out of the screen
		Camera(GLfloat ang, GLint rad, GLint yy)
		{
			heightLimiter = false;
			radiusLimiter = false;
			maxHeight = 200;
			minHeight = -100;
			maxRadius = 300;
			minRadius = 12;
			angle = ang;
			radius = rad;
			y = yy;
			x=static_cast<GLfloat>(radius*cos(angle)+12.0f);
			z=static_cast<GLfloat>(radius*sin(angle)-12.0f);
		}

		~Camera() {}

		void SetCamera(GLfloat ang, GLint rad, GLint yy)
		{
			angle = ang;
			radius = rad;
			x=static_cast<GLfloat>(radius*cos(angle)+12.0f);
			z=static_cast<GLfloat>(radius*sin(angle)-12.0f);
			y = yy;
		}

		GLfloat getX() {return x;}
		GLfloat getY() {return y;}
		GLfloat getZ() {return z;}
		void Up()
		{
			//dont let the camera get higher than maxHeight
			//if it does, then move it back down
			//until it gets all the way to minHeight
			if(y <= maxHeight && !heightLimiter)
			{
				if(y >= maxHeight)
					heightLimiter = true;

				y += 1.0f;				
			}
			else
			{
				if(y <= minHeight)
					heightLimiter = false;

				y -= 1.0f;
			}
		}

		void Down()
		{
			//don't let the camera get lower than minHeight
			//ifit does, then begin increasing it until it gets to maxHeight
			if(y >= minHeight && !heightLimiter)
			{
				if(y <= minHeight)
					heightLimiter = true;

				y -= 1.0f;
			}
			else
			{
				if(y >= maxHeight)
					heightLimiter = false;

				y += 1.0f;
			}
		}

		void RotateC()
		{
			//keep the angle between 360 and -360
			if(angle < -360)
				angle += 360;

			angle -= 0.1f;
			x=static_cast<GLfloat>(radius*cos(angle)+12.0f);
			z=static_cast<GLfloat>(radius*sin(angle)-12.0f);
		}

		void RotateCC()
		{
			//keep the angle between 360 and -360
			if(angle > 360)
				angle -= 360;

			angle += 0.1;
			x=static_cast<GLfloat>(radius*cos(angle)+12.0f);
			z=static_cast<GLfloat>(radius*sin(angle)-12.0f);
		}

		void In()
		{
			//don't let the camera get closer to the y than minRadius
			//if the radius gets down to 12, then increase it
			//until it gets to the maximum radius
			if(radius >= minRadius && !radiusLimiter)
			{
				if(radius <= minRadius)
					radiusLimiter = true;

				radius -= 1.0f;
			}
			else
			{
				if(radius >= maxRadius)
					radiusLimiter = false;
				radius += 1.0f;

			}

			x=static_cast<GLfloat>(radius*cos(angle)+12.0f);
			z=static_cast<GLfloat>(radius*sin(angle)-12.0f);				
		}

		void Out()
		{
			//dont let the camera go further than maxRadius away from the y axis
			//if it gets out to a radius of 100, then move it back in
			//until it gets all the way back in to the minimum radius
			if(radius <= maxRadius && !radiusLimiter)
			{
				if(radius >= maxRadius)
					radiusLimiter = true;

				radius += 1.0f;				
			}
			else
			{
				if(radius <= minRadius)
					radiusLimiter = false;

				radius -= 1.0f;
			}

			x=static_cast<GLfloat>(radius*cos(angle)+12.0f);
			z=static_cast<GLfloat>(radius*sin(angle)-12.0f);				
		}
};



#endif