#ifndef OOP_SINGLETON_H
#define OOP_SINGLETON_H

template <typename Derived>
class Singleton {
protected:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static Derived& getInstance() {
        static DerivedInstance instance;
        return instance;
    }
private:
    class DerivedInstance : public Derived{
    public:
        DerivedInstance() : Derived() {}
    };
};

#endif //OOP_SINGLETON_H
