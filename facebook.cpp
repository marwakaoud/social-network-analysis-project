
#include <iostream>
#include <string>
#include <list>
#include<stdlib.h>
#include<vector>
#include "facebook.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;
vector<vector<int>> friend_list;
int global_ID = 0;
vector<user> users;
int u_size = 0;
XMLDocument database;
XMLDocument database1;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

user::user(int ID, string name, string password, string email) {

	this->name = name;
	this->password = password;
	this->email = email;
	this->ID = ID;
	vector <int> new_list;
	friend_list.push_back(new_list);



}
user::user()
{
	 ID=0;
	 name="";
	 password="";
	 email="";
}

void user::add_friend(string email)
{
	for (int i = 0; i<users.size(); i++)
	{

		if (users[i].email == email)
		{

			friend_list[i].push_back(this->ID);
			friend_list[this->ID].push_back(i);
		}
	}

	this->display();
}

void creat_account()
{
	string name;
	string password;
	string email;
	cout << "please enter user name :";
	cin.ignore();
	getline(cin, name);
	cout << endl << "please enter email : \t";
	
	while(1)
	{ 
		cin >> email;
		bool flag = true;
		for (int c = 0; c < users.size(); c++)
		{
			 if (email == users[c].email)
			 {
				 cout << "email is existing...please enter another email" << endl;
				 flag = false;
				 break;
			 }
		}
		if (flag == true)break;
	}
	 
	cout << endl << "please enter password : \t";
	cin >> password;

	user m(global_ID, name, password, email);
	global_ID++;
	users.push_back(m);

	m.display();

}

void sign_in()
{
	string email;
	string password;
	int i = 0;
	bool flag = false;
	cout << "please enter your email : \t";
	while (1)
	{
		cin >> email;
		bool flag =false;
		for (int c = 0; c < users.size(); c++)
		{
			if (email == users[c].email)
			{
				  flag = true;
				break;
			}
		}
		if (flag == true)break;
		cout << "please enter another email...if you want to sign up please enter 1" << endl<<
			"if you want to repeat entering email plese enter 0"<<endl;
		int no;
		cin >> no;
		switch (no) { case(1):home_page(); case(0):break; }
		
	}
	
	cout << endl << "please enter password : \t";
	cin >> password;
	for (i; i <users.size(); i++)
	{

		if (users[i].email == email)
		{
			while (1)
			{
				if (users[i].password == password)
				{

					flag = true;

					//// break for while 
					break;
				}
				else
				{
					cout << endl << "please enter password : \t";
					cin >> password;
				}
			}

			//// break the for loop
			if (flag == true)
				break;
		}
	}
	if (flag == true) {
		///// call the function 

		users[i].display();

		////////////

	}


}

void home_page()
{
	int y=load_data();
	int x;
	cout << "welcome to Our social media network" << endl
		<< " if you want to creat new account please enter  ( 1) " << endl
		<< "if you want to sign in please enter ( 0) " << endl << endl << endl << "if you want to save and exit enter (2)" << endl;
	

	cin >> x;
	if (x == 1)
	{
		creat_account();
	}
	else if (x == 0)
	{
		sign_in();
	}
	else if (x == 2)
	{
		save_and_exit();
	}
	

}

void user::display() {
	int no;
	cout << "if you what to show  your posts press 0" << endl
		<< "if you want to show friends posts press 1" << endl
		<< "if want to write posts press 2" << endl
		<< "if want to sign out press 3" << endl
		<< "if you want to add friend press 4" << endl
		<< "if you want to show your friends list please press 5" << endl;

	cin >> no;
	switch (no)
	{
	case 0:
		this->show_my_posts();
		break;
	case 1:
		this->show_posts();
		break;
	case 2:
		this->write_post();
		break;
	case 3:
		this->sign_out();
		break;
	case 5:
		this->show_my_friends_list();
		break;
	case 4:
		string email;
		cout << "please the enter the friend email" << endl;
		cin >> email;
		this->add_friend(email);
		break;


	}
}


void user::show_my_posts() {

	for (int i = 0; i<this->my_posts.size(); i++)
		cout << "index :" << i << endl << this->my_posts[i].txt << endl << "likes : "
		<< this->my_posts[i].no_likes << endl;


	cout << "if you want to like please enter 0  " << endl
		<< "if you want to go back please enter 1 " << endl;
	int b;
	cin >> b;
	switch (b) {
	case 0:
		cout << "please inter the index of the post you want to like " << endl;
		int y;
		cin >> y;
		this->like_post(this->my_posts[y]);

	case 1: display();

	}
}


void user::like_post(post x)
{


	int owner;
	string liker_name;
	owner = x.owner_ID;

	for (int i = 0; i<users[owner].my_posts.size(); i++)
	{
		cout << users[owner].my_posts[i].txt << endl << x.txt << endl;

		if (users[owner].my_posts[i].txt == x.txt)
		{
			users[owner].my_posts[i].no_likes++;
			users[owner].my_posts[i].name_likes.push_back(this->name);
		}
	}


}

void user::comment_post(post x)
{
	comment newcomment;
	int owner=x.owner_ID;
	
	for (int i = 0; i<users[owner].my_posts.size(); i++)
	{
		//cout << users[owner].my_posts[i].txt << endl << x.txt << endl;

		if (users[owner].my_posts[i].txt == x.txt)
		{
			cout << "type your comment...";
			cin >> newcomment.text;
			//newcomment.owner = this->name;
			users[owner].my_posts[i].comments.push_back(newcomment);
			break;
		}
	}
	
}

void user::show_posts()
{

	vector <post> all_posts;


	for (auto i = friend_list[this->ID].begin(); i != friend_list[this->ID].end(); ++i)
	{
		int ID_friend = *i;
		cout << users[ID_friend].my_posts[0].txt;

		all_posts.reserve(all_posts.size() + users[ID_friend].my_posts.size());
		all_posts.insert(all_posts.end(), users[ID_friend].my_posts.begin(), users[ID_friend].my_posts.end());

	}

	for (int i = 0; i<all_posts.size(); i++)
	{
		cout << "index no." << i << ":" << endl << all_posts[i].txt << endl << "likes : " << all_posts[i].no_likes << endl;

	}

	cout << "if you want to like please enter 0 " << endl
		<< "press 1 if you want to go back " << endl;
	int b;
	cin >> b;
	switch (b) {
	case 0:
		int y;
		cout << "please enter index of the post : ";
		cin >> y;
		this->like_post(all_posts[y]);

	case 1: display();

	}
}

void user::write_post() {

	string my_new_post;
	cout << "enter your post " << endl;
	cin.ignore();
	getline(cin, my_new_post);
	post new_post;
	new_post.txt = my_new_post;
	new_post.no_likes = 0;
	new_post.owner_ID = this->ID;

	users[this->ID].my_posts.push_back(new_post);

	this->display();
}

void user::sign_out() {
	//save_and_exit();
	system("CLS");
	home_page();
}


void user::show_my_friends_list()
{
	for (auto i = friend_list[this->ID].begin(); i != friend_list[this->ID].end(); ++i)
	{
		int friend_ID = *i;
		cout << users[friend_ID].name << endl;

	}
	this->display();


}

void save_and_exit()
{
	
	XMLNode *root = database.NewElement("USERS_Data");
	database.InsertFirstChild(root);
	u_size = users.size();
	for (int i = 0; i < users.size(); i++)
	{
		XMLElement *new_user = database.NewElement("User");
		//new_user->SetAttribute("no", users[i].ID);

		XMLElement *ID = database.NewElement("ID");//list of each user data
		ID->SetText(users[i].ID);
		new_user->InsertEndChild(ID);

		XMLElement *name = database.NewElement("name");
		name->SetText(users[i].name.c_str());
		new_user->InsertEndChild(name);

		XMLElement *email = database.NewElement("email"); //list of each user data
		email->SetText(users[i].email.c_str());
		new_user->InsertEndChild(email);

		XMLElement *password = database.NewElement("password"); //list of each user data
		password->SetText(users[i].password.c_str());
		new_user->InsertEndChild(password);

		XMLElement *posts = database.NewElement("posts");
		for (int j = 0; j < users[i].my_posts.size(); j++)
		{
			XMLElement *new_post = database.NewElement("post");
			//new_post->SetAttribute("no",j);

			XMLElement *owner = database.NewElement("owner");
			owner->SetText(users[i].my_posts[j].owner_ID);
			new_post->InsertEndChild(owner);

			XMLElement *txt = database.NewElement("txt");
			txt->SetText(users[i].my_posts[j].txt.c_str());
			new_post->InsertEndChild(txt);

			XMLElement *likes = database.NewElement("no_likes");
			likes->SetText(users[i].my_posts[j].no_likes);
			new_post->InsertEndChild(likes);

			XMLElement *likers = database.NewElement("likers");
			for (int k = 0; k < users[i].my_posts[j].name_likes.size(); k++)
			{
				XMLElement * liker = database.NewElement("liker");
				liker->SetText(users[i].my_posts[j].name_likes[k].c_str());
				likers->InsertEndChild(liker);
			}
			new_post->InsertEndChild(likers);
			//msh mrkza dlwa2ytyy
			/*XMLElement *comments = database.NewElement("comments");*/
			/*for (int k = 0; k < users[i].my_posts[j].comments.size(); k++)
			{
				XMLElement * comment = database.NewElement("comment");
				comment->SetText(users[i].my_posts[j].comments[k].owner);
				comments->InsertEndChild(comment);
			}*/
			//new_post->InsertEndChild(comments);

			posts->InsertEndChild(new_post);

		}
		new_user->InsertEndChild(posts);

		XMLElement *friendslist = database.NewElement("friendslist");
		for (int l=0;l<friend_list[i].size();l++)
		{
			
			XMLElement *friends= database.NewElement("friends");
			friends->SetText(friend_list[i][l]);
			friendslist->InsertEndChild(friends);

		}
		new_user->InsertEndChild(friendslist);


		root->InsertEndChild(new_user);
	}
	//users_size = users.size();
	database.SaveFile("data.xml");
}
void load_data()
{


	XMLDocument xmlDoc2;
	XMLError eResult2 = xmlDoc2.LoadFile("data.xml");
	XMLCheckResult(eResult2);



	//bool found = false;
	//XMLError eResult2 =database.LoadFile("data.xml");
	////XMLCheckResult(eResult2);
	//XMLNode * root = database.FirstChild(); //users_Data
	//XMLElement* new_user = root->FirstChildElement("User");
	////users.resize(1000);
	//for( int i=0;new_user != nullptr ;i++)
	//{
	//	user u;
	//	XMLElement* ID = new_user->FirstChildElement("ID");
	//	ID->QueryIntText(&u.ID);
	//	
	//	string n;
	//	XMLElement *name = new_user->FirstChildElement("name");
	//	name->Attribute(n.c_str());

	//	XMLElement *email = new_user->FirstChildElement("email");
	//	name->Attribute(u.email.c_str());

	//	users.push_back(u);
	//	new_user = root->NextSiblingElement("User");
	//}
	
}

int main()
{

	home_page();
	system("pause");
	return 0;


}




