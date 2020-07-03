#include <dos.h>
#include <conio.h>
#include <iostream>
union REGS regin,regout;
void take_Input();
void pressAnyKey();
void drawXLines();
void drawXLines_1();
void drawYLines();
void drawYLines_all();
void drawYLines_1();
void drawYLines_1_no640x480();
void findDistanceX();
void findDistanceY();
int const lengthX=440.0;
int const lengthY=380.0;
int number1;
int number2;
int *distanceX;
int *distanceY;
main()
{
	take_Input();
   if(number1==0)
   {
   	if(number2==0)
      {
        cout<<"(0,0) grid cannot be created.";
      }
      else if(number2==1)
      {
      	pressAnyKey();
   		drawYLines_1();
      }
      else
      {
         pressAnyKey();
      	findDistanceX();
      	drawYLines_all();
      }
   }
   else if(number1==1)
   {
       if(number2==0)
      {
      	 pressAnyKey();
          drawXLines_1();
      }
      else if(number2==1)
      {
      	pressAnyKey();
      	drawXLines_1();
   		drawYLines_1_no640x480();
      }
      else
      {
      	pressAnyKey();
      	findDistanceX();
      	drawXLines_1();
      	drawYLines();
      }
   }
   else
   {
   	if(number2==0)
      {
      	 pressAnyKey();
       	 findDistanceY();
          drawXLines();
      }
      else if(number2==1)
      {
      	pressAnyKey();
      	findDistanceY();
      	drawXLines();
   		drawYLines_1_no640x480();
      }
      else
      {
      	pressAnyKey();
   		findDistanceY();
			drawXLines();
         findDistanceX();
      	drawYLines();
      }
   }

   getch();

}
void take_Input()
{
       do
      {
         cout << "Please, enter the first number(0-99): ";
          while (!(cin >> number1))
   		 {
      	  // Explain error
      	  cout << "ERROR: a number must be entered: ";
       	 // Clear input stream
       	 cin.clear();
       	 // Discard previous input
       	 cin.ignore(132, '\n');
  			 }
      }
      while (!(number1>=0 && number1 <100));

      do
      {
         cout << "Please, enter the second number(0-99): ";
         while (!(cin >> number2))
   		 {
      	  // Explain error
      	  cout << "ERROR: a number must be entered: ";
       	 // Clear input stream
       	 cin.clear();
       	 // Discard previous input
       	 cin.ignore(132, '\n');
  			 }
      }
      while (!(number2>=0 && number2 <100));
}
void findDistanceX()
{
   distanceX= new int [number2-2];
   int distanceX_mod=440%(number2-1);
   for(int j=0;j<(number2-1);j++)
   {
   	distanceX[j]= 440/(number2-1);
   }
   for(int z=0;z<distanceX_mod;z++)
   {
   	distanceX[z]=distanceX[z]+1;
   }
}
void findDistanceY()
{
   distanceY= new int [number1-2];
   int distanceY_mod=380%(number1-1);
   for(int j=0;j<(number1-1);j++)
   {
   	distanceY[j]= 380/(number1-1);
   }
   for(int z=0;z<distanceY_mod;z++)
   {
   	distanceY[z]=distanceY[z]+1;
   }
}
void drawXLines()
{
	regin.x.ax=0x0600;
   regin.h.bh=0x08;
   regin.x.cx=0x0000;
   regin.x.dx=0x184F;
   int86(0x10,&regin,&regout);
   regin.h.ah=0;
   regin.h.al=0x12;
   int86(0x10,&regin,&regout);
   regin.x.cx=100;
   regin.x.dx=50;
   for(int i=0;i<number1;i++)
   {
   	while(!(regin.x.cx==540))
      {
      	regin.h.ah=0x0C;
      	regin.h.al=0x01;
         int86(0x10,&regin,&regout);
         regin.x.cx=regout.x.cx+1;
      }
      regin.x.cx=100;
      regin.x.dx=regin.x.dx+distanceY[i];
   }
}


void drawXLines_1()
{
	regin.x.ax=0x0600;
   regin.h.bh=0x08;
   regin.x.cx=0x0000;
   regin.x.dx=0x184F;
   int86(0x10,&regin,&regout);
   regin.h.ah=0;
   regin.h.al=0x12;
   int86(0x10,&regin,&regout);
   regin.x.cx=100;
   regin.x.dx=50;

   	while(!(regin.x.cx==540))
      {
      	regin.h.ah=0x0C;
      	regin.h.al=0x01;
         int86(0x10,&regin,&regout);
         regin.x.cx=regout.x.cx+1;
      }

}

void drawYLines_all()  //This function is used if number1 is 0.
{
	regin.x.ax=0x0600;
   regin.h.bh=0x08;
   regin.x.cx=0x0000;
   regin.x.dx=0x184F;
   int86(0x10,&regin,&regout);
   regin.h.ah=0;
   regin.h.al=0x12;
   int86(0x10,&regin,&regout);
   regin.x.cx=100;
   regin.x.dx=50;
   for(int i=0;i<number2;i++)
   {
   	while(!(regin.x.dx==430))
      {
      	regin.h.ah=0x0C;
      	regin.h.al=0x01;
         int86(0x10,&regin,&regout);
         regin.x.dx=regout.x.dx+1;
      }
      regin.x.dx=50;
      regin.x.cx=regin.x.cx+distanceX[i];
   }
}

void drawYLines()  //This function is used if number1 is not 0.
{
   regin.x.cx=100;
   regin.x.dx=50;
   for(int i=0;i<number2;i++)
   {
   	while(!(regin.x.dx==430))
      {
      	regin.h.ah=0x0C;
      	regin.h.al=0x01;
         int86(0x10,&regin,&regout);
         regin.x.dx=regout.x.dx+1;
      }
      regin.x.dx=50;
     // cout<<distanceX[i]<<"\n";
      regin.x.cx=regin.x.cx+distanceX[i];
   }
}
void drawYLines_1()  //This function is used if number1 is 0 and number2=1.
{
	regin.x.ax=0x0600;
   regin.h.bh=0x08;
   regin.x.cx=0x0000;
   regin.x.dx=0x184F;
   int86(0x10,&regin,&regout);
   regin.h.ah=0;
   regin.h.al=0x12;
   int86(0x10,&regin,&regout);
   regin.x.cx=100;
   regin.x.dx=50;
   	while(!(regin.x.dx==430))
      {
      	regin.h.ah=0x0C;
      	regin.h.al=0x01;
         int86(0x10,&regin,&regout);
         regin.x.dx=regout.x.dx+1;
      }
}
void drawYLines_1_no640x480()  //This function is used if number1 is 0 and number2=1.
{
   regin.x.cx=100;
   regin.x.dx=50;
   	while(!(regin.x.dx==430))
      {
      	regin.h.ah=0x0C;
      	regin.h.al=0x01;
         int86(0x10,&regin,&regout);
         regin.x.dx=regout.x.dx+1;
      }
}
void pressAnyKey()
{
	cout<<"("<<number1<<","<<number2<<")"<<" grid drawing will start. Please wait until the drawing is completed."<<"\n";
   cout<<"Please press <Enter> to start the drawing operation!";
   cin.ignore();
	cin.get();

}