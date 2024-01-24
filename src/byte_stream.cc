#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) { byte_buff_.reserve(capacity); }

bool Writer::is_closed() const
{
  // Your code here.
  return is_closed_;
}

void Writer::push( string data )
{
  // Your code here.
  (void)data;
  if (data.size() + byte_buff_.size() <= capacity_) {
    byte_buff_.append(data);
    num_bytes_pushed_ += data.size();
  } else {
    int i = 0;
    while (byte_buff_.size() < capacity_) {
      // byte_buff_.append(to_string(data[i++])); // error
      // byte_buff_ = byte_buff_ + data[i++];  // is ok
      byte_buff_.push_back(data[i++]);
      num_bytes_pushed_++;
    }
  }
  return;
}

void Writer::close()
{
  // Your code here.
  is_closed_ = true;
}

void Writer::has_remain(bool has_remain)
{
  has_remain_ = has_remain;
}
uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - byte_buff_.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return num_bytes_pushed_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return is_closed_ && byte_buff_.size() == 0 && !has_remain_;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return num_bytes_poped_;
}

string_view Reader::peek() const
{
  // Your code here.
  return byte_buff_;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  (void)len;
  len = min(len, byte_buff_.size());
  byte_buff_.erase(0, len);
  num_bytes_poped_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return byte_buff_.size();
}
