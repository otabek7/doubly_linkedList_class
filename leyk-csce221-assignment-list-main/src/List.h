#pragma once

#include <cstddef>     // size_t
#include <iterator>    // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List
{
private:
    struct Node
    {
        Node *next, *prev;
        T data;
        explicit Node(Node *prev = nullptr, Node *next = nullptr)
            : next{next}, prev{prev} {}
        explicit Node(const T &data, Node *prev = nullptr, Node *next = nullptr)
            : next{next}, prev{prev}, data{data} {}
        explicit Node(T &&data, Node *prev = nullptr, Node *next = nullptr)
            : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = pointer_type;
        using reference = reference_type;

    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node *node;

        explicit basic_iterator(Node *ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node *ptr) noexcept : node{const_cast<Node *>(ptr)} {}

    public:
        basic_iterator()
        {
            /* TODO */
            node = nullptr;
        };
        basic_iterator(const basic_iterator &) = default;
        basic_iterator(basic_iterator &&) = default;
        ~basic_iterator() = default;
        basic_iterator &operator=(const basic_iterator &) = default;
        basic_iterator &operator=(basic_iterator &&) = default;

        reference operator*() const
        {
            // TODO
            return node->data;
        }
        pointer operator->() const
        {
            // TODO
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator &operator++()
        {
            // TODO
            this->node = this->node->next;
            return *(this);
        }
        // Postfix Increment: a++
        basic_iterator operator++(int)
        {
            // TODO
            basic_iterator temp = basic_iterator(this->node);
            ++(*this);
            return (temp);
        }
        // Prefix Decrement: --a
        basic_iterator &operator--()
        {
            // TODO
            this->node = this->node->prev;
            return *(this);
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int)
        {
            // TODO
            basic_iterator temp = basic_iterator(this->node);
            this->node = this->node->prev;
            return (temp);
        }

        bool operator==(const basic_iterator &other) const noexcept
        {
            // TODO
            if (node == other.node)
                return true;
            return false;
        }
        bool operator!=(const basic_iterator &other) const noexcept
        {
            // TODO
            if (node != other.node)
                return true;
            return false;
        }
    };

public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = basic_iterator<pointer, reference>;
    using const_iterator = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head(), tail(), _size(0)
    {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        // head.prev = nullptr;
        // tail.next = nullptr;
    }
    List(size_type count, const T &value) : head(), tail(), _size(0)
    {
        // TODO - Don't forget the list
        head.next = &tail;
        tail.prev = &head;
        for (int i = 0; i < count; i++)
            push_back(value);
    }
    explicit List(size_type count) : head(), tail(), _size(0)
    {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        for (int i = 0; i < count; i++)
            push_back(T());
    }

    List(const List &other) : head(), tail(), _size(0)
    {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        for (const_iterator i = other.begin(); i != other.end(); i++)
        {
            push_back(*i);
        }
    }
    List(List &&other) : head(), tail(), _size(0)
    {
        // TODO - Don't forget the list initialier
        if (other.empty())
        {
            head.next = &tail;
            tail.prev = &head;
        }

        else
        {
            head.next = other.head.next;
            tail.prev = other.tail.prev;

            head.prev = nullptr;
            tail.next = nullptr;

            other.head.next = &other.tail;
            other.tail.prev = &other.head;

            head.next->prev = &head;
            tail.prev->next = &tail;

            _size = other._size;
            other._size = 0;
        }
    }
    ~List()
    {
        // TODO
        clear();
    }
    List &operator=(const List &other)
    {
        // TODO
        if (this == &other)
        {
            return *this;
        }
        clear();

        for (const_iterator i = other.begin(); i != other.end(); i++)
        {
            push_back(*i);
        }
        return *this;
    }
    List &operator=(List &&other) noexcept
    {
        // TODO
        if (this == &other)
        {
            return *this;
        }
        clear();

        if (other.empty())
        {

            head.next = &tail;
            tail.prev = &head;
        }

        else
        {
            head.next = other.head.next;
            tail.prev = other.tail.prev;

            other.head.next = &other.tail;
            other.tail.prev = &other.head;

            head.next->prev = &head;
            tail.prev->next = &tail;

            _size = other._size;
            other._size = 0;
        }

        return *this;
    }

    reference front()
    {
        // TODO
        return head.next->data; // should i use arrow or head.data?
    }
    const_reference front() const
    {
        // TODO
        return head.next->data;
    }

    reference back()
    {
        // TODO
        return tail.prev->data;
    }
    const_reference back() const
    {
        // TODO
        return tail.prev->data;
    }

    iterator begin() noexcept
    {
        // TODO
        return iterator(head.next);
    }
    const_iterator begin() const noexcept
    {
        // TODO
        return const_iterator(head.next);
    }
    const_iterator cbegin() const noexcept // SAME thing as begin() or no?
    {
        // TODO
        return const_iterator(head.next);
    }

    iterator end() noexcept
    {
        // TODO
        return iterator(&tail);
    }
    const_iterator end() const noexcept
    {
        // TODO
        return const_iterator(&tail);
    }
    const_iterator cend() const noexcept
    {
        // TODO
        return const_iterator(&tail);
    }

    bool empty() const noexcept
    {
        // TODO
        if (_size == 0 /*head.next == nullptr && head.prev == nullptr*/)
            return true;
        return false;
    }

    size_type size() const noexcept
    {
        return _size;
    }

    void clear() noexcept
    {
        // TODO
        Node *tempNode = head.next;
        while (tempNode != &tail)
        {
            head.next = tempNode->next;
            delete tempNode;
            tempNode = head.next;
        }

        tempNode->prev = &head;
        _size = 0;
    }

    iterator insert(const_iterator pos, const T &value)
    {
        // // TODO
        Node *newNode = new Node(value);

        newNode->next = pos.node;
        newNode->prev = pos.node->prev;
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;

        _size += 1;

        return iterator(newNode);
    }

    iterator insert(const_iterator pos, T &&value)
    {
        // TODO
        Node *newNode = new Node(std::move(value));

        newNode->next = pos.node;
        newNode->prev = pos.node->prev;
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;

        _size += 1;

        return iterator(newNode);
    }

    iterator erase(const_iterator pos)
    {
        // TODO

        Node *tempNode = pos.node->next;
        pos.node->prev->next = pos.node->next;
        pos.node->next->prev = pos.node->prev;

        delete pos.node;
        _size -= 1;

        return iterator(tempNode);
    }

    void push_back(const T &value)
    {
        // TODO
        // Node* newNode = new Node(value);
        // tail.prev->next = newNode;
        // newNode->prev = tail.prev->next;

        // tail.prev = newNode;
        // newNode->next = tail;

        // _size+=1;

        insert(end(), value);
    }
    void push_back(T &&value)
    {
        // TODO

        insert(end(), std::move(value));
    }

    void pop_back()
    {
        // TODO
        erase(--end());
    }

    void push_front(const T &value)
    {
        // TODO
        insert(begin(), value);
    }
    void push_front(T &&value)
    {
        // TODO
        insert(begin(), std::move(value));
    }

    void pop_front()
    {
        // TODO
        erase(begin());
    }

    /*
      You do not need to modify these methods!

      These method provide the non-const complement
      for the const_iterator methods provided above.
    */
    iterator insert(iterator pos, const T &value)
    {
        return insert((const_iterator &)(pos), value);
    }

    iterator insert(iterator pos, T &&value)
    {
        return insert((const_iterator &)(pos), std::move(value));
    }

    iterator erase(iterator pos)
    {
        return erase((const_iterator &)(pos));
    }
};

/*
    You do not need to modify these methods!

    These method provide a overload to compare const and
    non-const iterators safely.
*/

namespace
{
    template <typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator,
            Iter>{} &&
            std::is_same<
                typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
                ConstIter>{},
        T>::type;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator &lhs, const ConstIter &rhs)
{
    return (const ConstIter &)(lhs) == rhs;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter &lhs, const Iterator &rhs)
{
    return (const ConstIter &)(rhs) == lhs;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator &lhs, const ConstIter &rhs)
{
    return (const ConstIter &)(lhs) != rhs;
}

template <typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter &lhs, const Iterator &rhs)
{
    return (const ConstIter &)(rhs) != lhs;
}