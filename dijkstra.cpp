#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;



class Dijsktra{

    public:
    string file_address;
    struct node{
        int node_number;
        int visited;
        int distance;
        vector<vector<int>> edges;
    };
    map<int,node> graph;
    vector<int> assigned;

    Dijsktra(string f_address){
        file_address=f_address;
        set_adj();
        graph.find(1)->second.distance=0;
        graph.find(1)->second.visited=1;
        assigned.push_back(1);
        
    }

    void set_adj(){
        ifstream infile;
        string row;
        string edge_info;
        string edge_info_parsed;
        int n;
        int n2;
        int weight;
        vector<int> edge;

        infile.open(file_address);

        while(infile.good()){
            getline(infile,row);
            stringstream ss(row);
            ss>>n;
            node new_node;
            new_node.node_number = n;
            new_node.visited=0;
            while(ss.good()){
                ss>>edge_info;
                stringstream sss(edge_info);
                getline(sss,edge_info_parsed,',');
                n2=stoi(edge_info_parsed);
                getline(sss,edge_info_parsed,',');
                weight=stoi(edge_info_parsed);
                edge = {n2,weight};
                new_node.edges.push_back(edge);

            }
                
            graph.insert(pair<int,node>(n, new_node));

        }    

        infile.close();

    }

    void find_min_distance(){
        for (int i=1; i<200; i++ ){
            int new_distace = INT_MAX;
            int new_node;
            for (int j=0; j<assigned.size(); j++){
                int node = assigned[j];
                int distance = graph.find(node)->second.distance;
                vector<vector<int>> edges = graph.find(node)->second.edges;
                for (int k=0; k<edges.size(); k++){
                    vector<int> edge = edges[k];
                    int head_node = edge[0];
                    int dis = edge[1];
                    if(graph.find(head_node)->second.visited==0){ 
                        if (new_distace>distance+edge[1]){
                            new_distace = distance+edge[1];
                            new_node = edge[0];
                        }
                    }
                }
            }

            assigned.push_back(new_node);
            graph.find(new_node)->second.distance = new_distace;
            graph.find(new_node)->second.visited = 1; 

        }


    }
    

};

void print_vector(vector<vector<int>> &V){
    for (int i; i<V.size(); i++){
        cout<<endl;
        for (int j=0; j<V[i].size(); j++){
            cout<<V[i][j]<<',';
        }
    }
}

int main(){
    string file_address = "G:\\My Drive\\course\\Algorithm\\Dijkstra\\DijkstraData.txt";
    Dijsktra djk(file_address);
    djk.find_min_distance();
    vector<int> report = {7,37,59,82,99,115,133,165,188,197};
    for(int i=0; i<report.size(); i++){
        cout <<djk.graph.find(report[i])->second.distance<<',';
    }
    cout<<endl<<djk.graph.find(1)->second.distance;
    return 0;
}