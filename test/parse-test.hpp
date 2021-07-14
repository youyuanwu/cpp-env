#include <cstdlib>
#include "gtest/gtest.h"
#include "env.hpp"

struct Env
{
    std::string EnvCPPString1;
    std::string EnvCPPString2;
    int EnvCPPInt;
    long EnvCPPLong;
    float EnvCPPFloat;
};

// This needs to be in global namespace
REFL_TYPE(Env, bases<>)
    REFL_FIELD(EnvCPPString1)
    REFL_FIELD(EnvCPPString2)
    REFL_FIELD(EnvCPPInt)
    REFL_FIELD(EnvCPPLong)
    REFL_FIELD(EnvCPPFloat)
REFL_END


struct Env2
{
    std::string EnvString;
};

REFL_TYPE(Env2)
    REFL_FIELD(EnvString, env::Name("EnvStringOverride"), env::Default("EnvStringDefaultValue"))
REFL_END

struct Env3
{
    std::string EnvString;
};

REFL_TYPE(Env3)
    REFL_FIELD(EnvString, env::Required())
REFL_END

namespace envtest{

TEST(Parse, Ok) {
    bool ret;

    std::string EnvCPPString1 = "EnvCPPString1";
    ret = env::SetEnvVar("EnvCPPString1",EnvCPPString1);
    EXPECT_EQ(ret, true);

    std::string EnvCPPString2 = "EnvCPPString2";
    ret = env::SetEnvVar("EnvCPPString2",EnvCPPString2);
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

    // parse
    Env e;
    env::Parse(e);

    EXPECT_EQ(e.EnvCPPString1,EnvCPPString1);
    EXPECT_EQ(e.EnvCPPString2,EnvCPPString2);
    EXPECT_EQ(e.EnvCPPInt,EnvCPPInt);
    EXPECT_EQ(e.EnvCPPLong,EnvCPPLong);
    EXPECT_EQ(e.EnvCPPFloat,EnvCPPFloat);
}

TEST(Parse, Exceptions) {
    int ret;
    ret = env::SetEnvVar("EnvCPPInt","bad-integer");
    EXPECT_EQ(ret, true);

    Env e;
    EXPECT_THROW(env::Parse(e), env::ParseException);
}

TEST(Parse, NameAttr) {
    int ret;
    std::string EnvStringOverride = "EnvStringOverrideValue";
    ret = env::SetEnvVar("EnvStringOverride", EnvStringOverride);
    EXPECT_EQ(ret, true);

    Env2 e;
    env::Parse(e);

    EXPECT_EQ(e.EnvString, EnvStringOverride);
}

TEST(Parse, DefaultAttr) {
    int ret;
    ret = env::UnsetEnvVar("EnvStringOverride");
    EXPECT_EQ(ret, true);

    Env2 e;
    env::Parse(e);

    EXPECT_EQ(e.EnvString, std::string("EnvStringDefaultValue"));
}

TEST(Parse, RequiredAttr) {
    int ret;
    ret = env::UnsetEnvVar("EnvString");
    EXPECT_EQ(ret, true);
    
    Env3 e;
    EXPECT_THROW(env::Parse(e), env::EnvNotFoundException);

    ret = env::SetEnvVar("EnvString", "dummy");
    EXPECT_EQ(ret, true);
    env::Parse(e);
}

} // namespace envtest

// Test custom type
struct MyStruct{
    int data;
};

struct MyStruct2{
    MyStruct st;
};

REFL_TYPE(MyStruct2)
    // data will not present in OS, but default value should be parsed.
    // The env_convert should be invoked.
    REFL_FIELD(st, env::Name("ComplexNameNoOneCares"), env::Default("dummy") )
REFL_END

inline void env_convert(std::string const & x, MyStruct &d){
    d.data = 100;
}

namespace envtest{

// custom type that can overload
TEST(FunctionOverload, Ok){
    MyStruct2 x;
    env::Parse(x);
    EXPECT_EQ(100, x.st.data);
}

} // namespace envtest
