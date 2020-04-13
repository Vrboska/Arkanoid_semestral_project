#include <vcl.h>

#pragma hdrstop

#include <math.h>



class TGulocka     // gulocku naprogramujeme pozmenenim triedy korytnacka

{
private:
  float FSmer;
  float FX, FY;
  bool FKresli;
  TImage *FImage;
  void ZmenX(float nX);
  void ZmenY(float nY);
public:
  TGulocka();
  void Inic(TImage *nImage);
  void Inic(TImage *nImage, int nX, int nY);
  void ZmenSmer(float nSmer);
  void ZmenXY(float nX, float nY);
  void Vlavo(float Uhol);
  void Vpravo(float Uhol);
  void Dopredu(float Dlzka);
  void PeroHore();
  void PeroDolu();
  void Kresli();
  void OdrazSa(TLod *L);
  float Smerom(float aX, float aY);
  void vl(float Uhol) {Vlavo(Uhol);};
  void vp(float Uhol) {Vpravo(Uhol);};
  void dp(float Dlzka) {Dopredu(Dlzka);};
  void pd() {PeroDolu();};
  void ph() {PeroHore();};
  __property float Smer={read=FSmer, write=ZmenSmer};
  __property float X={read=FX, write=ZmenX};
  __property float Y={read=FY, write=ZmenY};
  __property TImage *Image={read=FImage};
};


// verejne metody:

TGulocka::TGulocka()
{
  Inic(NULL,0,0);
}

void TGulocka::Inic(TImage *nImage)
{
  if (nImage==NULL) Inic(NULL, 0, 0);
  else Inic(nImage, nImage->Width/2, nImage->Height/2);
}

void TGulocka::Inic(TImage *nImage, int nX, int nY)
{
  FImage=nImage;
  FSmer=0;
  FX=nX;
  FY=nY;
  FKresli=(FImage!=NULL);

}

void TGulocka::ZmenSmer(float nSmer)
{
  if (FSmer==nSmer) return;
  FSmer=nSmer;
  while (FSmer<-180) FSmer=FSmer+360;
  while (FSmer>+180) FSmer=FSmer-360;
}

void TGulocka::ZmenXY(float nX, float nY)
{
  if (FX==nX && FY==nY) return;
  if (FKresli) {
    FImage->Canvas->MoveTo(X+0.5, Y+0.5);
    FImage->Canvas->LineTo(nX+0.5, nY+0.5);
  }
  FX=nX;
  FY=nY;
}


void TGulocka::Vlavo(float Uhol)
{
  ZmenSmer(FSmer-Uhol);
}

void TGulocka::Vpravo(float Uhol)
{
  ZmenSmer(FSmer+Uhol);
}

void TGulocka::Dopredu(float Dlzka)
{
  float a;
  a=FSmer*M_PI/180.0;
  ZmenXY(FX+Dlzka*sin(a), FY-Dlzka*cos(a));
}

void TGulocka::PeroHore()
{
  FKresli=false;
}

void TGulocka::PeroDolu()
{
  FKresli=(FImage!=NULL);
}


void TGulocka::ZmenX(float nX)
{
  ZmenXY(nX, FY);
}

void TGulocka::ZmenY(float nY)
{
  ZmenXY(FX, nY);
}


//uplne nove funkcie
void TGulocka::Kresli()

{
 FImage->Canvas->Brush->Color=clRed;
 FImage->Canvas->Ellipse(FX-7,FY-7,FX+7,FY+7);
 FImage->Canvas->Brush->Color=clWhite;
}

void TGulocka::OdrazSa(TLod *L)   // funkcia kt. zabezpecuje odrazanie sa gulocky od stien aj lode

{
 if (FX<=14/sqrt(2)){FX=14/sqrt(2);FSmer=360-FSmer;}
 if(FX>=Image->Width-14/sqrt(2)){FX=Image->Width-14/sqrt(2);FSmer=360-FSmer;}
 if(FY<=14/sqrt(2)){FY=14/sqrt(2);FSmer=180-FSmer;}
 if((FY-Image->Height+25)>0&&(FY-Image->Height+25)<7&&(abs(FX-L->X)<=L->Obrazok->Width/2))FSmer=(FX-L->X)*1.75;

}
