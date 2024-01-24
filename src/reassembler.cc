#include "reassembler.hh"
#include <iostream>

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  (void)first_index;
  (void)data;
  (void)is_last_substring;
  const Writer& WriteByteStream = writer();
  uint64_t nums_pushed = WriteByteStream.bytes_pushed();
  uint64_t available_capacity = WriteByteStream.available_capacity();
  if (nums_pushed < first_index) {
    uint64_t first_unacceptable_ix = nums_pushed + available_capacity;
    for (uint64_t i = 0; i < data.size(); ++i) {
      uint64_t ix = first_index + i;
      if (ix >= first_unacceptable_ix) {  
        break;
      }
      record_[ix] = data[i];
    }
  } else if (first_index + data.size() > nums_pushed) {
      output_.writer().push(data.substr(nums_pushed - first_index));
      nums_pushed = WriteByteStream.bytes_pushed();
      string substrings;
      for (auto it = record_.begin(); it != record_.end(); it = record_.erase(it)) {
        if (it->first == nums_pushed) {
          substrings.push_back(record_[nums_pushed++]);
        } else if (it->first > nums_pushed) {
          break;
        }
      }
      output_.writer().push(std::move(substrings));
  }
  if (is_last_substring) {
    output_.writer().close();
  }
  record_.size() ? output_.writer().has_remain(true) : output_.writer().has_remain(false);
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return record_.size();
}
