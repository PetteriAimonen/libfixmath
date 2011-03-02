#ifndef __libfixmath_fix16_hpp__
#define __libfixmath_fix16_hpp__

class Fix16 {
	public:
		fix16_t value;

		Fix16() { value = 0; }
		Fix16(const Fix16 &inValue)  { value = inValue.value;             }
		Fix16(const fix16_t inValue) { value = inValue;                   }
		Fix16(const float inValue)   { value = fix16_from_float(inValue); }
		Fix16(const double inValue)  { value = fix16_from_dbl(inValue);   }
		Fix16(const int16_t inValue) { value = fix16_from_int(inValue);   }

		operator fix16_t() { return value;                 }
		operator double()  { return fix16_to_dbl(value);   }
		operator float()   { return fix16_to_float(value); }
		operator int16_t() { return fix16_to_int(value);   }

		Fix16 & operator=(const Fix16 &rhs)  { value = rhs.value;             return *this; }
		Fix16 & operator=(const fix16_t rhs) { value = rhs;                   return *this; }
		Fix16 & operator=(const double rhs)  { value = fix16_from_dbl(rhs);   return *this; }
		Fix16 & operator=(const float rhs)   { value = fix16_from_float(rhs); return *this; }
		Fix16 & operator=(const int16_t rhs) { value = fix16_from_int(rhs);   return *this; }

		Fix16 & operator+=(const Fix16 &rhs)  { value += rhs.value;             return *this; }
		Fix16 & operator+=(const fix16_t rhs) { value += rhs;                   return *this; }
		Fix16 & operator+=(const double rhs)  { value += fix16_from_dbl(rhs);   return *this; }
		Fix16 & operator+=(const float rhs)   { value += fix16_from_float(rhs); return *this; }
		Fix16 & operator+=(const int16_t rhs) { value += fix16_from_int(rhs);   return *this; }

		Fix16 & operator-=(const Fix16 &rhs)  { value -= rhs.value; return *this; }
		Fix16 & operator-=(const fix16_t rhs) { value -= rhs; return *this; }
		Fix16 & operator-=(const double rhs)  { value -= fix16_from_dbl(rhs); return *this; }
		Fix16 & operator-=(const float rhs)   { value -= fix16_from_float(rhs); return *this; }
		Fix16 & operator-=(const int16_t rhs) { value -= fix16_from_int(rhs); return *this; }

		Fix16 & operator*=(const Fix16 &rhs)  { value = fix16_mul(value, rhs.value); return *this; }
		Fix16 & operator*=(const fix16_t rhs) { value = fix16_mul(value, rhs); return *this; }
		Fix16 & operator*=(const double rhs)  { value = fix16_mul(value, fix16_from_dbl(rhs)); return *this; }
		Fix16 & operator*=(const float rhs)   { value = fix16_mul(value, fix16_from_float(rhs)); return *this; }
		Fix16 & operator*=(const int16_t rhs) { value *= rhs; return *this; }

		Fix16 & operator/=(const Fix16 &rhs)  { value = fix16_div(value, rhs.value); return *this; }
		Fix16 & operator/=(const fix16_t rhs) { value = fix16_div(value, rhs); return *this; }
		Fix16 & operator/=(const double rhs)  { value = fix16_div(value, fix16_from_dbl(rhs)); return *this; }
		Fix16 & operator/=(const float rhs)   { value = fix16_div(value, fix16_from_float(rhs)); return *this; }
		Fix16 & operator/=(const int16_t rhs) { value /= rhs; return *this; }

		const Fix16 operator+(const Fix16 &other) const  { Fix16 ret = *this; ret += other; return ret; }
		const Fix16 operator+(const fix16_t other) const { Fix16 ret = *this; ret += other; return ret; }
		const Fix16 operator+(const double other) const  { Fix16 ret = *this; ret += other; return ret; }
		const Fix16 operator+(const float other) const   { Fix16 ret = *this; ret += other; return ret; }
		const Fix16 operator+(const int16_t other) const { Fix16 ret = *this; ret += other; return ret; }

		const Fix16 operator-(const Fix16 &other) const  { Fix16 ret = *this; ret -= other; return ret; }
		const Fix16 operator-(const fix16_t other) const { Fix16 ret = *this; ret -= other; return ret; }
		const Fix16 operator-(const double other) const  { Fix16 ret = *this; ret -= other; return ret; }
		const Fix16 operator-(const float other) const   { Fix16 ret = *this; ret -= other; return ret; }
		const Fix16 operator-(const int16_t other) const { Fix16 ret = *this; ret -= other; return ret; }

		const Fix16 operator*(const Fix16 &other) const  { Fix16 ret = *this; ret *= other; return ret; }
		const Fix16 operator*(const fix16_t other) const { Fix16 ret = *this; ret *= other; return ret; }
		const Fix16 operator*(const double other) const  { Fix16 ret = *this; ret *= other; return ret; }
		const Fix16 operator*(const float other) const   { Fix16 ret = *this; ret *= other; return ret; }
		const Fix16 operator*(const int16_t other) const { Fix16 ret = *this; ret *= other; return ret; }

		const Fix16 operator/(const Fix16 &other) const  { Fix16 ret = *this; ret /= other; return ret; }
		const Fix16 operator/(const fix16_t other) const { Fix16 ret = *this; ret /= other; return ret; }
		const Fix16 operator/(const double other) const  { Fix16 ret = *this; ret /= other; return ret; }
		const Fix16 operator/(const float other) const   { Fix16 ret = *this; ret /= other; return ret; }
		const Fix16 operator/(const int16_t other) const { Fix16 ret = *this; ret /= other; return ret; }

		const int operator==(const Fix16 &other)  const { return (value == other.value);             }
		const int operator==(const fix16_t other) const { return (value == other);                   }
		const int operator==(const double other)  const { return (value == fix16_from_dbl(other));   }
		const int operator==(const float other)   const { return (value == fix16_from_float(other)); }
		const int operator==(const int16_t other) const { return (value == fix16_from_int(other));   }

		const int operator!=(const Fix16 &other)  const { return (value != other.value);             }
		const int operator!=(const fix16_t other) const { return (value != other);                   }
		const int operator!=(const double other)  const { return (value != fix16_from_dbl(other));   }
		const int operator!=(const float other)   const { return (value != fix16_from_float(other)); }
		const int operator!=(const int16_t other) const { return (value != fix16_from_int(other));   }

		const int operator<=(const Fix16 &other)  const { return (value <= other.value);             }
		const int operator<=(const fix16_t other) const { return (value <= other);                   }
		const int operator<=(const double other)  const { return (value <= fix16_from_dbl(other));   }
		const int operator<=(const float other)   const { return (value <= fix16_from_float(other)); }
		const int operator<=(const int16_t other) const { return (value <= fix16_from_int(other));   }

		const int operator>=(const Fix16 &other)  const { return (value >= other.value);             }
		const int operator>=(const fix16_t other) const { return (value >= other);                   }
		const int operator>=(const double other)  const { return (value >= fix16_from_dbl(other));   }
		const int operator>=(const float other)   const { return (value >= fix16_from_float(other)); }
		const int operator>=(const int16_t other) const { return (value >= fix16_from_int(other));   }

		const int operator< (const Fix16 &other)  const { return (value <  other.value);             }
		const int operator< (const fix16_t other) const { return (value <  other);                   }
		const int operator< (const double other)  const { return (value <  fix16_from_dbl(other));   }
		const int operator< (const float other)   const { return (value <  fix16_from_float(other)); }
		const int operator< (const int16_t other) const { return (value <  fix16_from_int(other));   }

		const int operator> (const Fix16 &other)  const { return (value >  other.value);             }
		const int operator> (const fix16_t other) const { return (value >  other);                   }
		const int operator> (const double other)  const { return (value >  fix16_from_dbl(other));   }
		const int operator> (const float other)   const { return (value >  fix16_from_float(other)); }
		const int operator> (const int16_t other) const { return (value >  fix16_from_int(other));   }

		Fix16  sin() { return Fix16(fix16_sin(value));  }
		Fix16  cos() { return Fix16(fix16_cos(value));  }
		Fix16  tan() { return Fix16(fix16_tan(value));  }
		Fix16 asin() { return Fix16(fix16_asin(value)); }
		Fix16 acos() { return Fix16(fix16_acos(value)); }
		Fix16 atan() { return Fix16(fix16_atan(value)); }
		Fix16 atan2(const Fix16 &inY) { return Fix16(fix16_atan2(value, inY.value)); }
};

#endif
