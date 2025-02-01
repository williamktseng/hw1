#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string&val) {
  if(size_ == 0) {
    Item* node = new Item();
    node-val[ARRSIZE-1] = val;
    node->next = NULL;
    node->prev = NULL;
    node->first = ARRSIZE-1;
    node->last = ARRSIZE;
    head_ = node;
    tail_ = node;
    size_++;
  }
  else if(tail_->last >= ARRSIZE){
    item *node = new Item();
    node->val[0] = val;
    node->next = NULL;
    node->prev = tail_;
    tail_->next = node;
    tail_ = node;
    node->first = 0;
    node->last = 1;
    size_++;
  }
  else if(tail_->last < ARRSIZE){
    tail_->val(tail_->last) = val;
    tail_->last++;
    size_++;
  }
}

void ULListStr::push_front(const std::string& val){
  if(size_ ==0){
    Item *node = new Item();
    node->val[0] = val;
    node->next = NULL;
    node->prev = NULL;
    node->first = 0;
    node->last = 1;
    head_ = node;
    tail_ = node;
    size++
  }
  else if(head_->first == 0){
    Item *node = new Item();
    node->val[ARRSIZE-1] = val;
    node->next = head_;
    node->prev = NULL;
    head_->prev = node;
    head_ = node;
    node->first = ARRSIZE-1;
    node->last = ARRSIZE;
    size_++;
  }
  else if(head_->first > 0){
    head_->val[(head_->first) - 1] = val;
    head_->first--;
    size_++;
  }
}

void ULListStr::pop_back(){
  if(size_ > 0){
    tail_->last--;
    if(tail_->first == tail_->last){
      Item *tailTemp = tail_;
      if(tail_->prev != NULL){
        tail_ = tail_->prev;
        tail_->next = NULL;
      }
      else if(tail_->prev == NULL){
        head_ = NULL;
        tail_ = NULL;
      }
      delete tailTemp;
    }
    size_--;
  }
}

void ULListStr::pop_front(){
  if(size_>0){
    head_->first++;
  if(head_->first == head_->last){
    Item *headTemp = head_;
    if(head_->first == head_->last){
      Item *headTemp = head_;
      if(head_->next != NULL){
        head_ = head_->next;
        head_->next = NULL;
      }
      else if(head_->next == NULL){
        head_ = NULL;
        tail_ = NULL;
      }
      delete headTemp;
    }
    size_--;
  }
}

std::string const & ULListStr::back() const{
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc < 0 || loc > size_){
    return NULL;
  }

  int count = 0;
  int idx = head_->first;

  Item *temp = head_;

  while(count < loc){
    if(idx == temp->last-1){
      temp = temp->next;
      idex = 0;
    }else{
     idx++;
    }
    count++;
  }
}