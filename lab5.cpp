#include <bits/stdc++.h>
using namespace std;

int prec(char c)
{
    if(c == '^')
    return 3;
    else if(c=='$')
	return 4;
    else if(c == '*' || c == '/')
    return 2;
    else if(c == '+' || c == '-')
    return 1;
    else
    return -1;
}
struct node{
	int x;
	char opr;
	bool b;
};
struct et{
	node val;
	et * left;
	et * right;
};

et * make_tree(vector<node>v){
	stack<et *> s;
	et *t, *t1, *t2;
	for(int i=0;i<v.size();i++){
		if(v[i].b){
			t=new et;
			t->val=v[i];
			t1=s.top();
			s.pop();
			t2=s.top();
			s.pop();
			t->right=t1;
			t->left=t2;
			s.push(t);
		}
		else{
			t=new et;
			t->val=v[i];
			t->left=NULL;
			t->right=NULL;
			s.push(t);
		}
	}
	return s.top();
}
stack<node>st;
vector<node> intopost(vector<node>v){
	vector<node> ans;
 for(int i=0;i<v.size();i++){
		if(v[i].b){
			char c=v[i].opr;
			if(c=='('){
				st.push(v[i]);
			}
			else if(c==')'){
				while(st.top().opr!='('){
					ans.push_back(st.top());
					st.pop();
				}
				st.pop();
			}
			else{
				while(st.top().opr!='('&&prec(c)<=prec(st.top().opr)){
					if(prec(c)==3&&prec(st.top().opr)==3) break;
					if(prec(c)==4&&prec(st.top().opr)==4) break;
					ans.push_back(st.top());
					st.pop();
				}

				st.push(v[i]);
			}
		}
		else{
			ans.push_back(v[i]);
		}
	}
	return ans;

}
int eval(et * root){
	if(root==NULL) return 0;
	if(root->left==NULL&&root->right==NULL){
		return root->val.x;
	}
	int l=eval(root->left);
	int r=eval(root->right);
	if(root->val.opr=='+') return l+r;
	else if(root->val.opr=='-'||root->val.opr=='$') return l-r;
	else if(root->val.opr=='*') return l*r;
	else if(root->val.opr=='/') return l/r;
	else return pow(l,r);
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;

		vector<string> key;
		vector<int> val;
		while(n--){
			string var="",curr_var="";
			string s="(";
			string tmps;
			cin>>tmps;
			int c=1; int check=1;
			for(int i=0;i<tmps.size();i++){
				if(!(tmps[i]>='a'&&tmps[i]<='z'||tmps[i]>='A'&&tmps[i]<='Z')&&(tmps[i]!='=')){
					if(curr_var.size()!=0){
						int x=-1;
						for(int j=0;j<key.size();j++){
							if(key[j]==curr_var){
								x=j; break;
							}
						}
						if(x==-1) {cout<<"CANT BE EVALUATED"<<endl; check=0;}
						else {s+=to_string(val[x]); curr_var="";}
					}
				}
				if(tmps[i]>='0'&&tmps[i]<='9'){
					c=0;
					s+=tmps[i];
				}
				else if(tmps[i]=='('||tmps[i]==')'){
					s+=tmps[i];
				}
				else if(tmps[i]>='a'&&tmps[i]<='z'||tmps[i]>='A'&&tmps[i]<='Z'){
					curr_var+=tmps[i];
				}
				else if(tmps[i]=='='){
					var=curr_var;
					curr_var="";
					continue;
				}
				else{
					if(c!=0&&tmps[i]=='-'){
						s+="0$";
					}
					else s+=tmps[i];
					c++;
				}
				if(check==0) break;
			}

			if(curr_var.size()!=0){

				int x=-1;
				for(int j=0;j<key.size();j++){
					if(key[j]==curr_var){
						x=j; break;
					}
				}
				if(x==-1){ cout<<"CANT BE EVALUATED"<<endl; check=0;}
				else {s+=to_string(val[x]); curr_var="";}

			}
			if(check==0) continue;
			s+=')';
			int a=0,o=0;
			string curr="";
			vector<node> v;
			for(int i=0;i<s.size();i++){
				if(s[i]>='0'&&s[i]<='9'){
					curr+=s[i];
				}
				else{
					if(!curr.size()&&s[i]=='-'){
						curr+=s[i];
					}
					else if(curr.size()==1&&curr[0]=='-'){
						curr+='1';
						s[i-1]='*';
						i-=2;
					}
					else {
						if(curr.size()){
						node n;
						n.b=0;
						n.x=stoi(curr);
						v.push_back(n);
          }
						curr="";
						node n;
						n.opr=s[i];
						n.b=1;
						v.push_back(n);
					}
				}
			}
			if(curr.size()){
				node n;
				n.b=0;
				n.x=stoi(curr);
				v.push_back(n);
			}
			vector<node> post=intopost(v);
			et * root=make_tree(post);
			if(var.size()==0)cout<<eval(root)<<endl;
			else{

				key.push_back(var);
				val.push_back(eval(root));
			}
		}
	}
	return 0;
}
