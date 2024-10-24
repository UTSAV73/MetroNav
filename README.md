# MetroNav-
This is a simple python project to find shortest distance between 2 metro stations along with minimum cost and minimum distance with minimum changes in the path for daily travellers.
Originally made on C++ application designed to find the minimum distance between metro stations and python REST API deployed on Replit. 
The C++ app runs on the command line on any platform.
# Assumptions
- Cost of travel in metro is linearly but not uniform
- All stations are equidistance apart (had no compiled data on distance between stations)
- The metro lines is a undirected-acyclic-unweighted graph so a simple BFS is used instead of Dijkstra's Algorithm which can also be used assumed unit distance between each node
# Features
- Faster than delhi metro app.
- API is fast and responsive, can find route with shortest path and shortest path with minimum line changes for long distance travellers.
- Estimates the cost of travel
- Readable code and very scalable since addition of new stations and lines is easy and customizable.
## Use this [URL](https://c1e498fd-97c8-49a2-ac88-426c1af551ea-00-wj2hcx7lgmh5.picard.replit.dev/find_route?start_station=Palam&end_station=Samaypur%20Badli)
## Run the API on [Replit](https://replit.com/@UtsavJoshi2/Metroo) before accessing the link
## Change the start and end stations accordingly (station names MUST follow Pascal Case).

# Future Plans
- Make a travel planner using city map and A* algorithm to find the shortest and cheapest way of travelling from one point to another
- Include other options to travel like bus, rickshaw and cab
- Use google API to predict to monitor the congestion and shortcuts.
- Cheapest travel rates for students and visitors.
  

