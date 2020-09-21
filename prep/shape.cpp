#include <iostream>
#include <string>

class Shape {
  private:
    std::string d_name;

  public:
    // CREATORS
    Shape(const std::string& name);

    // ACCESSORS
    const std::string& name() const;
    virtual void draw() const = 0;
};

class Line : public Shape {
  public:
    // CREATORS
    Line(const std::string& name);

    // ACCESSORS
    virtual void draw() const override;
};

class Circle : public Shape {
  public:
    // CREATORS
    Circle(const std::string& name);

    // ACCESSORS
    virtual void draw() const override;
};

Shape::Shape(const std::string& name)
: d_name(name)
{
}

const std::string& Shape::name() const
{
    return d_name;
}

Line::Line(const std::string& name)
: Shape(name)
{
}

void Line::draw() const
{
    std::cout << "A line named \"" << name() << "\" has been drawn!"
        << std::endl;
}

Circle::Circle(const std::string& name)
: Shape(name)
{
}

void Circle::draw() const
{
    std::cout << "A circle called \"" << name() << "\" has been drawn!"
        << std::endl;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Line myLine("my line");
    Line yourLine("your line");
    myLine.draw();
    yourLine.draw();
    Circle theCircle("the circle");
    theCircle.draw();
    Shape *shapePtr = &myLine;
    shapePtr->draw();
    shapePtr = &yourLine;
    shapePtr->draw();
    shapePtr = &theCircle;
    shapePtr->draw();
    return 0;
}
