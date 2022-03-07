class B;
class A {
public:
    A(int val);
    ~A();
    void print();
    int val;
private:
    B* b;
};