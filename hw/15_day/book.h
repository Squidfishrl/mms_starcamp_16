#ifndef __BOOK_H__
#define __BOOK_H__

struct Book {
        char title[150];
        char author[100];
        unsigned int pages;
        float price;
};

#endif // !__BOOK_H__
