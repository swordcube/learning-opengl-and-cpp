#include <string>
#include <string.h>
#include "vortex/utilities/Color.h"

namespace vortex {
    Color::Color() {}

    Color::Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color(int hexInt) {
        r = ((hexInt >> 16) & 0xff) / 255.0f;
        g = ((hexInt >> 8) & 0xff) / 255.0f;
        b = (hexInt & 0xff) / 255.0f;
        a = ((hexInt >> 24) & 0xff) / 255.0f;
    }

    Color::Color(const char* hexString) {
        if(isHTMLValid(hexString))
            html(hexString);
    }

    void Color::html(const char* htmlColor) {
        size_t length = strlen(htmlColor);

        if (length == 0)
            return;

        int offset = 0;

        if (htmlColor[0] == '#') {
            length -= 1;
            offset = 1;
        }

        // If enabled, use 1 hex digit per channel instead of 2.
        // Other sizes aren't in the HTML/CSS spec but we could add them if desired.
        bool isShortHand = length < 5;
        bool alpha = false;

        if (length == 8)
            alpha = true;
        else if (length == 6)
            alpha = false;
        else if (length == 4)
            alpha = true;
        else if (length == 3)
            alpha = false;

        r, g, b, a = 1.0;
        if (isShortHand) {
            r = (float)_parseCol4(htmlColor + offset, 0) / 15.0f;
            g = (float)_parseCol4(htmlColor + offset, 1) / 15.0f;
            b = (float)_parseCol4(htmlColor + offset, 2) / 15.0f;
            if (alpha)
                a = (float)_parseCol4(htmlColor + offset, 3) / 15.0f;
        } else {
            r = (float)_parseCol8(htmlColor + offset, 0) / 255.0f;
            g = (float)_parseCol8(htmlColor + offset, 2) / 255.0f;
            b = (float)_parseCol8(htmlColor + offset, 4) / 255.0f;
            if (alpha)
                a = (float)_parseCol8(htmlColor + offset, 6) / 255.0f;
        }
    }

    bool Color::isHTMLValid(const char* htmlColor) {
        size_t length = strlen(htmlColor);

        if (length == 0)
            return false;

        int offset = 0;

        if (htmlColor[0] == '#') {
            length -= 1;
            offset = 1;
        }

        // Check if the amount of hex digits is valid.
        if (!(length == 3 || length == 4 || length == 6 || length == 8))
            return false;

        // Check if each hex digit is valid.
        for (int i = 0; i < length; i++) {
            if (_parseCol4(htmlColor + offset, i) == -1)
                return false;
        }

        return true;
    }

    int Color::_parseCol4(const char *p_str, int p_ofs) {
        char character = p_str[p_ofs];

        if (character >= '0' && character <= '9') {
            return character - '0';
        } else if (character >= 'a' && character <= 'f') {
            return character + (10 - 'a');
        } else if (character >= 'A' && character <= 'F') {
            return character + (10 - 'A');
        }
        return -1;
    }

    int Color::_parseCol8(const char *p_str, int p_ofs) {
        return _parseCol4(p_str, p_ofs) * 16 + _parseCol4(p_str, p_ofs + 1);
    }
}