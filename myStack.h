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

    template<typename T>
    Stack<T>::Stack(const Stack &other) : head(nullptr) {
        Node<T> *temp = other.head;

        while (temp != nullptr) {
            push(temp->data);
            temp = temp->next;
        }
    }

    template<typename T>
    Stack<T>::Stack(Stack &&other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    template<typename T>
    Stack<T> &Stack<T>::operator=(const Stack &other) {
        if (this != &other) {
            clear();

            Node<T> *temp = other.head;
            while (temp != nullptr) {
                push(temp->data);
                temp = temp->next;
            }
        }

        return *this;
    }

    template<typename T>
    Stack<T> &Stack<T>::operator=(Stack &&other) noexcept {
        if (this != &other) {
            clear();

            head = other.head;
            other.head = nullptr;
        }

        return *this;
    }

    template<typename T>
    Stack<T>::~Stack() {
        clear();
    }

    template<typename T>
    void Stack<T>::push(const T &value) {
        Node<T> *newNode = new Node<T>(value);

        newNode->next = head;
        head = newNode;
    }

    template<typename T>
    void Stack<T>::push(T &&value) {
        Node<T> *newNode = new Node<T>(std::move(value));

        newNode->next = head;
        head = newNode;
    }

    template<typename T>
    void Stack<T>::pop() {
        if (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    template<typename T>
    T Stack<T>::top() const {
        if (head != nullptr) {
            return head->data;
        } else {
            throw std::out_of_range("Empty stack");
        }
    }

    template<typename T>
    void Stack<T>::clear() {
        while (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

}