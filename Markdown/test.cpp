#include <iostream>

using namespace std;

#define _STRING_CAT(a,b) a ## b
#define STRING_CAT(a,b) _STRING_CAT(a,b)

template<typename T>
struct ScopeExit
{
    ScopeExit(T _t) : t(_t) {}
    ~ScopeExit() { t(); }

    T t;
};

template<typename T>
ScopeExit<T> MakeScopeExit(T t)
{
    return ScopeExit<T>(t);
}

#define SCOPE_EXIT(expression) \
    auto STRING_CAT(scope_exit, __LINE__) = MakeScopeExit( [=]() { expression } );

int g_value = 0;

int Test(int vlaue)
{
    if( SCOPE_EXIT(g_value += 1) )
    {
        cout << "test" << endl;
    }

    // SCOPE_EXIT(cout << "scope exit" << endl; );
}

int main()
{
    Test(1);
}