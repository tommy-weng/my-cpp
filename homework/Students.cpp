#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class GraduateCertificate
{
public:
    virtual void printGraduateCertificate() = 0;
};

class EducationCertificate
{
public:
    virtual void printEducationCertificate() = 0;
};

class Diploma
{

};

class GraduateStudent : public GraduateCertificate, public EducationCertificate
{
public:
    void printGraduateCertificate()
    {
        cout << "GraduateCertificate for GraduateStudent" << endl;
    }
    void printEducationCertificate()
    {
        cout << "EducationCertificate for GraduateStudent" << endl;
    }
};

class UnderGraduateStudent : public GraduateCertificate, public EducationCertificate
{
public:
    void printGraduateCertificate()
    {
        cout << "GraduateCertificate for UnderGraduateStudent" << endl;
    }
    void printEducationCertificate()
    {
        cout << "EducationCertificate for UnderGraduateStudent" << endl;
    }
};

class HighSchoolStudent : public EducationCertificate
{
public:
    void printEducationCertificate()
    {
        cout << "EducationCertificate for HighSchoolStudent" << endl;
    }
};

int main()
{
    std::shared_ptr<GraduateCertificate> gc1 = std::make_shared<GraduateStudent>();
    gc1->printGraduateCertificate();
    std::shared_ptr<GraduateCertificate> gc2 = std::make_shared<UnderGraduateStudent>();
    gc2->printGraduateCertificate();

    std::shared_ptr<EducationCertificate> ec1 = std::make_shared<GraduateStudent>();
    ec1->printEducationCertificate();
    std::shared_ptr<EducationCertificate> ec2 = std::make_shared<UnderGraduateStudent>();
    ec2->printEducationCertificate();
    std::shared_ptr<EducationCertificate> ec3 = std::make_shared<HighSchoolStudent>();
    ec3->printEducationCertificate();
    return 0;
}   

