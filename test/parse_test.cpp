#include <cstdlib>
#include "gtest/gtest.h"
#include "env.hpp"

struct Env
{
    std::string EnvCPPName;
    std::string EnvCPPAddress;
    int EnvCPPAge;
    long EnvCPPHeight;
    float EnvCPPEnergy;
};

// This needs to be in global namespace
REFL_TYPE(Env, bases<>)
    REFL_FIELD(EnvCPPName, env::serializable())
    REFL_FIELD(EnvCPPAddress, env::serializable())
    REFL_FIELD(EnvCPPAge, env::serializable())
    REFL_FIELD(EnvCPPHeight, env::serializable())
    REFL_FIELD(EnvCPPEnergy, env::serializable())
REFL_END

namespace mytest{

TEST(Parse, Ok) {
    bool ret;

    std::string EnvCPPName = "EnvCPPNameVal";
    ret = env::SetEnvVar("EnvCPPName",EnvCPPName);
    EXPECT_EQ(ret, true);

    std::string EnvCPPAddress = "EnvCPPAddressVal";
    ret = env::SetEnvVar("EnvCPPAddress",EnvCPPAddress);
    EXPECT_EQ(ret, true);

    int EnvCPPAge = 10;
    ret = env::SetEnvVar("EnvCPPAge","10");
    EXPECT_EQ(ret, true);

    long EnvCPPHeight = 20;
    ret = env::SetEnvVar("EnvCPPHeight","20");
    EXPECT_EQ(ret, true);

    float EnvCPPEnergy = 10.1;
    ret = env::SetEnvVar("EnvCPPEnergy","10.1");
    EXPECT_EQ(ret, true);

    // parse
    Env e;
    env::Parse(e);

    EXPECT_EQ(e.EnvCPPName,EnvCPPName);
    EXPECT_EQ(e.EnvCPPAddress,EnvCPPAddress);
    EXPECT_EQ(e.EnvCPPAge,EnvCPPAge);
    EXPECT_EQ(e.EnvCPPHeight,EnvCPPHeight);
    EXPECT_EQ(e.EnvCPPEnergy,EnvCPPEnergy);
}

TEST(Parse, Exceptions) {
    int ret;
    ret = env::SetEnvVar("EnvCPPAge","bad-integer");
    EXPECT_EQ(ret, true);

    Env e;
    EXPECT_THROW(env::Parse(e), env::ParseException);
}

}