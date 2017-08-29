
#ifndef __AnnoBitmap_h__
#define __AnnoBitmap_h__

#include <vcl.h>

class AnnoBitmap : public Graphics::TBitmap
{
public:
    __fastcall AnnoBitmap();
    int __fastcall LoadBitmap( AnsiString src, int index );
    int __fastcall SaveBitmap( AnsiString src, AnsiString dst, int index );
    virtual void __fastcall Assign(Classes::TPersistent* Source);
    virtual __fastcall ~AnnoBitmap();

private:
    struct LogPal
    {
        TLogPalette lpal;
        TPaletteEntry dummy[256];
    };

    struct Gfxhdr
    {
        char gfxid[16];
        int length;
        int index[1];
    };

    static bool paletteInitialised;
    static LogPal logPal;
    static int _palette[];
    static Byte Transparent;
    int WriteBm(TFileStream* fs);
};

#endif
