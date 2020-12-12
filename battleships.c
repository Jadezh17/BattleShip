#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>


#include <math.h>



struct ship
{
  int startpoint[2];
  int end_point[2];
  int life;
};

struct cell
{
  int pointX;
  int pointY;
  int status;
  char shipName[100];

};
struct board
{
  struct cell c[64];
  int status;
  struct ship s[5];
};

struct Player{
  struct board b;
};

struct Player p[2];



void setup(){

  int cell=1;
  for(int i=1 ; i < 9;i++)
  {
    for(int j =1; j< 9; j++)
    {
      cell+=1;
      p[0].b.c[cell].pointX = i;
      p[0].b.c[cell].pointY = j;
      p[0].b.c[cell].status = 0;


    }
  }

  int cell2=1;
  for(int i=1 ; i < 9;i++)
  {

    for(int j =1; j< 9; j++)
    {
      cell2+=1;
      p[1].b.c[cell2].pointX = i;
      p[1].b.c[cell2].pointY = j;
      p[1].b.c[cell2].status = 0; // cell status to 0 is not hit , 1 is hit , 2 is miss


    }
  }



}











int getCellNumber(int x, int y, int person){
  int cellNumber;
  // printf("This is x: %d this is y: %d this is person: %d\n",x,y,person);


  for(int j =   1 ; j<= (sizeof(p[person].b.c)/sizeof(p[person].b.c[0])+1); j ++){

    if ((p[person].b.c[j].pointX == x ) &&(p[person].b.c[j].pointY == y)){

      cellNumber = j;
    }

  }

  return (cellNumber -1);
}

int setCellStatus (int x, int y , int a)
{

  int s;
  int m;



  s = getCellNumber(x,y,a); //


  m = p[a].b.c[s].status;
  // printf("status in m : %d\n",m);





  return m;

}

int  getBoatIndex(char arr[]){


  if((strcmp(arr,"Carrier"))== 0){
    return 0;
  }

  else if ((strcmp(arr,"Battleship"))== 0){
    return 1;
  }
  else if ((strcmp(arr,"Destroyer"))== 0){
    return 2;
  }
  else if ((strcmp(arr,"Submarine"))== 0){
    return 3;
  }
  else if ((strcmp(arr,"Patrol Boat"))== 0){
    return 4;
  }
}

char getcellstatus(int x , int y , int i){

  int state;


  state = setCellStatus(x,y,i);
  // printf("Current status: %d\n",state);



  if (state == 0){
    return ' ';
  }
  else if (state == 1){
    return '0';
  }
  else if (state == 2){
    return 'X';
  }

}


int checkLife(int index,int person)
{

  if (p[person].b.s[index].life == 0)
  {
    return 1;
  }
  else
  {
    // printf("%d",p[person].b.s[index].life);
    return 0;
  }
}

void checkWIn(int person){
  int win = 5;


  for(int i = 0 ; i< 5; i ++ ){
    if((p[person].b.s[i].life) ==0){
      win = (win -1);
    }

  }

  if(win == 0){
    if(person == 0){
      printf("Player 2 wins!\n");
      exit(0);
    }
    else
    {
      printf("Player 1 wins!\n");
      exit(0);
    }

  }
}

int hasAlreadyhit(int x, int y , int person){
  int cellNumber;
  cellNumber = getCellNumber(x,y,person);
  if( p[person].b.c[cellNumber].status != 0){


    return 1;
  }
  return 0;


}


void hit (int x, int y , int person)
{

  int cellNumber;
  int alive; // equal 1 is sunk
  int boatIndex;

  int hashit = 0;


  cellNumber = getCellNumber(x,y,person);
  boatIndex = getBoatIndex(p[person].b.c[cellNumber].shipName);
  hashit = hasAlreadyhit(x,y,person);


  // printf("This is cell Number: %d\n", cellNumber);
  // printf("Name: %s\n",p[person].b.c[cellNumber].shipName);
  //
  // printf("status : %d\n",p[person].b.c[cellNumber].status);
  // printf("This is status %d\n",p[person].b.c[cellNumber].status);
  // printf("This is name %s\n",p[person].b.c[cellNumber].shipName);





  if((strlen(p[person].b.c[cellNumber].shipName) !=0))
  {

    if(p[person].b.c[cellNumber].status == 0){
      p[person].b.c[cellNumber].status = 2;

      p[person].b.s[boatIndex].life -=1;
      // printf("status : %d\n",p[person].b.c[cellNumber].status);


      alive = checkLife(boatIndex,person);



      if (alive ==1)
      {

        printf("We have sunk your %s!\n",p[person].b.c[cellNumber].shipName);
        printf("\n");
        checkWIn(person);
        printf("Player %d's turn\n",person + 1);
        printf("\n");

      }
      else
      {
        printf("We have hit the target!\n");
        printf("\n");
        printf("Player %d's turn\n",person + 1);
        printf("\n");


      }

    }
  }

  else if (hashit == 0)
  {



    printf("You have missed!\n");
    printf("\n");
    p[person].b.c[cellNumber].status = 1;
    printf("Player %d's turn\n",person + 1);
    printf("\n");


  }







}


void draw(int p)
{
  printf("\n");
  char status;



  for(int i=0 ; i < 9;i++)
  {
    for(int j =0; j< 18; j++)
    {
      if (i==0)
      {
        //print first row
        if ( j%2 ==0 && j!=0)
        {
          printf("%d",(int)round(j/2));
        }
        else if (i ==0 &&j==17){
          continue;
        }
        else
        {
          printf("%c",' ');
        }
      }

      if (j==0)
      {
        //print first columm
        if (i ==1){
          printf("%c",'A');
        }
        else if (i ==2){
          printf("%c",'B');
        }
        else if (i ==3){
          printf("%c",'C');
        }
        else if (i ==4){
          printf("%c",'D');
        }
        else if (i ==5){
          printf("%c",'E');
        }
        else if ( i ==6){
          printf("%c",'F');
        }
        else if ( i ==7){
          printf("%c",'G');
        }
        else if ( i ==8){
          printf("%c",'H');
        }

      }

      if (i>0 && j>0)
      {
        //print rest of column
        if ( j%2 !=0){
          printf("%c",'|');
        }


        else{


          status = getcellstatus(i,j/2,p);
          // printf("This is x: %d This is y: %d  thIS IS Person: %d:\n", i,j/2,p);
          printf("%c",status);

        }
      }
    }
    printf("\n");
  }
  printf("\n");



}

int check(int x, int y, int person)
{
  int cellNum;
  cellNum = getCellNumber(x,y,person);
  if((strlen(p[person].b.c[cellNum].shipName) != 0)){

    return 1;
  }

  else if (( x >0 && x<9) &&(y>0 && y<9)){

    return 0;

  }


  else{
    return 1;
  }

}
int checkCoordinates(int x, int y, int person){
  if (( x >0 && x<9) &&(y>0 && y<9)){
    return 0;
  }
  else{
    return 1;
  }

}

int ShipLife(char arr[]){
  if(strcmp(arr,"Carrier") == 0){
    return 5;
  }
  else if(strcmp(arr,"Battleship") == 0){
    return 4;
  }
  else if(strcmp(arr,"Destroyer") == 0){
    return 3;
  }
  else if(strcmp(arr,"Submarine") == 0){
    return 2;
  }
  else if(strcmp(arr,"Patrol Boat") == 0){
    return 2;
  }

}






void inputShip(int player){

  setup();
  char ChaX[2];
  int x;
  int i = 0;
  int y;
  char o[2];
  int cell;
  int shipLife;

  char ships[][20] = {"Carrier","Battleship","Destroyer","Submarine","Patrol Boat"};
  printf("Player %d, please set up your ships (y, x, orientation)\n",player+1);

  while (i< 5)
  {
    printf("%s: ",ships[i]);
    shipLife = ShipLife(ships[i]);

    p[player].b.s[i].life = shipLife;

    scanf("%s %d %s", ChaX, &y, o);


    x = ChaX[0] - 'A';
    x +=1;



    if(check(x,y,player) == 0)
    {
      cell = getCellNumber(x,y,player);
      strncpy(p[player].b.c[cell].shipName, ships[i], 100);
    //  printf("This is cell: %d\n",cell);

    //  printf("This is name: %s\n",p[player].b.c[cell].shipName);

      if ((strcmp(o,"V")) == 0)
      {
        // printf("thIS IS CELL LIFE: %d\n",shipLife);
        for(int j =1; j<shipLife;j++)
        {
          if(check(j+x,y,player) ==0)
          {
            cell = getCellNumber(j+x,y,player);
            //printf("This is cell: %d\n",cell);
            strncpy(p[player].b.c[cell].shipName, ships[i], 100);
          //  printf("This is name: %s\n",p[player].b.c[cell].shipName);

          }
          else
          {
            printf("Invalid ship configuration\n");
            i-=1;
          }
        }
      }

      else if ((strcmp(o,"H"))== 0)
      {
        // printf("thIS IS CELL LIFE: %d\n",shipLife);

        for(int k=1;k<shipLife;k++)
        {
          if(check(x,y+k,player)==0)
          {
            // printf("This is j: %d\n",k);


            cell = getCellNumber(x,y+k,player);

            strncpy(p[player].b.c[cell].shipName, ships[i], 100);

          }
          else
          {
            printf("Invalid ship configuration\n");
            i-=1;
          }
        }

      }
      i++;
    }

    else
    {
      printf("Invalid ship configuration\n");
    }





  }

  printf("\n");

}




int main()
{

  inputShip(0);
  printf("\n");

  inputShip(1);







  int counter = 0;
  int cx = 0;
  int cy =0;
  int person = ((counter%2) +1);
  char initalSentence[100];
  int isHit = 0; //0 false 1 is tru
  int cellNumber = 0;


  printf("All boats set up, Player 1 can now strike.\n");
  printf("\n");


  getchar();

  while (1)
  {
    scanf("%[^\n]%*c",initalSentence);
    //printf("This is token: %s\n",initalSentence);

    char * token = strtok(initalSentence, " ");


    while(token != NULL)
    {

      for(int i =0; i< strlen(token);i++)
      {
        token[i] =toupper(token[i]);
      }

      if(strcmp(token,"EXIT") == 0)
      {
        exit(0);
      }


      else if (strcmp(token,"FIRE") ==0)
      {
        // printf("\n");
        isHit =1;

      }

      else if (strcmp(token,"SHOTS") ==0)
      {
        if(counter%2 ==0)
        {
          draw((counter%2 +1));

        }
        else
        {
          draw((counter%2 -1));

        }
      }
      else if(token[0] >= '0' && token[0] <= '9')
      {
        cy = atoi(token);
        if((cy>8) || (cy <=0))
        {
          cy = 0;
        }


      }


      else if (token[0] >= 'A' && token[0] <= 'H')
      {
        cx = token[0] - 'A';
        cx +=1;

      }

      token = strtok(NULL, " ");


    }
  //  printf("This is cx:%d This is cy:%d This is ishit: %d\n",cx,cy,isHit);



    if(isHit == 1)
    {
      if(checkCoordinates(cx,cy,person) == 1){

        printf("Invalid coordinates\n");

      }

      else if (counter%2 == 0)
      {
        if (hasAlreadyhit(cx,cy,counter%2 +1) == 1){
          printf("You have already fired at this location\n");

        }
        else{
          printf("\n");
          hit(cx,cy,counter%2 +1);
          counter +=1;


        }


      }

      else
      {
        if (hasAlreadyhit(cx,cy,counter%2 -1) == 1){
          printf("You have already fired at this location\n");

        }
        else{
          printf("\n");
          hit(cx,cy,counter%2-1);
          counter +=1;


        }




      }




      isHit = 0;

    }




  }
  return 0;
}
