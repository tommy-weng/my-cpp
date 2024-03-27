// g++ TestTranscript.cpp main.cpp -lgtest -lgmock -lpthread -I..

#define Transcript_orig
//#define arithmetics_orig

#include <gtest/gtest.h>
#include "Transcript.cpp"
//#include "Arithmetics.cpp"
#include <memory>
namespace testing
{

class TestTranscript : public Test
{
public:
    void SetUp() override
    {
        mockArithmeticsConstructor = std::make_unique<MockArithmeticsConstructor>();
        mockArithmetics = std::make_shared<MockArithmetics>();
        EXPECT_CALL(*mockArithmeticsConstructor, construct()).WillRepeatedly(Return(mockArithmetics));
        transcript = std::make_shared<Transcript>();
    }

    void TearDown() override
    {
        mockArithmeticsConstructor.reset();
    }
protected:

    std::shared_ptr<Transcript> transcript{nullptr};
    std::shared_ptr<MockArithmetics> mockArithmetics{nullptr};
};

TEST_F(TestTranscript, testCompute)
{
    EXPECT_CALL(*mockArithmetics, plus(Gt(1),Gt(1))).Times(AnyNumber()).WillRepeatedly(Return(98));
    EXPECT_CALL(*mockArithmetics, minus(Lt(100),Le(100))).Times(AnyNumber()).WillRepeatedly(Return(98));
    EXPECT_EQ(98, transcript->compute(98, 99, 100));
}

// For conventional practise

TEST_F(TestTranscript, testSucceedAndFail)
{
    SUCCEED();
    GTEST_SKIP();
    FAIL();
}

using Transcript_DeathTest = TestTranscript;

testing::AssertionResult IsEven(int n) {
  if ((n % 2) == 0)
    return testing::AssertionSuccess();
  else
    return testing::AssertionFailure() << n << " is odd";
}


void NormalExit()
{
    std::cerr << "Bad thing happend again.";
    std::exit(22);
}

TEST_F(Transcript_DeathTest, testDeathOrExit)
{
    EXPECT_DEATH({std::cerr << "error"; int* p = nullptr; *p = 1;}, "error");
    EXPECT_EXIT(NormalExit(), testing::ExitedWithCode(1), "Bad thing happend again.");
    // EXPECT_EXIT(KillProcess(), testing::KilledBySignal(SIGKILL),
}


} // namespace ::testing
