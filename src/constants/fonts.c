#include "../include/fonts.h"

const GFXfont *HEADLINE_FONT = (GFXfont *)&OpenSans26B;
const GFXfont *TITLE_FONT = (GFXfont *)&OpenSans14B;
const GFXfont *TEXT_FONT_BOLD = (GFXfont *)&OpenSans12B;
const GFXfont *TEXT_FONT = (GFXfont *)&OpenSans12;

GFXfont* getFont(int size, bool bold) {
    switch (size) {
        case 8:
            return bold ? (GFXfont *)&OpenSans8B : (GFXfont *)&OpenSans8;
        case 9:
            return bold ? (GFXfont *)&OpenSans9B : (GFXfont *)&OpenSans9;
        case 10:
            return bold ? (GFXfont *)&OpenSans10B : (GFXfont *)&OpenSans10;
        case 11:
            return bold ? (GFXfont *)&OpenSans11B : (GFXfont *)&OpenSans11;
        case 12:
            return bold ? (GFXfont *)&OpenSans12B : (GFXfont *)&OpenSans12;
        case 13:
            return bold ? (GFXfont *)&OpenSans13B : (GFXfont *)&OpenSans13;
        case 14:
            return bold ? (GFXfont *)&OpenSans14B : (GFXfont *)&OpenSans14;
        case 15:
            return bold ? (GFXfont *)&OpenSans16B : (GFXfont *)&OpenSans15;
        case 16:
            return bold ? (GFXfont *)&OpenSans16B : (GFXfont *)&OpenSans16;
        case 18:
            return bold ? (GFXfont *)&OpenSans18B : (GFXfont *)&OpenSans18;
        case 20:
            return bold ? (GFXfont *)&OpenSans20B : (GFXfont *)&OpenSans20;
        case 24:
            return bold ? (GFXfont *)&OpenSans24B : (GFXfont *)&OpenSans24;
        case 26:
            return bold ? (GFXfont *)&OpenSans26B : (GFXfont *)&OpenSans26;
        default:
            return (GFXfont *)&OpenSans12;
    }
}