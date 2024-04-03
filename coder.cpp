#include <iostream>
#include <bitset>

class HammingCoder {
public:
    static std::bitset<8> encode(std::bitset<4> &part) {
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

    static std::bitset<4> decode(std::bitset<8> encoded) {
        std::bitset<4> decoded;

        bool p1 = encoded[0];
        bool d1 = encoded[1];
        bool p2 = encoded[2];
        bool d2 = encoded[3];
        bool p3 = encoded[4];
        bool d3 = encoded[5];
        bool p4 = encoded[6];
        bool d4 = encoded[7];

        bool A = (p1 + d1 + d3 + d4) % 2;
        bool B = (d1 + p2 + d2 + d4) % 2;
        bool C = (d1 + d2 + p3 + d3) % 2;
        bool D = (p1 + d1 + p2 + d2 + p3 + d3 + p4 + d4) % 2;

        if ((A == 0 || B == 0 || C == 0) && D == 1) {
            std::cout << "Error detected, cannot be corrected." << std::endl;
            return decoded;
        }

        if ((A == 0 || B == 0 || C == 0) && D == 0) {
            if (A == 0 && B == 0 && C == 0) {
                d1 ^= 1;
            }
            if (A == 1 && B == 0 && C == 0) {
                d2 ^= 1;
            }
            if (A == 0 && B == 1 && C == 0) {
                d3 ^= 1;
            }
            if (A == 0 && B == 0 && C == 1) {
                d4 ^= 1;
            }
        }

        decoded[0] = d1;
        decoded[1] = d2;
        decoded[2] = d3;
        decoded[3] = d4;

        return decoded;
    }
};

int Encode1(char sym)
{
    std::bitset<8> bits(sym);
    std::bitset<16> encoded;

    std::bitset<4> first(bits.to_string().substr(0, 4));
    std::bitset<4> second(bits.to_string().substr(4, 4));

    std::bitset<8> encodedFirstPart = HammingCoder::encode(first);
    std::bitset<8> encodedSecondPart = HammingCoder::encode(second);

    encoded |= (encodedFirstPart.to_ulong() << 8);

    encoded |= encodedSecondPart.to_ulong();

    int value = static_cast<int>(encoded.to_ulong());

    return value;
}



int decode1(short c)
{
    int g = c >> 8;
    int t = c;
    int H = (HammingCoder::decode(std::bitset<8>(g)).to_ulong() << 4) + HammingCoder::decode(std::bitset<8>(t)).to_ulong();


    return H;
}

int main() {
    char sym;
    std::cin >> sym;

    int encodedSym = Encode1(sym);

    std::cout << "Encoded: " << std::bitset<16>(encodedSym) << std::endl;

    int decodedSym = decode1(encodedSym);

    std::cout << "Decoded: " << decodedSym << std::endl;

    return 0;
}
