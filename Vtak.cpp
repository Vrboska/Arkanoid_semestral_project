class TVtak          //este jedna nova objektova trieda
 {
public:

  int Faza;
  int Zivot;                //pocet zivotov vtaka
  int Druh;                 //identifikuje druh vtaka
  Graphics::TBitmap *bmp[8]; //obrazky
  float X, Y;                //poloha
  int Smer;                  //smer(+1vpravo,-1 vlavo)

 TVtak(int nX, int nY,int nZivot,int nSmer, int nDruh);
 ~TVtak();
  void Kresli(TCanvas *Canvas);
  void Pohni(int dX);
  void ZmenFazu();
  void ZmenSmer();
  bool Test(TGulocka *Gulocka);
 };


TVtak::TVtak(int nX, int nY,int nZivot,int nSmer, int nDruh)
{
 int i;
 for (i=0;i<8;i++){bmp[i]=new Graphics::TBitmap;
                   if(i<4){bmp[i]->LoadFromFile("Vtak"+IntToStr(nDruh)+"p"+IntToStr(i+1)+".bmp");bmp[i]->Transparent=true;}
                   else {bmp[i]->LoadFromFile("Vtak"+IntToStr(nDruh)+"l"+IntToStr(i-4+1)+".bmp");bmp[i]->Transparent=true;}
                   }
 Smer=nSmer;
 X=nX;
 Y=nY;
 Druh=nDruh;
 Zivot=nZivot;
 if(nSmer==1)Faza=0;
 if(nSmer==-1)Faza=4;
}


TVtak::~TVtak()
{
 int i;
 for (i=0;i<8;i++)delete bmp[i];
}

void TVtak::Kresli(TCanvas *Canvas)
{
 Canvas->Draw(X,Y,bmp[Faza]);
}

void TVtak::Pohni(int dX)
{
 X=X+dX;
}

void TVtak::ZmenFazu()
{
 if(Smer==1){if(Faza>=3)Faza=0 ;
             else Faza++;}
 if(Smer==-1){if(Faza<4||Faza==7)Faza=4;
             else Faza++;}
}

void TVtak::ZmenSmer()
{
 Smer=-1*Smer;
}



bool TVtak::Test(TGulocka *Gulocka)    //funkcia bude testovat ci je gulocka v blikosti obrazka
{
 if (Gulocka->X>=X&&Gulocka->X<=X+bmp[Faza]->Width&&Gulocka->Y>=Y&&Gulocka->Y<=Y+bmp[Faza]->Height)return true;
 return false;
}
