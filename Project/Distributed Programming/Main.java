import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Main {
    public static void main(String[] args) {
        int numThreads = Runtime.getRuntime().availableProcessors();
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);

        Graph graph2 = Graph.createRandomGraph(10);
        ColorManager colors2 = new ColorManager(5);
        colors2.insertColor(0, "red");
        colors2.insertColor(1, "green");
        colors2.insertColor(2, "blue");
        colors2.insertColor(3, "yellow");
        colors2.insertColor(4, "pink");

        try {
            long start = System.nanoTime();
            Future<Map<Integer, String>> result = executor.submit(() -> {
                try {
                    return GraphColoring.colorGraphMain(numThreads, graph2, colors2);
                } catch (Exception e) {
                    e.printStackTrace();
                    return null;
                }
            });

            Map<Integer, String> coloredGraph = result.get(); // Waits for the task to complete
            System.out.println(coloredGraph);

            long stop = System.nanoTime();
            long time = stop - start;
            System.out.println("Time: " + time / 1000000 + " ms");
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            executor.shutdown();
        }
    }
}
