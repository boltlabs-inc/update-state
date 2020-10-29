#ifndef EMP_UPDATE_STATE_UTILS_H__
#define EMP_UPDATE_STATE_UTILS_H__
#include <string>

#include <gmp.h>
#include "emp-tool/circuits/integer.h"

using std::string;

namespace emp {

uint32_t bool_to32(const bool * data);
inline string change_base(string str, int old_base, int new_base);
inline string dec_to_bin(const string& dec);
inline string bin_to_dec(const string& bin2);
void int32_to_bool(bool * data, uint32_t input, int length);

inline Integer inv(Integer in);

#include "utils.hpp"
}
#endif// EMP_UPDATE_STATE_UTILS_H__