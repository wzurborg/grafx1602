#include <sysutils.hpp>

#include "AnnoBitmap.h"
#include "BmDisplay.h"

int AnnoBitmap::_palette[] =
{
0x00000000, 0x00000080, 0x00008000, 0x00008080, 0x00800000, 0x006c1f6d, 0x00808000, 0x00c0c0c0,
0x00ff00fd, 0x00ff00fe, 0x00000000, 0x00040400, 0x00080800, 0x00001000, 0x0003060b, 0x00000815,
0x00000425, 0x00041400, 0x00061606, 0x00002100, 0x00032603, 0x00051c0e, 0x00043108, 0x00001820,
0x00002c1b, 0x00120c0a, 0x00141c08, 0x00101618, 0x000c1723, 0x00152901, 0x00132c0c, 0x00112b18,
0x000f2923, 0x0025160a, 0x00252c0a, 0x001f1f24, 0x001d3122, 0x002c2412, 0x00292e26, 0x00402213,
0x00063d04, 0x00063b10, 0x00083e15, 0x00043d25, 0x00283c0e, 0x00233b21, 0x00203d29, 0x0040370e,
0x003d3d18, 0x003d3121, 0x00393d25, 0x00483a11, 0x00423d29, 0x004e3c11, 0x005e3a11, 0x00004d0d,
0x00004e25, 0x00084d12, 0x00254d17, 0x00484d1c, 0x00584d19, 0x006e4916, 0x00035f11, 0x00006225,
0x003d5d16, 0x002d7016, 0x00249615, 0x006b7c19, 0x0071941c, 0x008c5200, 0x00904a08, 0x0030c2f8,
0x00945208, 0x00945608, 0x008c4e0c, 0x00885217, 0x008c6300, 0x008c5e18, 0x009c5a08, 0x00a05a0c,
0x00946312, 0x00946512, 0x0096750a, 0x00ad5a08, 0x00a96308, 0x00a5670c, 0x00a56815, 0x00ad7906,
0x00ab7313, 0x00a57321, 0x00b5760a, 0x00b17718, 0x00ad7321, 0x00b17b21, 0x00bb7518, 0x00bd8808,
0x00c4880b, 0x00dc8811, 0x00849c21, 0x00949c00, 0x00b19c18, 0x00d69c00, 0x00ce940c, 0x005e78c4,
0x00d8ad0b, 0x00e79408, 0x00ef9408, 0x00e6a00c, 0x00e2981c, 0x00e1b215, 0x00efb110, 0x00e7bd18,
0x00debd21, 0x00f79400, 0x00e29650, 0x00ff9c00, 0x006c8ae0, 0x007a99f2, 0x000271e9, 0x00027dff,
0x00f7a508, 0x0034d8fb, 0x002daff4, 0x00f79c10, 0x00ef9418, 0x00fb9814, 0x009dfcff, 0x00f7a521,
0x00041136, 0x0004114a, 0x000c2d35, 0x000b2c46, 0x000b4a3c, 0x00006329, 0x00135a3b, 0x0000672d,
0x0000702e, 0x0008632d, 0x00116a2c, 0x00026d37, 0x00116a37, 0x00036a42, 0x00106c44, 0x00262f3b,
0x0029443e, 0x00403d3b, 0x003f4a3d, 0x002d613c, 0x00445b41, 0x004b4d3f, 0x004b633c, 0x005a4c31,
0x00554b3f, 0x005a622e, 0x00566541, 0x00685f3a, 0x00756237, 0x008c6637, 0x0005165e, 0x00142a59,
0x001a405a, 0x000b6059, 0x002d5e5a, 0x00465058, 0x00446657, 0x00504f59, 0x00506755, 0x004d6b5d,
0x0059585a, 0x005a6f56, 0x00626357, 0x00756658, 0x000a2173, 0x00144171, 0x00115f6f, 0x0039526f,
0x00416f6c, 0x005a6b6f, 0x006b686b, 0x00041d8f, 0x000d5689, 0x001f588c, 0x00406389, 0x000527ac,
0x00255da6, 0x000831c5, 0x001e54cd, 0x00027e29, 0x00007b31, 0x00007f35, 0x00007b42, 0x000b7b34,
0x00147b36, 0x00497a36, 0x00048431, 0x00008442, 0x00148431, 0x00168440, 0x00008c35, 0x00378635,
0x00328d31, 0x001da731, 0x00098253, 0x003e7e5b, 0x006b7957, 0x00677b6c, 0x0006ab52, 0x002f9155,
0x0029b659, 0x003c7e77, 0x00697777, 0x0030b474, 0x002a80aa, 0x00677d91, 0x003abb85, 0x0034acca,
0x0074852b, 0x00737f53, 0x00737c7f, 0x00738e7d, 0x007e7e4a, 0x00a48049, 0x007b8476, 0x008f8776,
0x007ca02b, 0x00849c5f, 0x0088b52d, 0x008ac13f, 0x00bda95c, 0x00a7de3f, 0x00c8ed56, 0x007b8990,
0x0085998d, 0x007f9598, 0x007c9aaf, 0x008ca598, 0x008db298, 0x008cb0a9, 0x0085c2cc, 0x00adb09a,
0x00a0b6b9, 0x00a7c8b3, 0x00cfd1ac, 0x00b5dadd, 0x00e2efe1, 0x00e6fafe, 0x00ff9400, 0x00a4a0a0,
0x00808080, 0x000000ff, 0x0000ff00, 0x0000ffff, 0x00ff0000, 0x00ff00ff, 0x00ffff00, 0x00ffffff
};

AnnoBitmap::LogPal AnnoBitmap::logPal;
bool AnnoBitmap::paletteInitialised = false;
Byte AnnoBitmap::Transparent = 253;

__fastcall AnnoBitmap::AnnoBitmap()
{
    if( !paletteInitialised )
    {
        logPal.lpal.palVersion = 0x300;
        logPal.lpal.palNumEntries = 256;
        memcpy( &logPal.lpal.palPalEntry[0], _palette, 256*4 );
        paletteInitialised = true;
    }

    Canvas->Brush->Color = TColor(_palette[Transparent]);

//    Byte c = BestColor( clGreen );
//    ShowMessage(AnsiString("Color: ") + c + "/" + _palette[c]);
}

__fastcall AnnoBitmap::~AnnoBitmap()
{
}

int __fastcall AnnoBitmap::LoadBitmap( AnsiString src, int index )
{
    TFileStream* fs;
    fs = new TFileStream( src, fmOpenRead );

    Gfxhdr hdr;
    fs->Read( &hdr, sizeof(hdr) );
    if( AnsiString(hdr.gfxid) != "BSH" )
    {
        delete fs;
        throw "Ungültige Datei";
    }

    int maxIndex = hdr.index[0] / sizeof(int) - 1;
    if( index > maxIndex )
    {
        delete fs;
        return 0;
    }

    // position on index
    int zero = 20;
    fs->Position = zero + index * sizeof(int);
    int offset = 0;
    fs->Read( &offset, sizeof(int) );
    fs->Position = zero + offset;

    // read bitmap
    int width, height, num, len;

    fs->Read( &width, sizeof(int) );
    fs->Read( &height, sizeof(int) );
    fs->Read( &num, sizeof(int) );
    fs->Read( &len, sizeof(int) );

    if(width > 0)
        this->Width = width;
    if(height > 0)
        this->Height = height;
    this->PixelFormat = pf8bit;
    this->Canvas->Brush->Color = TColor(_palette[Transparent]);
    this->Palette = CreatePalette( &logPal.lpal );

    Byte id = 0;
    int line = 0;
    int col = 0;
    Byte* bytes = 0;
    while( id != 0xFF )   // loop until end of bm
    {
        if( col == 0 )
        {
            try
            {
                bytes = (Byte*)ScanLine[line];
            }
            catch( Exception& ex )
            {
//                ShowMessage( ex.Message );
//                ShowMessage("Ungültige Bitmap");
                delete fs;
                return 0;
            }
        }

        // Read block
        fs->Read( &id, 1 );
        switch( id )
        {
        case 0xFE:  // end of line
            line++;
            col = 0;
            break;

        case 0xFF: // end of bitmap
            break;

        default:    // number of spaces
            col += id;
            Byte num;
            fs->Read( &num, 1 );  // number of pixels
            fs->Read( &bytes[col], num );  // pixels
            col += num;
            break;
        } // end switch
    }  // end loop over blocks

    delete fs;
    return 1;
}

int __fastcall AnnoBitmap::SaveBitmap( AnsiString src,
                AnsiString dst, int index )
{
    this->PixelFormat = pf8bit;
    this->Canvas->Brush->Color = TColor(_palette[Transparent]);
    this->Palette = CreatePalette( &logPal.lpal );

    TFileStream* ifs;
    ifs = new TFileStream( src, fmOpenRead );

    TFileStream* ofs;
    ofs = new TFileStream( dst, fmCreate );

    // Copy header
    ofs->CopyFrom( ifs, 20 );

    // Read and write number of bitmaps
    int firstOffs;
    ifs->Read( &firstOffs, sizeof(int) );
    int numBitmaps = firstOffs / sizeof(int);
    ifs->Position -= sizeof(int);

    // Copy up to index
    if( index > 0 )
        ofs->CopyFrom( ifs, index * sizeof(int) );

    // Read and write offset for this BM
    int offs;
    ifs->Read( &offs, sizeof(int) );
    ofs->Write( &offs, sizeof(int) );

    // Copy up to that offset
    ofs->CopyFrom( ifs, 20 + offs - ifs->Position );

    // Write out BM to this offs
    int newlen = WriteBm( ofs );

    // Skip the old BM in input stream
    int oldlen;
    ifs->Position += 3 * sizeof(int);   //w, h, 1
    ifs->Read( &oldlen, sizeof(int) );
    ifs->Position = 20 + offs + oldlen;

    // Copy the rest to output
    if( ifs->Size > ifs->Position )
        ofs->CopyFrom( ifs, ifs->Size - ifs->Position );

    // Correct total length
    int totalLen = ofs->Position - 20;
    ofs->Position = 16;
    ofs->Write( &totalLen, sizeof(int) );

    // Correct offsets that are bigger than ours
    int corr = newlen - oldlen;
    int tmpOffs;
    for( int i=0; i<numBitmaps; i++ )
    {
        ofs->Read( &tmpOffs, sizeof(int) );
        if( tmpOffs > offs )
        {
            tmpOffs += corr;
            ofs->Position -= sizeof(int);
            ofs->Write( &tmpOffs, sizeof(int) );
        }
    }

    delete ifs;
    delete ofs;

    this->Modified = false;
    return 1;
}

static float MIN( float a, float b )
{
    return a < b ? a : b;
}

void __fastcall AnnoBitmap::Assign(Classes::TPersistent* Source)
{
    AnsiString bmClass = Source->ClassName();

    if( bmClass == "TBitmap" || bmClass == "AnnoBitmap" ||
        bmClass == "TClipboard" )
    {
        Graphics::TBitmap* tmpBm = new Graphics::TBitmap();
        tmpBm->Assign( Source );
        // scale only if required
        if( (!BmForm->AdjustButton->Down) ||
            this->Width == 0 || this->Height == 0 ||
            (tmpBm->Width == this->Width &&
             tmpBm->Height == this->Height ))
        {
            Graphics::TBitmap::Assign( Source );
        }
        else
        {
            // scale rectangle
            float w1 = tmpBm->Width;
            float h1 = tmpBm->Height;
            float w2 = this->Width;
            float h2 = this->Height;
            float r = MIN( w2/w1, h2/h1 );
            float w = r * w1;
            float h = r * h1;
            TRect rect;
            rect.Top = (h2 - h)/2.0;
            rect.Left = (w2 - w)/2.0;
            rect.Right = (w2 + w)/2.0;
            rect.Bottom = (h2 + h)/2.0;
            this->Canvas->FillRect(Canvas->ClipRect);
            this->Canvas->StretchDraw( rect, tmpBm );
        }
        delete tmpBm;
    }
    else
    {
        ShowMessage(bmClass);
        throw "Invalid Object Assignment";
    }

    this->Modified = true;
}

int AnnoBitmap::WriteBm(TFileStream* fs)
{
    int savepos = fs->Position;
    int bmhdr[4] = { Width, Height, 1, 0 };

    // write width, height, 1, size
    fs->Write( &bmhdr[0], sizeof(bmhdr) );

    // Loop over scan lines
    for( int line=0; line<Height; line++ )
    {
        Byte* buffer = (Byte*) ScanLine[line];
        // Loop over multiple blocks within line
        int col = 0;
        while( col < Width )
        {
            // count number of skip pixels
            Byte numSkip = 0;
            while( numSkip < 255 && col < Width  && buffer[col] == Transparent )
            {
                numSkip++;
                col++;
            }

            if( col < Width )
            {
                // not end of line, write num skips
                fs->Write( &numSkip, 1 );

                // save position of pixel count, write dummy count
                int posCnt = fs->Position;
                Byte pixelCnt = 0;
                fs->Write( &pixelCnt, 1 );

                // count num of pixels
                while( pixelCnt < 255 && col < Width && buffer[col] != Transparent )
                {
                    fs->Write( &buffer[col], 1 );
                    pixelCnt++;
                    col++;
                }

                // correct pixelcount
                fs->Position = posCnt;
                fs->Write( &pixelCnt, 1 );
                fs->Position += pixelCnt;
            }

            if( col == Width )
            {
                // end of line
                numSkip = 0xFE;
                fs->Write( &numSkip, 1 );
                break; // loop over blocks
            }

        }   // loop ( col < Width )

    }   // loop ( line < Height )

    Byte eof = 0xFF;
    fs->Position -= 1;  // overwrite last FE
    fs->Write( &eof, 1 );

    // fill up to word boundary
    while( fs->Position % 4 )
        fs->Write( &eof, 1 );

    // correct size
    bmhdr[3] = fs->Position - savepos;
    fs->Position = savepos;
    fs->Write( &bmhdr[0], sizeof(bmhdr) );
    fs->Position = savepos + bmhdr[3];
    return bmhdr[3];
}

