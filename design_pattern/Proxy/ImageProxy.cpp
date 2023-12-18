#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

class Graphic
{
public:
    virtual void draw() = 0;
};

class Image: public Graphic
{
public:
    Image(const std::string& name): imageName{name}{}
    void draw() override
    {
        cout << "Draw image" << endl;
    }
private:
    std::string imageName{nullptr};
};

class ImageProxy: public Graphic
{
public:
    ImageProxy(const std::string& name): imageName{name}{}

    void draw() override
    {
        getImage()->draw();
    }

private:
    std::shared_ptr<Image> getImage()
    {
        return nullptr == image ? std::make_shared<Image>(imageName) : image;
    }
    std::shared_ptr<Image> image{nullptr};
    std::string imageName{};
};
int main()
{
    std::shared_ptr<Graphic> graphic = std::make_shared<ImageProxy>("proxy.png");
    graphic->draw();

    return 0;
}