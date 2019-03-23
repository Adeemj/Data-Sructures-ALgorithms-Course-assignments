#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

void print_vector(vector<int>& );

vector<string> process(vector<string> v){
    for (size_t i = 0;i<v.size();i++){
        if ((v[i].back()=='.') || (v[i].back()==',') || (v[i].back()==':'))v[i].pop_back();
        transform(v[i].begin(), v[i].end(), v[i].begin(), ::tolower);
    }
    //v.pop_back()
    return v;
}

map<string,vector<int>> construct_index(vector<string>& v){
    map<string,vector<int>> index;
    for (size_t i = 0;i<v.size();i++){
        if(index.count(v[i])>0) index[v[i]].push_back(i);
        else {
            vector<int> temp;
            temp.push_back(i);
            index[v[i]] = temp;
        }
    }
    return index;
}

vector<vector<int>> construct_v_of_v(map<string,vector<int>>& m, vector<string>& v_of_str){
    vector<vector<int>> v;
    for (size_t i=0; i<v_of_str.size();i++){
        v.push_back(m[v_of_str[i]]);
    }
    return v;
}

vector<int> location_of_phrase(vector<string>& s, map<string,vector<int>>& m){
    vector<vector<int>> v_of_v = construct_v_of_v(m,s);
    vector<int> v = v_of_v[0];
    for(size_t i=1; i<v_of_v.size(); i++){
        vector<int> temp ;
        size_t j=0,k=0;
        while(j<v.size()){
            //cout<<"j = "<<j<<endl;
            while(v_of_v[i][k]<v[j]+1)k++;
            if (v_of_v[i][k]==v[j]+1){
                temp.push_back(v_of_v[i][k]);
                k++;
            }
            j++;
            //cout<<"j = "<<j<<endl;
        }
        v = temp;
    }
    for(size_t i=0; i<v.size();i++){
        v[i] = v[i] - s.size() + 1;
    }
    return v;
}

void print_vector(vector<int>& v){
    for(size_t i=0; i<v.size();i++){
        cout<<v[i]<<' ';
    }
    cout<<endl;
}

int main(){
//vector<string>a = read_into_vector();
string word;
vector<string> document,phrase;
bool flag = 0;
while(cin>>word){
    if (word=="*"){
        flag = 1;
        continue;
    }
    if (!flag)document.push_back(word);
    else phrase.push_back(word);
}

document = process(document);
phrase = process(phrase);

map<string,vector<int>>m = construct_index(document);

for(auto cNp : m)
{
  cout << cNp.first << " ";
  print_vector(cNp.second);
}
cout<<"* ";

vector<int> output = location_of_phrase(phrase,m);
print_vector(output);

}
