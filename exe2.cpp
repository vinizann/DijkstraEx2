#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;
typedef pair<int, int> my_pair;

//funcao recursiva auxiliar para printar os vertices (cidades) do caminho de menor custo
void print_cidades(vector<int> previous, int v) {
    if(previous[v] == -1) {
        return;
    }
    print_cidades(previous, previous[v]); 
    cout << " -> " << v;
}

//imprime a solucao do problema
void print_menor_custo(int source, int destination, double cost, vector<int> previous) {
    cout << "Cidade de Origem: "  << source << endl; 
    cout << "Cidade de Destino: " << destination << endl;
    cout << "Custo da viagem: R$ " << cost << endl;
    cout << "Rota de menor custo: " << source;
    print_cidades(previous, destination);
    cout << endl;
}

//funcao dijkstra para calcular o menor custo da viagem
//recebe a lista de adjacencias do grafo, o numero de vertices, a origem e o destino, os valores do pedagio de cada cidade, o preco do combustivel e a autonomia do veiculo
void dijkstra(vector<my_pair> adj[], int V, int source, int destination, vector<double> pedagio, double preco_combustivel, double autonomia) {
    vector<double> custos; //vector para armazenar os custos da viagem ate cada vertice
    custos.assign(V, INF);
    vector<bool> visited; //vetor de bool para armazenar se um vertice ja foi visitado ou nao
    visited.assign(V, false);
    vector<int> previous; //armazenar os vertices (cidades) que compoem o caminho do menor custo da viagem
    previous.assign(V, -1);
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> my_pq; //fila de prioridades para armazenar os custos e os vertices (utilizando min-heap)

    //inicializa o custo da origem com 0 e insere a origem na fila de prioridades
    custos[source] = 0;
    my_pq.push({0, source});

    //enquanto a fila de prioridades nao estiver vazia, ira repetir ate os custos da viagem serem verificados
    while(!my_pq.empty()) { 
        int u = my_pq.top().second; //retorna o vertice que esta no topo da fila de prioridades
        my_pq.pop(); //retira da fila de prioridade o pair com menor custo    
        if(visited[u]) {
            continue; //se o vertice ja foi analisado, pula para a proxima iteracao
        }
        visited[u] = true;
        if(u == destination) { //se o vertice que esta sendo analisado eh o destino
            print_menor_custo(source, destination, custos[u], previous);
            return;
        }
        //percorre os vertices adjacentes ao qual esta analisando
        for(auto e : adj[u]) {
            //primeiro elemento 'v' eh o vertice adjacente
            //segundo elemento 'w' eh a distancia em Km do vertice atual 'u' ate esse vertice 'v' 
            int v = e.first;
            int w = e.second;
            //relaxamento: verifica se existe um caminho de menor custo do que o armazenado atualmente   
            if(custos[v] > ((custos[u] + (w / autonomia) * preco_combustivel) + pedagio[v])) { 
                custos[v] = (custos[u] + (w / autonomia) * preco_combustivel) + pedagio[v]; //atualiza a rota de menor custo
                previous[v] = u; //atribui para o vertice o seu antecessor que compoe a rota de menor custo
                my_pq.push({custos[v], v}); //adiciona na fila de prioridades o novo custo atualizado e o vertice v
            }
        }
    }
}

int main() {
    int V = 5;
    vector<my_pair> adj[V];
    vector<double> pedagio;
    double preco_combustivel = 4;
    double autonomia = 10;

    //adicionando na lista de adjacencias os vertices com seus respectivos vizinhos e distancias
    adj[0].push_back({1, 10});
    adj[0].push_back({4, 100});
    adj[0].push_back({3, 30});
    adj[1].push_back({2, 50});
    adj[2].push_back({4, 10});
    adj[3].push_back({2, 20});
    adj[3].push_back({4, 60});

    //armazenando o valor do pedagio de cada vertice
    pedagio.push_back(5);
    pedagio.push_back(6.5);
    pedagio.push_back(8.9);
    pedagio.push_back(7);
    pedagio.push_back(6.5);

    //chamada para calcular o caminho de menor custo passando:
    //a lista de adjacencias, o numero de vertices do grafo, a origem, o destino, 
    //a lista com o valor do pedagio de cada cidade, preco do combustivel, e autonomia do veiculo
    dijkstra(adj, V, 0, 4, pedagio, preco_combustivel, autonomia);

    return 0;
}