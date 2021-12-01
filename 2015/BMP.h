#ifndef BMP_H
#define BMP_H

#include <ostream>

class BMP {
    uint16_t typeSignature; // = "BM"
    uint32_t filesize;     //filesize in Bytes
    uint32_t reserved;     // = 0 for this program
    uint32_t headerOffset; // = 54

    uint32_t infoHeaderSize;    //size of header in byte. ( = 40)
    uint32_t Width;             //width of file in pixels
    uint32_t Height;            // height of file in pixels

    uint16_t Colors;       //colorbits per pixel (24 for 3byte RGB)
    uint16_t bitsPerPixel;
    uint32_t Compression ;       //compression mode; 0 for uncompressed.
    uint32_t SizeImg;         //if biCompress = 0, =0. Else: filesize.

    uint32_t xPelsPerMeter;     // for output device;
    uint32_t yPelsPerMeter;     // 0 for this program

    uint32_t ColorsUsed;      // Colours used; = 0 for all
    uint32_t ColorsImportant; // num. of used colours, 0 for all

public:
    BMP(unsigned w, unsigned h) :
            typeSignature('M' << 8 | 'B'), filesize(54 + (w * 3 + (4 - (w * 3) % 4) % 4)* h), reserved(0), headerOffset(54),
            infoHeaderSize(40), Width(w), Height(h), Colors(1), bitsPerPixel(24), Compression(0), SizeImg(0),
            xPelsPerMeter(0), yPelsPerMeter(0), ColorsUsed(0), ColorsImportant(0) {}

    void writeHeader(std::ostream &out) {
        out.write(reinterpret_cast<const char *>(this), sizeof(*this));
        static_assert(sizeof(*this) == 54, "sizeof mismatch");
    }

    void writeImgBuf(std::ostream &out, void *buf) {
        const char *img = static_cast<char *>(buf);
        const char padding[] = {0x00, 0x00, 0x00};

        for (int i = 0; i < Height; i++) {
            out.write(img + (i * Width * 3),  Width * 3);
            out.write(padding,  (4 - (Width * 3) % 4) % 4);
        }

    }

    size_t sizeofImgBuf() {
        return 3 * Width * Height;
    }

    void setPixel(void *buf, unsigned x, unsigned y, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) {
        uint8_t *img = static_cast<uint8_t *>(buf);

        img[(x + y * Width) * 3 + 0] = r;
        img[(x + y * Width) * 3 + 1] = g;
        img[(x + y * Width) * 3 + 2] = b;

    }
} __attribute__((packed));


#endif //BMP_H
