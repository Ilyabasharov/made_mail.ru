//
//  main.cpp
//  A
//
//  Created by Илья Башаров on 28.04.2020.
//  Copyright © 2020 MIPT. All rights reserved.
//

#include <iostream>
#include <queue>
#include <limits>

bool bfs(std::size_t** network, std::size_t& flow_dim,
         std::size_t s, std::size_t t,
         std::size_t* parent)
{
    std::queue<std::size_t> queue;
    
    auto visited = new bool[flow_dim - 1];
    queue.push(s);
    visited[s] = true;
    
    while(!queue.empty())
    {
        std::size_t mother = queue.front();
        queue.pop();
        
        for (std::size_t child = 0; child < flow_dim; child ++)
            if (!visited[child] && network[mother][child])
            {
                queue.push(child);
                parent[child] = mother;
                visited[child] = true;
            }
    }
    
    return visited[t - 1];
}

std::size_t fordFulkerson(std::size_t** network, std::size_t& flow_dim)
{
    
    std::size_t* parent = new std::size_t[flow_dim - 1](),
                          max_flow = 0, current_flow = 0,
                          child = 0, mother = 0;
    
    while (bfs(network, flow_dim, 0, flow_dim - 1, parent))
    {
        current_flow = std::numeric_limits<std::size_t>::max();
        
        for (mother = 0; mother != flow_dim - 1; mother = parent[mother])
            current_flow = std::min(current_flow, network[parent[mother]][mother]);
        
        for (mother = 0; mother != flow_dim - 1; mother = parent[mother])
        {
            child = parent[mother];
            network[child][mother] -= current_flow;
            network[mother][child] += current_flow;
        }
        
        max_flow += current_flow;
    }
    
    return current_flow;
}

int main()
{
    std::size_t N, M, a, b, c;
    
    std::cin >> N >> M;

    auto network = new std::size_t *[N]();
    
    for (std::size_t i = 0; i < N; i++)
        network[i] = new std::size_t [N]();
    
    for (std::size_t i = 0; i < M; i++)
    {
        std::cin >> a >> b >> c;
        network[a - 1][b - 1] = c;
    }
    
    std::cout << fordFulkerson(network, N) << std::endl;
    
    for (std::size_t i = 0; i < N; i++)
         delete [] network[i];
    
    delete [] network;
    
    return 0;
}
