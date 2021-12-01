#include <openssl/md5.h>
#include <string>
#include <iomanip>
#include <iostream>

static std::string md5(const std::string &pass) {
    unsigned char tmp_hash[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)pass.c_str(), pass.size(), tmp_hash);

    std::ostringstream sout;
    sout<<std::hex<<std::setfill('0');
    for(auto c: tmp_hash) sout<<std::setw(2)<<(int)c;

    return sout.str();
}

static unsigned mineAdventCoin(const std::string &pass_base) {
    unsigned pass_nr = 0;
    std::string pass;

    do {
        pass_nr++;
        pass = pass_base + std::to_string(pass_nr);

        pass = md5(pass);

    } while(pass.compare(0, 5, "00000") != 0);

 //   std::cout << "CoinHash: " << pass << std::endl;
    return pass_nr;
}

static unsigned mineAdventCoinNative(const std::string &pass_base) {
    unsigned pass_nr = 0;
    std::string pass;
    unsigned char thash[MD5_DIGEST_LENGTH];

    do {
        pass_nr++;
        pass = pass_base + std::to_string(pass_nr);
        MD5((unsigned char *) pass.c_str(), pass.size(), thash);
    } while (!(thash[0] == 0 && thash[1] == 0 && (thash[2] & 0xF0) == 0));

    return pass_nr;
}

static unsigned mineAdventCoinNative6(const std::string &pass_base) {
    unsigned pass_nr = 0;
    std::string pass;
    unsigned char thash[MD5_DIGEST_LENGTH];

    do {
        pass_nr++;
        pass = pass_base + std::to_string(pass_nr);
        MD5((unsigned char *) pass.c_str(), pass.size(), thash);
    } while (!(thash[0] == 0 && thash[1] == 0 && thash[2] == 0));

    return pass_nr;
}


int main(int argc, char *argv[]) {
    //std::cout << "md5('abcdef609043')=" << md5("abcdef609043") << std::endl;
    //std::cout << "md5('pqrstuv1048970')=" << md5("pqrstuv1048970") << std::endl;

    std::cout << "P1: AdventCoin: " << mineAdventCoin("yzbqklnj") << std::endl;
    std::cout << "P1: AdventCoinNative: " << mineAdventCoinNative("yzbqklnj") << std::endl;
    std::cout << "P2: AdventCoinNative6: " << mineAdventCoinNative6("yzbqklnj") << std::endl;
    return 0;
}