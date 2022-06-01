/*#include <iostream>
#include <vector>
class Pare // Objecte
{
public:
    Pare() {}
    virtual double f(double d) = 0;
};
class Fill1 : public Pare // Esfera
{
public:
    Fill1() {}
    double f(double d)
    {
        return d * 2;
    }
};
class Fill2 : public Pare // Intersecció
{
public:
    Pare *pare1;
    Fill2(Pare *p) : pare1(p) {}
    double f(double d)
    {
        return pare1->f(d);
    }
};
int main()
{
    Fill1 fill1;
    std::vector<Pare *> Vec;
    Vec.push_back(new Fill2(&fill1));
    std::cout << Vec[0]->f(3);

    return 0;
}
*/