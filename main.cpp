#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;

//Using BFS as assumtions are made like all stations are equally apart ie 1.
vector<string> BFS(const string& source, const string& destination, 
                   const unordered_map<string, vector<pair<string, string>>>& graph) {
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

        for (const auto& neighbor : graph.at(current_node)) {
            if (!visited[neighbor.first]) { 
                visited[neighbor.first] = true;
                parents[neighbor.first] = current_node; 
                q.push(neighbor.first); 
            }
        }
    }

    return {}; // Return empty path if destination not found
}

int main() {
    unordered_map<string, vector<pair<string, string>>> stations; // Adjacency list with colors format is like stationA: (stationB,colorA), (stationC,colorC)
    vector<string> files = {"red.txt", "blue.txt", "pink.txt", "yellow.txt", "magenta.txt", "violet.txt"};

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

    //EDIT THIS PART
    vector<string> path = BFS("Samaypur Badli", "Palam", stations);

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
        cout << endl << "Stations travelled: " << path.size() + 1;
    } else {
        cout << "No path found from source to destination." << endl;
    }

    return 0;
}