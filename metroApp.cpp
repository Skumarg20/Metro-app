#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> adj[100];
#define pb push_back
map<string,int>mp;
map<int,string>i2s;
int sz;
vector<string>keys;
void addEdge(string a,string b,int dis){
    int x=mp[a];
    int y=mp[b];
    adj[x].pb({y,dis});
    adj[y].pb({x,dis});
}

void Create_Metro_map(){
    keys.pb("Noida Sector 62~B");
    keys.pb("Botanical Garden~B");
    keys.pb("Yamuna Bank~B");
    keys.pb("Rajiv Chowk~BY");
    keys.pb("Vaishali~B");
    keys.pb("Moti Nagar~B");
    keys.pb("Janak Puri West~BO");
    keys.pb("Dwarka Sector 21~B");
    keys.pb("Huda City Center~Y");
    keys.pb("Saket~Y");
    keys.pb("Vishwavidyalaya~Y");
    keys.pb("Chandni Chowk~Y");
    keys.pb("New Delhi~YO");
    keys.pb("AIIMS~Y");
    keys.pb("Shivaji Stadium~O");
    keys.pb("DDS Campus~O");
    keys.pb("IGI Airport~O");
    keys.pb("Rajouri Garden~BP");
    keys.pb("Netaji Subhash Place~PR");
    keys.pb("Punjabi Bagh West~P");

    for(int i=0;i<keys.size();i++){
        mp[keys[i]]=i;
        i2s[i]=keys[i];
    }
    sz=keys.size();
    addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
    addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
    addEdge("Yamuna Bank~B", "Vaishali~B", 8);
    addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
    addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
    addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
    addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
    addEdge("Huda City Center~Y", "Saket~Y", 15);
    addEdge("Saket~Y", "AIIMS~Y", 6);
    addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
    addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
    addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
    addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
    addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
    addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
    addEdge("DDS Campus~O", "IGI Airport~O", 8);
    addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
    addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
    addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
    //cout<<"\n***********************************************************************\n";
    
    
    
    return;
}

void displaystations(){
    
    for(int i=0;i<keys.size();i++){
        cout<<i+1<<". "<<keys[i]<<endl;
        
    }
    
}
vector<int>metro_map;
void dfs(int src,int par,vector<bool>&vis){
    vis[src]=1;
    metro_map.pb(src);
    for(auto x:adj[src]){
        if(!vis[x.first]){
            dfs(x.first,src,vis);
        }
    }
}
void displaymap(){
    vector<bool>vis(sz);
    dfs(0,-1,vis);
    for(int i=0;i<metro_map.size();i++){
        if(i!=metro_map.size()-1){
            cout<<i2s[metro_map[i]]<<"=> ";
        }
        else{
            cout<<i2s[metro_map[i]];
        }
    }
    cout<<endl;
}

int shortestdistance(int src,int dest){
    vector<int>dist(sz,INT_MAX);
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({src,0});
    while(!pq.empty()){
        auto x=pq.top();
        pq.pop();
        int dis=x.second;
        for(auto y:adj[x.first]){
            int vertex=y.first;
            int dis_ver=y.second;
            if(dist[vertex]>dis+dis_ver){
                dist[vertex]=dis+dis_ver;
                pq.push({vertex,dist[vertex]});
            }
        }
    }
    return dist[dest];
}

void bfs(vector<int>parent[],int src){
    vector<int>dist(sz,INT_MAX);
    queue<int>q;
    q.push(src);
    parent[src]={-1};
    dist[src]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto x:adj[u]){
            int v=x.first;
            int dis_v=x.second;
            if(dist[v]>dist[u]+dis_v){
                dist[v]=dist[u]+1;
                q.push(v);
                parent[v].clear();
                parent[v].push_back(u);
            }
            else if(dist[v]==dist[u]+dis_v){
                parent[v].push_back(u);
            }
        }
    }
}

void find_paths(vector<vector<int>>& paths,vector<int>& path,vector<int> parent[],int u){
    if(u==-1){
        paths.pb(path);
        return;
    }
    for(auto par:parent[u]){
        path.pb(u);
        find_paths(paths,path,parent,par);
        path.pop_back();
    }
}

void printpath(int src,int dest){
    vector<vector<int>>paths;
    vector<int>path;
    vector<int>parent[sz];

    bfs(parent,src);
    find_paths(paths,path,parent,dest);

    for(auto v:paths){
        reverse(v.begin(),v.end());
        for(int u:v){
            cout<<i2s[u]<<" => ";
        }
        cout<<endl;
        break;
    }
}

int main(){
    //displaystations();
    Create_Metro_map();

    cout<<"\n\t\t\t****WELCOME TO THE METRO APP*****\n";
    while(true){
        cout<<"\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout<<("1. LIST ALL THE STATIONS IN THE MAP\n");
        cout<<("2. SHOW THE METRO MAP\n");
        cout<<("3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        cout<<("4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        cout<<("5. GET SHORTEST PATH TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        cout<<("6. EXIT THE MENU\n\n");
        cout<<("\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 6) : \n");
        int choice;
        cin>>choice;
        if(choice==1){
            displaystations();
        }
        else if(choice==2){
            displaymap();
        }
        else if(choice==3){
            cout<<"Enter the serial no. of Source and Destination"<<endl;
            displaystations();
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            int p=shortestdistance(x,y);
            cout<<"Shortest distance between source and destination is "<<p<<"KM\n";
        }

        else if(choice==4){
            cout<<"Enter the serial no. of Source and Destination"<<endl;
            displaystations();
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            int p=shortestdistance(x,y);
            cout<<"Shortest distance between source and destination is "<<p<<"Minutes\n";
        }
        else if(choice==5){
            cout<<"Enter the serial no. of Source and Destination"<<endl;
            displaystations();
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            printpath(x,y);
        }
        else{
            break;
        }
    }
    
}
