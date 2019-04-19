#ifndef DSA_CHAR1_FIBONACCI_
#define DSA_CHAR1_FIBONACCI_
class Fib{
private:
    int f,g;

public:
    Fib(int n){f=1;g=0;while(g<n)next();}
    int get() { return g;}
    int next(){ g += f;f = g - f; return g;}
    int prev(){ f = g - f;g -= f; return g;}
};

#endif // DSA_CHAR1_FIBONACCI_