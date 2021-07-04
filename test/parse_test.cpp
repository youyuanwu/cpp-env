#include <cstdlib>
#include "gtest/gtest.h"
#include "env.hpp"

struct Env
{
    std::string EnvCPPName;
    std::string EnvCPPAddress;
    int EnvCPPAge;
//    float EnvCPPEnergy;
};

// This needs to be in global namespace
REFL_TYPE(Env, bases<>)
    REFL_FIELD(EnvCPPName, env::serializable())
    REFL_FIELD(EnvCPPAddress, env::serializable())
    REFL_FIELD(EnvCPPAge, env::serializable())
//    REFL_FIELD(EnvCPPEnergy, env::serializable())
REFL_END

namespace mytest{

bool setEnv(std::string const & key , std::string const & val){
    int ret = setenv(key.c_str(),val.c_str(), true/*overwrite*/);
    return ret == 0;
}

TEST(ParseTest, Ok) {
    bool ret;

    std::string EnvCPPName = "EnvCPPNameVal";
    ret = setEnv("EnvCPPName",EnvCPPName);
    EXPECT_EQ(ret, true);

    std::string EnvCPPAddress = "EnvCPPAddressVal";
    ret = setEnv("EnvCPPAddress",EnvCPPAddress);
    EXPECT_EQ(ret, true);

    int EnvCPPAge = 10;
    ret = setEnv("EnvCPPAge","10");
    EXPECT_EQ(ret, true);

    float EnvCPPEnergy = 10.1;
    ret = setEnv("EnvCPPAge","10.1");
    EXPECT_EQ(ret, true);

    // parse
    Env e;

    env::Parse(e);

    EXPECT_EQ(e.EnvCPPName,EnvCPPName);
    EXPECT_EQ(e.EnvCPPAddress,EnvCPPAddress);
    EXPECT_EQ(e.EnvCPPAge,EnvCPPAge);
   

    // float is not working yet
    // EXPECT_EQ(e.EnvCPPEnergy,EnvCPPEnergy);
}

}