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

	

	//матрица смежности от Adjacency matrix
	vector< vector< int > > adj_matrix;
	// кол-во вершин
	int count_vertex;
	// кол-во узлов в списке ребер
	int count_nodes;
	
	// вектор ребер
	vector< node > node_list;
	
	//инициализация через консоль
	void init_console(){
		
		cout << "Введите количество вершин: ";

		cin >> count_vertex;
		
		cout << "Заполните матрицу смежности\n";

		adj_matrix.resize(count_vertex);
		for(int i=0; i<count_vertex; i++){
			adj_matrix[i].resize(count_vertex);
			for(int j=0; j<count_vertex; j++){
				cin >> adj_matrix[i][j];
			}
		}
	}
	
	//инициализация через файл
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
		
	// для преобразованния матрицы смежности в список ребер
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
	//конструктор
	Graph(){
		bool exit = false;
		while(!exit){
			system("cls");
			char choice;
			cout << "!!!ДЛЯ КОРРЕКТНОГО ВЫВОДА ИСПОЛЬЗУЙТЕ ГРАФЫ НАЧИНАЮЩИЕСЯ С 1!!!\n"
				<< "Считать граф\n"
				<< "1: Из файла\n" 
				<< "2: Из консоли\n";
			choice = _getch();
			switch(choice){
				case 49:{ // клавиша 1
					system("cls");
					cout << "Введите название файла/путь к фалу: ";
					string path;
					getline(cin, path);
					ifstream file(path);
					if(!file.is_open()){
						cout << "Неверное имя файла.";
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
				case 50:{ // клавиша 2
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
		cout << "Список смежности\n";
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
		cout << "Список рёбер\n";
		for(int i=0; i<count_nodes; i++){
			cout << node_list[i].x + 1 << "->" << node_list[i].y + 1 << " Weight: " << node_list[i].weight << "\n";
		}
	}
	
	void bfs(){
		cout << "----------------BFS----------------\n\n";

		queue<int> q; // очередь
		int current_vertex = 1; // текущая вершина
	
		vector<bool> visited(count_vertex, false); //массив для пометки посещена ли вершина
		
		
		q.push(--current_vertex); // заносим текущую вершину в стек(индексация с нуля поэтому --)
		visited[current_vertex] = true;// помечаем её посещенной
		
		//пока в очереди есть элементы
		while (!q.empty()) {
		    current_vertex = q.front(); //берем первый элемент очереди
			q.pop(); //удаляем из очереди
		    cout << current_vertex + 1; //выводим на экран
		    _getch(); //ждём нажатие любой клавиши
		    
		    // перебираем соседние вершины с текущей
		    for (int i = 0; i < count_vertex; i++) {
		        if (adj_matrix[current_vertex][i] != 0 && !visited[i]) { // если не посещена
		            q.push(i);     // добавляем ее в очередь
		            visited[i] = true; // помечаем посещенной
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
		stack<int> stack; // стек
		int current_vertex = 1; // текущая вершина

		vector<bool> visited(count_vertex, false); //массив для пометки посещена ли вершина
		
		
		stack.push(--current_vertex); // заносим текущую вершину в стек(индексация с нуля поэтому --)
		visited[current_vertex] = true; // помечаем её посещенной
		
		//пока в стеке есть элементы
		while (!stack.empty()) {
		    current_vertex = stack.top(); //берем верхний элемент стека
			stack.pop(); //удаляем из стека
		    cout << current_vertex + 1; //выводим на экран
		    
		    _getch(); //ждём нажатие любой клавиши
		    // перебираем соседние вершины с текущей
		    for (int i = 0; i < count_vertex; i++) { 
		        if (adj_matrix[current_vertex][i] != 0 && !visited[i]) { // если не посещена
		            stack.push(i);     // добавляем ее в стек
		            visited[i] = true; // помечаем посещенной
		        }
		    }
		    
		    //вывод стрелок
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
		// сортировка рёбер по возрастанию
		sort(node_list.begin(), node_list.end());

		int count_nodes_ost = 0; // кол-во рёбер остовного дерева(должно быть меньше на 1 кол-ва вершин)
		int weight_ost = 0; // вес отсовного дерева
		
		//массив в котором для каждой вершины хранится номер дерева, которому она принадлежит
		vector<int> tree_id(count_vertex);
		for (int i = 0; i < count_vertex; i++){
			tree_id[i] = i;
		}


		//пока не обойдем все ребра и размер остовного дерева < кол-во вершин - 1
		for (int i = 0; i < count_nodes && count_nodes_ost < count_vertex - 1; i++) {
			// если деревья принадлежат разным деревьям
			if (tree_id[node_list[i].x] != tree_id[node_list[i].y])
			{
				count_nodes_ost++; // кол-во вершин остова ++
				weight_ost += node_list[i].weight; // вес + текущий вес ребра
				for (int j = 0; j < count_vertex; j++)
					if (tree_id[j] == tree_id[node_list[i].y])
						tree_id[j] = tree_id[node_list[i].x];
				cout << node_list[i].x + 1 << "->" << node_list[i].y + 1 << " weight: " << node_list[i].weight << "\n";
				_getch();
			}
		}

		cout << "Общий вес остовного дерева: " << weight_ost << "\n\n";
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

		// пока размер остовного дерева < кол - во вершин - 1
		while (count_nodes_ost < count_vertex - 1) { 
			int min = 999;
			for (int i = 0; i <	count_vertex; i++) { // проходим по всей матрице
				if (visited[i]) { // если текущая вершина посещена
					for (int j = 0; j < count_vertex; j++) { // проходим по этой вершине
						if (!visited[j] && adj_matrix[i][j]) { // если следующая вершина не посещена и её вес не равен 0
							if (min > adj_matrix[i][j]) { // меняем значение мин значения и запоминаем индексы
								min = adj_matrix[i][j];
								x = i;
								y = j;
							}
						}
					}
				}
			}

			count_nodes_ost++;
			visited[y] = true; // помечаем вторую вершину посещенной
			weight_ost += adj_matrix[x][y]; // вес оствоного дерева увеличиваем
			cout << x+1 << "->" << y+1 << " weight: " << adj_matrix[x][y] << "\n";
			_getch();
		}
		cout << "Общий вес остовного дерева: " << weight_ost << "\n\n";
		cout << "---------------Prima---------------\n\n";
	}

	void dijkstra(int current_vertex) {
		cout << "-------------Dijkstra--------------\n\n";

		int inf = 9999;
		current_vertex--; // в ++ нумерация с 0
		vector<int> dist(count_vertex, inf); // дистанция до всех вершин
		vector<bool> visited(count_vertex, false); //массив для пометки посещена ли вершина
		vector<int> path(count_vertex); // для сохранения пути от вершины
		
		for (int i = 0; i < count_vertex; i++) {
			path[i] = i;
		}

		path[current_vertex] = -1; // текущая вершина будет иметь индекс -1

		dist[current_vertex] = 0; // расстояние до текущей вершины равно нулю

		for (int i = 0; i < count_vertex; i++)
		{
			//находим вершину с минимальным расстоянием 
			int min = inf, ind = 0;
			for (int i = 0; i < count_vertex; i++) {
				if (!visited[i] && dist[i] <= min) { // если не посещена и расстояние до вершины меньше min
					min = dist[i]; // обновляем min
					ind = i; // обновляем индекс
				}
			}

			visited[ind] = true; // помечаем вершину посещенной

			// обновляем расстояния
			for (int i = 0; i < count_vertex; i++)
			{
				// если вершина ещё не помечена пройденной и не равна нулю и расстояние от прошлой вершины + до следующей меньше меньше расстояние
				// чем до следующей 
				if (!visited[i] && adj_matrix[ind][i] && dist[ind] + adj_matrix[ind][i] < dist[i]) {
					dist[i] = dist[ind] + adj_matrix[ind][i]; // обновляем расстояние до вершины
					path[i] = ind; // меняем индекс i - откуда, ind - куда
				}
			}
		}
		
		// вывод
		cout << "Vertex\tDistance  Path\n";
		for (int i = 0; i < count_vertex; i++)
		{ 
			cout << current_vertex+1 << "->" << i + 1 << "\t" << dist[i] << "\t  ";

			// для вывода пути
			vector<int> tmp_path;
			tmp_path.push_back(i + 1); // добавляем текущую вершину
			for (int j = i; path[j] != -1; j = path[j]) {
				tmp_path.push_back(path[j] + 1); // добавляем вершины пока они не равны -1
			}

			// выводим вершины в обратном порядке
			for (int k = tmp_path.size() - 1; k >= 0; k--) {
				cout << tmp_path[k];
				if (k != 0) cout << "->";
			}
			cout << endl;
		}


		cout << "\n-------------Dijkstra--------------\n\n";
	}

	void Menu() {
		cout << "Выберите действие\n"
			<< "1)Вывести граф\n"
			<< "2)Обход в ширину\n"
			<< "3)Обход в глубину\n"
			<< "4)Алгоритм Прима\n"
			<< "5)Алгоритм Краскала\n"
			<< "6)Алгоритм Дейкстры\n"
			<< "Выйти из программы - ESC\n";
		char choice = _getch();
		switch (choice) {
		case 49: { // клавиша 1

			bool exit = false;
			do {
				system("cls");
				cout << "1: Список рёбер\n2: Список смежности";
				char choice;
				choice = _getch();
				switch (choice) {
				case 49: // клавиша 1
					system("cls");
					show_list();
					exit = true;
					break;
				case 50: // клавиша 2
					system("cls");
					show_graph();
					exit = true;
					break;
				}
			} while (!exit);
			break;
		}

		case 50: // клавиша 2
			system("cls");
			bfs();
			break;
		case 51: // клавиша 3
			system("cls");
			dfs();
			break;
		case 52: // клавиша 4
			system("cls");
			prima();
			break;
		case 53: // клавиша 5
			system("cls");
			kruskala();
			break;
		case 54: // клавиша 6
			system("cls");
			int current_vertex;
			cout << "Введите вершину: ";
			while (cin >> current_vertex) {
				if (current_vertex <= 0 || current_vertex>count_vertex) {
					system("cls");
					cout << "Нет вершины, Введите вершину ещё раз: ";
				}
				else {
					break;
				}
			}
			system("cls");
			dijkstra(current_vertex);
			break;
		case 27: // клавиша esc
			system("cls");
			exit(0); // завершение программы
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
