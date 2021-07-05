#include <cstdlib>
#include "gtest/gtest.h"
#include "env.hpp"

// Declare struct as usual
struct ExampleEnv
{
    std::string EnvCPPString1;
    std::string EnvCPPString2;
    int EnvCPPInt;
    long EnvCPPLong;
    float EnvCPPFloat;
};

// Add struct meta data
// This needs to be in global namespace, and is a limitation of refl-cpp pkg.
REFL_TYPE(ExampleEnv)
    REFL_FIELD(EnvCPPString1, env::Name("EnvString1Override"))
    REFL_FIELD(EnvCPPString2, env::Default("EnvString2DefaultValue"))
    REFL_FIELD(EnvCPPInt, env::Required())
    REFL_FIELD(EnvCPPLong)
    REFL_FIELD(EnvCPPFloat)
REFL_END

TEST(ExampleParse, Ok) {
    bool ret;

    std::string EnvCPPString1 = "Override Value";
    ret = env::SetEnvVar("EnvString1Override",EnvCPPString1);
    EXPECT_EQ(ret, true);

    // string2 is not present in env
    ret = env::UnsetEnvVar("EnvCPPString2");
    EXPECT_EQ(ret, true);

    int EnvCPPInt = 10;
    ret = env::SetEnvVar("EnvCPPInt","10");
    EXPECT_EQ(ret, true);

    long EnvCPPLong = 20;
    ret = env::SetEnvVar("EnvCPPLong","20");
    EXPECT_EQ(ret, true);

    float EnvCPPFloat = 10.1;
    ret = env::SetEnvVar("EnvCPPFloat","10.1");
    EXPECT_EQ(ret, true);

    // Parse reads the Env struct meta-data and retrieves env values from OS
    ExampleEnv e;
    env::Parse(e);

    // Check Env e fields values are populated
    EXPECT_EQ(e.EnvCPPString1,EnvCPPString1);
    EXPECT_EQ(e.EnvCPPString2,std::string("EnvString2DefaultValue"));
    EXPECT_EQ(e.EnvCPPInt,EnvCPPInt);
    EXPECT_EQ(e.EnvCPPLong,EnvCPPLong);
    EXPECT_EQ(e.EnvCPPFloat,EnvCPPFloat);
}
