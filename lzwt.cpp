#include "lzw.h"
#include <stdexcept>

//==============================================================================================
//lzwtree
//==============================================================================================

//----------------------------------------------------------------------------------------------
//ctors/dtors
//lel.

lzwtree::lzwtree():
    m_At(&m_Root)
    {};
    
lzwtree::~lzwtree()
{
    iterator it=begin();
    node* n;
    
    while(it)
    {
        n=it.m_At;
        ++it;
        if(n!=&m_Root)
            delete n;
    }
}

//----------------------------------------------------------------------------------------------
//Insertion

void lzwtree::put_bit(bool bit)
{
    if(m_At->descend(bit))
        m_At = &m_Root;
    else
        m_At = m_At->child(bit);
};

//----------------------------------------------------------------------------------------------
//Parse file from stream
//Note: the lineskipping seen in z3a7.cpp is not included

size_t lzwtree::from_stream(std::istream& is)
{
    bool in_comment=0;
    unsigned char b;
    size_t read_count=0;
    
    while(is.read((char*)&b, sizeof(unsigned char)))
    {
        read_count++;
        
        if(b=='>')
            in_comment=1;
        else if(b=='\n')
            in_comment=0;
        else if(in_comment)
            continue;
        else if(b=='N')     //Why do we hate N's so much?
            continue;
        else
        {
            for(size_t i=0; i<8; i++)
            {
                put_bit(b&0x80);
                b<<=1;
            }
        }
    }
	
	return read_count;
}

//----------------------------------------------------------------------------------------------
//Iterators

lzwtree::iterator lzwtree::begin()
{
    return ++iterator(&m_Root);
}

lzwtree::iterator lzwtree::end()
{
    return iterator(NULL);
}

//----------------------------------------------------------------------------------------------
//Overloaded operators

lzwtree& operator<<(lzwtree& tree, bool bit)
{
    tree.put_bit(bit);
    return tree;
}

std::istream& operator>>(std::istream& is, lzwtree& tree)
{
    tree.from_stream(is);
    return is;
}

//==============================================================================================
//lzwtree::node
//==============================================================================================

//----------------------------------------------------------------------------------------------
//ctors/dtors

lzwtree::node::node(char val, size_t d):
    m_Value(val),
    m_Depth(d)
{
    m_Children[0]=0;
    m_Children[1]=0;
}

/** Create child **/
/* Returns false if child already existed 
 * i.e. returns number of nodes created
 * */
bool lzwtree::node::descend(bool dir)
{
    if(m_Children[dir])
        return 0;
    else
    {
        m_Children[dir]=new node(dir, m_Depth+1);
        return 1;
    }
}

/** Get child **/
lzwtree::node* lzwtree::node::child(bool dir)
{
    return m_Children[dir];
}

/** Get node value **/
/* Either '/', '0' or '1' 
 * note to self: this seems a bit quirky. */
char lzwtree::node::value() const
{
    switch(m_Value)
    {
        case '/': return '/'; 
        case   0: return '0';
        case   1: return '1';
		
		default:
			return 0;
    }
}

size_t lzwtree::node::depth() const
{
    return m_Depth;
}

bool lzwtree::node::is_leaf() const
{
    return (m_Children[0]==NULL && m_Children[1]==NULL);
}

//==============================================================================================
//lzwtree::iterator
//==============================================================================================

lzwtree::iterator::iterator(node* at):
    m_At(at),
    m_Step(s_right)
    {}
    
lzwtree::iterator& lzwtree::iterator::advance()
{
    //End iterators don't advance
    if(m_At==NULL)
        return *this;
    
    switch(m_Step)
    {
        case s_up:
            if(m_Visit.empty())
            {
                m_At=NULL;
                return *this;
            }
            
            //Return upper node, next time step left
            m_At=m_Visit.top();
            m_Visit.pop();
            m_Step=s_left;
            return *this;
            
        case s_right:
            //Find the rightmost node
            while(m_At->child(1))
            {
                m_Visit.push(m_At);
                m_At=m_At->child(1);
            }
            
            //Return current node, next time step left
            m_Step=s_left;
            return *this;
            
        case s_left:
            if(m_At->child(0))
            {
                m_At=m_At->child(0);
                m_Step=s_right;
                return ++(*this);
            }
            else
            {
                m_Step=s_up;
                return ++(*this);
            }
    }
	
	//All of the enum's values are covered here, but I still get an error, so: 
	return *this;
}

lzwtree::iterator& lzwtree::iterator::operator++()
{
    return advance();
}

bool lzwtree::iterator::operator!() const
{
    return !m_At;
}

lzwtree::iterator::operator bool() const
{
    return m_At;
}

bool lzwtree::iterator::operator==(const lzwtree::iterator& rhs) const
{
    return m_At==rhs.m_At;
}

bool lzwtree::iterator::operator!=(const lzwtree::iterator& rhs) const
{
    return m_At!=rhs.m_At;
}

char lzwtree::iterator::value() const
{
    if(!m_At){std::out_of_range e("lzwtree::iterator::value() on NULL-iterator"); throw e;}
    
    return m_At->value();
}

size_t lzwtree::iterator::depth() const
{
    if(!m_At){std::out_of_range e("lzwtree::iterator::depth() on NULL-iterator"); throw e;}
    
    return m_At->depth();
}

bool lzwtree::iterator::is_leaf() const
{
    if(!m_At){std::out_of_range e("lzwtree::iterator::is_leaf() on NULL-iterator"); throw e;}
    
    return m_At->is_leaf();
}

lzwtree::iterator lzwtree::iterator::left() const
{
    return iterator(*this).advance();
}

lzwtree::iterator lzwtree::iterator::right() const
{
    return iterator(*this).advance();
}
