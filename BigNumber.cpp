#include<iostream>
#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

struct BigNumber{
    static const int BASE=1e8;
    static const int WIDTH=8;
    vector<int> s;

    BigNumber(long long num=0){*this=num;}

    //如何理解a=b？ 答：a.operator=(b)
    BigNumber operator = (long long num){
        s.clear();
        do{
            s.push_back(num%BASE);
            num/=BASE;
        }while(num>0);
        return *this;
    }
    BigNumber operator = (const string& str){
        s.clear();
        int x,len=(str.length()-1)/WIDTH+1;
        for(int i=0;i<len;i++)
        {
            int end=str.length()-i*WIDTH;
            int start=max(0,end-WIDTH);
            sscanf(str.substr(start,end-start).c_str(),"%d",&x);
            s.push_back(x);
        }
        return *this;
    }


    //如何理解cout<<a？ 答：operator<<(cout,a)
    //如何理解cin>>a？ 答：operator>>(cin,a)
    friend ostream& operator << (ostream& out,const BigNumber& x){
        out<<x.s.back();
        for(int i=x.s.size()-2;i>=0;i--){
            char buf[20];
            sprintf(buf,"%08d",x.s[i]);
            for(int j=0;j<strlen(buf);j++) out<<buf[j];
        }
        return out;
    }
    friend istream& operator >> (istream& in,BigNumber& x){
        string s;
        if(!(in>>s)) return in;
        x=s;
        return in;
    }


    //如何理解a+b？ 答：a.operator+(b)
    BigNumber operator + (const BigNumber &b){
        BigNumber c;
        c.s.clear();
        for(int i=0,g=0;;i++)
        {
            if(g==0&&i>=s.size()&&i>=b.s.size()) break;
            int x=g;
            if(i<s.size()) x+=s[i];
            if(i<b.s.size()) x+=b.s[i];
            c.s.push_back(x%BASE);
            g=x/BASE;
        }
        return c;
    }
    //如何理解a+=b？ 答：a.operator+=(b)
    BigNumber operator += (const BigNumber &b){
        *this = *this + b;
        return *this;
    }    

    //如何理解a<b？ 答：a.operator<(b)
    bool operator < (const BigNumber &b)const{
        if(s.size()!=b.s.size()) return s.size()<b.s.size();
        for(int i=s.size()-1;i>=0;i--)
        {
            if(s[i]!=b.s[i]) return s[i]<b.s[i];
        }
        return false;//相等
    }
    bool operator > (const BigNumber &b)const{
        return b < *this;
    }
    bool operator <= (const BigNumber &b)const{
        return !(b < *this);
    }
    bool operator >= (const BigNumber &b)const{
        return !(*this < b);
    }
    bool operator != (const BigNumber &b)const{
        return b<*this || *this < b;
    }
    bool operator == (const BigNumber &b)const{
        return !(b<*this || *this < b);
    }
};
int main()
{
    BigNumber a,b;
    a=56;
    b=25;
    cout<<a+b;
}
