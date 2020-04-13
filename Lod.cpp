class TLod                        //definujem si vlastnu triedu TLod, ktora bude odrazat lopticku
{
 public:
  int X,Y;                        //pamata si aktualnu polohu lode
  Graphics::TBitmap *Obrazok;     //Obrazok lode
 public:
  TLod ();
  ~TLod();
  void Inic(int nX,int nY,AnsiString Subor);   //funkcia analogicka konstruktoru s parametrom, bude ju ale casto potrebne volat v tele programu 
  void Zmen(int dX);                           //zmeni polohu
  void ZmenObrazok(AnsiString Subor);          //zmeni obrazok
  void Kresli(TImage *Image);                 //funkcia vykresli lod do image

};


TLod::TLod()
{
 X=0;
 Y=0;
 Obrazok=new Graphics::TBitmap;
}

void TLod::Inic(int nX,int nY, AnsiString Subor)
{
 X=nX;
 Y=nY;
 Obrazok->LoadFromFile(Subor);
 Obrazok->Transparent=true;
}


TLod::~TLod()
{
 delete Obrazok;
}


void TLod::Zmen(int dX)
{

 X=dX;
}


void TLod::ZmenObrazok(AnsiString Subor)
{
 Obrazok->LoadFromFile(Subor);
}

void TLod::Kresli( TImage *Image)
{
 if (X<Obrazok->Width/2)X=Obrazok->Width/2;
 if (X>Image->Width-Obrazok->Width/2)X= Image->Width-Obrazok->Width/2;
 Image->Canvas->Draw(X-Obrazok->Width/2,Y,Obrazok);
}
