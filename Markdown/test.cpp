#include <iostream>

using namespace std;


class OperatorTemp
{
public:
OperatorTemp() : a(13) { }

operator float() { return (float)a;}

private:
    int a;
};

int main()
{

    OperatorTemp* _temp = new OperatorTemp();

    cout << (float)*_temp << endl;

    delete _temp;
}