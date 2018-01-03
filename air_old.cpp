#include <iostream>
#include <vector>
#include <map>
#include "EK.cpp"
using namespace std;

struct aresta{
  int n;
  int lw; //lower bound
  int cap;//capacity
  aresta(int to,int c){
    n=to;
    cap=c;
    lw=0;
  }
  aresta(){}
};
struct node{
  int ciutat;
  int hora;
  int demanda;
  node(int c,int h){
    ciutat=c;
    hora=h;
    demanda=0;
  }
  node(){}
};
void print_estat (const vector<node> & n,const vector<vector<aresta> > &g){
  for (int i=0;i<n.size();i++){
    switch(i){
      case 0:
        cout<<"Real source: "<<endl;
        break;
      case 1:
        cout<<"Real sink: "<<endl;
        break;
      case 2:
        cout<<"Demands source: Demanda: "<<n[i].demanda<<endl;
        break;
      case 3:
        cout<<"Demands sink: Demanda: "<<n[i].demanda<<endl;
        break;
      default:
        cout<<endl<<"Node "<<i;
        if (i%2==0) cout<<" (Origen)";
        else cout<<" (Destí)";
        cout<<" :"<<endl;
        cout<<"(Ciutat: "<<n[i].ciutat<<",Hora: "<<n[i].hora<<",Demanda: "<<n[i].demanda<<")"<<endl;
        break;
    }
    for (int j=0;j<g[i].size();j++){
      cout<<"aresta"<<j<<":";
      cout<<" ("<<g[i][j].n<<",low: "<<g[i][j].lw<<" ,cap: "<<g[i][j].cap<<" ) "<<endl;
    }
  }
}
/*
  afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
  per tot node destí comprobem per tot node origen si es possible fer transició
  cost n * n on n son els vols
*/
void version1 (const vector<node> & n, vector<vector<aresta> > &g){
  for (int i=5;i<n.size();i+=2){//i es desti
    for (int j=4;j<n.size();j+=2){//j es origen
      if (j!=i-1){ //per evitar fer calculs sobre el mateix vol
        if (n[i].ciutat==n[j].ciutat and n[j].hora - n[i].hora >=15){
          //aresta del desti i al origen j amb pes 1
          g[i].push_back(aresta(j,1));
        }
      }
    }
  }
}
/*
  elimina els lower bound de les arestes i actualitza les demandes
  les uniques arestes amb lower suerten de les ciutats d'origen
*/
void elimina_lower( vector<node> & n, vector<vector<aresta> > &g){
  for (int i=4;i<n.size();i+=2){
    //la primera aresta es la del viatge
    g[i][0].cap=g[i][0].cap-g[i][0].lw;
    g[i][0].lw=0;
    //sumo 1 a la demanda de l'origen, i resto 1 a la de destí
    n[i].demanda+=1;
    n[i+1].demanda-=1;
  }
}
/*
  elimina les demandes  i actualizta el sink i drain reals amb les
  arestes necessaries
*/

void elimina_demanda( vector<node> & n, vector<vector<aresta> > &g){
  for (int i=2;i<n.size();i++){
    if (n[i].demanda>0){ // si demanda >0 es un sink i va a t
      g[i].push_back(aresta(1,n[i].demanda));
      n[i].demanda=0;
    }
    else if (n[i].demanda<0){ // si es source s va a el
      g[0].push_back(aresta(i,-n[i].demanda));
      n[i].demanda=0;
    }
  }
}

void transforma_max( vector<node> & n, vector<vector<aresta> > &g){
  int gr[16][16];
  for (int u = 0; u < 16; u++)
      for (int v = 0; v < 16; v++)
           gr[u][v]=0;
  cout<<"ok"<<endl;
  for(int i=0;i<n.size();i++){
    for (int j=0;j<g[i].size();j++){
      gr[i][g[i][j].n]=g[i][j].cap;
    }
  }
  cout<<"Max flow: "<<endl;
  cout<<endl<<EdmondKarp(gr,0,1)<<endl;
}
int main(){
  int o,d,h1,h2;
  //estructura de dades per guardar les arestes
  vector<vector<aresta> > graf(4);//sources and sinks
  //graf [0] source without demands
  //graf [1] sink without demands
  //graf [2] source with demands
  //graf [3] sink with demands

  //nodes
  vector<node> nodes(4);

  int i=4;
  while(cin>>o>>d>>h1>>h2){
    //operacions descrites a la pagina 390 del llibre
    //afegeix  el node de la ciutat d'origen
    nodes.push_back(node(o,h1));
    //afegeix el node de la ciutat de destí
    nodes.push_back(node(d,h2));
    //afegeix l'aresta entre vols
    graf.push_back(vector<aresta>(1,aresta(i+1,1)));
    graf[i][0].lw=1;
    //afegeix l'aresta del source al origen
    graf[2].push_back(aresta(i,1));
    //afegeix l'aresta del desti al sink
    graf.push_back(vector<aresta>(1,aresta(3,1)));
    i+=2;
  }
  //TODO Falta la aresta de s a t amb capacitat k
  int k=2;
  graf[2].push_back(aresta(3,k));
  nodes[2].demanda=-k;
  nodes[3].demanda=k;
  //afegir arestes si es pot arribar d'un vol a un altre
  version1(nodes,graf);
  //eliminar els lower bound
  elimina_lower(nodes,graf);
  //eliminar les demandes
  elimina_demanda(nodes,graf);
  print_estat(nodes,graf);
  transforma_max(nodes,graf);
  //print_estat(nodes,graf);


}
