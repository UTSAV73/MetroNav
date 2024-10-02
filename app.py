from flask import Flask, request, jsonify
import heapq

app = Flask(__name__)

# File loader and graph builder
def load_map(color_files):
    graph = {}
    for color, file in color_files.items():
        with open(file, 'r') as f:
            stations = f.read().strip().split('\n')
            for i in range(len(stations) - 1):
                station_a = stations[i].strip()
                station_b = stations[i + 1].strip()
                
                if station_a not in graph:
                    graph[station_a] = {}
                if station_b not in graph:
                    graph[station_b] = {}
                
                graph[station_a][station_b] = (1, color)
                graph[station_b][station_a] = (1, color)

    return graph

# Dijkstra's algorithm modified
def dijkstra(graph, start, end):
    queue = [(0, start)]
    distances = {station: float('inf') for station in graph}
    distances[start] = 0
    previous_stations = {station: None for station in graph}
    
    while queue:
        current_distance, current_station = heapq.heappop(queue)

        if current_station == end:
            break
        
        for neighbor, (weight, _) in graph[current_station].items():
            distance = current_distance + weight
            
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous_stations[neighbor] = current_station
                heapq.heappush(queue, (distance, neighbor))

    path = []
    current_station = end
    while previous_stations[current_station] is not None:
        path.append(current_station)
        current_station = previous_stations[current_station]
    path.append(start)
    path.reverse()

    return path, distances[end]

def dijkstra_modified(graph, start, end):
    queue = [(0, start, None)]
    distances = {station: float('inf') for station in graph}
    distances[start] = 0
    previous_stations = {station: None for station in graph}
    
    while queue:
        current_cost, current_station, current_color = heapq.heappop(queue)

        if current_station == end:
            break
        
        for neighbor, (weight, color) in graph[current_station].items():
            color_change_cost = 1 if current_color != color else 0
            total_cost = current_cost + weight + color_change_cost
            
            if total_cost < distances[neighbor]:
                distances[neighbor] = total_cost
                previous_stations[neighbor] = current_station
                heapq.heappush(queue, (total_cost, neighbor, color))

    path = []
    current_station = end
    while previous_stations[current_station] is not None:
        path.append(current_station)
        current_station = previous_stations[current_station]
    path.append(start)
    path.reverse()

    return path, distances[end]

color_files = {
    'violet': 'violet.txt',
    'blue': 'blue.txt',
    'magenta': 'magenta.txt',
    'red': 'red.txt',
    'pink': 'pink.txt',
    'yellow': 'yellow.txt',
}

# Load the metro map
graph = load_map(color_files)

def calculate_cost(distance):
    if distance <= 2:
        return 10
    elif distance <= 5:
        return 20
    elif distance < 11:
        return 30
    elif distance < 20:
        return 40
    elif distance <= 28:
        return 50
    else:
        return 40

@app.route('/find_route', methods=['GET'])
def find_route():
    start_station = request.args.get('start_station')
    end_station = request.args.get('end_station')
    
    if not start_station or not end_station:
        return jsonify({"error": "Please provide both start_station and end_station."}), 400
    
    #shortest path by distance
    path_distance, distance = dijkstra(graph, start_station, end_station)
    cost = calculate_cost(distance)

    #shortest path by minimizing changes
    path_color_changes, min_changes_distance = dijkstra_modified(graph, start_station, end_station)
    cost_with_color_changes = calculate_cost(min_changes_distance)

    # dict to jsonify
    response = {
        "shortest_path_by_distance": path_distance,
        "distance": distance,
        "cost": cost,
        "shortest_path_min_color_changes": path_color_changes,
        "shortest_distance": min_changes_distance,
        "min_cost_with_min_color_changes": cost_with_color_changes
    }

    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)
