//----------------------------------------------------------------------------
#ifndef ChildWinH
#define ChildWinH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ImgList.hpp>
//----------------------------------------------------------------------------
#include <map>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//#include "TntComCtrls.hpp"
//----------------------------------------------------------------------------
class TMDIChild : public TForm
{
__published:
    TImageList *ImageList;
    TStatusBar *StatusBar1;
    TListView *ListView;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ListViewClick(TObject *Sender);
    void __fastcall ListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall ListViewDataHint(TObject *Sender, int StartIndex,
          int EndIndex);
    void __fastcall ListViewData(TObject *Sender, TListItem *Item);
    void __fastcall ListViewDataFind(TObject *Sender, TItemFind Find,
          const AnsiString FindString, const TPoint &FindPosition,
          Pointer FindData, int StartIndex, TSearchDirection Direction,
          bool Wrap, int &Index);
    void __fastcall ListViewDeletion(TObject *Sender, TListItem *Item);
    void __fastcall ListViewDataStateChange(TObject *Sender,
          int StartIndex, int EndIndex, TItemStates OldState,
          TItemStates NewState);
private:
    AnsiString FileName;
    Graphics::TBitmap* __fastcall makeIcon(Graphics::TBitmap* bm);
    void LoadImage(int listIndex);
    typedef std::map<int,int> ImageMap;
    ImageMap imageMap;
    typedef std::map<int,String> TextMap;
    TextMap textMap;
        
public:
	virtual __fastcall TMDIChild(TComponent *Owner);
    void OpenFile(AnsiString filename, int FromIndex, int ToIndex);
    void UpdateIcon(int index, Graphics::TBitmap* bm);
    void __fastcall ExportAll();
};
//----------------------------------------------------------------------------
#endif
