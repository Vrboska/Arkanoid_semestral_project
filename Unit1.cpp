//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Lod.cpp"
#include "Gulocka.cpp"
#include "Vtak.cpp"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


Graphics::TBitmap *Pozadie;
Graphics::TBitmap *Zasah;

TLod l;                        /*tri hlavne objekty, lodicka, gulocka a vtak*/
TGulocka g;
TVtak v1(random(300),0,5,1,1);
TVtak v2(random(300),0,6,1,2);
TVtak v3(random(300),0,7,1,3);

int zivoty,level;
int a=0;
int pohyb_gulocky=0;//pomocne premenne


void __fastcall TForm1::FormCreate(TObject *Sender)        //nacita sa uvodne rozostavenie a hra sa moze zacat
{

        Pozadie=new Graphics::TBitmap();
        Pozadie->LoadFromFile("pozadie.bmp");
        Image1->Canvas->Draw(0, 0, Pozadie );



        zivoty=2;
        level=1;
        Label4->Caption=level;
        Label3->Caption=zivoty;

        l.Inic(Image1->Width/2,Image1->Height-20,"Lod2.bmp");
        l.Kresli(Image1);
        g.Inic(Image1,Image1->Width/2,Image1->Height-20);
        g.Kresli();
        g.PeroHore();
        g.vp(30);



}

void Inicializuj()  //funkcia nastavi vsetko do povodneho stavu
{

 Form1->Timer2->Enabled=false;
 Form1->Timer1->Enabled=false;
 Form1->Image1->Canvas->Draw(0, 0, Pozadie );
 Form1->Image1->Canvas->Brush->Color=clGreen;
 Form1->Image1->Canvas->FillRect(Rect(0,Form1->Image1->Height-30,Form1->Image1->Width,Form1->Image1->Height));

 level=1;
 zivoty=2;
 pohyb_gulocky=0;

 v1.Y=0;
 v1.Zivot=5;
 v1.X=random(300);
 v1.Smer=1;

 v2.Y=0;
 v2.Zivot=6;
 v2.X=random(300);
 v2.Smer=1;

 v3.Y=0;
 v3.Zivot=7;
 v3.X=random(300);
 v3.Smer=1;


 Form1->Label4->Caption=level;
 Form1->Label3->Caption=zivoty;
 l.Inic(Form1->Image1->Width/2,Form1->Image1->Height-20,"Lod2.bmp");
 l.Kresli(Form1->Image1);
 g.Inic(Form1->Image1,Form1->Image1->Width/2,Form1->Image1->Height-20);
 g.Kresli();
 g.PeroHore();
 g.vp(30);

 }

//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,    //funkcia ovladajuca pohyb lode
      int X, int Y)
{
 l.Zmen(X);
 Image1->Canvas->Brush->Color=clGreen;
 Image1->Canvas->FillRect(Rect(0,Form1->Image1->Height-30,Form1->Image1->Width,Form1->Image1->Height));
 l.Kresli(Image1);

 if (pohyb_gulocky==0){g.Inic(Image1,l.X,l.Y-3);g.vp(30);g.Kresli();}

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Image1MouseDown(TObject *Sender,    //spusti pohyb
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 Timer2->Enabled=true;
 pohyb_gulocky=1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer2Timer(TObject *Sender) //hlavna funkcia programu zabezpecujuca chod
{
  if (g.Y>Image1->Height){                              //situacia ked gulocka "spadne"
                                   zivoty=zivoty--;    //odoberie zivot

                                   if(zivoty==0){                   //ukonci hru ak to bol posledny zivot
                                                 Inicializuj();
                                                 ShowMessage("Koniec hry, nemas zivoty! Skus to znova.");

                                                 return;
                                                }

                                    //gulocka sa zinicializuje

                                   pohyb_gulocky=0;
                                   Label4->Caption=level;
                                   Label3->Caption=zivoty;
                                   l.Inic(Image1->Width/2,Image1->Height-20,"Lod2.bmp");
                                   l.Kresli(Image1);
                                   g.Inic(Image1,Image1->Width/2,Image1->Height-18);
                                   g.Kresli();
                                   g.PeroHore();
                                   g.vp(30);
                          }


 // nastavovanie rychlosti, gulocka sa hybe len po zapnuti timer2 kliknutim mysi
 if (Timer2->Enabled==true&&pohyb_gulocky>0){if(Edit1->Text=="7"||Edit1->Text=="6"||Edit1->Text=="4"||Edit1->Text=="3"||Edit1->Text=="5")g.dp(StrToInt(Edit1->Text));
                            else g.dp(3);
                            }
 //vykreslovanie pozadia a lodky
 Image1->Canvas->Draw(0, 0, Pozadie );
 l.Kresli(Image1);

 //vykreslenie gulocky a jej pripadne odrazenie
 g.Kresli();
 g.OdrazSa(&l);



 // riadenie pohybu vtakov v zavislosti od daneho levelu, vtaci sa hybu len pokial nie su zasiahnuti
 if (Timer1->Enabled==false)

 switch (level)
 {
   //level1
   case 1:

                        { if(a==10){a=0;
                                        v1.ZmenFazu();
                                        v1.Pohni(v1.Smer*8);
                                        if(v1.X+v1.bmp[v1.Faza]->Width>Image1->Width||v1.X<=0){v1.ZmenSmer();v1.Y=v1.Y+30; }
                                        }
                                a++;
                                v1.Kresli(Image1->Canvas);
                                if (v1.Test(&g)==true){if(v1.Zivot>=2){Timer1->Enabled=true;v1.Zivot--;}
                                                        else{Image1->Canvas->Draw(0,0,Pozadie);Timer2->Enabled=false;pohyb_gulocky=0;level++;ShowMessage("Bravo, je mrtvy. Stlac 'Ok' na druhy level.");}
                                                       }
                                if(v1.Y>280){Inicializuj();ShowMessage ("Koniec hry, vtak pristal!Skus to znova.");}
                         }
                        break;
  //level2
   case 2:

                        { if(a==10){a=0;
                                        v2.ZmenFazu();
                                        v2.Pohni(v2.Smer*18);
                                        v2.Y=v2.Y+1;
                                        if(v2.X+v2.bmp[v2.Faza]->Width>Image1->Width||v2.X<=0){v2.ZmenSmer();v2.Y=v2.Y+30; }
                                        }
                                a++;
                                v2.Kresli(Image1->Canvas);
                                if (v2.Test(&g)==true){if(v2.Zivot>=2){Timer1->Enabled=true;v2.Zivot--;}
                                                       else{Image1->Canvas->Draw(0,0,Pozadie);Timer2->Enabled=false;pohyb_gulocky=0;level++;ShowMessage("Bravo, je mrtvy. Stlac 'Ok' na treti level."); }
                                                       }
                                if(v2.Y>280){Inicializuj();ShowMessage ("Koniec hry, vtak pristal!Skus to znova.");}
                         }
                        break;
   //level 3
   case 3:



                         { if(a==10){a=0;
                                        v3.ZmenFazu();
                                        v3.Pohni(v3.Smer*18);
                                        v3.Y=v3.Y+2;
                                        if(v3.X+v3.bmp[v2.Faza]->Width>Image1->Width||v3.X<=0){v3.ZmenSmer();v3.Y=v3.Y+30; }
                                        }
                                a++;
                                v3.Kresli(Image1->Canvas);
                                if (v3.Test(&g)==true){if(v3.Zivot>=2){Timer1->Enabled=true;v3.Zivot--;}
                                                       else{Image1->Canvas->Draw(0,0,Pozadie);Timer2->Enabled=false;pohyb_gulocky=0;level=0;ShowMessage("Bravo, je mrtvy.Vyhral si");}
                                                       }
                                if(v3.Y>280){Inicializuj();ShowMessage ("Koniec hry, vtak pristal!Skus to znova.");}
                         }
                        break;

  }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)  //zmaze dynamicke premenne
{
 delete Pozadie;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender) //spusti novu hru
{
 Inicializuj();
}
//---------------------------------------------------------------------------

int b=0;        //pomocna premenna
void __fastcall TForm1::Timer1Timer(TObject *Sender)    //funkcia zabezpecujuca blikanie vtaka po zasahu
{b++;

 Zasah=new Graphics::TBitmap;
 Zasah->LoadFromFile("Zasah.bmp");
 Zasah->Transparent=true;

switch (level)
 {
  case 1:
         {
         if (b%10)v1.Kresli(Image1->Canvas);
         Image1->Canvas->Draw(v1.X,v1.Y,Zasah);

         if (b==130){b=0;Timer1->Enabled=false;}
         }
         break;


  case 2:
         {
         if (b%10)v2.Kresli(Image1->Canvas);
         Image1->Canvas->Draw(v2.X,v2.Y,Zasah);

         if (b==130){b=0;Timer1->Enabled=false;}
         }
         break;

  case 3:
        {
         if (b%10)v3.Kresli(Image1->Canvas);
         Image1->Canvas->Draw(v3.X,v3.Y,Zasah);

         if (b==130){b=0;Timer1->Enabled=false;}
         }
         break;

  }


 delete Zasah;
}
//---------------------------------------------------------------------------


