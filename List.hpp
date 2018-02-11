template <class T> class list
{
public:
  struct Node
  {
    T value;
    Node *Next = nullptr, *Prev = nullptr;

    Node() = default;
    Node(T value)
    {
      this->value = value;
    }
  };
  class Iterator
  {
  public:
    explicit Iterator(Node *node)
    {
      this->node = node;
    }

    T& operator*()
    {
      return node->value;
    }
    Node* operator->()
    {
      return this->node;
    }
    Node* operator++()
    {
      this->node = this->node->Next;
      return this->node;
    }

    bool operator==(Iterator node)
    {
      return (this->node == node.node);
    }
    bool operator!=(Iterator node)
    {
      return !(*this == node);
    }

  private:
    Node *node;
  };

public:
  list() = default;
  list(list &list)
  {
    this->clear();

    for (auto i : list)
      this->push_back(i);
  }
  //用初始化列表初始链表 用法: list lst = { ... };
  list(std::initializer_list<T> init_value)
  {
    for (T i : init_value)
      this->push_back(i);
  }

  //尾部添加
  void push_back(T value)
  {
    if (this->Head == nullptr || this->Tail == nullptr)
      EmptyList(value);

    return InsertNode(this->Tail->Prev, new Node(value));
  }
  //头部添加
  void push_front(T value)
  {
    if (this->Head == nullptr || this->Tail == nullptr)
      EmptyList(value);

    return InsertNode(this->Head, new Node(value));
  }

  //移除尾尾部
  void pop_back()
  {
    this->DeleteNode(this->Head->Next);
  }
  //移除首元素
  void pop_front()
  {
    this->DeleteNode(this->Tail->Prev);
  }

  //移除元素  pos:下标
  void remove(int pos)
  {
    return DeleteNode(IndexToNode(pos));
  }
  //插入元素  pos:下标
  void insert(int pos, T value)
  {
    this->InsertNode(IndexToNode(pos), new ListNode(value));
  }

  //清除链表
  void clear()
  {
    this->DeleteALLNode(this->Head);

    this->Length = 0;
    this->Head = nullptr;
    this->Tail = nullptr;
  }
  //链表长度
  size_t size()
  {
    return this->Length;
  }

  //删除本身, 等于新链表
  void operator=(list list)
  {
    this->clear();

    for (auto i : list)
      this->push_back(i);
  }
  //链表相加
  list operator+(list list)
  {
    List tmp = *this;

    for (auto i : list)
      tmp.push_back(i);

    return tmp;
  }
  //下标访问元素
  T& operator[](int pos)
  {
    return this->IndexToNode(pos)->value;
  }

  //查找某个元素是否存在
  bool find(T val)
  {
    for (auto i : *this)
      if (i == val)
        return i;
    return T();
  }
  //根据条件查找出第一个符合的元素
  T& find(std::function<bool(T)> fun)
  {
    for (auto i : *this)
      if (fun(i))
        return i;
  }
  //查找出符合条件的所有元素
  list findall(std::function<bool(T)> fun)
  {
    list list;

    for (auto i : *this)
      if (fun(i))
        list.push_back(i);

    return list;
  }

  //链表翻转
  list flip()
  {
    list list;
    for (auto i : *this)
      list.push_front(i);
    return list;
  }

  ~list()
  {
    this->clear();
  }

public:
  //c++11 for( : )
  Iterator begin()
  {
    return Iterator(this->Head->Next);
  }
  Iterator end()
  {
    return Iterator(this->Tail);
  }

private:
  //插入节点
  void InsertNode(Node *insert, Node *current)
  {
    Node *tmp = insert->Next;

    insert->Next = current;
    current->Prev = insert;
    current->Next = tmp;
    tmp->Prev = current;

    this->Length++;
  }
  //删除一个节点
  void DeleteNode(Node *Delete)
  {
    if (this->Length <= 0) return;

    ListNode *front = Delete->Prev;
    ListNode *back = Delete->Next;

    front->Next = back;
    back->Prev = front;

    this->Length--;
  }

  //处理空链表
  void EmptyList(T value)
  {
    this->Head = new Node();
    this->Tail = new Node();

    this->Head->Next = this->Tail;
    this->Tail->Prev = this->Head;
  }
  //清除所有节点
  void DeleteALLNode(Node *node)
  {
    if (node != nullptr)
      DeleteALLNode(node->Next);
    delete node;
  }

  //节点返回下标  -1代表没有
  int NodeToIndex(Node *node)
  {
    int Count = 0;

    for (ListNode *i = this->Head->Next; i != this->Tail; i = i->Next)
    {
      if (i == node)
        return Count;
      Count++;
    }
    return -1;
  }
  //下标返回节点
  Node* IndexToNode(int pos)
  {
    if (pos < 0 || pos > this->Length)
      return this->Head;

    Node *p = this->Head->Next;

    for (int i = 0; i < pos; i++)
      p = p->Next;

    return p;
  }

private:
  size_t Length = 0;
  Node *Head = nullptr, *Tail = nullptr;
};
