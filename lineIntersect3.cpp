#include <simplecpp>
#include <set>
#include <algorithm>

template <typename T>
void exchange(T &f, T& s){ T t = f; f = s; s = t;}

struct point{
  double x,y;
  bool operator==(const point &other){ return x == other.x && y == other.y;}
};

int orientation(point p, point q, point r){
  // crossProduct(pq,pr) using determinant.
  double val = (q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y);
  if (val == 0) return 0;  // p, q, r are collinear
  if (val > 0) return 1;   // p, q, r are clockwise
  else return 2;           // p, q, r are counterclockwise
}

struct seg{
  point top, bottom;
  bool operator<(const seg & rhs) const{
    bool res;
    if(top.y < rhs.top.y)
      res = orientation(top, bottom, rhs.top) == 2;
    else
      res = orientation(rhs.top, rhs.bottom, top) == 1;
    cout <<top.x<<','<<top.y<<"   "<<rhs.top.x<<','<<rhs.top.y<<": "<<res<<endl;
    return res;
  }
};

struct ptseg{
  point pt; size_t segIndex;
  ptseg(point pp, size_t i){pt = pp; segIndex = i;}
};

bool intersect(seg l1, seg l2){
  int o1 = orientation(l1.top, l1.bottom, l2.top);
  int o2 = orientation(l1.top, l1.bottom, l2.bottom);
  int o3 = orientation(l2.top, l2.bottom, l1.top);
  int o4 = orientation(l2.top, l2.bottom, l1.bottom);
 
  bool r = (o1 != o2 && o3 != o4);     // only General case
  //  cout << r << endl;
  return r;
}

void print(vector<seg> &al){
  for(auto l : al)
    cout <<'('<<l.top.x<<','<<l.top.y<<' '
	 <<l.bottom.x<<','<<l.bottom.y<<") ";
  cout << endl;
}

int main(){
  vector<seg> segs;
  initCanvas("segs",800,800);
  while(true){
    seg s;
    int click = getClick(); s.top.x=click/65536, s.top.y=click%65536;
    if(s.top.x < 10 and s.top.y < 10) break; // top corner to end input
    click = getClick(); s.bottom.x=click/65536, s.bottom.y=click%65536;
    Line(s.top.x, s.top.y, s.bottom.x, s.bottom.y).imprint();
    segs.push_back(s);
  }  

  for(seg &l : segs)  // Make sure top is really above.
    if(l.top.y > l.bottom.y) exchange(l.top,l.bottom);

  print(segs);

  vector<ptseg>ptls; // Endpoints with link back to segments
  for(size_t i=0; i<segs.size(); i++){
    ptls.push_back(ptseg(segs[i].top, i));
    ptls.push_back(ptseg(segs[i].bottom, i));
  }

  sort(ptls.begin(),ptls.end(),  // sort top to bottom
       [](ptseg &p, ptseg &q)
       {return p.pt.y < q.pt.y;});

  set<seg> S;
  bool found = false;
  for(auto p : ptls){
    Line(0,p.pt.y,800,p.pt.y).imprint(); wait(1);
    if(p.pt == segs[p.segIndex].top){  // top endpoint
      S.insert(segs[p.segIndex]);
      cout << "inserted "<<segs[p.segIndex].top.x<<','
	   <<segs[p.segIndex].top.y<<endl;
      auto l = S.find(segs[p.segIndex]);
      //      cout << "found"<<endl;
      if(next(l) != S.end() && intersect(*l, *next(l))){
	found = true; break;
      }
      cout << "Checked next intersection.\n";
      //      if(prev(l) != S.end() && intersect(*l, *prev(l))){
      if(l != S.begin() && intersect(*l, *prev(l))){
	found = true; break;
      }
      cout << "Checked prev intersection.\n";
    }
    else{  // bottom endpoint
      auto l = S.find(segs[p.segIndex]);
      if(next(l) != S.end() && prev(l) != S.end()
	 && intersect(*prev(l), *next(l))){
	found = true; break;
      }
      S.erase(l);
    }
  }
  cout <<"intersection: "<<found<<endl;
  getClick();
}

