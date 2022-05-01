//
// Created by Mingwei Shi on 29/03/2022.
//

#ifndef HSSS_MEMBERSHIPHASHUTIL_H
#define HSSS_MEMBERSHIPHASHUTIL_H

unsigned int hashMysqlNR(const char *key, unsigned int len);
unsigned int hashMysqlNRCaseUp(const char *key, unsigned int len);
unsigned long hashPhp(char *arKey, unsigned int nKeyLength);
unsigned long hashOpenSSL(char *str);
unsigned int hash(char *str);




#endif //HSSS_MEMBERSHIPHASHUTIL_H
