#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;

class MetroSystem {
public:
    void loadStations(const vector<string>& files);
    vector<string> findShortestPath(const string& source, const string& destination);
    void displayPath(const vector<string>& path);

private:
    unordered_map<string, vector<pair<string, string>>> stations; 
    vector<string> BFS(const string& source, const string& destination);
};

void MetroSystem::loadStations(const vector<string>& files) {
    for (const auto& file : files) {
        string path = "C:/Users/Utsav/OneDrive/Desktop/MetroNav/" + file; 
        ifstream inputfile(path);    

        if (!inputfile.is_open()) { 
            cerr << "Error opening the file: " << file << endl;
            continue; 
        }

        string line;
        vector<string> temp;
        string color = file.substr(0, file.find('.')); 

        while (getline(inputfile, line)) {
            temp.emplace_back(line); 
        }

        for (size_t i = 1; i < temp.size(); i++) {
            stations[temp[i - 1]].emplace_back(temp[i], color);
            stations[temp[i]].emplace_back(temp[i - 1], color);
        }
        temp.clear();
    }
}

vector<string> MetroSystem::BFS(const string& source, const string& destination) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> parents; 
    queue<string> q;

    q.push(source);
    visited[source] = true;
    parents[source] = ""; 

    while (!q.empty()) {
        string current_node = q.front();
        q.pop();

        if (current_node == destination) {
            vector<string> path;
            for (string at = destination; at != ""; at = parents[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : stations.at(current_node)) {
            if (!visited[neighbor.first]) { 
                visited[neighbor.first] = true;
                parents[neighbor.first] = current_node; 
                q.push(neighbor.first); 
            }
        }
    }

    return {};
}

vector<string> MetroSystem::findShortestPath(const string& source, const string& destination) {
    return BFS(source, destination);
}

void MetroSystem::displayPath(const vector<string>& path) {
    if (!path.empty()) {
        cout << "Shortest path from source to destination is: ";
        for (size_t i = 0; i < path.size(); ++i) {
            const auto& station = path[i];
            string color;
            for (const auto& neighbor : stations[station]) {
                color = neighbor.second; 
                break; 
            }
            cout << station << " (" << color << ")";
            if (i < path.size() - 1) { 
                cout << " -> ";
            }
        }
        cout << endl << "Stations travelled: " << path.size() + 1 << endl;
    } else {
        cout << "No path found from source to destination." << endl;
    }
}

int main() {
    MetroSystem metro;
    vector<string> files = {"red.txt", "blue.txt", "pink.txt", "yellow.txt", "magenta.txt", "violet.txt"};
    
    metro.loadStations(files);

    cout << R"(
 __       __             __                          __    __                     
|  \     /  \           |  \                        |  \  |  \                    
| $$\   /  $$  ______  _| $$_     ______    ______  | $$\ | $$  ______  __     __ 
| $$$\ /  $$$ /      \|   $$ \   /      \  /      \ | $$$\| $$ |      \|  \   /  \
| $$$$\  $$$$|  $$$$$$\\$$$$$$  |  $$$$$$\|  $$$$$$\| $$$$\ $$  \$$$$$$\\$$\ /  $$ 
| $$\$$ $$ $$| $$    $$ | $$ __ | $$   \$$| $$  | $$| $$\$$ $$ /      $$ \$$\  $$ 
| $$ \$$$| $$| $$$$$$$$ | $$|  \| $$      | $$__/ $$| $$ \$$$$|  $$$$$$$  \$$ $$  
| $$  \$ | $$ \$$     \  \$$  $$| $$       \$$    $$| $$  \$$$ \$$    $$   \$$$   
 \$$      \$$  \$$$$$$$   \$$$$  \$$        \$$$$$$  \$$   \$$  \$$$$$$$    \$    
  )" << endl << endl;
cout<<"Press Enter to continue"<<endl;
    int choice = 1;

    cin.ignore(); // Clear the input buffer
    while (choice) {
        cout << "1. Find path" << endl;
        cout << "2. Explore" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            string source, destination;
            cin.ignore();
            cout << "Enter source: ";
            getline(cin, source); 
            cout << "Enter destination: ";
            getline(cin, destination); 
            vector<string> path = metro.findShortestPath(source, destination);
            metro.displayPath(path);
        } else if (choice == 2) {
            cout << "Open the map to explore..." << endl;
        } else {
            choice = 0; 
        }
    }

    return 0;
}
