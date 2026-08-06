#include "ArgParserStl.h"
#include "gtest/gtest.h"

using namespace std;
using namespace keo_tool;

class ArgParserTestStl : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

// Tests parser without arguments.
TEST_F(ArgParserTestStl, NoArgs)
{
    vector<string> args;
    args.push_back("programName");
    ArgParserStl parser;

    string output;
    EXPECT_TRUE(parser.parse(args, output));
}

// Tests parser without a mandatory argument.
TEST_F(ArgParserTestStl, MandatoryArgMissing)
{
    vector<string> args;
    args.push_back("programName");
    ArgParserStl parser;

    parser.addArgument("-v", "--verbose", "Be verbose", ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_TRUE(output.find("missing") != string::npos);
}

// Tests parser without a mandatory argument, but with an overriding flag.
TEST_F(ArgParserTestStl, MandatoryArgMissingWithOverrideFlag)
{
    vector<string> args;
    args.push_back("programName");
    ArgParserStl parser;

    parser.addArgument("-V", "--verbose", "Be verbose", ArgParserStl::MANDATORY);
    parser.addArgument("-v", "--version", "Print version", ArgParserStl::FLAG_OVERRIDING_MANDATORY);

    args.push_back("-v");

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_FALSE(output.find("missing") != string::npos);
}

// Tests parser without an optional argument.
TEST_F(ArgParserTestStl, OptionalArgMissing)
{
    vector<string> args;
    args.push_back("programName");
    ArgParserStl parser;

    parser.addArgument("-V", "--verbose", "Be verbose", ArgParserStl::OPTIONAL);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_FALSE(output.find("missing") != string::npos);
}

// Adding an argument twice.
TEST_F(ArgParserTestStl, AddingArgumentTwice)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("--integer-value=789");
    ArgParserStl parser;

    EXPECT_TRUE(parser.addArgument("-v", "--integer-value", "Will be accepted", ArgParserStl::MANDATORY));

    EXPECT_FALSE(parser.addArgument("-v", "--willbeignored", "Will be ignored", ArgParserStl::FLAG));

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(789 == atoi(parser.getValue("--integer-value").c_str()));
}

// Case sensivity of shortname
TEST_F(ArgParserTestStl, ShortNameCase)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-v=11");
    args.push_back("-V=12");
    ArgParserStl parser;

    parser.addArgument("-v", "--dontcare", "dont care", ArgParserStl::MANDATORY);

    parser.addArgument("-V", "--dontcare_again", "dont care", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(11 == atoi(parser.getValue("-v").c_str()));
    EXPECT_TRUE(12 == atoi(parser.getValue("-V").c_str()));
}

TEST_F(ArgParserTestStl, Args)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-v");

    ArgParserStl parser;
    parser.setHelpProlog("Test the command line argument parser.");
    parser.setHelpEpilog("This program does a lot of useful things.");

    parser.addArgument("-V", "--verbose", "Be verbose", ArgParserStl::FLAG);

    parser.addArgument("-b", "--enable-blubber", "Enable blubber", ArgParserStl::FLAG);

    parser.addArgument(
        "-n", "--enable-notset                             and a very long string", "Not be set", ArgParserStl::FLAG);

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::OPTIONAL);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    // EXPECT_TRUE(parser.getValue("-v").toBool());
}

TEST_F(ArgParserTestStl, ValueInt)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-l");
    args.push_back("123");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(123 == atoi(parser.getValue("-l").c_str()));
}

TEST_F(ArgParserTestStl, ValueIntWithAssignment)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-l=123");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(123 == atoi(parser.getValue("-l").c_str()));
}

TEST_F(ArgParserTestStl, ValueIntLongName)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("--bla-bla");
    args.push_back("123");

    ArgParserStl parser;

    parser.addArgument("-l", "--bla-bla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(123 == atoi(parser.getValue("-l").c_str()));
}

TEST_F(ArgParserTestStl, ValueIntWithAssignmentLongName)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("--bla-bla=123");

    ArgParserStl parser;

    parser.addArgument("-l", "--bla-bla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(123 == atoi(parser.getValue("-l").c_str()));
}

TEST_F(ArgParserTestStl, ValueNegativeIntWithAssignment)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-l=-123");

    ArgParserStl parser;

    parser.addArgument("-l", "--bla-bla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(-123 == atoi(parser.getValue("-l").c_str()));
}

TEST_F(ArgParserTestStl, ValueNegativeIntWithoutAssignment)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-l");
    args.push_back("-123");

    ArgParserStl parser;

    parser.addArgument("-l", "--bla-bla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
}

TEST_F(ArgParserTestStl, ValueNegativeIntWithAssignmentLongName)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("--bla-bla=-123");

    ArgParserStl parser;

    parser.addArgument("-l", "--bla-bla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(-123 == atoi(parser.getValue("-l").c_str()));
}

TEST_F(ArgParserTestStl, ValueNegativeIntWithoutAssignmentLongName)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("--bla-bla");
    args.push_back("-123");

    ArgParserStl parser;

    parser.addArgument("-l", "--bla-bla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
}

TEST_F(ArgParserTestStl, ValueNotGiven)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-l");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
}

TEST_F(ArgParserTestStl, ValueNotGivenWithTrailingAssignmentOperator)
{
    vector<string> args;
    args.push_back("programName");
    args.push_back("-l=");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
}

TEST_F(ArgParserTestStl, ValueWithDoubleQuotes)
{
    vector<string> args;
    string value = "value with blanks";
    args.push_back("programName");
    args.push_back("-l=\"" + value + "\"");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(value == parser.getValue("-l"));
}

TEST_F(ArgParserTestStl, ValueWithSingleQuotes)
{
    vector<string> args;
    string value = "value with blanks";
    args.push_back("programName");
    args.push_back("-l=\'" + value + "\'");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", "bla bla help", ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_EQ(value, parser.getValue("-l"));
    EXPECT_TRUE(value == parser.getValue("-l"));
}

TEST_F(ArgParserTestStl, GetHelpText)
{
    vector<string> args;
    string help = "bla bla help";
    args.push_back("programName");
    args.push_back("-l=lall");

    ArgParserStl parser;

    parser.addArgument("-l", "--blabla", help, ArgParserStl::MANDATORY);

    string output;
    EXPECT_TRUE(parser.getHelpText().empty());
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(parser.getHelpText().find(help) != string::npos);
}

TEST_F(ArgParserTestStl, GetHelpShortForm)
{
    string help = "bla bla help";
    string progname("programName");
    string shortName = "-l";
    string longName = "--blabla";
    vector<string> args;

    args.push_back(progname);
    args.push_back("-h");

    ArgParserStl parser;

    parser.addArgument(shortName, longName, help, ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_TRUE(output.find(progname) != string::npos);
    EXPECT_TRUE(output.find("Usage:") != string::npos);
    EXPECT_TRUE(output.find(shortName) != string::npos);
    EXPECT_TRUE(output.find(longName) != string::npos);
}

TEST_F(ArgParserTestStl, GetHelpLongForm)
{
    string help = "bla bla help";
    string progname("programName");
    string shortName = "-l";
    string longName = "--blabla";
    vector<string> args;

    args.push_back(progname);
    args.push_back("-h");

    ArgParserStl parser;

    parser.addArgument(shortName, longName, help, ArgParserStl::MANDATORY);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_TRUE(output.find(progname) != string::npos);
    EXPECT_TRUE(output.find("Usage:") != string::npos);
    EXPECT_TRUE(output.find(shortName) != string::npos);
    EXPECT_TRUE(output.find(longName) != string::npos);
}

// Tests parser without a long name.
TEST_F(ArgParserTestStl, onlyShortName)
{
    string shortName = "-s";
    string value = "value";
    vector<string> args;
    args.push_back("programName");
    args.push_back(shortName);
    args.push_back(value);

    ArgParserStl parser;

    parser.addArgument(shortName, "", "Only short name", ArgParserStl::OPTIONAL);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
    EXPECT_TRUE(value == parser.getValue(shortName));
}

// Tests parser without a long name and the short name is pretty long.
TEST_F(ArgParserTestStl, onlyShortNameWithMoreThanTwoLetters)
{
    string shortName = "-shortnameisprettylong";
    string value = "value";
    vector<string> args;
    args.push_back("programName");
    args.push_back(shortName);
    args.push_back(value);

    ArgParserStl parser;

    parser.addArgument(shortName, "", "Only short name", ArgParserStl::OPTIONAL);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
    EXPECT_TRUE(value == parser.getValue(shortName));
}

// Tests parser without a short name.
TEST_F(ArgParserTestStl, onlyLongName)
{
    string longName = "--long-name";
    string value = "value";
    vector<string> args;
    args.push_back("programName");
    args.push_back(longName);
    args.push_back(value);

    ArgParserStl parser;

    parser.addArgument("", longName, "Only long name", ArgParserStl::OPTIONAL);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
    EXPECT_TRUE(value == parser.getValue(longName));
}

// Tests parser with and relation that is not defined
TEST_F(ArgParserTestStl, andRelation_notDefined)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, relation1);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Error") != string::npos);
    EXPECT_TRUE(output.find(shortName1) != string::npos);
    EXPECT_TRUE(output.find(longName1) != string::npos);
    EXPECT_TRUE(output.find("does not exist") != string::npos);
    EXPECT_TRUE(output.find(shortName2) != string::npos);
}

// Tests parser with xor relation that is not defined
TEST_F(ArgParserTestStl, xorRelation_notDefined)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, vector<string>(), relation1);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Error") != string::npos);
    EXPECT_TRUE(output.find(shortName1) != string::npos);
    EXPECT_TRUE(output.find(longName1) != string::npos);
    EXPECT_TRUE(output.find("does not exist") != string::npos);
    EXPECT_TRUE(output.find(shortName2) != string::npos);
}

// Tests parser with and relation that is defined
TEST_F(ArgParserTestStl, andRelation_DefinedNoneGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");
    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, relation2);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
}

// Tests parser with and relation that is defined
TEST_F(ArgParserTestStl, andRelation_DefinedButNotGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");
    args.push_back(shortName2);
    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, relation2);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Error") != string::npos);
    EXPECT_TRUE(output.find(shortName1) != string::npos);
    EXPECT_TRUE(output.find(longName1) != string::npos);
    EXPECT_TRUE(output.find("must be used together with") != string::npos);
    EXPECT_TRUE(output.find(shortName2) != string::npos);
}

// Tests parser with xor relation that is defined
TEST_F(ArgParserTestStl, xorRelation_DefinedBothGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");
    args.push_back(longName1);
    args.push_back(longName2);

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, vector<string>(), relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, vector<string>(), relation2);

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Error") != string::npos);
    EXPECT_TRUE(output.find(shortName1) != string::npos);
    EXPECT_TRUE(output.find(longName1) != string::npos);
    EXPECT_TRUE(output.find("must not be used") != string::npos);
    EXPECT_TRUE(output.find(shortName2) != string::npos);
}

// Tests parser with and relation that is defined
TEST_F(ArgParserTestStl, andRelation_DefinedAndGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");
    args.push_back(shortName1);
    args.push_back(shortName2);

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, relation2);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
}

// Tests parser with xor relation that is defined and only one given
TEST_F(ArgParserTestStl, andRelation_DefinedAndOneGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);

    vector<string> relation2;
    relation2.push_back(shortName1);

    args.push_back("programName");
    args.push_back(shortName2);

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, vector<string>(), relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, vector<string>(), relation2);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
}

// Tests parser with and relation between 3 parameters and two given
TEST_F(ArgParserTestStl, andRelationBetween3_TwoGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    string shortName3 = "-z";
    string longName3 = "--z-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);
    relation1.push_back(shortName3);

    args.push_back("programName");
    args.push_back(shortName1);
    args.push_back(shortName2);

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, vector<string>(), vector<string>());

    parser.addArgument(shortName3, longName3, "help text", ArgParserStl::FLAG, vector<string>(), vector<string>());

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Error") != string::npos);
    EXPECT_TRUE(output.find(shortName1) != string::npos);
    EXPECT_TRUE(output.find(longName1) != string::npos);
    EXPECT_TRUE(output.find("must be used together with") != string::npos);
    EXPECT_TRUE(output.find(shortName3) != string::npos);
}

// Tests parser with xor relation between 3 parameters and two given
TEST_F(ArgParserTestStl, xorRelationBetween3_TwoGiven)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    string shortName2 = "-y";
    string longName2 = "--y-long-name";
    string shortName3 = "-z";
    string longName3 = "--z-long-name";
    vector<string> args;

    vector<string> relation1;
    relation1.push_back(shortName2);
    relation1.push_back(shortName3);

    args.push_back("programName");
    args.push_back(shortName1);
    args.push_back(shortName3);

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG, vector<string>(), relation1);

    parser.addArgument(shortName2, longName2, "help text", ArgParserStl::FLAG, vector<string>(), vector<string>());

    parser.addArgument(shortName3, longName3, "help text", ArgParserStl::FLAG, vector<string>(), vector<string>());

    string output;
    EXPECT_FALSE(parser.parse(args, output));
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Error") != string::npos);
    EXPECT_TRUE(output.find(shortName1) != string::npos);
    EXPECT_TRUE(output.find(longName1) != string::npos);
    EXPECT_TRUE(output.find("must not be used") != string::npos);
    EXPECT_TRUE(output.find(shortName3) != string::npos);
}

// Tests isDefined() returns true if defined
TEST_F(ArgParserTestStl, isDefined_ReturnTrue)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    vector<string> args;

    args.push_back("programName");
    args.push_back(shortName1);

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
    EXPECT_TRUE(parser.isDefined(shortName1));
}

// Tests isDefined() returns false if not defined
TEST_F(ArgParserTestStl, isDefined_ReturnFalse)
{
    string shortName1 = "-x";
    string longName1 = "--x-long-name";
    vector<string> args;

    args.push_back("programName");

    ArgParserStl parser;

    parser.addArgument(shortName1, longName1, "help text", ArgParserStl::FLAG);

    string output;
    EXPECT_TRUE(parser.parse(args, output));
    EXPECT_TRUE(output.empty());
    EXPECT_FALSE(parser.isDefined(shortName1));
}
