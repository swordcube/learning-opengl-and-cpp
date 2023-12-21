namespace vortex {
    class Color {
        public:
            float r = 0.0;
            float g = 0.0;
            float b = 0.0;
            float a = 0.0;

            Color();
            Color(float r, float g, float b, float a);
            Color(int hexInt);
            Color(const char* hexString);

            void html(const char* htmlColor);
            static bool isHTMLValid(const char* htmlColor);

        private:
            static int _parseCol4(const char *p_str, int p_ofs);
            static int _parseCol8(const char *p_str, int p_ofs);
    };
}