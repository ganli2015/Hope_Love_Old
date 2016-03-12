#pragma once

#define assert_same_int(a,b) assert(a==b)
#define assert_same_double(a,b) assert(Math::DoubleCompare(a,b)==0)
#define assert_less(a,b)  assert(a<b)
#define assert_less_equal(a,b)  assert(a<=b)

#define Check(expression) if((expression)==false) throw runtime_error(__FUNCTION__)