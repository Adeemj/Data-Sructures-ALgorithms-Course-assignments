#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

struct point{
  double x,y;
  point(double x_coordinate = 0, double y_coordinate = 0){
    x = x_coordinate; 
    y = y_coordinate;
  }

  bool operator==(const point &other){ return x == other.x && y == other.y;};

};

struct circle{
  point centre,top,bottom;
  double radius;

  circle(point pt, double r = 0){
    centre = pt;
    radius = r;
    top = point(centre.x,centre.y-radius);
    bottom = point(centre.x,centre.y+radius);
  }

  
    bool operator<(const circle & rhs)const {
      bool res = centre.x < rhs.centre.x;
      return res;
    }
};

struct circle_y_endpoint{
  point pt; size_t circle_index;
  circle_y_endpoint(point initialise_pt, size_t i){
    pt = initialise_pt; circle_index = i;
  }
};

double distance(point pt1, point pt2){
  return sqrt(pow(pt1.x-pt2.x,2) + pow(pt1.y-pt2.y,2));
}

bool overlap(circle c1, circle c2){
  return distance(c1.centre,c2.centre) < (c1.radius+c2.radius);
}

void print(vector<circle> &v_circles){
  for(auto l : v_circles){

    cout<<'('<<l.centre.x<<','<<l.centre.y<<' '<<l.radius<<") "<<endl;
  }
}


int main(){
  vector<circle> circles;
  int i=0;
  double d,x,y,r;
  
  while(true){
      cin>>d;
      if(cin.eof()) break;
      if(i%3==0){x=d;}
      else if(i%3==1){y=d;}
      else {
          r=d;
          circles.push_back(circle(point(x,y),r));
      }
      i++;
  }

  vector<circle_y_endpoint> line_sweep; // Endpoints with link back to segments

  for(size_t i=0; i<circles.size(); i++){
    line_sweep.push_back(circle_y_endpoint(circles[i].top,i)) ;
    line_sweep.push_back(circle_y_endpoint(circles[i].bottom,i));
  }

  sort(line_sweep.begin(),line_sweep.end(),  // sort top to bottom
       [](circle_y_endpoint &p, circle_y_endpoint &q)
       {return p.pt.y < q.pt.y;});

  set<circle> S;
  bool found = false;

  
  for(auto p : line_sweep){

    if(p.pt == circles[p.circle_index].top){  // top endpoint
      S.insert(circles[p.circle_index]);

      auto l = S.find(circles[p.circle_index]);
      if(next(l) != S.end() && overlap(*l, *next(l))){
	      found = true; 
        break;
      }
      if(l != S.begin() && overlap(*l, *prev(l))){
	      found = true; 
        break;
      }
    }
    
    else{  // bottom endpoint
      auto l = S.find(circles[p.circle_index]);
      if(next(l) != S.end() && prev(l) != S.end() && overlap(*prev(l), *next(l))){
	      found = true; break;
      }
      S.erase(l);
    }
  }
  cout <<found<<endl;
}
