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

void ULListStr::push_back(const std::string& val) {
  // if the list is empty
  if (size_ == 0) {
    Item *node = new Item();
    node->val[ARRSIZE-1] = val;
    node->next = NULL;
    node->prev = NULL;
    node->first = ARRSIZE-1;
    node->last = ARRSIZE;
    head_ = node;
    tail_ = node;
    size_++;
  }
  // if the item is full
  else if(tail_->last >= ARRSIZE) {
    Item *node = new Item();
    node->val[0] = val;
    node->next = NULL;
    node->prev = tail_;
    tail_->next = node;
    tail_ = node;
    node->first = 0;
    node->last = 1;
    size_++;

  }
  // if there is space in the item
  else if(tail_->last < ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }

}

void ULListStr::push_front(const std::string& val) {
// if the list is empty
if (size_ == 0) {
  Item *node = new Item();
  node->val[0] = val;
  node->next = NULL;
  node->prev = NULL;
  node->first = 0;
  node->last = 1;
  head_ = node;
  tail_ = node;
  size_++;
}
// if the item is full
else if (head_->first == 0) {
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

// if there is space in the item
else if (head_->first > 0) {
  head_->val[(head_->first) - 1] = val;
  head_->first--;
  size_++;
}
}

void ULListStr::pop_back() {
  if(size_ > 0) {
    // decrement last so that the original last will no longer be counted as a part of the list
    tail_->last--;

    // tail is empty
    if(tail_->first == tail_->last) {
      Item *tailTemp = tail_;

      // checks if there is more than one item
      if(tail_->prev!= NULL) {
        tail_ = tail_->prev;
        tail_->next = NULL;
      }
      // if there is only one item, then set both head_ and tail_ to null, since the last element was just popped
      else if(tail_->prev == NULL) {
        head_ = NULL;
        tail_ = NULL;
        
      }


      delete tailTemp;
    }
    
    size_--;
  }
}

void ULListStr::pop_front() {
  if(size_> 0) {
    // increment first so that the original first will no longer be counted as a part of the list
    head_->first++;

    // head is empty
    if(head_->first == head_->last) {
      Item *headTemp = head_;

      // checks if there is more than one item
      if(head_->next != NULL) {
        head_ = head_->next;
        head_->next = NULL; // CHANGED THIS LINE OF CODE: has to be head_->prev = NULL, not head_->next = NULL
      }
      // if there is only one item, then set both head_ and tail_ to null, since the last element was just popped
      else if(head_->next == NULL) {
        head_ = NULL;
        tail_ = NULL;
      }

      delete headTemp;
    }
    size_--;
  }
}

std::string const & ULListStr::back() const {
  // return the index of last-1 because last would return one index extra 
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];

}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  // if the loc is out of bounds, then return NULL
  if(loc < 0 || loc > size_) { // CHANGED THIS LINE OF CODE: has to be loc < 0 not loc <= 0 
    return NULL;
  }

  
  int count = 0; // CHANGED THIS LINE OF CODE: has to be count = 0 no count = 1
  int idx = head_->first;

  Item *temp = head_;

  // since the index of the elements in val will restart once the algorithm moves to a new iem, count will be used to keep track of how many elements have been traversed so far
  while(count < loc) {
    // if idx reaches the last element, move on to the next item
    if(idx == temp->last-1) { // CHANGED THIS LINE OF CODE: has to be idx == temp->last-1 not idx == temp->last
      temp = temp->next;
      idx = 0;
    }
    // if idx did not reach the last element, increment idx and don't move on to the next item yet
    else {
      idx++; 
    }

    
    count++;
  }

  return &temp->val[idx];
  
}

