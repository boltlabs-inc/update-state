#include "tokens/ag2pc/translation.h"
#include "emp-tool/utils/utils.h"
#include <iostream>

using namespace std;
using namespace emp;

void test_translate_constants() {
    bool *in = new bool[5222];
    int pos = translate_constants(in, 0);
    assert(pos == 5222);
    string res = "";
    for(int i = 0; i < 5222; ++i)
        res += (in[i]?"1":"0");
    assert("01101100011011000110110001101100000000000000000000000000000000010000000000010000000000000000000000111010001110100011101000111010000000001100000000000000000000000000000101000000000000000000000011111111111111111111111111111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000001100000000000000000000000000110011111010001010001010000101000100100100010111011001000111011110011110111110000001110101101101001011101101110101101100101111101101001000011011010101001110010001111100010001000111110011010001001010100000111111100010010011010101101111010001110001101010100011001010101011110000000011011100000001101101011000001010010000111110110100001100011000010010011000011101111100011000010101010001011101011101001111101010011100111111110001101011110110000000111100101011000000011101111011001001011101000111111011001100000111000001110010110110110010010011101100001111000100111110111110111011000111011100110000011111100000011001110000101001100000010010011110110001101001001011110110100010101010010000100101110010100100011101110010101000011010011101001011011000100011001111101101110010010101000101001111100000110011011011001100011100011000001010100010011111001001100000000001101111000111111111010011010111111011100111111010000000001110110001111100010100010011110010110101011100010101100011001010011011000001110011010010100100101000010100010100001010100001110110111100100000111001000010011011000011101000011111110110110001101001011001011001000101100000001110011001010001010101100111001010000101001101101110101010000010101100110111001110100100100110100001110000001101000010011010001001110010010011000010100010111111111010100010111010010011001100101100000010101000011101101000111010010010000111100010110001010001101101110001110011000000101110100100110001011001001000110000010011001011010111010000110101100011100000010111100001110000001010101011000001000011010001000001100100101100110000001000000110110111011000111100000110010111011100001001011100100101011010011110100001101001011001100110100110000001110001001110001010010010101010001101101110010111100100101001100111001110110101100111111110110011101000001011001110111010000011111000100101110111101101100011010100101000111100010100000011110000100110010000100010000010000001110001100110001010111111111111101111101000010011101011100110110000010100010010111101111110001011001111101111101010011110001111010001110011000111110011001100111100100000101011010100001011101011110011011011101010011101100111101110110001111000101110010101111111100101010010111111110010010100111000010001010001100010001011010100000110110011101010110011011110000011111100010011000101100110000011111011010000000000000010000010101110001100001000100000000000000000000000000000000000000000000000010000100000000001110011000000000000000000100000000000000000000000000000000000000000000001010000011110011101011100100110100000000000000000000000111000000000000000000000000110101000101100000000000000000000000000000010000000000010001000110100000000000000000000000000000000000000000000010100000000000010101101100001000000000000000000000000000000000000000001000001000000000000000010000000000000000000011010010000000000000000000000000000000000000000000000100000010010100000011001000110111011100101010101111100011011110011100111110001011100111101011110111100111111001110000100011010100111111001101110100010110101010001010001110110110010000111110100011111001111010100111100000100101000100001000100000101001100110000011100000000010000100010010101110001001110101010010100000000000000000111111111111111111111111111111110000000000000000000000001000000000000100111000000000000000000000100001000100101011000110010011100000000000000000100001000000000001001010000000000000000000000000111100110100000011100110011101011000010010101110010011011010000000000000000101100011010100000000111111110000000000000000000000000000000011111111111111111111111110000000000000000000000000000000000000010000000000000000000000000001111000010000000000000000000000000000000000001111111100000000000000001111111100000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110101110101010111011011100111001101010111101001000101000000011101110111111110100100101111010001100110100000011011001000001010000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110101110101010111011011100111001101010111101001000101000000011101110111111110100100101111010001100110100000011011001000001010000010" == res);
}

void test_translate_uint32() {
    //0x0c8dda80 0x1001c9a5 0x5f720c5f 0x379ce09e 0x42416780 0xf98fef79 0x00bd26b3 0x72b81850
    uint32_t x[8];
    x[0] = 0x0c8dda80;
    x[1] = 0x1001c9a5;
    x[2] = 0x5f720c5f;
    x[3] = 0x379ce09e;
    x[4] = 0x42416780;
    x[5] = 0xf98fef79;
    x[6] = 0x00bd26b3;
    x[7] = 0x72b81850;
    bool *in = new bool[256];
    int pos = translate_general(x, 8, in, 0);
    assert(pos == 256);
    string res = "";
    for(int i = 160; i < 192; ++i)
        res += (in[i]?"1":"0");
    cout << res << endl;
//    cout << hex_to_binary("0c8dda801001c9a55f720c5f379ce09e42416780f98fef7900bd26b372b81850") << endl;
//    assert(hex_to_binary("0c8dda80") == res);
}

void test_bin_to_uint() {
 //10011110111101111111000110011111
    char one = '1';

    bool *out = new bool[32];
    string tmp = "10011110111101111111000110011111";
    for(int i = 0; i < tmp.length(); ++i)
        out[i] = (tmp[i] == one);
    uint32_t x = bool_to_int<uint32_t>(out, 32);
    cout << x << endl;
}

int main(int argc, char** argv) {
    test_translate_constants();
    test_translate_uint32();
    test_bin_to_uint();
}

//0000000101011011101100010011000010100101100100111000000000001000111110100011000001001110111110100111100100000111001110011110110000000001111001101000001001000010100111101111011111110001100111111100110101100100101111010000000000001010000110000001110101001110
//0000000101011011101100010011000010100101100100111000000000001000111110100011000001001110111110100111100100000111001110011110110000000001111001101000001001000010100111101111011111110001100111111100110101100100101111010000000000001010000110000001110101001110
//0000000101011011101100010011000010100101100100111000000000001000111110100011000001001110111110100111100100000111001110011110110000000001111001101000001001000010100111101111011111110001100111111100110101100100101111010000000000001010000110000001110101001110