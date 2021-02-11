#include <string>

#include "format.h"

using std::string;

// Done by Lidia: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
 long m,h;
 string m_,h_,s_; 
  m=div(seconds,60).quot;
  seconds=div(seconds,60).rem;
  h=div(m,60).quot;
  m=div(m,60).rem;
  h_=std::to_string(h);
  if (h_.size()==1) h_="0"+ h_;
  m_=std::to_string(m);
  if (m_.size()==1) m_="0"+ m_;
  s_=std::to_string(seconds);
  if (s_.size()==1) s_="0"+ s_;
  return (h_+":"+ m_ +":" + s_ );
  
  }