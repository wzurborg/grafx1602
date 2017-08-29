//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BmDisplay.h"
#include "Main.h"
#include "clipbrd.hpp"
#include "AnnoBitmap.h"
#include "ChildWin.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBmForm *BmForm;
//---------------------------------------------------------------------------
__fastcall TBmForm::TBmForm(TComponent* Owner)
    : TForm(Owner), ListView(0)
{
    Image->IncrementalDisplay = false;
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::EditPaste1Update(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = this->Visible && Clipboard()->HasFormat(CF_BITMAP);
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::EditPaste1Execute(TObject *Sender)
{
    if( !CloseQuery() )
        return;

    AnnoBitmap* abm = dynamic_cast<AnnoBitmap*>(Image->Picture->Bitmap);
    abm->Assign( Clipboard() );
    SetCaption();
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::EditCopy1Execute(TObject *Sender)
{
    Clipboard()->Assign( Image->Picture );
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::EditCopy1Update(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = ( this->Visible ) && (Image->Picture != 0);
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::FileSaveAsExecute(TObject *Sender)
{
    if( !SaveDialog->Execute() )
        return;

    Image->Picture->Bitmap->SaveToFile( SaveDialog->FileName );
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::FileSaveAsUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (Image->Picture != 0);
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::FileLoadExecute(TObject *Sender)
{
    if( !CloseQuery() || !OpenPictureDialog->Execute() )
        return;

    AnnoBitmap* abm = dynamic_cast<AnnoBitmap*>(Image->Picture->Bitmap);
    abm->LoadFromFile( OpenPictureDialog->FileName );
    SetCaption();
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::FileLoadUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (Image->Picture != 0);
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::FileSaveExecute(TObject *Sender)
{
/*
    AnsiString msg = "Really overwrite image ";
    msg += IntToStr( FileIndex + 1 );
    msg += " with this image? (No Undo!)";
*/
    AnsiString msg = "Diese Grafik wirklich überschreiben?";
    int rsp = MessageDlg(
        msg, mtConfirmation,
        TMsgDlgButtons() << mbYes << mbCancel,
        0 );

    if( rsp != mrYes )
        return;

    AnnoBitmap* abm = dynamic_cast<AnnoBitmap*>(Image->Picture->Bitmap);
    AnsiString tmpFile = ChangeFileExt(FileName, ".tmp");
    if( abm->SaveBitmap( FileName, tmpFile, FileIndex ))
    {
        // Rename .tmp to .bsh
        DeleteFile( FileName );
        RenameFile( tmpFile, FileName );
    }

    ListView->UpdateIcon( FileIndex, Image->Picture->Bitmap );
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::FileSaveUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = Image->Picture->Bitmap->Modified;
}
//---------------------------------------------------------------------------

bool TBmForm::LoadFromBsh(AnsiString filename, int index, TMDIChild* listView)
{
    ListView = listView;

    if( filename == FileName && index == FileIndex )
        return false;

    if( !CloseQuery() )
        return false;

    AnnoBitmap* bm = new AnnoBitmap();
    if( bm->LoadBitmap( filename, index ) == 0 )
    {
        delete bm;
        return false;
    }
    Image->Picture->Bitmap = bm;
    Visible = true;

    FileName = filename;
    FileIndex = index;
    SetCaption();
    Image->Picture->Bitmap->Modified = false;
    return true;
}

//---------------------------------------------------------------------------

void TBmForm::SetCaption(void)
{
    Caption = String("Bild ") + (FileIndex+1) + " ("
        + Image->Picture->Width + "x" + Image->Picture->Height + ")";
    SetBounds( Left, Top, 1, Height );  // force resizing

    AnsiString BaseName = MainForm->OpenFileDialog->InitialDir;
    StatusBar->Panels->BeginUpdate();
    StatusBar->Panels->Items[0]->Text =
        ExtractRelativePath( BaseName, FileName );
    StatusBar->Panels->Items[1]->Text =
        String("Bild ") + (FileIndex+1);
    StatusBar->Panels->Items[2]->Text =
        IntToStr(Image->Picture->Width) + "x" + Image->Picture->Height;
    StatusBar->Panels->EndUpdate();
}

//---------------------------------------------------------------------------

bool __fastcall TBmForm::CanAutoSize(int & NewWidth, int & NewHeight)
{
    int pw = Image->Picture->Width;
    int ph = Image->Picture->Height;
    float r1 = (float)pw / (float)ph;

    NewWidth = ((float)NewHeight - 27.0) * r1 + 8.0;

    return true;
}

//---------------------------------------------------------------------------


void __fastcall TBmForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !Image->Picture->Bitmap->Modified )
    {
        CanClose = true;
        return;
    }

    int rsp = MessageDlg(
        "Soll die Grafik gespeichert werden?",
        mtConfirmation,
        TMsgDlgButtons() << mbYes << mbNo << mbCancel,
        0 );

     switch( rsp )
     {
     case mrYes:
        FileSaveExecute( Sender );
        // intentional fall through
     case mrNo:
        // avoid another query...
        Image->Picture->Bitmap->Modified = false;
        CanClose = true;
        break;
     case mrCancel:
        CanClose = false;
        break;
     }
}
//---------------------------------------------------------------------------


void TBmForm::FormChange( void )
{
    if( !Image->Picture->Bitmap->Modified )
    {
        return;
    }

    int rsp = MessageDlg(
        "Soll die Grafik gespeichert werden?",
        mtConfirmation,
        TMsgDlgButtons() << mbYes << mbNo,
        0 );

     switch( rsp )
     {
     case mrYes:
        FileSaveExecute( this );
        // intentional fall through
     case mrNo:
        // avoid another query...
        Image->Picture->Bitmap->Modified = false;
     }
}
void __fastcall TBmForm::EditUndo1Update(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = Image->Picture->Bitmap->Modified;
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::EditUndo1Execute(TObject *Sender)
{
    AnnoBitmap* bm = new AnnoBitmap();
    bm->LoadBitmap( FileName, FileIndex );
    Image->Picture->Bitmap = bm;
    Image->Picture->Bitmap->Modified = false;
    SetCaption();
}
//---------------------------------------------------------------------------

void __fastcall TBmForm::AdjustSizeUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = ( this->Visible ) && (Image->Picture != 0);
}
//---------------------------------------------------------------------------


