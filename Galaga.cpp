#include<windows.h>
#include <GL/glut.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int pageOne=1,pageTwo=0,pageThree=0,pageFour=0;
float width=1020,hight=680;
/*-------------------PAGE1------------------------*/
float charx=0;
void marque()
{
    char title[]="COMPUTER GRAPHICS MINI PROJECT";
    glColor3f(0.0,1.0,1.0);

    glRasterPos2f(charx,hight-70);
    for(char *i=title;*i!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
    }
    if(charx<=750)
    {
        charx+=0.1;
    }
    else
    {
        charx=0;
    }
glutPostRedisplay();
  }

void displayPageOne()
{
//  glClearColor(1.0,1.0,1.0,1.0);
 glClear(GL_COLOR_BUFFER_BIT);
    marque();
    char name[2][20]={{"Akshay:4vp16cs005"},{"Abhi:4vp16cs001"}};
    float page1Ypos=(hight/2)+50;
    glColor3f(1.0,0.0,0.0);
    for(int i=0;i<2;i++)
    {
    glRasterPos2f((width/2)-100,page1Ypos);
    for(char *j=name[i];*j!='\0';j++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*j);
    }
    page1Ypos-=40;
  }
	glFlush();
  //glutSwapBuffers();
}

/*------------------------------------------------*/

/*-------------------PAGE2------------------------*/
float menuxy[3][2];
void displayPageTwo()
{
  //glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
float page2Ypos=(hight/2)+100;
    char gameMenu[3][10]={{"New Game"},{"Help"},{"Quit"}};
int k=0;
    for(int i=0;i<3;i++)
    {
      glBegin(GL_LINE_LOOP);
        glVertex2f((width/2)-100,page2Ypos+30);
        glVertex2f((width/2)-100,page2Ypos-30);
        glVertex2f((width/2)+100,page2Ypos-30);
        glVertex2f((width/2)+100,page2Ypos+30);
      glEnd();
      glRasterPos2f((width/2)-80,page2Ypos);

    for(char *j=gameMenu[i];*j!='\0';j++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*j);
    }
    menuxy[i][k]=page2Ypos+30;
    menuxy[i][k+1]=page2Ypos-30;
    page2Ypos-=60;
  }
   glFlush();
}
/*------------------------------------------------*/

/*-------------------PAGE3------------------------*/
struct BBot //Rocket Bot
{
    float x;
    float y;
    float step;
};

struct Bullet   //Bullet Bot
{
    float x;
    float y;
    struct Bullet *next;
}*head=NULL,*tail=NULL,*temp=NULL,*temp1,*temp2;

struct TBot    // Bullet Generator
{
    float x;
    float y;
    struct TBot *next;
}*Thead=NULL,*Ttail=NULL,*Ttemp=NULL,*Ttemp1,*Ttemp2;

/***********************************/
BBot bottomBot= {(width/2),130,30.0};
TBot topBot= {0,hight};
float maxL=0,maxR=width,maxU=hight,maxD=0;
int flag=1,num,max=hight-40,min=40,menu,score=0;
char str[10]="Score :";
bool bullet=false,topbot=false;
float hp=0;
/*****************structure for bullet****************************/

void createBullet(float x1,float y1)
{
if(head==NULL)
    {
        head=(struct Bullet*)malloc(1*sizeof(struct Bullet));
        head->x=x1;
        head->y=y1;
        head->next=NULL;
        tail=head;
    }
else
    {
        temp=(struct Bullet*)malloc(1*sizeof(struct Bullet));
        temp->x=x1;
        temp->y=y1;
        temp->next=NULL;
        tail->next=temp;
        tail=temp;
    }
}
/*************************************/
void DeleteBullet(float yvalue)
{
	temp1=head;
	temp2=head;
	while(temp1->y!=yvalue)
		{
			temp1=temp1->next;
		}
	if(temp1==head)
	{
       if(head->next==NULL)
            {
                head=NULL;
            }
        else
            {
                head=temp1->next;
                free(temp1);
            }
	}
	else
	{
		temp2=head;
		while(temp2->next!=temp1)
		{
            temp2=temp2->next;
		}
		if(temp1->next==NULL)
		{
			tail=temp2;
			tail->next=NULL;
            free(temp1);
		}
		else
		{
			temp2->next=temp1->next;
			free(temp1);
        }
	}
}
/*********************************************/
/*****************structure for ****************************/
void createTopBot(float x1,float y1)
{
    if(Thead==NULL)
    {
        Thead=(struct TBot*)malloc(1*sizeof(struct TBot));
        Thead->x=x1;
        Thead->y=y1;
        Thead->next=NULL;
        Ttail=Thead;
    }
    else
    {
        Ttemp=(struct TBot*)malloc(1*sizeof(struct TBot));
        Ttemp->x=x1;
        Ttemp->y=y1;
        Ttemp->next=NULL;
        Ttail->next=Ttemp;
        Ttail=Ttemp;
    }
}
/*************************************/
void DeleteTopBot(float yvalue)
{
	Ttemp1=Thead;
	Ttemp2=Thead;
	while(Ttemp1->y!=yvalue)
	{
		Ttemp1=Ttemp1->next;
	}
	if(Ttemp1==Thead)
	{
		if(Thead->next==NULL)
		{
            Thead=NULL;
        }
		else
		{
            Thead=Ttemp1->next;
			free(Ttemp1);
		}
	}
	else
	{
		Ttemp2=Thead;
		while(Ttemp2->next!=Ttemp1)
		{
			Ttemp2=Ttemp2->next;
		}
		if(Ttemp1->next==NULL)
		{
			Ttail=Ttemp2;
			Ttail->next=NULL;
			free(Ttemp1);
		}
		else
		{
        	Ttemp2->next=Ttemp1->next;
			free(Ttemp1);
		}
	}
}
/*********************************************/
void displayBottomBotPageThree()
{
    glLineWidth(3.0);
    glColor3f(1.0,0.62745098,0.478431373);

	glBegin(GL_LINE_LOOP);
		glVertex2f(bottomBot.x,bottomBot.y);
		glVertex2f(bottomBot.x-8,bottomBot.y-10);
		glVertex2f(bottomBot.x-8,bottomBot.y-50);
    glVertex2f(bottomBot.x-40,bottomBot.y-70);
  glVertex2f(bottomBot.x-40,bottomBot.y-80);
    glVertex2f(bottomBot.x-8,bottomBot.y-70);
    glVertex2f(bottomBot.x-8,bottomBot.y-100);
    glVertex2f(bottomBot.x-20,bottomBot.y-115);
    glVertex2f(bottomBot.x-20,bottomBot.y-125);
    glVertex2f(bottomBot.x,bottomBot.y-115);
    glVertex2f(bottomBot.x+20,bottomBot.y-125);
    glVertex2f(bottomBot.x+20,bottomBot.y-115);
    glVertex2f(bottomBot.x+8,bottomBot.y-100);
    glVertex2f(bottomBot.x+8,bottomBot.y-70);
    glVertex2f(bottomBot.x+40,bottomBot.y-80);
    glVertex2f(bottomBot.x+40,bottomBot.y-70);
    glVertex2f(bottomBot.x+8,bottomBot.y-50);
    glVertex2f(bottomBot.x+8,bottomBot.y-10);
    glVertex2f(bottomBot.x,bottomBot.y);
	glEnd();
}
/*********************************************/
void displayTopBotPageThree(float x,float y)
{
    glColor3f(0.5,0.5,1.0);
/*	glBegin(GL_POLYGON);
		glVertex2f(x-15,y+10);
		glVertex2f(x-15,y+30);
		glVertex2f(x+15,y+30);
		glVertex2f(x+15,y+10);
		glVertex2f(x,y);
	glEnd();*/

  glBegin(GL_LINE_LOOP);
		glVertex2f(x,y);
glVertex2f(x+4,y+5);
      glVertex2f(x+4,y+25);
    glVertex2f(x+20,y+35);
    glVertex2f(x+20,y+40);
    glVertex2f(x+4,y+35);
    glVertex2f(x+4,y+50);
      glVertex2f(x+10,y+57.5);
    glVertex2f(x+10,y+62.5);
      glVertex2f(x,y+57.5);
    glVertex2f(x-10,y+62.5);
      glVertex2f(x-10,y+57.5);
      glVertex2f(x-4,y+50);
      glVertex2f(x-4,y+35);
    glVertex2f(x-20,y+40);
      glVertex2f(x-20,y+35);
    glVertex2f(x-4,y+25);
    glVertex2f(x-4,y+5);
    glVertex2f(x,y);
	glEnd();
}
/*********************************************/
void displayBulletPageThree(float x,float y)
{
    glColor3f(0.5,1.0,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(x-5,y);
		glVertex2f(x-5,y+5);
		glVertex2f(x,y+10);
		glVertex2f(x+5,y+5);
		glVertex2f(x+5,y);
	glEnd();
}
/*********************************************/
void displayScorePageThree()
{
    glColor3f(1.0,0.0,0.0);
    glRasterPos2f(20,hight-50);
    for(char *i=str;*i!='\0';i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*i);
    }
    int j=0,k,posx=80,p,n=10;
    p=score;
    while(p>9)
    {
        k=p%10;
        glRasterPos2f(posx+n,hight-50);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,k+48);
        j++;
        p=p/10;
    }
    glRasterPos2f(posx-j,hight-50);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,48+p);
}



/*********************************************/



void displayPageThree()
{



      //  glPointSize(5);
        /*glBegin(GL_QUADS);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(0,0);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(0,40);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(750,40);
            glColor3f(0.0,0.0,3.0);
            glVertex2f(750,0);
        glEnd();*/
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f((width-150),hight-50);
        glVertex2f((width-50),hight-50);
        glVertex2f((width-50),hight-30);
        glVertex2f((width-150),hight-30);
        glEnd();
        if(hp==75)
          glColor3f(1.0,0.0,0.0);//red
        else if(hp>=25)
        glColor3f(1.0,1.0,0.0);//yellow
          else
          glColor3f(0.0,1.0,0.0);//green
        glBegin(GL_POLYGON);
        glVertex2f(hp+(width-150),hight-50);
        glVertex2f((width-50),hight-50);
        glVertex2f((width-50),hight-30);
        glVertex2f(hp+(width-150),hight-30);
        glEnd();
        displayBottomBotPageThree();
        if(bullet)
        {
            temp1=head;
            while(temp1!=NULL)
            {
                displayBulletPageThree(temp1->x,temp1->y);
                temp1=temp1->next;
            }
        }
        if(topbot)
        {
            Ttemp1=Thead;
            while(Ttemp1!=NULL)
            {
                displayTopBotPageThree(Ttemp1->x,Ttemp1->y);
                Ttemp1=Ttemp1->next;
            }
        }
        displayScorePageThree();
}

/********************************************************/
int timer=0;
int GOverTimer=0;
void gameOver()
{
  char over[10]="Game Over";
  glRasterPos2f((width/2)-50,(hight/2)-50);

for(char *j=over;*j!='\0';j++)
{
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*j);
}
glFlush();
//glutPostRedisplay();
}
void idlePageThree()
{
	temp1=head;
	if(temp1==NULL)
	{
		bullet=false;
	}
	else
	{
		while(temp1!=NULL)
		{
			temp1->y=temp1->y+1;
			if(temp1->y > maxU)
            {
                DeleteBullet(temp1->y);
            }
			temp1=temp1->next;
		}
	}
	if(flag==1)
	{
		srand(time(NULL));
		num=(min)+rand()%(((max)-(min)+1));
		createTopBot(float(num),maxU);
		flag=0;
		topbot=true;
	}
	Ttemp1=Thead;
	if(Ttemp1==NULL)
	{
		topbot=false;
	}
	else
	{
		while(Ttemp1!=NULL)
		{
            Ttemp1->y=Ttemp1->y-0.1;
			if(Ttemp1->y < maxD )
			{
				DeleteTopBot(Ttemp1->y);
                hp+=25;
                if(hp>=100)
                //exit(1);
                {
                //GOverTimer=0;
                pageFour=1;
                pageThree=0;
              //  gameOver();
              }
			}
      else if(bottomBot.y>=Ttemp1->y)
      {
        if(bottomBot.x-40<=Ttemp1->x && bottomBot.x+40>=Ttemp1->x)
        {
          DeleteTopBot(Ttemp1->y);
                  hp+=25;
                  if(hp>=100)
                  //exit(1);
                  {
                  //GOverTimer=0;
                  pageFour=1;
                  pageThree=0;
                  //gameOver();
                }
        }
      }
            Ttemp1=Ttemp1->next;
		}

	}
    temp1=head;//bullts
    Ttemp1=Thead;//topbot
    while(temp1!=NULL)
    {
        while(Ttemp1!=NULL)
        {
            if(temp1->x < Ttemp1->x +20 and temp1->x > Ttemp1->x -20)
            {
                if(temp1->y+10 < Ttemp1->y +30 and temp1->y+10 > Ttemp1->y)
                {
                    DeleteBullet(temp1->y);
                    DeleteTopBot(Ttemp1->y);
                    score+=1;
                }
            }
            Ttemp1=Ttemp1->next;
        }
        temp1=temp1->next;
    }

    glutPostRedisplay();
}


/*------------------------------------------------*/
void reshape(int w,int h)
{
  glClearColor(0.0,0.0,0.0,1.0);
//  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  //
  gluOrtho2D(0.0,width,0.0,hight);

 glViewport(0.0,0.0,w,h);
  //
  //glMatrixMode(GL_MODELVIEW);
}
/*****************************************************/
void optionsPageThree(int id)
{
  if(pageThree==1)
  {
    switch(id)
    {
        case 1:flag=0;
        score=0;
        Ttemp1=Thead;
      	if(Ttemp1==NULL)
      	{
      		topbot=false;
      	}
      	else
      	{
      		while(Ttemp1!=NULL)
      		{
                  Thead=Ttemp1->next;
                  free(Ttemp1);
                  Ttemp1=Thead;

      		}
          topbot=false;
        }
        break;
        case 2:pageTwo=1;
        pageThree=0;
        break;
    }
  }
}
/*****************************/
void keyboard(unsigned char key,int x,int y)
{
  if(pageOne==1 && key=='a')
  {
pageTwo=1;
pageOne=0;
  }
  else if(pageTwo==1 && key=='a')
  {

pageThree=1;
pageTwo=0;


  }
  else
  {

	if(key=='a' or key=='A')
    {
        if(bottomBot.x-58 > maxL)
        {
            bottomBot.x-= bottomBot.step;
        }
    }
    else if(key=='d' or key=='D')
    {
        if(bottomBot.x+58 < maxR)
        {
            bottomBot.x += bottomBot.step;
        }
    }
	else if(key=='w' or key=='W')
	{
		createBullet(bottomBot.x,bottomBot.y+30);
		bullet=true;
	}
}
	glutPostRedisplay();
}

/***********************************/
/***********************************/
void mouse(int btn,int state,int x,int y)
{
  if(pageThree==1)
  {
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		createBullet(bottomBot.x,bottomBot.y+30);
		bullet=true;
	}
if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
{
    menu=glutCreateMenu(optionsPageThree);
      glutAddMenuEntry("Restart",1);
      glutAddMenuEntry("Quit",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
  }
}
else if(pageTwo==1)
{
  if(x>(width/2)-100 && x<(width/2)+100)
  {
    float y1=hight-y;
    if(y1<menuxy[0][0] && y1>menuxy[0][1])
    {
      pageTwo=0;
      pageThree=1;
    }
    else if(y1<menuxy[1][0] && y1>menuxy[1][1])
    {
      pageTwo=0;
      pageThree=1;
    }
    else if(y1<menuxy[2][0] && y1>menuxy[2][1])
    {
      exit(0);
    }
  }
}

	glutPostRedisplay();
}
/**************************************/
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
if(pageOne==1)
{
displayPageOne();
}
else if(pageTwo==1)
{
displayPageTwo();
}
else if(pageFour==1)
{
  gameOver();
  if(GOverTimer>700)
      {
    pageTwo=1;
    pageThree=0;
    pageFour=0;
    GOverTimer=0;
      }
  GOverTimer++;
}
else if(pageThree==1)
{
  displayPageThree();
}
if(timer>1000)
    {
  flag=1;
  timer=0;
    }
timer++;

glFlush();
glutSwapBuffers();
}
/****************************************************/


 int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(width,hight);
glutCreateWindow("Galaga");
  //gluOrtho2D(0.0,750.0,0.0,750.0);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
	glutIdleFunc(idlePageThree);
  glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
