//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "ChildWin.h"
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Messages.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include "adpInstanceControl.hpp"
//#include "TntComCtrls.hpp"

//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TMenuItem *Window1;
	TMenuItem *Help1;
	TMenuItem *WindowCascadeItem;
	TMenuItem *WindowTileItem;
	TMenuItem *WindowArrangeItem;
	TMenuItem *HelpAboutItem;
	TMenuItem *WindowMinimizeItem;
        TStatusBar *StatusBar;
        TActionList *ActionList1;
        TAction *FileExit1;
        TAction *FileOpen1;
        TWindowCascade *WindowCascade1;
        TWindowTileHorizontal *WindowTileHorizontal1;
        TWindowArrange *WindowArrangeAll1;
        TWindowMinimizeAll *WindowMinimizeAll1;
        TAction *HelpAbout1;
        TWindowClose *FileClose1;
        TWindowTileVertical *WindowTileVertical1;
        TMenuItem *WindowTileItem2;
        TToolBar *ToolBar2;
        TToolButton *ToolButton1;
        TToolButton *ToolButton3;
        TToolButton *ToolButton8;
        TToolButton *ToolButton10;
        TToolButton *ToolButton11;
        TImageList *ImageList1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *N1;
    TMenuItem *Exit1;
    TMenuItem *Close1;
    THelpContents *HelpContents1;
    TMenuItem *Contents1;
    TMenuItem *N2;
    TAction *FileSaveBitmaps;
    TMenuItem *SaveBitmapsSaveallbitmaps1;
    TOpenDialog *OpenFileDialog;
    TadpInstanceControl *instanceControl;
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
    void __fastcall EditPaste1Execute(TObject *Sender);
    void __fastcall FileClose1Execute(TObject *Sender);
    void __fastcall HelpContents1Execute(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FileSaveBitmapsExecute(TObject *Sender);
    void __fastcall FileSaveBitmapsUpdate(TObject *Sender);
    void __fastcall instanceControlMaxInstancesReached(TObject *Sender,
          const DWORD LastInstanceHandle);
private:
	void __fastcall CreateMDIChild(const String Name);
    AnsiString GetInstallPath(void);
    AnsiString ToolDir;
    bool initialised;
    void __fastcall WMReceiveData(TMessage &Message);

public:
	virtual __fastcall TMainForm(TComponent *Owner);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_COPYDATA, TMessage, WMReceiveData)
    END_MESSAGE_MAP(TForm);

};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif    
