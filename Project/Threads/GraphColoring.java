import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class GraphColoring {

    public static Map<Integer, String> getColoredGraph(int numThreads, Graph graph, Colors colorPalette) throws Exception {
        List<Integer> colorCodesList = new ArrayList<>();
        int totalColors = colorPalette.getTotalColors();
        List<Integer> nodeColors = new ArrayList<>(Collections.nCopies(graph.getTotalVertices(), 0));
        Lock threadLock = new ReentrantLock();

        findColoredGraph(new AtomicInteger(numThreads), 0, graph, totalColors, nodeColors, threadLock, colorCodesList);

        // No solution found
        if (colorCodesList.isEmpty()) {
            throw new Exception("No valid solution found!");
        }

        // Solution found
        return colorPalette.getColorsByCodes(colorCodesList);
    }

    private static void findColoredGraph(AtomicInteger numThreads, int currentNode, Graph graph, int totalColors, List<Integer> nodeColors, Lock threadLock, List<Integer> colorCodesList) {
        // Solution already found
        if (!colorCodesList.isEmpty()) {
            return;
        }

        // Found valid solution
        if (currentNode + 1 == graph.getTotalVertices()) {
            if (isValidColoring(currentNode, nodeColors, graph)) {
                threadLock.lock();
                if (colorCodesList.isEmpty()) {
                    colorCodesList.addAll(nodeColors);
                }
                threadLock.unlock();
            }
            return;
        }

        // Find possible colors for the next node
        int nextNode = currentNode + 1;
        List<Thread> threadsList = new ArrayList<>();
        List<Integer> validColorOptions = new ArrayList<>();

        for (int color = 0; color < totalColors; color++) {
            nodeColors.set(nextNode, color);
            if (isValidColoring(nextNode, nodeColors, graph)) {
                if (numThreads.getAndDecrement() > 0) {
                    List<Integer> updatedNodeColors = new ArrayList<>(nodeColors);

                    Thread thread = new Thread(() -> findColoredGraph(numThreads, nextNode, graph, totalColors, updatedNodeColors, threadLock, colorCodesList));
                    thread.start();
                    threadsList.add(thread);
                } else {
                    validColorOptions.add(color);
                }
            }
        }

        // Join threads
        for (Thread thread : threadsList) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        for (int color : validColorOptions) {
            nodeColors.set(nextNode, color);
            List<Integer> updatedNodeColors = new ArrayList<>(nodeColors);
            findColoredGraph(numThreads, nextNode, graph, totalColors, updatedNodeColors, threadLock, colorCodesList);
        }
    }

    // Check if the coloring is valid (no adjacent nodes with the same color)
    private static boolean isValidColoring(int node, List<Integer> nodeColors, Graph graph) {
        for (int neighbor = 0; neighbor < node; neighbor++) {
            if ((graph.hasConnection(node, neighbor) || graph.hasConnection(neighbor, node)) && nodeColors.get(node) == nodeColors.get(neighbor)) {
                return false;
            }
        }
        return true;
    }
}