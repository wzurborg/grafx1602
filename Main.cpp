//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "BmDisplay.h"
#include "clipbrd.hpp"
#include "registry.hpp"
#include "filectrl.hpp"
//---------------------------------------------------------------------------
//#pragma link "OpenDialog"
#pragma link "adpInstanceControl"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent *Owner)
	: TForm(Owner),initialised(false)
{
    ToolDir = GetCurrentDir();
    OpenFileDialog->InitialDir = GetInstallPath();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateMDIChild(String Name)
{
	TMDIChild *Child;

	//--- create a new MDI child window ----
	Child = new TMDIChild(Application);
	Child->Caption = Name;
    if( FileExists( Name ) )
    {
        Child->OpenFile( Name, 0, 0 );
    }

    if(MDIChildCount > 1)
    {
        Child->WindowState = wsNormal;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileOpen1Execute(TObject *Sender)
{
	if (OpenFileDialog->Execute())
    {
        BmForm->Visible = false;
        for(int i=0; i<OpenFileDialog->Files->Count; i++)
        {
    		CreateMDIChild(OpenFileDialog->Files->Strings[i]);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileExit1Execute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::EditPaste1Execute(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = Clipboard()->HasFormat(CF_BITMAP);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileClose1Execute(TObject *Sender)
{
    TMDIChild* child = (TMDIChild*)ActiveMDIChild;
    if( child != 0 )
    {
        child->Close();
    }
}
//---------------------------------------------------------------------------


AnsiString TMainForm::GetInstallPath(void)
{
    // Get Savegame directory from registry
    TRegistry* Registry = new TRegistry;
    Registry->RootKey = HKEY_LOCAL_MACHINE;
    AnsiString installDir;
    try
    {
        Registry->OpenKeyReadOnly( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\1602.EXE" );
        installDir = Registry->ReadString( "Path" );
        AnsiString Key( "\\SOFTWARE\\Sir Henry\\Sir Henry's 1602 Grafx Tool" );
        Registry->OpenKeyReadOnly( Key );
        ToolDir = Registry->ReadString( "InstallDir" );
    }
    __finally
    {
        delete Registry;
    }

    if( !DirectoryExists( installDir ) )
        installDir = "";

    return installDir;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpContents1Execute(TObject *Sender)
{
//    ShellExecute(Handle, "open", LoadStr(107).c_str(), NULL, ToolDir.c_str(), SW_SHOW);
    ShellExecute(Handle, "open", "grafx1602-de.chm", NULL, ToolDir.c_str(), SW_SHOW);  
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
    if(!initialised)
    {
        initialised = true;
        if(ParamCount() > 0)
        {
            // open specified file
            CreateMDIChild(ParamStr(1));
        }
    }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::FileSaveBitmapsExecute(TObject *Sender)
{
    TMDIChild* child = (TMDIChild*)ActiveMDIChild;
    if( child != 0 )
    {
        child->ExportAll();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSaveBitmapsUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (ActiveMDIChild != 0);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::instanceControlMaxInstancesReached(
      TObject *Sender, const DWORD LastInstanceHandle)
{
    // Send new filename to existing application
    if(ParamCount() > 0)
    {
        String filename = ParamStr(1);
        COPYDATASTRUCT data;
        data.dwData = 0;
        data.cbData = filename.Length();
        data.lpData = filename.c_str();

        // Find window handle for first instance
        HWND handle = GetWindow((HWND)LastInstanceHandle, GW_HWNDFIRST);
        char buffer[MAX_PATH];
        while(handle != 0)
        {
            GetWindowText(handle, buffer, MAX_PATH-1);
            if(String(buffer).Pos(this->Caption) > 0 &&
                handle != this->Handle)
                    break;
            handle = GetWindow(handle, GW_HWNDNEXT);
        }

        // Send filename across
        if(handle != 0)
        {
            SendMessage(handle, WM_COPYDATA, (WPARAM)this->Handle, (LPARAM)&data);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WMReceiveData(TMessage &Message)
{
    COPYDATASTRUCT* data = (COPYDATASTRUCT*)Message.LParam;
    String filename((char*)data->lpData, (int)data->cbData);
    CreateMDIChild(filename);
}

//---------------------------------------------------------------------------

