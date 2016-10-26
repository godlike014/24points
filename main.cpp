#include "Number.h"
#include "iostream"
//using std::vector;
using namespace std;
void SDLinit();
void draw();
void Updateoperator();
void judge();
int calculate();
SDL_Window* window;
SDL_Renderer* rend;
SDL_Surface* numberSurface;
SDL_Surface* bgSurface;
SDL_Surface* chooseSurface;
SDL_Surface* comSurface;
SDL_Surface* ysSurface;

SDL_Texture* numberTex;
SDL_Texture* bgTex;
SDL_Texture* chooseTex;
SDL_Texture* comTex;
SDL_Texture* ysTex;

SDL_Rect cut[10],ccut[4],abox[10][10],bbox[4],cbox[4],opcut[4],opbox[3];

int m,n,bm,bn,temp=0,hp=5; // m means y  ,   n means x
int operate[4],a[10][10]= {0},b[4]={0};

vector<Number> vNumber;
vector<Number> getNumber;

int main(int argc,char* argv[])
{
    srand((unsigned)time(NULL));
    Number ntemp[NUM];
    for(int i=0; i<NUM; i++)
    {
        vNumber.push_back(ntemp[i]);
        //cout <<vNumber[i].getnum()<<"  ";
        //cout <<ntemp[i].getnum()<<"  ";
    }
    SDLinit();
    SDL_Event event;
    bool quit = false;
    while(!quit)
    {
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                quit = true;
            else if(event.type==SDL_MOUSEMOTION)
            {
                if(event.motion.x<win_w&&event.motion.y<win_w)
                {
                    if(a[event.motion.y/(win_w/10)][event.motion.x/(win_w/10)]==0)
                    {
                        m=event.motion.y/(win_w/10);
                        n=event.motion.x/(win_w/10);
                    }
                }
            }
            else if(event.type== SDL_MOUSEBUTTONDOWN)
            {
                if(event.motion.x<win_w&&event.motion.y<win_w&&temp<4)
                {
                    a[m][n]=1;
                    b[temp]=m*10+n;
                    //cout <<bn<<"   "<<bm<<endl;
                    //cout <<m<<"   "<<n<<endl;
                    //cout <<vNumber[m*10+n].getnum()<<endl;
                    getNumber.push_back(vNumber[m*10+n]);
                    temp++;
                }
                else if (event.motion.x/(win_w/10)>=7&&event.motion.y/(win_w/10)>=10){
                    judge();
                }
            }
            draw();
        }
    }
    SDL_Delay(10);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
void SDLinit()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Twenty-four Points",SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,win_w,win_h,SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    numberSurface = SDL_LoadBMP("image/1-10.bmp");
    bgSurface = SDL_LoadBMP("image/mvbg.bmp");
    chooseSurface = SDL_LoadBMP("image/choose.bmp");
    comSurface = SDL_LoadBMP("image/com.bmp");
    ysSurface = SDL_LoadBMP("image/ys.bmp");
    SDL_SetColorKey(chooseSurface,SDL_TRUE,SDL_MapRGB(chooseSurface->format,255,255,255));
    //SDL_SetColorKey(comSurface,SDL_TRUE,SDL_MapRGB(comSurface->format,255,255,255));
    //SDL_SetColorKey(ysSurface,SDL_TRUE,SDL_MapRGB(ysSurface->format,255,255,255));
    //SDL_SetColorKey(numberSurface,SDL_TRUE,SDL_MapRGB(numberSurface->format,255,255,255));
    numberTex = SDL_CreateTextureFromSurface(rend,numberSurface);
    bgTex = SDL_CreateTextureFromSurface(rend,bgSurface);
    chooseTex = SDL_CreateTextureFromSurface(rend,chooseSurface);
    comTex = SDL_CreateTextureFromSurface(rend,comSurface);
    ysTex = SDL_CreateTextureFromSurface(rend,ysSurface);

    Updateoperator();

}
void draw()
{
    SDL_RenderCopy(rend,bgTex,NULL,NULL);
    //SDL_RenderCopy(rend,ysTex,NULL,&combox);
    for(int i=0; i<10; i++)
    {
        cut[i].x=numberSurface->w/10*i;
        cut[i].y=0;
        cut[i].w=numberSurface->w/10;
        cut[i].h=numberSurface->h;
    }

    cbox[0].x=0;
    cbox[1].x=20;
    cbox[2].x=170;
    cbox[3].x=270;

    bbox[0].x=40;
    bbox[1].x=120;
    bbox[2].x=220;
    bbox[3].x=320;

    opbox[0].x=90;
    opbox[1].x=190;
    opbox[2].x=290;

    for(int i=0;i<4;i++){
        ccut[i].x=i*comSurface->w/4;
        ccut[i].y=0;
        ccut[i].w=comSurface->w/4;
        ccut[i].h=comSurface->h;

        opcut[i].x=i*ysSurface->w/4;
        opcut[i].y=0;
        opcut[i].w=ysSurface->w/4;
        opcut[i].h=ysSurface->h;

        bbox[i].y=win_w+25;
        bbox[i].w=win_w/10;
        bbox[i].h=win_w/10;

        cbox[i].y=win_w+25;
        cbox[i].w=20;
        cbox[i].h=win_w/10;

        if(i<3)
        {
            opbox[i].y=win_w+25;
            opbox[i].w=30;
            opbox[i].h=win_w/10;
        }

    }
    for(int i=0;i<4;i++)
    {
        SDL_RenderCopy(rend,comTex,&ccut[i],&cbox[i]);
        if(i<3)
        {
            SDL_RenderCopy(rend,ysTex,&opcut[operate[i]],&opbox[i]);
        }
    }

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(a[i][j]==0)
            {
                abox[i][j].x=j*win_w/10;
                abox[i][j].y=i*win_w/10;
                abox[i][j].w=win_w/10;
                abox[i][j].h=win_w/10;
                SDL_RenderCopy(rend,numberTex,&cut[vNumber[10*i+j].getnum()-1],&abox[i][j]);
            }
        }
    }
    for(int i=0;i<getNumber.size();i++)
    {
        SDL_RenderCopy(rend,numberTex,&cut[(getNumber[i].getnum())-1],&bbox[i]);
    }
    SDL_RenderCopy(rend,chooseTex,NULL,&abox[m][n]);
    SDL_RenderPresent(rend);
    SDL_Delay(10);
    SDL_RenderClear(rend);
}
void judge()
{
    if(temp==4){
        if(calculate()==24){
                Updateoperator();
                for(int i=0;i<temp;i++){
                    a[(b[i]/10)][(b[i]%10)]=2;
                }
        }
        else{
            for(int i=0;i<temp;i++){
                a[(b[i]/10)][(b[i]%10)]=0;
            }
        }
    }
    else {
        for(int i=0;i<temp;i++){
                a[(b[i]/10)][(b[i]%10)]=0;
            }
    }
    for(int i=0;i<temp;i++){
        getNumber.pop_back();
    }
    temp=0;
}
int calculate()
{
    int result=getNumber[0].getnum();
    for(int i=0;i<3;i++)
    {
        switch (operate[i])
        {
        case 0:
            result+=getNumber[i+1].getnum();
            break;
        case 1:
            result-=getNumber[i+1].getnum();
            break;
        case 2:
            result*=getNumber[i+1].getnum();
            break;
        case 3:
            result/=getNumber[i+1].getnum();
            break;
        }
    }
    return result;
}
void Updateoperator()
{
    do{
    for(int i=0;i<3;i++)
        operate[i]= rand()%4;
    }while((operate[0]%2==1&&operate[1]%2==1&&operate[2]%2==1)
             ||(operate[0]%2==1&&operate[1]%2==1&&operate[2]==0)
                ||(operate[0]%2==1&&operate[2]%2==1&&operate[1]==0)
                    ||(operate[1]%2==1&&operate[2]%2==1&&operate[0]==0));
}
