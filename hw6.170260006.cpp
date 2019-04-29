#include <iostream>
#include <vector>
// #include <queue>
#include <set>
#include <algorithm>
using namespace std; 
  
struct vertex
{
    int id;
    int colour = 0;
    int n_ucolour_nbors = 0;
    vector <vertex*> nbors; 
    vertex(int id_this){
        id = id_this;
    }

    bool operator<(const vertex & v) const {
        if(n_ucolour_nbors == v.n_ucolour_nbors) return id<v.id;
        else return n_ucolour_nbors < v.n_ucolour_nbors;
    }
};

void addEdge(vertex &u, vertex &v) 
{   
    u.nbors.push_back(&v);
    u.n_ucolour_nbors++;
    v.nbors.push_back(&u);
    v.n_ucolour_nbors++;
 
} 

struct classcomp {
  bool operator() (vertex* const& lhs, vertex* const& rhs) const
  {return (*lhs) < (*rhs);}
};

int main() 
{ 
    int V,E;
    cin>>V;cin>>E;
    vector<vertex> vec_of_v; 
    for (int i=0; i<V; i++){
        vec_of_v.push_back(vertex(i));
    }
    for (int i=0; i<E; i++){
        int u,v;
        cin>>u; cin>>v;
        addEdge(vec_of_v[u], vec_of_v[v]);
    }

    set <vertex*,classcomp> set_pvertex;
    
    for (size_t i=0; i<vec_of_v.size(); i++){
        set_pvertex.insert(&vec_of_v[i]);
        
    }

    while(!set_pvertex.empty()){
        vertex* ptop_vertex = *set_pvertex.begin();
        int max_colour =0;

        set<int> set_colours;
        set_colours.insert(0);
        for (size_t i=0; i<ptop_vertex->nbors.size(); i++){
            vertex* pthis_vertex = ptop_vertex->nbors[i];
            max_colour = max(max_colour,pthis_vertex->colour);
            if(pthis_vertex -> colour==0){
                set_pvertex.erase(pthis_vertex);
                pthis_vertex -> n_ucolour_nbors --;
                set_pvertex.insert(pthis_vertex);
            }
            else{
                set_colours.insert(pthis_vertex -> colour);
            }
        }
        set<int>::iterator it;
        for (it =set_colours.begin(); it != set_colours.end(); ++it) {
            if(*it+1 != *next(it)){
                ptop_vertex->colour = *it+1;
                break;
            }
            if(next(it)==set_colours.end()){
                ptop_vertex -> colour = *it+1;
                cout<<"chose new color "<<*it+1<<endl;
            }
        }
        set_pvertex.erase(ptop_vertex);
    }
    
    for (int i=0; i<V; i++){
        cout<<vec_of_v[i].colour<<' ';
    }

    return 0; 
}