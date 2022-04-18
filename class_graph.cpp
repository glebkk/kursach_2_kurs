#include <iostream>
#include <fstream>

#include <conio.h>

#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using namespace std;

class Graph{
private:
	
	struct node{
		int x;
		int y;
		int weight;

		bool operator==(const node& node) { //matrix to nodes
			return x == node.x && y == node.y && weight == node.weight;
 		}

		bool operator<( const node& node) { //kruskala(sort)
			return weight < node.weight;
		}
	};

	

	//������� ��������� �� Adjacency matrix
	vector< vector< int > > adj_matrix;
	// ���-�� ������
	int count_vertex;
	// ���-�� ����� � ������ �����
	int count_nodes;
	
	// ������ �����
	vector< node > node_list;
	
	//������������� ����� �������
	void init_console(){
		
		cout << "������� ���������� ������: ";

		cin >> count_vertex;
		
		cout << "��������� ������� ���������\n";

		adj_matrix.resize(count_vertex);
		for(int i=0; i<count_vertex; i++){
			adj_matrix[i].resize(count_vertex);
			for(int j=0; j<count_vertex; j++){
				cin >> adj_matrix[i][j];
			}
		}
	}
	
	//������������� ����� ����
	void init_file(ifstream & file){
		file >> count_vertex;
		adj_matrix.resize(count_vertex);
		for(int i=0; i<count_vertex; i++){
			adj_matrix[i].resize(count_vertex);
			for(int j=0; j<count_vertex; j++){
				file >> adj_matrix[i][j];
			}
		}
		file.close();
	}
		
	// ��� ��������������� ������� ��������� � ������ �����
	void matrix_to_nodes(){
		count_nodes = 0;
		for(int i=0; i<count_vertex; i++){
			for(int j=0; j<count_vertex; j++){
				node current_node = {j, i, adj_matrix[i][j]};
				if(adj_matrix[i][j] != 0 && find(node_list.begin(), node_list.end(), current_node) == node_list.end()){
					node_list.push_back({i, j, adj_matrix[i][j]});
					count_nodes++;
				}
			}
		}
	}

public:
	//�����������
	Graph(){
		bool exit = false;
		while(!exit){
			system("cls");
			char choice;
			cout << "!!!��� ����������� ������ ����������� ����� ������������ � 1!!!\n"
				<< "������� ����\n"
				<< "1: �� �����\n" 
				<< "2: �� �������\n";
			choice = _getch();
			switch(choice){
				case 49:{ // ������� 1
					system("cls");
					cout << "������� �������� �����/���� � ����: ";
					string path;
					getline(cin, path);
					ifstream file(path);
					if(!file.is_open()){
						cout << "�������� ��� �����.";
						_getch();
						break;
					}
					else{
						init_file(file);
						system("cls");
						exit = true;
						break;
					}
				}
				case 50:{ // ������� 2
					init_console();
					system("cls");
					exit = true;
					break;
				}
				default:{
					continue;
				}
			}
		}
		/*ifstream file("input.txt");
		init_file(file);*/
		matrix_to_nodes();
	}
	
	
	void show_graph(){
		cout << "������ ���������\n";
		for(int i=0; i<count_vertex; i++){
			cout << i+1 << ": ";
			for(int j=0; j<count_vertex; j++){
				if(adj_matrix[i][j] != 0)
					cout << j+1 << " ";
			}
			cout << "\n";
		}
	}
	
	void show_list(){
		cout << "������ ����\n";
		for(int i=0; i<count_nodes; i++){
			cout << node_list[i].x + 1 << "->" << node_list[i].y + 1 << " Weight: " << node_list[i].weight << "\n";
		}
	}
	
	void bfs(){
		cout << "----------------BFS----------------\n\n";

		queue<int> q; // �������
		int current_vertex = 1; // ������� �������
	
		vector<bool> visited(count_vertex, false); //������ ��� ������� �������� �� �������
		
		
		q.push(--current_vertex); // ������� ������� ������� � ����(���������� � ���� ������� --)
		visited[current_vertex] = true;// �������� � ����������
		
		//���� � ������� ���� ��������
		while (!q.empty()) {
		    current_vertex = q.front(); //����� ������ ������� �������
			q.pop(); //������� �� �������
		    cout << current_vertex + 1; //������� �� �����
		    _getch(); //��� ������� ����� �������
		    
		    // ���������� �������� ������� � �������
		    for (int i = 0; i < count_vertex; i++) {
		        if (adj_matrix[current_vertex][i] != 0 && !visited[i]) { // ���� �� ��������
		            q.push(i);     // ��������� �� � �������
		            visited[i] = true; // �������� ����������
		        }
		    }
		    
		    
		    if(q.size() != 0){
		    	cout << "->";
			}
			else{
				cout << "\n\n";
			}
		}
		cout << "----------------BFS----------------\n\n";
	}
	
	void dfs(){
		cout << "----------------DFS----------------\n\n";
		stack<int> stack; // ����
		int current_vertex = 1; // ������� �������

		vector<bool> visited(count_vertex, false); //������ ��� ������� �������� �� �������
		
		
		stack.push(--current_vertex); // ������� ������� ������� � ����(���������� � ���� ������� --)
		visited[current_vertex] = true; // �������� � ����������
		
		//���� � ����� ���� ��������
		while (!stack.empty()) {
		    current_vertex = stack.top(); //����� ������� ������� �����
			stack.pop(); //������� �� �����
		    cout << current_vertex + 1; //������� �� �����
		    
		    _getch(); //��� ������� ����� �������
		    // ���������� �������� ������� � �������
		    for (int i = 0; i < count_vertex; i++) { 
		        if (adj_matrix[current_vertex][i] != 0 && !visited[i]) { // ���� �� ��������
		            stack.push(i);     // ��������� �� � ����
		            visited[i] = true; // �������� ����������
		        }
		    }
		    
		    //����� �������
		    if(stack.size() != 0){
		    	cout << "->";
			}
			else{
				cout << "\n\n";
			}
		}
		cout << "----------------DFS----------------\n\n";
	}
	
	void kruskala() {
		cout << "-------------Kruskala--------------\n\n";
		// ���������� ���� �� �����������
		sort(node_list.begin(), node_list.end());

		int count_nodes_ost = 0; // ���-�� ���� ��������� ������(������ ���� ������ �� 1 ���-�� ������)
		int weight_ost = 0; // ��� ��������� ������
		
		//������ � ������� ��� ������ ������� �������� ����� ������, �������� ��� �����������
		vector<int> tree_id(count_vertex);
		for (int i = 0; i < count_vertex; i++){
			tree_id[i] = i;
		}


		//���� �� ������� ��� ����� � ������ ��������� ������ < ���-�� ������ - 1
		for (int i = 0; i < count_nodes && count_nodes_ost < count_vertex - 1; i++) {
			// ���� ������� ����������� ������ ��������
			if (tree_id[node_list[i].x] != tree_id[node_list[i].y])
			{
				count_nodes_ost++; // ���-�� ������ ������ ++
				weight_ost += node_list[i].weight; // ��� + ������� ��� �����
				for (int j = 0; j < count_vertex; j++)
					if (tree_id[j] == tree_id[node_list[i].y])
						tree_id[j] = tree_id[node_list[i].x];
				cout << node_list[i].x + 1 << "->" << node_list[i].y + 1 << " weight: " << node_list[i].weight << "\n";
				_getch();
			}
		}

		cout << "����� ��� ��������� ������: " << weight_ost << "\n\n";
		cout << "-------------Kruskala--------------\n\n";
	}

	void prima() {
		cout << "---------------Prima---------------\n\n";


		int min = 999, x = 0, y = 0;
		int current_vertex = 0;
		int count_nodes_ost = 0;
		int weight_ost = 0;

		vector<bool> visited(count_vertex, false);

		visited[current_vertex] = true;

		// ���� ������ ��������� ������ < ��� - �� ������ - 1
		while (count_nodes_ost < count_vertex - 1) { 
			int min = 999;
			for (int i = 0; i <	count_vertex; i++) { // �������� �� ���� �������
				if (visited[i]) { // ���� ������� ������� ��������
					for (int j = 0; j < count_vertex; j++) { // �������� �� ���� �������
						if (!visited[j] && adj_matrix[i][j]) { // ���� ��������� ������� �� �������� � � ��� �� ����� 0
							if (min > adj_matrix[i][j]) { // ������ �������� ��� �������� � ���������� �������
								min = adj_matrix[i][j];
								x = i;
								y = j;
							}
						}
					}
				}
			}

			count_nodes_ost++;
			visited[y] = true; // �������� ������ ������� ����������
			weight_ost += adj_matrix[x][y]; // ��� ��������� ������ �����������
			cout << x+1 << "->" << y+1 << " weight: " << adj_matrix[x][y] << "\n";
			_getch();
		}
		cout << "����� ��� ��������� ������: " << weight_ost << "\n\n";
		cout << "---------------Prima---------------\n\n";
	}

	void dijkstra(int current_vertex) {
		cout << "-------------Dijkstra--------------\n\n";

		int inf = 9999;
		current_vertex--; // � ++ ��������� � 0
		vector<int> dist(count_vertex, inf); // ��������� �� ���� ������
		vector<bool> visited(count_vertex, false); //������ ��� ������� �������� �� �������
		vector<int> path(count_vertex); // ��� ���������� ���� �� �������
		
		for (int i = 0; i < count_vertex; i++) {
			path[i] = i;
		}

		path[current_vertex] = -1; // ������� ������� ����� ����� ������ -1

		dist[current_vertex] = 0; // ���������� �� ������� ������� ����� ����

		for (int i = 0; i < count_vertex; i++)
		{
			//������� ������� � ����������� ����������� 
			int min = inf, ind = 0;
			for (int i = 0; i < count_vertex; i++) {
				if (!visited[i] && dist[i] <= min) { // ���� �� �������� � ���������� �� ������� ������ min
					min = dist[i]; // ��������� min
					ind = i; // ��������� ������
				}
			}

			visited[ind] = true; // �������� ������� ����������

			// ��������� ����������
			for (int i = 0; i < count_vertex; i++)
			{
				// ���� ������� ��� �� �������� ���������� � �� ����� ���� � ���������� �� ������� ������� + �� ��������� ������ ������ ����������
				// ��� �� ��������� 
				if (!visited[i] && adj_matrix[ind][i] && dist[ind] + adj_matrix[ind][i] < dist[i]) {
					dist[i] = dist[ind] + adj_matrix[ind][i]; // ��������� ���������� �� �������
					path[i] = ind; // ������ ������ i - ������, ind - ����
				}
			}
		}
		
		// �����
		cout << "Vertex\tDistance  Path\n";
		for (int i = 0; i < count_vertex; i++)
		{ 
			cout << current_vertex+1 << "->" << i + 1 << "\t" << dist[i] << "\t  ";

			// ��� ������ ����
			vector<int> tmp_path;
			tmp_path.push_back(i + 1); // ��������� ������� �������
			for (int j = i; path[j] != -1; j = path[j]) {
				tmp_path.push_back(path[j] + 1); // ��������� ������� ���� ��� �� ����� -1
			}

			// ������� ������� � �������� �������
			for (int k = tmp_path.size() - 1; k >= 0; k--) {
				cout << tmp_path[k];
				if (k != 0) cout << "->";
			}
			cout << endl;
		}


		cout << "\n-------------Dijkstra--------------\n\n";
	}

	void Menu() {
		cout << "�������� ��������\n"
			<< "1)������� ����\n"
			<< "2)����� � ������\n"
			<< "3)����� � �������\n"
			<< "4)�������� �����\n"
			<< "5)�������� ��������\n"
			<< "6)�������� ��������\n"
			<< "����� �� ��������� - ESC\n";
		char choice = _getch();
		switch (choice) {
		case 49: { // ������� 1

			bool exit = false;
			do {
				system("cls");
				cout << "1: ������ ����\n2: ������ ���������";
				char choice;
				choice = _getch();
				switch (choice) {
				case 49: // ������� 1
					system("cls");
					show_list();
					exit = true;
					break;
				case 50: // ������� 2
					system("cls");
					show_graph();
					exit = true;
					break;
				}
			} while (!exit);
			break;
		}

		case 50: // ������� 2
			system("cls");
			bfs();
			break;
		case 51: // ������� 3
			system("cls");
			dfs();
			break;
		case 52: // ������� 4
			system("cls");
			prima();
			break;
		case 53: // ������� 5
			system("cls");
			kruskala();
			break;
		case 54: // ������� 6
			system("cls");
			int current_vertex;
			cout << "������� �������: ";
			while (cin >> current_vertex) {
				if (current_vertex <= 0 || current_vertex>count_vertex) {
					system("cls");
					cout << "��� �������, ������� ������� ��� ���: ";
				}
				else {
					break;
				}
			}
			system("cls");
			dijkstra(current_vertex);
			break;
		case 27: // ������� esc
			system("cls");
			exit(0); // ���������� ���������
		default:
			system("cls");
			break;
		}
			
	}
};

int main(){
	system("chcp 1251");
	system("cls");
	
	Graph graph;
	
	while (true) {
		graph.Menu();
	}
	return 0;
}
