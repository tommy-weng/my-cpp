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
public:
    void printGraduateCertificate(std::shared_ptr<GraduateCertificate> gc)
    {
        gc->printGraduateCertificate();
    }
    void printEducationCertificate(std::shared_ptr<EducationCertificate> ec)
    {
        ec->printEducationCertificate();
    }
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
    Diploma diploma;
    diploma.printGraduateCertificate(std::make_shared<GraduateStudent>());
    diploma.printGraduateCertificate(std::make_shared<UnderGraduateStudent>());
    diploma.printEducationCertificate(std::make_shared<GraduateStudent>());
    diploma.printEducationCertificate(std::make_shared<UnderGraduateStudent>());
    diploma.printEducationCertificate(std::make_shared<HighSchoolStudent>());

    return 0;
}   

