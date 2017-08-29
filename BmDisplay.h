//---------------------------------------------------------------------------

#ifndef BmDisplayH
#define BmDisplayH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <StdActns.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "ChildWin.h"
//---------------------------------------------------------------------------
class TBmForm : public TForm
{
__published:	// IDE-managed Components
    TImage *Image;
    TPopupMenu *PopupMenu;
    TActionList *ActionList;
    TEditCopy *EditCopy1;
    TEditPaste *EditPaste1;
    TAction *FileSaveAs;
    TMenuItem *Copy1;
    TMenuItem *Paste1;
    TMenuItem *N1;
    TMenuItem *SaveAs1;
    TToolBar *ToolBar;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton4;
    TSavePictureDialog *SaveDialog;
    TAction *FileLoad;
    TToolButton *ToolButton5;
    TMenuItem *Replace1;
    TOpenPictureDialog *OpenPictureDialog;
    TAction *FileSave;
    TMenuItem *SaveImage1;
    TStatusBar *StatusBar;
    TEditUndo *EditUndo1;
    TToolButton *ToolButton6;
    TAction *AdjustSize;
    TToolButton *AdjustButton;
    TToolButton *ToolButton8;
    void __fastcall EditPaste1Update(TObject *Sender);
    void __fastcall EditPaste1Execute(TObject *Sender);
    void __fastcall EditCopy1Execute(TObject *Sender);
    void __fastcall EditCopy1Update(TObject *Sender);
    void __fastcall FileSaveAsExecute(TObject *Sender);
    void __fastcall FileSaveAsUpdate(TObject *Sender);
    void __fastcall FileLoadExecute(TObject *Sender);
    void __fastcall FileLoadUpdate(TObject *Sender);
    void __fastcall FileSaveExecute(TObject *Sender);
    void __fastcall FileSaveUpdate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall EditUndo1Update(TObject *Sender);
    void __fastcall EditUndo1Execute(TObject *Sender);
    void __fastcall AdjustSizeUpdate(TObject *Sender);
private:
    AnsiString FileName;
    int FileIndex;
    TMDIChild* ListView;
    void SetCaption(void);	// User declarations
public:		// User declarations
    __fastcall TBmForm(TComponent* Owner);
    bool LoadFromBsh(AnsiString filename, int index, TMDIChild* ListView);
    virtual bool __fastcall CanAutoSize(int & NewWidth, int & NewHeight);
    void FormChange(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TBmForm *BmForm;
//---------------------------------------------------------------------------
#endif
