#include <iostream>
// 类前置声明
class Iterator;

/*
 * Aggregate
 * 描述： 表示集合的接口
 * 生成用于遍历集合的迭代器
 */
class Aggregate {
public:
  virtual ~Aggregate() {}
  virtual Iterator *iterator() = 0;
};
/*
 * ConcreateAggregate
 * 描述： 实际集合
 * 实现了Aggregate接口，
 * 该类作为实际集合使用,集合底层的数据结构可以任意，这里以int数组做展示
 */
class ConcreateAggregate : public Aggregate {
public:
  ConcreateAggregate(const unsigned int size) {
    element = new int[size](); //值初始化, 即指为0
    count = size;
  }

  ~ConcreateAggregate() { delete[] element; }

  Iterator *iterator();

  unsigned int size() const { return count; }

  int at(unsigned int index) { return element[index]; }

private:
  int *element;
  unsigned int count;
};

/*
 * Iterator
 * Iterator接口用于遍历集合的元素
 */
class Iterator {
public:
  virtual ~Iterator() {}

  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool hasNext() const = 0;
  virtual int currentItem() const = 0;
};

/*
 * ConcreteIterator
 * 实现了Iterator接口负责遍历实际集合的遍历， 屏蔽了内部数据组织细节
 * 可以创建多个不同遍历顺序的迭代器， 这也是Iterator模型的优点所在，
 * 将遍历与实现分开的好处， 可以尽量少或者不用动实际的遍历所使用的代码
 */
class ConcreteIterator : public Iterator {
public:
  //生成具体迭代器，指向具体集合
  ConcreteIterator(ConcreateAggregate *l) : list(l), index(0) {}

  ~ConcreteIterator() {}

  void first() { index = 0; }

  void next() { index++; }

  bool hasNext() const {
    if (index < list->size())
      return true;
    else
      return false;
  }

  int currentItem() const {
    if (hasNext())
      return list->at(index);
    else
      return -1;
  }
  //  int currentItem() const

private:
  ConcreateAggregate *list;
  unsigned int index;
};

Iterator *ConcreateAggregate::iterator() { return new ConcreteIterator(this); }

//测试
int main() {
  unsigned int size = 5;
  ConcreateAggregate l = ConcreateAggregate(size);

  Iterator *it = l.iterator();
  for (; it->hasNext(); it->next())
    std::cout << "Item value: " << it->currentItem() << std::endl;

  delete it;
  return 0;
}