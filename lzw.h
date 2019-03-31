#ifndef GERIES_LZW_H
#define GERIES_LZW_H

#include "platform/types.h"
#include <iostream>

class LZWT
{
private:

    struct node
    {
        node* left; // 0
        node* right; // 1

        node();
        node(const node& cpy);
        ~node();

        U32 depth() const;
        U64 acc_leaf_depth(U32 current = 0) const;
        U32 acc_leaf() const;
        F64 var(F64 average, U32 current = 0) const;
        void print(std::ostream& out, bool right, U32 current = 0) const;
    };

    node* current;
    node root;

public:

    LZWT();
    ~LZWT();

    LZWT(const LZWT& cpy);
    LZWT& operator =(const LZWT& cpy);

    // Takes '0' or '1'
    LZWT& operator <<(char c);
    // Takes true or false
    LZWT& operator <<(bool b);

    // Max leaf depth
    U32 depth() const;
    // Average leaf depth
    F64 mean() const;
    // Variance of leaf depth
    F64 var() const;

    void print(std::ostream& out) const;
};

inline std::ostream& operator <<(std::ostream& out, const LZWT& tree)
{
    tree.print(out);
    return out;
}

inline LZWT& LZWT::operator <<(char c)
{
    if (c == '0') {
        this->operator<< (false);
    }
    else if (c == '1') {
        this->operator<< (true);
    }
    else {
        // Herp derp case.
        // Random error handlin' shall be comin' here.
    }
    return *this;
}

#endif // GERIES_LZW_H
