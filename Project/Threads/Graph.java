import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Graph {
    /*
    totalVertices: int representing the total number of nodes in the graph
    adjacencyMap: a map where the key is the node identifier and the value is a set of neighboring node identifiers
     */
    private int totalVertices;
    private Map<Integer, Set<Integer>> adjacencyMap;

    // Constructor
    public Graph(int vertexCount) {
        this.totalVertices = vertexCount;
        this.adjacencyMap = new HashMap<>();

        for (int vertexId = 0; vertexId < vertexCount; vertexId++) {
            adjacencyMap.put(vertexId, new HashSet<>());
        }
    }

    // Add a connection between two vertices
    public boolean addConnection(int startVertex, int endVertex) {
        return adjacencyMap.get(startVertex).add(endVertex);
    }

    // Check if a connection exists between two vertices
    public boolean hasConnection(int startVertex, int endVertex) {
        return adjacencyMap.get(startVertex).contains(endVertex);
    }

    public int getTotalVertices() {
        return totalVertices;
    }

    public void setTotalVertices(int totalVertices) {
        this.totalVertices = totalVertices;
    }

    public Map<Integer, Set<Integer>> getAdjacencyMap() {
        return adjacencyMap;
    }

    public void setAdjacencyMap(Map<Integer, Set<Integer>> adjacencyMap) {
        this.adjacencyMap = adjacencyMap;
    }

    // Generate a random graph with a given number of vertices
    public static Graph generateRandomGraph(int vertexCount) {
        Graph graph = new Graph(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (i != j) {
                    if (Math.random() < 0.5 && !graph.hasConnection(i, j)) {
                        graph.addConnection(i, j);
                    }
                }
            }
        }
        return graph;
    }

    @Override
    public String toString() {
        return "Graph{" +
                "totalVertices=" + totalVertices +
                ", adjacencyMap=" + adjacencyMap +
                '}';
    }
}