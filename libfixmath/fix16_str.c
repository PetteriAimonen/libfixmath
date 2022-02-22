#include "fix16.h"
#include <stdbool.h>
#ifndef FIXMATH_NO_CTYPE
#include <ctype.h>
#else
static inline int isdigit(int c)
{
    return c >= '0' && c <= '9';
}

static inline int isspace(int c)
{
    return c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\v' || c == '\f';
}
#endif

static const uint32_t scales[8] = {
    /* 5 decimals is enough for full fix16_t precision */
    1, 10, 100, 1000, 10000, 100000, 100000, 100000
};

static char *itoa_loop(char *buf, uint32_t scale, uint32_t value, bool skip)
{
    while (scale)
    {
        unsigned digit = (value / scale);
    
        if (!skip || digit || scale == 1)
        {
            skip = false;
            *buf++ = '0' + digit;
            value %= scale;
        }
        
        scale /= 10;
    }
    return buf;
}

void fix16_to_str(fix16_t value, char *buf, int decimals)
{
    uint32_t uvalue = (value >= 0) ? value : -value;
    if (value < 0)
        *buf++ = '-';

    /* Separate the integer and decimal parts of the value */
    unsigned intpart = uvalue >> 16;
    uint32_t fracpart = uvalue & 0xFFFF;
    uint32_t scale = scales[decimals & 7];
    fracpart = fix16_mul(fracpart, scale);
    
    if (fracpart >= scale)
    {
        /* Handle carry from decimal part */
        intpart++;
        fracpart -= scale;    
    }
    
    /* Format integer part */
    buf = itoa_loop(buf, 10000, intpart, true);
    
    /* Format decimal part (if any) */
    if (scale != 1)
    {
        *buf++ = '.';
        buf = itoa_loop(buf, scale / 10, fracpart, false);
    }
    
    *buf = '\0';
}

fix16_t fix16_from_str(const char *buf)
{
    while (isspace((unsigned char) *buf))
        buf++;
    
    /* Decode the sign */
    bool negative = (*buf == '-');
    if (*buf == '+' || *buf == '-')
        buf++;

    /* Decode the integer part */
    uint32_t intpart = 0;
    int count = 0;
    while (isdigit((unsigned char) *buf))
    {
        intpart *= 10;
        intpart += *buf++ - '0';
        count++;
    }
    
    if (count == 0 || count > 5
        || intpart > 32768 || (!negative && intpart > 32767))
        return fix16_overflow;
    
    fix16_t value = intpart << 16;
    
    /* Decode the decimal part */
    if (*buf == '.' || *buf == ',')
    {
        buf++;
        
        uint32_t fracpart = 0;
        uint32_t scale = 1;
        while (isdigit((unsigned char) *buf) && scale < 100000)
        {
            scale *= 10;
            fracpart *= 10;
            fracpart += *buf++ - '0';
        }
        
        value += fix16_div(fracpart, scale);
    }
    
    /* Verify that there is no garbage left over */
    while (*buf != '\0')
    {
        if (!isdigit((unsigned char) *buf) && !isspace((unsigned char) *buf))
            return fix16_overflow;
        
        buf++;
    }
    
    return negative ? -value : value;
}

