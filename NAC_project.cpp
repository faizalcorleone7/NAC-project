#include<iostream>																																			//thoda better karna hai
#include<string.h>
#include<malloc.h>
using namespace std;
typedef struct Node
{
	char c;									
	struct Node *array[128];
	bool check;	
}node;
node* initialise(node *t)
{
	for (int i=0;i<128;i++)
	{
		t->array[i]=NULL;
		t->check=false;
	}
return t;
}
class trie
{
	private:
		string s,s1;
		node *head, *head1;
		int shift1,shift2;
	public:
		void get_sender_string()
		{
		string s1;
		cin>>s1;
		s=s1;			
		}
		void get_receiver_string()
		{
		string S1;
		cin>>S1;
		s1=S1;			
		}
		trie()
		{
			head=NULL;
			head1=NULL;
		}
		void create_shift1()
		{
			shift1=(int)s[0];
			for (int i=1;i<s.length();i++)
			{
				shift1=shift1+s[i];
				shift1=shift1%128;
			}
			cout<<"Sender side key = "<<shift1<<endl;
		}
		void create_shift2()
		{
			shift2=(int)s1[0];
			for (int i=1;i<s1.length();i++)
			{
				shift2=shift2+s1[i];
				shift2=shift2%128;
			}
			cout<<"Receiver side key = "<<shift2<<endl;
		}
		void create_trie_sender()
		{			
			head = new node;		
			head->c='$';
			head->check=true;
			head->array[(shift1+(int)s[0])%128]= new node;
			head->array[(shift1+(int)s[0])%128]->check=true;
			node *t=head->array[(shift1+(int)s[0])%128];
			for (int i=1;i<=s.length();i++)		
			{
				cout<<"updating "<<(shift1+(int)s[i-1])%128<<endl;
				t->c=s[i-1];
				t=initialise(t);
				t->check=true;				
				t->array[(shift1+(int)s[i])%128]=new node;								
				t=t->array[(shift1+(int)s[i])%128];
				t->check=true;
			}
			t->check=false;
		}
		void create_trie_receiver()
		{			
			head1 = new node;		
			head1->c='$';
			head1->check=true;
			head1->array[(shift2+(int)s1[0])%128]= new node;
			head1->array[(shift2+(int)s1[0])%128]->check=true;
			node *t=head1->array[(shift2+(int)s1[0])%128];
			for (int i=1;i<=s1.length();i++)		
			{
				cout<<"updating "<<(shift2+(int)s1[i-1])%128<<endl;
				t->c=s1[i-1];
				t=initialise(t);
				t->check=true;				
				t->array[(shift2+(int)s1[i])%128]=new node;								
				t=t->array[(shift2+(int)s1[i])%128];
				t->check=true;
			}
			t->check=false;
		}		
		void check_message()
		{
			int t=1;
			if (shift1!= shift2)
			{
				t=0;
				cout<<"Strings don't match";
			}
			else if (s.length()==s1.length())
			{
			node *t1=head,*t2=head1;
			for (int i=0;i<s.length();i++)
			{
				if ((t1->c==t2->c) && (t1->check==t2->check))			//character being checked in the respective tries...shift is needed else attacker will know which part of the trie is to be manipulated....shift generated for each string is not exactly unique, but matching the shift values is not very easy.... 
				{
					t1=t1->array[(shift1+(int)s[i])%128];
					t2=t2->array[(shift2+(int)s1[i])%128];
				}
				else
				{
					t=0;
					cout<<"Strings don't match";
					break;
				}
			}
			}
			else
			{
				t=0;
				cout<<"Strings don't match";
			}
			if (t==1)
			{
				cout<<"Strings match";
			}
		}
};
int main()
{
	trie t;
	cout<<"Sender side code"<<endl;
	t.get_sender_string();
	t.create_shift1();
	t.create_trie_sender();
	cout<<"\n----------------------\n";
	cout<<"Receiver side code"<<endl;	
	t.get_receiver_string();
	t.create_shift2();	
	t.create_trie_receiver();
	cout<<"\n----------------------\n";
	cout<<"Checking"<<endl;
	t.check_message();
	return 0;
}
