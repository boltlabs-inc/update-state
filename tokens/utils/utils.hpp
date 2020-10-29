inline uint32_t bool_to32(const bool * data) {
    uint64_t res = 0;
    for(int i = 0; i < 32; ++i) {
        if(data[i])
            res |= (1ULL<<i);
    }
    return res;
}

inline string bin_to_dec(const string& bin2) {
    if(bin2[0] == '0')
        return change_base(bin2, 2, 10);
    string bin = bin2;
    bool flip = false;
    for(int i = bin.size()-1; i>=0; --i) {
        if(flip)
            bin[i] = (bin[i] == '1' ? '0': '1');
        if(bin[i] == '1')
            flip = true;
    }
    return "-"+change_base(bin, 2, 10);
}

inline string dec_to_bin(const string& dec) {
    string bin = change_base(dec, 10, 2);
    if(dec[0] != '-')
        return '0' + bin;
    bin[0] = '1';
    bool flip = false;
    for(int i = bin.size()-1; i>=1; --i) {
        if(flip)
            bin[i] = (bin[i] == '1' ? '0': '1');
        if(bin[i] == '1')
            flip = true;
    }
    return bin;
}

inline string change_base(string str, int old_base, int new_base) {
    mpz_t tmp;
    mpz_init_set_str (tmp, str.c_str(), old_base);
    char * b = new char[mpz_sizeinbase(tmp, new_base) + 2];
    mpz_get_str(b, new_base, tmp);
    mpz_clear(tmp);
    string res(b);
    delete[]b;
    return res;
}

inline void int32_to_bool(bool * data, uint32_t input, int length) {
    for (int i = 0; i < length; ++i) {
        data[i] = (input & 1)==1;
        input >>= 1;
    }
}

inline Integer inv(Integer in) {
    Integer res(in);
    for(int i = 0; i < in.size(); ++i)
        res.bits[i] = !res.bits[i];
    return res;
}