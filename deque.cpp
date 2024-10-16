#include <deque>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Deque {
 public:
  Deque() = default;
  void PushBack(const T& value) {
    if (size_ == 0) {
      MakeDeque(value);
      return;
    }
    end_->next_node = new Node(value);
    end_->next_node->prev_node = end_;
    end_ = end_->next_node;
    ++size_;
  }

  void PushFront(const T& value) {
    if (size_ == 0) {
      MakeDeque(value);
      return;
    }
    begin_->prev_node = new Node(value);
    begin_->prev_node->next_node = begin_;
    begin_ = begin_->prev_node;
    ++size_;
  }

  void PopBack() {
    if (size_ <= 0) {
      throw std::out_of_range("Out of range");
    }
    if (size_ == 1) {
      FromOneToZero();
      return;
    }
    Node* holder = end_;
    end_ = end_->prev_node;
    delete holder;
    end_->next_node = nullptr;
    --size_;
  }

  void PopFront() {
    if (size_ <= 0) {
      throw std::out_of_range("Out of range");
    }
    if (size_ == 1) {
      FromOneToZero();
      return;
    }
    Node* holder = begin_;
    begin_ = begin_->next_node;
    delete holder;
    begin_->prev_node = nullptr;
    --size_;
  }

  T Front() {
    if (size_ > 0) {
      return begin_->value;
    }
    throw std::out_of_range("Out of range");
  }

  T Back() {
    if (size_ > 0) {
      return end_->value;
    }
    throw std::out_of_range("Out of range");
  }

  void Traverse() {
    Node* iter = begin_;
    while (iter != nullptr) {
      std::cout << iter->value << ' ';
      iter = iter->next_node;
    }
    std::cout << '\n';
  }

  bool Empty() { return (size_ <= 0); }

  ~Deque() {
    if (size_ == 0) {
      return;
    }
    while (begin_ != end_) {
      Node* holder = begin_;
      begin_ = begin_->next_node;
      delete holder;
    }
    delete begin_;
  }

 private:
  struct Node {
    Node(T val) : value(val) {}
    T value;
    Node* prev_node = nullptr;
    Node* next_node = nullptr;
  };
  void MakeDeque(const T& value) {
    begin_ = new Node(value);
    end_ = begin_;
    size_ = 1;
  }
  void FromOneToZero() {
    Node* holder = begin_;
    delete holder;
    begin_ = nullptr;
    end_ = nullptr;
    size_ = 0;
  }
  Node* begin_ = nullptr;
  Node* end_ = nullptr;  // end points at the last element
  size_t size_ = 0;
};
