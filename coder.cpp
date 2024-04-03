#include <iostream>
#include <bitset>

class HammingEncoder {
private:
    std::bitset<8> EncodePart(const std::bitset<4>& part) {
        std::bitset<8> encoded;

        bool d1 = part[0];
        bool d2 = part[1];
        bool d3 = part[2];
        bool d4 = part[3];

        bool p1 = (d1 + d3 + d4 + 1) % 2;
        bool p2 = (d1 + d2 + d4 + 1) % 2;
        bool p3 = (d1 + d2 + d3 + 1) % 2;
        bool p4 = (1 + p1 + d1 + p2 + d2 + p3 + d3 + d4) % 2;

        encoded[0] = p1;
        encoded[1] = d1;
        encoded[2] = p2;
        encoded[3] = d2;
        encoded[4] = p3;
        encoded[5] = d3;
        encoded[6] = p4;
        encoded[7] = d4;

        return encoded;
    }

public:
    std::bitset<16> Encode(char sym) {
        std::bitset<8> bits(sym);
        std::bitset<16> encoded;

        std::bitset<4> first(bits.to_string().substr(0, 4));
        std::bitset<4> second(bits.to_string().substr(4, 4));

        std::bitset<8> encodedFirstPart = EncodePart(first);
        std::bitset<8> encodedSecondPart = EncodePart(second);

        encoded |= (encodedFirstPart.to_ulong() << 8);
        encoded |= encodedSecondPart.to_ulong();

        return encoded;
    }

};

int main() {
    char sym;
    std::cin >> sym;

    HammingEncoder encoder;
    std::bitset<8> tmp(sym);
    std::bitset<16> encodedSym = encoder.Encode(sym);

    std::cout << "Original: " << sym << " = " << tmp << '\n';
    std::cout << "Encoded: " << encodedSym << '\n';

    return 0;
}
