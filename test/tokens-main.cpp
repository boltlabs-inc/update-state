#include <emp-tool/emp-tool.h>
#include "emp-ag2pc/emp-ag2pc.h"
#include "tokens/ag2pc/sha256.h"
#include "tokens/utils/utils.h"
#include "tokens/utils/io/gonet_io_channel.h"
#include "tokens/utils/io/lndnet_io_channel.h"
#include "tokens/utils/io/net_callback.h"
using namespace std;
using namespace emp;

int translate_initSHA256(bool *in, int pos) {
    for(int i=0; i<64; i++) {
      int32_to_bool(&in[pos], k_clear[i], 32);
      pos = pos + 32;
    }
    for(int i=0; i<8; i++) {
      int32_to_bool(&in[pos], IV_clear[i], 32);
      pos = pos + 32;
    }
    return pos;
}

inline const char* hex_char_to_bin(char c) {
    switch(toupper(c)) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: return "0";
    }
}

inline string hex_to_binary(string hex) {
    string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
        bin += hex_char_to_bin(hex[i]);
    return bin;
}

const string circuit_file_location = macro_xstr(EMP_CIRCUIT_PATH);
void test(int party, NetIO* io, string name, string check_output = "") {
    // read in the circuit from the location where it was generated
	string file = circuit_file_location + name;
        cout << file << endl;
	BristolFormat cf(file.c_str());
    //
    // initialize some timing stuff?
	auto t1 = clock_start();
	C2PC<NetIO> twopc(io, party, &cf);
	io->flush();
	cout << "one time:\t"<<party<<"\t" <<time_from(t1)<<endl;

    // preprocessing?
	t1 = clock_start();
	twopc.function_independent();
	io->flush();
	cout << "inde:\t"<<party<<"\t"<<time_from(t1)<<endl;

    // more preprocessing?
	t1 = clock_start();
	twopc.function_dependent();
	io->flush();
	cout << "dep:\t"<<party<<"\t"<<time_from(t1)<<endl;

    // create and fill in input vectors (to all zeros with memset)
    int in_length = party==BOB?cf.n2:cf.n1;
	bool *in = new bool[in_length];
    memset(in, false, in_length);
    cout << "input size: max " << cf.n1 << "\t" << cf.n2 <<endl;
	bool * out = new bool[cf.n3];
//	int pos = 0;
	if (party == ALICE) {
        memset(in, true, in_length);
	}
	memset(out, false, cf.n3);

	string res = "";
	for(int i = 0; i < in_length; ++i)
        res += (in[i]?"1":"0");
    cout << "in: " << res << endl;

    // online protocol execution
	t1 = clock_start();
	twopc.online(in, out);
	cout << "online:\t"<<party<<"\t"<<time_from(t1)<<endl;

    // compare result to our hardcoded expected result
	if(party == BOB and check_output.size() > 0){
		string res = "";
		for(int i = 0; i < cf.n3; ++i)
			res += (out[i]?"1":"0");
		cout << "result: " << res << endl;
		cout << (res == hex_to_binary(check_output)? "GOOD!":"BAD!")<<endl;
	}
	delete[] in;
	delete[] out;
}

int main(int argc, char** argv) {
    // set up parties
	cout << "start1" <<endl;
	int party, port;
	parse_party_and_port(argv, &party, &port);
    NetIO* io = new NetIO(party==ALICE ? nullptr:IP, port);
	cout << "start3" <<endl;
	io->set_nodelay();
	cout << "start4" <<endl;
	test(party, io, "test.circuit.txt", string("00000000"));
	delete io;
	return 0;
}