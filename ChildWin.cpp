//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChildWin.h"
#include "Progress.h"
#include "AnnoBitmap.h"
#include "BmDisplay.h"
//---------------------------------------------------------------------
//#pragma link "TntComCtrls"
#pragma resource "*.dfm"

//---------------------------------------------------------------------
__fastcall TMDIChild::TMDIChild(TComponent *Owner)
	: TForm(Owner)
{
    ListView->OwnerData = true;
    ListView->OnData = ListViewData;
    ListView->OnDataHint = ListViewDataHint;
    ListView->DoubleBuffered = true;
}
//---------------------------------------------------------------------
void __fastcall TMDIChild::FormClose(TObject *Sender, TCloseAction &Action)
{
    BmForm->Close();
	Action = caFree;
}

//---------------------------------------------------------------------

void TMDIChild::LoadImage(int listIndex)
{
    AnnoBitmap* bm = new AnnoBitmap();
    if( bm->LoadBitmap( FileName, listIndex ) == 1 )
    {
        AnsiString Image = "Bild ";
        String caption = Image + (listIndex + 1) +
            " (" + bm->Width + "x" + bm->Height + ")";

        Graphics::TBitmap* icon = makeIcon(bm);

//        int index = ImageList->AddMasked( icon, TColor(0xFF00FF) );
        int index = ImageList->Add( icon, 0 );

//        Item->ImageIndex = index;
//        Item->Caption = caption;
        imageMap[listIndex] = index;
        textMap[listIndex] = caption;
        delete icon;
    }

    delete bm;
}

//---------------------------------------------------------------------

void TMDIChild::OpenFile(AnsiString filename,
    int FromIndex, int ToIndex )
{
    FileName = filename;
//    ListView->Items->Clear();

    TFileStream* fs = new TFileStream( filename, fmOpenRead );
    int numBitmaps;
    fs->Position = 20;
    fs->Read( &numBitmaps, sizeof(int) );
    numBitmaps /= sizeof(int);
    delete fs;

    ListView->Items->Count = numBitmaps;
}

//---------------------------------------------------------------------

Graphics::TBitmap* __fastcall TMDIChild::makeIcon(Graphics::TBitmap* bm)
{
    const int SIZE = ImageList->Width;

    Graphics::TBitmap* icon = new Graphics::TBitmap();
    icon->Width = SIZE;
    icon->Height = SIZE;
//    icon->TransparentColor = bm->TransparentColor;
    icon->Canvas->Brush->Assign( bm->Canvas->Brush );
    icon->PixelFormat = bm->PixelFormat;
     
    if( bm->Width > SIZE || bm->Height > SIZE )
//    if( true )
    {
        // scale BM down
        TRect r;
        float f;
        if( bm->Width > bm->Height )
        {
            // scale width
            f = ((float)SIZE) / ((float)bm->Width);
            r.Left = 0;
            r.Top = (SIZE - (bm->Height * f)) / 2;
            r.Right = SIZE;
            r.Bottom = r.Top + (bm->Height * f);
        }
        else
        {
            f = ((float)SIZE) / ((float)bm->Height);
            r.Left = (SIZE - (bm->Width * f)) / 2;
            r.Top = 0;
            r.Right = r.Left + (bm->Width * f);
            r.Bottom = SIZE;
        }
        icon->Canvas->StretchDraw( r, bm );
    }
    else
    {
        icon->Canvas->Draw((SIZE-bm->Width)/2, (SIZE-bm->Height)/2, bm );
    }
    return icon;
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = BmForm->CloseQuery();
}

//---------------------------------------------------------------------------

void __fastcall TMDIChild::ListViewClick(TObject *Sender)
{
    if( ListView->SelCount > 0 )
    {
        TListItem* Item = ListView->Selected;
        BmForm->LoadFromBsh( FileName, Item->Index, this );
    }
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::ListViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
    if( !Selected )
    {
        BmForm->FormChange();
    }
    else
    {
        BmForm->LoadFromBsh( FileName, Item->Index, this );
    }
}
//---------------------------------------------------------------------------


void TMDIChild::UpdateIcon(int index, Graphics::TBitmap* bm)
{
    LoadImage(index);
    
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::ListViewDataHint(TObject *Sender,
      int StartIndex, int EndIndex)
{
    for(int i=StartIndex; i<=EndIndex; i++)
    {
        if(imageMap.find(i) == imageMap.end())
        {
            LoadImage(i);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::ListViewData(TObject *Sender, TListItem *Item)
{
    if(imageMap.find(Item->Index) == imageMap.end())
    {
        LoadImage(Item->Index);
    }
    Item->ImageIndex = imageMap[Item->Index];
    Item->Caption = textMap[Item->Index];
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::ListViewDataFind(TObject *Sender,
      TItemFind Find, const AnsiString FindString,
      const TPoint &FindPosition, Pointer FindData, int StartIndex,
      TSearchDirection Direction, bool Wrap, int &Index)
{
    ShowMessage("OnDataFind");    
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::ListViewDeletion(TObject *Sender,
      TListItem *Item)
{
    ShowMessage("OnDeletion");
}
//---------------------------------------------------------------------------


void __fastcall TMDIChild::ListViewDataStateChange(TObject *Sender,
      int StartIndex, int EndIndex, TItemStates OldState,
      TItemStates NewState)
{
    ShowMessage("OnDataStateChange");
}
//---------------------------------------------------------------------------

void __fastcall TMDIChild::ExportAll()
{
    String ext = ExtractFileExt(FileName);
    String dirname = FileName.SubString(0, FileName.Pos(ext));

    if(DirectoryExists(dirname))
    {
        int rsp = MessageDlg(
            "Das Verzeichnis existiert bereits. Überschreiben?",
            mtConfirmation, mbOKCancel, -1 );
        if( rsp != mrOk )
            return;
    }

    ForceDirectories(dirname);

    String path = dirname + "\\" + "Bild";

    int num = ListView->Items->Count;
    ProgressForm->Show();
    ProgressForm->ProgressBar->Min = 0;
    ProgressForm->ProgressBar->Max = num;
    ProgressForm->stopRequested = false;

    for(int i=0; i<ListView->Items->Count &&
        !ProgressForm->stopRequested; i++)
    {
        AnnoBitmap* bm = new AnnoBitmap();
        if( bm->LoadBitmap( FileName, i ) == 1 )
        {
            bm->SaveToFile(path + (i+1) + ".bmp");
            ProgressForm->ProgressBar->Position = i;
            String text = Format("Speichere Bild %d von %d ...", ARRAYOFCONST((i,num)));
            ProgressForm->Label->Caption = text;
            Application->ProcessMessages();
        }
        delete bm;
    }

    ProgressForm->Hide();
}
