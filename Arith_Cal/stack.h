#ifndef STACK_H
#define STACK_H



template <class T>
class stack
{

    private:
        int len;
        T *store;

    public:
        stack();
        bool empty();
        void push(T ele);
        void pop();
        T top();
        ~stack();
};

#endif // STACK_H
