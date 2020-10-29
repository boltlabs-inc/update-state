inline ExtInteger::ExtInteger(int len, const string& str, int party) {
    bool* b = new bool[len];
    bool_data(b, len, str);
    bits.resize(len);
    if (party == PUBLIC) {
        block one = CircuitExecution::circ_exec->public_label(true);
        block zero = CircuitExecution::circ_exec->public_label(false);
        for(int i = 0; i < len; ++i)
            bits[i] = b[i] ? one : zero;
    }
    else {
        ProtocolExecution::prot_exec->feed((block *)bits.data(), party, b, len);
    }

    delete[] b;
}