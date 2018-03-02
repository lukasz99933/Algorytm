#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Rpq
{
  Rpq(int r,int p,int q):
	  r(r),
	  p(p),
	  q(q)
	{}
  int r;
  int p;
  int q;
};

void wczytywanie(vector<Rpq> &dane_rpq,int n)
{
  int r,p,q;
  fstream plik("plik2.txt");
  if(plik.good())
  {
    plik>>n;
    while(plik>>r>>p>>q)
    {
      Rpq k(r,p,q);
      dane_rpq.push_back(k);
    }	    
  }
  plik.close();
}

int algorytm_Schrage(vector<Rpq> &N, int n)
{
  int t=0,Cmax=0;
  vector<Rpq> G;
  vector<Rpq> C=N;
  Rpq l(0,0,9999999);
  while(!G.empty() || !N.empty())
  {
    do{
    auto ik=min_element(N.begin(),N.end(),[](Rpq first,Rpq second){return first.r<second.r;});
    while(!N.empty() && (*ik).r<=t)
    {
      G.push_back(*ik);
      N.erase(ik);
      ik=min_element(N.begin(),N.end(),[](Rpq first,Rpq second){return first.r<second.r;});
      if((*ik).q>l.q)
      {
        l.p=t-(*ik).r;
	t=(*ik).r;
	if(l.p>0)
        {
          G.push_back(l);
        }
      }
    }
    if(G.empty())
    {
      t=(*ik).r;	    
    }
    }while(G.empty());
    auto e=min_element(G.begin(),G.end(),[](Rpq first,Rpq second){return first.q>second.q;});
    l=(*e);
    t=t+(*e).p;
    Cmax=max(Cmax,(t+(*e).q));
    G.erase(e);
  }
  return Cmax;
}

int main()
{
  vector<Rpq> dane_rpq;
  int n;
  wczytywanie(dane_rpq, n);
  cout << "Cmax to :" << algorytm_Schrage(dane_rpq,n)<<endl;
  return 0;
}
