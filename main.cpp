#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>

#define M 25
#define N 25

using namespace sf;

int campo[M][N] = {0};

int ts = 18;

void pintar(int y,int x)
{
  if (campo[y][x]==0) campo[y][x]=-1;
  if (campo[y-1][x]==0) pintar(y-1,x);
  if (campo[y+1][x]==0) pintar(y+1,x);
  if (campo[y][x-1]==0) pintar(y,x-1);
  if (campo[y][x+1]==0) pintar(y,x+1);
}

void rellenar(){

    for(int i = 0; i<M; i++){
        for(int j = 0; j<N; j++){
            if(campo[i][j] == 2){
                campo[i][j] = 1;
            }
        }
    }
}


int main()
{
    //Logica

    srand(time(0));
    RenderWindow window(VideoMode(M*ts,N*ts), "SplixIO");
    window.setFramerateLimit(60);

    int origen = 1;

    Texture t1,t2;

    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");

    Sprite sTile(t1), sGameOver(t2);

    float timer=0, delay=0.07;
    Clock clock;

    int x=9, y=9, dx=0, dy=0;

    for(int i = 0; i<M; i++){
        for(int j = 0; j< N; j++){
            if(i == 8 && j == 8) campo[i][j] = origen;
            if(i == 8 && j == 9) campo[i][j] = origen;
            if(i == 8 && j == 10) campo[i][j] = origen;
            if(i == 9 && j == 8) campo[i][j] = origen;
            if(i == 9 && j == 9) campo[i][j] = origen;
            if(i == 9 && j == 10) campo[i][j] = origen;
            if(i == 10 && j == 8) campo[i][j] = origen;
            if(i == 10 && j == 9) campo[i][j] = origen;
            if(i == 10 && j == 10) campo[i][j] = origen;
        }
    }

    while(window.isOpen()){

        float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        Event e;

        while(window.pollEvent(e)){
            if(e.type == Event::Closed){
                window.close();
            }

            if(e.type == Event::KeyPressed){
                if(e.key.code == Keyboard::Escape){
                    window.close();
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;}
	    if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;}
	    if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;}

		if (timer>delay)
		{
         x+=dx;
         y+=dy;

		 if (x<0) x=0; if (x>N-1) x=N-1;
         if (y<0) y=0; if (y>M-1) y=M-1;

         if (campo[y][x]==2) return 0;
         if (campo[y][x]==0) campo[y][x]=2;
         if (campo[x][y]==1) {

            rellenar();
            for(int i = 0; i < M; i++){
                for(int j = 0; j< N; j++){
                    if(campo[i][j]==0){
                        if(campo[i][j-1] == 1 && campo[i-1][j] == 1){
                            pintar(i,j);
                       }
                    }
                }
            }
         }
         timer=0;
		}

        ///draw
        window.clear();

        for(int i = 0; i<M; i++){
            for(int j = 0; j<N; j++){
                if(campo[i][j] == 0) continue;
                if(campo[i][j] == 1) sTile.setTextureRect(IntRect(0,0,ts,ts));
                sTile.setPosition(j*ts,i*ts);
                window.draw(sTile);
            }
        }

        sTile.setTextureRect(IntRect(36,0,ts,ts));
        sTile.setPosition(x*ts,y*ts);
        window.draw(sTile);

        window.display();
    }

    return 0;
}
