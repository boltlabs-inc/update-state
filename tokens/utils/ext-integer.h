#ifndef EMP_EXT_INTEGER_H__
#define EMP_EXT_INTEGER_H__

#include "emp-tool/circuits/integer.h"
#include "utils.h"
namespace emp {
    class ExtInteger : public Integer {
    public:
        ExtInteger(int length, const string& str, int party = PUBLIC);

        static void bool_data(bool* data, size_t len, string str) {
            string bin = dec_to_bin(str);
            std::reverse(bin.begin(), bin.end());
            int l = (bin.size() > (size_t)len ? len : bin.size());
            for(int i = 0; i < l; ++i)
                data[i] = (bin[i] == '1');
            for (size_t i = l; i < len; ++i)
                data[i] = data[l-1];
        }
    };

#include "ext-integer.hpp"
}
#endif //EMP_EXT_INTEGER_H__