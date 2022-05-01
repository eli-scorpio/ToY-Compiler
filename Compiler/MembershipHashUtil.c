//
// Created by Mingwei Shi on 29/03/2022.
//

#include "MembershipHashUtil.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "MembershipHashUtil.h"

/**
 * MySql中出现的字符串Hash函数
 * 这种哈希是迄今为止我们所见过的所有函数中产生碰撞最少的，对数字和字符串都很有效。
 */
unsigned int hashMysqlNR(const char *key, unsigned int len)
{
    const char *end=key+len;
    unsigned int hash;

    for (hash = 0; key < end; key++) {
        hash *= 16777619;
        hash ^= (unsigned int) *(unsigned char*) key;
    }

    return (hash);
}

/**
 * MySql中出现的字符串Hash函数
 * 计算一个键的哈希值，大小写独立
 */
unsigned int hashMysqlNRCaseUp(const char *key, unsigned int len)
{
    const char *end=key+len;
    unsigned int hash;

    for (hash = 0; key < end; key++) {
        hash *= 16777619;
        hash ^= (unsigned int) (unsigned char) toupper(*key);
    }

    return (hash);
}


/**
 * PHP中出现的字符串Hash函数
 */
unsigned long hashPhp(char *arKey, unsigned int nKeyLength)
{
    unsigned long h = 0, g;
    char *arEnd=arKey+nKeyLength;

    while (arKey < arEnd) {
        h = (h << 4) + *arKey++;
        if ((g = (h & 0xF0000000))) {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }
    return h;
}

/**
 * OpenSSL中出现的字符串Hash函数
 */
unsigned long hashOpenSSL(char *str)
{
    int i,l;
    unsigned long ret=0;
    unsigned short *s;

    if (str == NULL) return(0);
    l=(strlen(str)+1)/2;
    s=(unsigned short *)str;

    for (i=0; i<l; i++)
        ret^=(s[i]<<(i&0x0f));
    return(ret);
}

/**
 * 另一个经典字符串Hash函数
 */
unsigned int hash(char *str)
{
    register unsigned int h;
    register unsigned char *p;

    for(h=0, p = (unsigned char *)str; *p ; p++) {
        h = 31 * h + *p;
    }

    return h;
}
