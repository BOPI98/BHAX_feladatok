
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>

#define null NULL

class Binfa
{
private:
	class Node
	{
	public:
		Node(char c='/')
		{
			this->c=c;
			this->left = null;
			this->right = null;
		}
		char c;
		Node* left;
		Node* right;
	};
	Node* fa;
	

public:
	Binfa(): fa(&gyoker)
	{

	}
	
	void operator<<(char c)
	{
		if(c=='0')
		{
			if(fa->left == null)
			{
				fa->left = new Node('0');
				fa = &gyoker;
			}
			else
			{
				fa = fa->left;
			}
		}
		else
		{
			if(fa->right == null)
			{
				fa->right = new Node('1');
				fa = &gyoker;
			}
			else
			{
				fa = fa->right;
			}
		}
	}
	
	void preorder(Node* elem,int depth=0)
	{
		if(elem==null)
		{
			return;
		}
		if(depth) 
		{
			char *spaces;
			spaces =(char*) malloc(sizeof(char)*depth*2+1);
			for(int i=0;i<depth;i+=2)
			{
				spaces[i]='-';
				spaces[i+1]='-';
			}
			spaces[depth*2]='\0';

			printf("%s%c\n",spaces,elem->c);
			free(spaces);
		}
		else
		{
			printf("%c\n",elem->c);
		}
		preorder(elem->left,depth+1);	
		preorder(elem->right,depth+1);
	}

	void inorder(Node* elem,int depth=0)
	{
		if(elem==null)
		{
			return;
		}
		inorder(elem->left,depth+1);
		if(depth) 
		{
			char *spaces;
			spaces =(char*) malloc(sizeof(char)*depth*2+1);
			for(int i=0;i<depth;i+=2)
			{
				spaces[i]='-';
				spaces[i+1]='-';
			}
			spaces[depth*2]='\0';

			printf("%s%c\n",spaces,elem->c);
			free(spaces);
		}
		else
		{
			printf("%c\n",elem->c);
		}	
		inorder(elem->right,depth+1);
	}

	void postorder(Node* elem,int depth=0)
	{
		if(elem==null)
		{
			return;
		}
		postorder(elem->left,depth+1);
		postorder(elem->right,depth+1);
		if(depth) 
		{
			char *spaces;
			spaces =(char*) malloc(sizeof(char)*depth*2+1);
			for(int i=0;i<depth;i+=2)
			{
				spaces[i]='-';
				spaces[i+1]='-';
			}
			spaces[depth*2]='\0';

			printf("%s%c\n",spaces,elem->c);
			free(spaces);
		}
		else
		{
			printf("%c\n",elem->c);
		}	
	}

	void destroy_tree(Node* elem)
	{
		if(elem==null)
		{
			return;
		}
		destroy_tree(elem->left);
		destroy_tree(elem->right);
		if(elem->c!='/') delete elem;
	}

	Node gyoker;

};

void usage()
{
	printf("Használat: ./binfa KAPCSOLÓ\n");
	printf("Az KAPCSOLÓ lehet:\n");
	printf("--preorder\tA bináris fa preorder bejárása\n");
	printf("--inorder\tA bináris fa inorder bejárása\n");
	printf("--postorder\tA bináris fa postorder bejárása\n");
}

int main(int argc, char** argv)
{
	srand(time(0));
	Binfa bfa;
	for(int i=0;i<100;i++)
	{
		int x=rand()%2;
		if(x)
		{
			bfa<<'1';
		}
		else
		{
			bfa<<'0';
		}
	}
	if(argc == 2)
	{
		if(strcmp(argv[1],"--preorder")==0)
		{
			bfa.preorder(&bfa.gyoker);
		}
		else if(strcmp(argv[1],"--inorder")==0)
		{
			bfa.inorder(&bfa.gyoker);
		}
		else if(strcmp(argv[1],"--postorder")==0)
		{
			bfa.postorder(&bfa.gyoker);
		}
		else
		{
			usage();
		}
	}
	else
	{
		usage();
	}
	bfa.destroy_tree(&bfa.gyoker);
	return 0;
}
