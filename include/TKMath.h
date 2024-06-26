#pragma once

namespace TiKiRa
{
    class Vector4 {
    public:
        union {
            struct {
                float x, y, z, w;
            };
            struct {
                unsigned char r, g, b, a;
            };
        };

        Vector4() : x(0), y(0), z(0), w(0) {}
        Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        Vector4(char r, char g, char b, char a) : r(r), g(g), b(b), a(a) {}
    };
} // namespace TiKiRa
