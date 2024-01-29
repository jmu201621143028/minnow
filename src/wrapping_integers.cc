#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  // Your code here.
  (void)n;
  (void)zero_point;
  uint32_t value = (n + zero_point.raw_value_) % (1LL << 32);
  return Wrap32 { value };
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
  (void)zero_point;
  (void)checkpoint;
  uint32_t seqno = this->raw_value_ - zero_point.raw_value_;
  uint64_t abs_seqno;
  if (checkpoint > seqno) {
    int k = (checkpoint - seqno) / (1LL << 32);
    uint64_t abs_seqno_down = seqno + (k++) * (1LL << 32);
    uint64_t abs_seqno_up = seqno + k * (1LL << 32);
    abs_seqno = (checkpoint - abs_seqno_down) < (abs_seqno_up - checkpoint) ? abs_seqno_down : abs_seqno_up;
  } else {
    int k = 1.0 * (seqno - checkpoint) / (1LL << 32);
    abs_seqno = seqno > k * (1LL << 32) ? seqno - k * (1LL << 32) : seqno;
  }
  return abs_seqno;
}
