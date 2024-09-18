#include <cstdio>
#include <cstdint>
#include <utility>

void rc4_init(uint8_t* s, const uint8_t* key, size_t length)
{
    uint8_t k[256];
    for (size_t i = 0; i < 256; ++i)
    {
        s[i] = static_cast<uint8_t>(i);
        k[i] = key[i % length];
    }
    for (size_t i = 0, j = 0; i < 256; ++i)
    {
        j = (j + s[i] + k[i]) % 256;
        std::swap(s[i], s[j]);
    }
}

void rc4_crypt(uint8_t* s, uint8_t* buffer, size_t length, uint8_t exkey)
{
    uint8_t i = 0, j = 0;
    for (size_t k = 0; k < length; ++k)
    {
        j = j + s[++i];
        std::swap(s[i], s[j]);
        buffer[k] ^= (s[static_cast<uint8_t>(s[i] + s[j])] ^ exkey);
    }
}

int main()
{
    uint8_t s1[256];
    uint8_t s2[256];
    rc4_init(s1, reinterpret_cast<const uint8_t*>("EzHv_Key"), 8);
    rc4_init(s2, reinterpret_cast<const uint8_t*>("Hypervisor"), 10);

    uint8_t buffer[33] = 
    {
        0x24, 0x8D, 0xFC, 0x91, 0x1E, 0x85, 0x32, 0xF9,
        0x95, 0xC1, 0x13, 0x02, 0x71, 0xCB, 0x1C, 0x87,
        0x0E, 0xED, 0xCB, 0x37, 0x39, 0x5B, 0xB6, 0xC6,
        0x42, 0x51, 0x52, 0x13, 0xC4, 0xE5, 0xE2, 0x4F,
        0x00
    };

    rc4_crypt(s2, buffer, 32, 0xEFu);
    rc4_crypt(s1, buffer, 32, 0xADu);
    printf("%s\n", buffer);

    return 0;
}

// flag{S1mple_W1nd0Ws_Hyper5is0r!}
