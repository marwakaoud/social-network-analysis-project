#include <iostream>
#include <string>
#include <list>
using namespace std;
#include<vector>
struct comment
{
	string text;
	int owner;
};
struct post 
{
	int owner_ID;
	string txt ;
	int no_likes ;
    vector <string >name_likes ;
   	vector <comment> comments;
};


class user {

private:

	int ID;
    string name ;
    string password ;
    string email ;
	
    vector <post> my_posts ;
	friend void	save_and_exit();
	friend void  load_data();


public :
	user (int ID  ,string name , string password , string email) ;
	user();
	void add_friend (string email);
	void display() ;
	void show_posts() ;
	void show_my_posts();
	
	friend void sign_in ();
	friend void creat_account();                                          
	void write_post();
	void sign_out();
	void show_my_friends_list();
	void like_post(post x) ;
	void comment_post(post x);
};


void creat_account ();

void home_page();
void sign_in ();

void save_and_exit();
void load_data();




