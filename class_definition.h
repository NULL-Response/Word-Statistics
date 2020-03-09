#ifndef CLASS_DEFINITION_H_INCLUDED
#define CLASS_DEFINITION_H_INCLUDED

#include<string.h>
#include<fstream>
#include<iostream>

class Word
{
		char *word;//the word itself
		int count,length;//the times it appears, and the length of it
	public:
	    Word(){word=NULL;count=0;length=0;}
		Word(char *w,int c,int l){Set_word(w,c,l);}
		char *Get_word() const{return word;}
		int Get_count() const{return count;}
		int Get_length() const{return length;}
		void Show_word(const int &mode1,const std::string &result_file) const//if mode1==0, don't print the length; if mode1==1, do
		{
		    using namespace std;
			ofstream fout(result_file.c_str(),ios::app);
			if(!fout) {cout<<"结果文件打开失败，退出中。";return;}
			if(mode1==0) fout<<word<<'\t'<<count;
			else if(mode1==1) fout<<word<<'\t'<<count<<'\t'<<length;
			fout.clear();fout.close();
		}
		void Set_word(char *w,int c,int l);
		void Set_word(const int &c){count=c;}
		void switch_word(Word &w);//switch this Word object with w
		bool operator < (const Word &w) const;
		~Word(){delete word;}
};

#endif // CLASS_DEFINITION_H_INCLUDED
