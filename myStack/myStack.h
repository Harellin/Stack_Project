#ifndef mySTACK
#define mySTACK

namespace myStack {

    template<typename T>
    class Node {
    public:
        T data;
        Node *next;
        Node(T value) : data(value), next(nullptr) {}
    };

    template<typename T>
    class Stack {
    public:
        Stack() : head(nullptr) {}

        Stack(const Stack &other);

        Stack(Stack &&other) noexcept;

        Stack &operator=(const Stack &other);

        Stack &operator=(Stack &&other) noexcept;

        ~Stack();

        void push(const T &value);

        void push(T &&value);

        void pop();

        T top() const;

    private:
        Node<T> *head;
        void clear();
    };
}

#endif