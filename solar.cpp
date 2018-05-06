#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415


class glFunctions
{
public:
	void circle(float R,float red,float green,float blue,float X ,float Y )
	{
		glColor3f(red,green,blue);
		double p,x=0,y=R;
		p=(5/4)-R;
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(X,Y);
		while(x<=y)
		{
			glVertex2d(X+x,Y+y);
			glVertex2d(X+y,Y+x);
			glVertex2d(X-x,Y+y);
			glVertex2d(X+y,Y-x);
			glVertex2d(X-x,Y-y);
			glVertex2d(X-y,Y-x);
			glVertex2d(X+x,Y-y);
			glVertex2d(X-y,Y+x);
			if(p < 0)
			{
				x++;
				p += 2*x + 1;
			}
			else
			{
				x++;
				y--;
				p+= 2*x + 1 - 2*y;
			}
		}
		glEnd();
	}



	void ellipse(float rx, float ry,float red,float green,float blue,float cx ,float cy)
	{
		glColor3f(red,green,blue);
		glBegin(GL_POINTS);
		float x,y;
		x=0;
		y=ry;
		float p=ry*ry -rx*rx*ry +ry*ry*0.25;
		while(ry*ry*x<rx*rx*y)
		{
			x++;
			if(p<0)
			{
				p+= 2*ry*ry*x +ry*ry;
			}
			else
			{
				y--;
				p+=2*ry*ry*x-2*rx*rx*y+ry*ry;
			}
			glVertex2d(x+cx,y+cy);
			glVertex2d(x+cx,-y+cy);
			glVertex2d(-x+cx,y+cy);
			glVertex2d(-x+cx,-y+cy);
		}

		p=ry*ry*(x+0.5)*(x+0.5) + rx*rx*(y-1)*(y-1) -rx*rx*ry*ry;
		while(y>0){
			y--;
			if(p>0){
				p=p-2*rx*rx*y +rx*rx;
			}
			else{
				x++;
				p=p-2*rx*rx*y+2*ry*ry*x+rx*rx;
			}
			glVertex2d(x+cx,y+cy);
			glVertex2d(x+cx,-y+cy);
			glVertex2d(-x+cx,y+cy);
			glVertex2d(-x+cx,-y+cy);
		}

		glEnd();
	}
};


class orbit
{
public:
	float x;
	float y;
};

class planet
{
public:
	float x;
	float y;
	float ang;
	float red ,green ,blue;
	float size;
	float rate;
	orbit orb;
	glFunctions gl;
	planet ( float majorAxis , float minorAxis, float x , float y ,float rate , float size ,float red = 0 , float green = 0 , float blue = 0 ,float ang = 0)
	{
		this->x = x;
		this->y = y;
		this->ang  = ang;
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->rate = rate;
		this->size = size;
		this->orb.x = majorAxis;
		this->orb.y = minorAxis;
	}

	void getNextValue()
	{
		if(ang < 0 ) ang = 2 * PI;
		ang-=rate;
		x = orb.x * cos(ang) ;
		y =  orb.y * sin(ang);
	}

	void drawMe()
	{
		gl.ellipse(orb.x,orb.y,red,green,blue,0,0); 
		gl.circle(size,red,green,blue,x,y);
	}
};

class moon 
{

public:
	float x;
	float y;
	float ang;
	float red ,green ,blue;
	float size;
	float rate;
	orbit orb;
	glFunctions gl;
	float parentX;
	float parentY;
	moon(float parentX, float parentY , float x, float y , float rate ,float size ,float majorAxis, float minorAxis, float red = 0 , float green = 0, float blue = 0 )
	{
		this->x = x;
		this->y = y;
		this->parentX = parentX;
		this->parentY = parentY;
		this->ang  = 0;
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->rate = rate;
		this->size = size;
		this->orb.x = majorAxis;
		this->orb.y = minorAxis;
	}
	void getNextValue(float parentX, float parentY)
	{
		this->parentX = parentX;
		this->parentY = parentY;
		if(ang < 0 ) ang = 2 * PI;
		ang-=rate;
		x = orb.x * cos(ang) + parentX ;
		y =  orb.y * sin(ang) + parentY;
	}

	void drawMe()
	{
		gl.ellipse(orb.x,orb.y,red,green,blue,parentX,parentY); 
		gl.circle(size,red,green,blue,x,y);
	}

};
planet mercury(400, 130 , -400 , 0 , 0.002, 45,1,0,0) , venus(500, 230 , -500 , 0 , 0.0009, 70,1,0.4,0);
planet earth(700, 400 , -700 , 0 , 0.0005 , 70 , 0 , 0 , 1 );
planet mars(1000,580,-1000, 0 , 0.0008, 60, 0.7 , 0.1 , 0 );
planet jupiter(1400, 750 , -1400 , 0 , 0.0009 , 100 , 1,1,0.2);
planet saturn(1900 , 900 , -1900 , 0 ,  0.0008, 70 , 0.9 , 0.8 , 0.4);
planet uranus(2500 , 1100 , -2500 , 0 , 0.0004 , 100 , 0.5, 0.9, 0.4);
planet neptune(3200 , 1300 , -3200 , 0 , 0.0001 , 75 , 0.5 , 0.1 , 1);
moon m (earth.x, earth.y, (earth.x -180) , 0 , 0.002 , 40 , 180 , 100 , 1, 1, 1);
moon saturnRing1 (saturn.x, saturn.y , (saturn.x - 180) , 0 , 0.002 , 0 , 180 , 100 , 0.9 , 0.8, 0.4);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mercury.drawMe();
	venus.drawMe();
	earth.drawMe();
	mars.drawMe();
	jupiter.drawMe();
	saturn.drawMe();
	uranus.drawMe();
	neptune.drawMe();
	m.drawMe();
	saturnRing1.drawMe();
	glFlush();

}

void animation()
{
	mercury.getNextValue();
	venus.getNextValue();
	earth.getNextValue();
	mars.getNextValue();
	jupiter.getNextValue();
	saturn.getNextValue();
	neptune.getNextValue();
	uranus.getNextValue();
	m.getNextValue(earth.x , earth.y);
	saturnRing1.getNextValue(saturn.x, saturn.y);
	display();
}
void init(void)
{
	glClearColor (0.1, 0, 0.1, 0.0);
	
	gluOrtho2D(-3300,3300,-4000,4000);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Solar System ");
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}



// if(jupiterY>0 && jupiterX>= -1400 && jupiterX<0){
    //     rj = -(jupiterX/7);
    //     if(rj<=30){
    //         rj=30;
    //     }
    //             if(rj>=200){
    //         rj=200;
    //     }

    //     circle(rj,1,1,0.2,jupiterX,jupiterY);//jupiter
    // }

    // else if(jupiterY>0 && jupiterX<= 1400 && jupiterX>=0){
    //     rj = (jupiterX/7);
    //     if(rj<=30){
    //         rj=30;
    //     }
    //     if(rj>=200){
    //         rj=200;
    //     }
    //     circle(rj,1,1,0.2,jupiterX,jupiterY);//jupiter
    // }

    // else if(jupiterY<0 && jupiterX<1400 && jupiterX>0){

    //     rj = jupiterY/5;
    //     rj=-rj;
    //     if(rj<=200){
    //         rj = 200;
    //     }
    //     circle(rj,1,1,0.2,jupiterX,jupiterY);//jupiter
    // }

    // else if(jupiterY<0 && jupiterX>-1400 && jupiterX<=0){
    //     rj = jupiterY/5;
    //     rj=-rj;
    //     if(rj<=t){
    //         rj=200;
    //     }
    //     circle(rj,1,1,0.2,jupiterX,jupiterY);//jupiter
    // }