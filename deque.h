#include <iostream>

template <typename T>
class DequeNode
{
    public:
        T data;
        DequeNode *prev;
        DequeNode *next;

        // 默认构造函数
        DequeNode() : data(T()), prev(nullptr), next(nullptr) {}

        // 带参数的构造函数
        DequeNode(const T &value) : data(value), prev(nullptr), next(nullptr) {}

        DequeNode(std::nullptr_t) : data(T()), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DequeIterator : public DequeNode<T>
{
    public:
        DequeIterator() : DequeNode<T>() {}

        DequeIterator(DequeNode<T>* node) : DequeNode<T>()
        {
            if (node)
            {
                this->data = node->data;
                this->prev = node->prev;
                this->next = node->next;
            }
            else
            {
                this->next = nullptr;
                this->prev = nullptr;
            }
        }

        DequeIterator &operator++()
        {
            if (this->next)
            {
                this->data = this->next->data;
                this->prev = this->next->prev;
                this->next = this->next->next;
            }
            return *this;
        }

        DequeIterator operator++(int)
        {
            DequeIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        DequeIterator &operator--()
        {
            if (this->prev)
            {
                this->data = this->prev->data;
                this->next = this->prev->next;
                this->prev = this->prev->prev;
            }
            return *this;
        }

        DequeIterator operator--(int)
        {
            DequeIterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const DequeIterator &other) const
        {
            return this->data == other.data && this->prev == other.prev && this->next == other.next;
        }

        bool operator!=(const DequeIterator &other) const
        {
            return !(*this == other);
        }

        DequeIterator& operator=(const DequeIterator& other)
        {
            if (this != &other)
            {
                this->data = other.data;
                this->prev = other.prev;
                this->next = other.next;
            }
            return *this;
        }

        T &operator*()
        {
            return this->data;
        }
        
        const T &operator*() const
        {
            return this->data;
        }

        T *operator->() const
        {
            return &(this->data);
        }

        T &operator[](int index) const
        {
            DequeIterator temp = *this;
            temp += index;
            return *temp;
        }

        bool operator<(const DequeIterator &other) const
        {
            return this->data < other.data;
        }

        bool operator>(const DequeIterator &other) const
        {
            return this->data > other.data;
        }

        bool operator<=(const DequeIterator &other) const
        {
            return this->data <= other.data;
        }

        bool operator>=(const DequeIterator &other) const
        {
            return this->data >= other.data;
        }

        // 向后移动 n 个位置
        DequeIterator &operator+=(int n)
        {
            for (int i = 0; i < n; ++ i)
            {
                ++ (*this);
            }
            return *this;
        }

        // 向前移动 n 个位置
        DequeIterator &operator-=(int n)
        {
            for (int i = 0; i < n; ++ i)
            {
                -- (*this);
            }
            return *this;
        }

        // 返回向后移动 n 个位置后的迭代器
        DequeIterator operator-(int n) const
        {
            DequeIterator tmp = *this;
            tmp -= n;
            return tmp;
        }

        // 返回向前移动 n 个位置后的迭代器
        DequeIterator operator+(int n) const
        {
            DequeIterator tmp = *this;
            tmp += n;
            return tmp;
        }
};

template <typename T>
class Deque
{
    private:
        DequeNode<T> *Front;
        DequeNode<T> *rear;
        size_t Size;

    public:
        // 构造函数
        Deque() : Front(nullptr), rear(nullptr), Size(0) {}

        Deque(const Deque &other) : Front(nullptr), rear(nullptr), Size(0)
        {
            DequeIterator<T> it = other.begin();
            while (it != other.end())
            {
                push_back(*it);
                it ++ ;
            }
        }

        // 析构函数
        ~Deque()
        {
            clear();
        }

        // 运算符重载 =
        Deque &operator=(const Deque &other)
        {
            if (this != &other)
            {
                clear();
                DequeIterator<T> it = other.begin();
                while (it != other.end())
                {
                    push_back(*it);
                    ++ it;
                }
            }
            return *this;
        }

        // assign
        void assign(size_t n, const T &elem)
        {
            clear();
            for (size_t i = 0; i < n; ++i)
            {
                push_back(elem);
            }
        }

        void assign(DequeIterator<T> beg, DequeIterator<T> end)
        {
            clear();
            while (beg != end)
            {
                push_back(*beg);
                ++ beg;
            }
        }

        // empty
        bool empty() const
        {
            return Size == 0;
        }

        // size
        size_t size() const
        {
            return Size;
        }

        // resize
        void resize(size_t num)
        {
            while (Size < num)
            {
                push_back(T());
            }
            while (Size > num)
            {
                pop_back();
            }
        }

        void resize(size_t num, const T &elem)
        {
            while (Size < num)
            {
                push_back(elem);
            }
            while (Size > num)
            {
                pop_back();
            }
        }

        // push_back
        void push_back(const T &elem)
        {
            DequeNode<T> *newNode = new DequeNode<T>(elem);
            DequeNode<T> *nullp = new DequeNode<T>(nullptr);
            newNode->next = nullptr;                            
            if (empty())
            {
                Front = rear = newNode;
                Front->prev = nullp;
                Front->next = nullp;
                rear->next = nullp;
                rear->prev = nullp;
            }
            else
            {
                newNode->prev = rear;
                rear->next = newNode;
                rear = newNode;
                rear->next = nullp;
            }
            ++ Size;
        }

        // push_front
        void push_front(const T &elem)
        {
            DequeNode<T> *newNode = new DequeNode<T>(elem);
            DequeNode<T> *nullp = new DequeNode<T>(nullptr);
            newNode->next = nullptr;   
            if (empty())
            {
                Front = rear = newNode;
                Front->prev = nullp;
                Front->next = nullp;
                rear->next = nullp;
                rear->prev = nullp;
            }
            else
            {
                newNode->next = Front;
                Front->prev = newNode;
                Front = newNode;
                Front->prev = nullp;
            }
            ++ Size;
        }

        // pop_back
        void pop_back()
        {
            DequeNode<T> *nullp = new DequeNode<T>(nullptr);
            if (!empty())
            {
                DequeNode<T> *tmp = rear;
                rear = rear->prev;
                if (rear)
                {
                    rear->next = nullp;
                }
                else
                {
                    Front = nullp;
                }
                delete tmp;
                Size -- ;
            }
        }

        // pop_front
        void pop_front()
        {
            DequeNode<T> *nullp = new DequeNode<T>(nullptr);
            if (!empty())
            {
                DequeNode<T> *tmp = Front;
                Front = Front->next;
                if (Front)
                {
                    Front->prev = nullp;
                }
                else
                {
                    rear = nullp;
                }
                delete tmp;
                Size -- ;
            }
        }

        // insert
        DequeIterator<T> insert(DequeIterator<T> pos, const T &elem)
        {
            DequeNode<T> *newNode = new DequeNode<T>(elem);
            DequeNode<T> *current = &pos;

            newNode->prev = current->prev;
            newNode->next = current;

            if (current->prev)
            {
                current->prev->next = newNode;
            }
            else
            {
                Front = newNode;
            }

            current->prev = newNode;
            ++ Size;

            return DequeIterator<T>(newNode);
        }

        void insert(DequeIterator<T> pos, size_t n, const T &elem)
        {
            for (size_t i = 0; i < n; ++i)
            {
                pos = insert(pos, elem);
            }
        }

        void insert(DequeIterator<T> pos, DequeIterator<T> beg, DequeIterator<T> end)
        {
            while (beg != end)
            {
                pos = insert(pos, *beg);
                ++ beg;
            }
        }

        // clear
        void clear()
        {
            while (!empty())
            {
                pop_back();
            }
        }

        // erase
        DequeIterator<T> erase(DequeIterator<T> beg, DequeIterator<T> end)
        {
            while (beg != end)
            {
                beg = erase(beg);
            }
            return beg;
        }

        DequeIterator<T> erase(DequeIterator<T> pos)
        {
            DequeNode<T> *current = &pos;
            DequeNode<T> *nextNode = current->next;

            if (current->prev)
            {
                current->prev->next = current->next;
            }
            else
            {
                Front = current->next;
            }

            if (current->next)
            {
                current->next->prev = current->prev;
            }
            else
            {
                rear = current->prev;
            }

            Size -- ;
            return DequeIterator<T>(nextNode);
        }

        // at
        T &at(int idx) const
        {
            DequeIterator<T> it = begin();
            for (int i = 0; i < idx; ++i)
            {
                it ++ ;
            }
            return *it;
        }

        // 运算符重载 []
        T &operator[](int idx) const
        {
            return at(idx);
        }

        // front
        T &front() const
        {
            return Front->data;
        }

        // back
        T &back() const
        {
            return rear->data;
        }

        // 迭代器
        DequeIterator<T> begin() const
        {
            return DequeIterator<T>(this->Front);
        }

        DequeIterator<T> end() const
        {
            return DequeIterator<T>(nullptr);
        }

        DequeIterator<T> rbegin() const
        {
            return DequeIterator<T>(this->rear);
        }

        DequeIterator<T> rend() const
        {
            return DequeIterator<T>(nullptr);
        }
};