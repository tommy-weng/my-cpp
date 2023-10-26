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
    EXPECT_CALL(*mockArithmetics, minus(Lt(100),Lt(100))).Times(AnyNumber()).WillRepeatedly(Return(98));
    EXPECT_GT(110, transcript->compute());
}

} // namespace ::testing
