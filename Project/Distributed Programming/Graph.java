import java.util.*;

public class Graph {
    /*
    totalNodes: int representing the total number of nodes in the network;
    adjacencyList: map with (key, value) pairs; key is the identifier of the node, value is a set of connected nodes;
     */
    private int totalNodes;
    private Map<Integer, Set<Integer>> adjacencyList;

    // Constructor
    public Graph(int total) {
        this.totalNodes = total;

        adjacencyList = new HashMap<>();
        for (int id = 0; id < total; id++) {
            adjacencyList.put(id, new HashSet<>());
        }
    }

    // Method to add a new connection between nodes
    public boolean connectNodes(int fromNode, int toNode) {
        return adjacencyList.get(fromNode).add(toNode);
    }

    // Method to check if a connection exists between two nodes
    public boolean hasConnection(int fromNode, int toNode) {
        return adjacencyList.get(fromNode).contains(toNode);
    }

    public int getTotalNodes() {
        return totalNodes;
    }

    public void setTotalNodes(int totalNodes) {
        this.totalNodes = totalNodes;
    }

    public Map<Integer, Set<Integer>> getAdjacencyList() {
        return adjacencyList;
    }

    public void setAdjacencyList(Map<Integer, Set<Integer>> adjacencyList) {
        this.adjacencyList = adjacencyList;
    }

    // Static method to generate a random network with a given number of nodes
    public static Graph createRandomGraph(int nodeCount) {
        Graph graph = new Graph(nodeCount);
        for (int i = 0; i < nodeCount; i++) {
            for (int j = 0; j < nodeCount; j++) {
                if (i != j) {
                    if (Math.random() < 0.5 && !graph.hasConnection(i, j)) {
                        graph.connectNodes(i, j);
                    }
                }
            }
        }
        return graph;
    }

    @Override
    public String toString() {
        return "Network{" +
                "totalNodes=" + totalNodes +
                ", adjacencyList=" + adjacencyList +
                '}';
    }
}
