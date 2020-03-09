#include "class_definition.h"
#include "headers_and_prototypes.h"

void Word::Set_word(char *w,int c,int l)
{
	count=c;length=l;
	char *temp=new char[l+1];
	strcpy(temp,w);
	word=temp;
}

void Word::switch_word(Word &w)
{
    char *temp=this->word;
    int c=this->count,l=this->length;
    this->word=w.word;this->count=w.count;this->length=w.length;
    w.word=temp;w.count=c;w.length=l;
}

bool Word::operator < (const Word &w) const
{
    for(int i=0;i<(this->length)&&i<(w.length);i++){
        if(islower(this->word[i])&&isupper(w.word[i])) return true;
        else if(isupper(this->word[i])&&islower(w.word[i])) return false;
        else if(isalpha(this->word[i])&&'\''==w.word[i]) return true;
        else if(isalpha(w.word[i])&&'\''==this->word[i]) return false;
        else if((this->word[i])<w.word[i]) return true;
        else if((this->word[i])>w.word[i]) return false;
    }
    if(this->length<w.length) return true;
    else return false;
}

