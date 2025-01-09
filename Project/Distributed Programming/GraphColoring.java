import java.util.Arrays;
import java.util.Map;
import java.util.concurrent.Callable;

public class GraphColoring {
    public static Map<Integer, String> colorGraphMain(int numThreads, Graph graph, ColorManager colorManager) throws Exception {
        int totalColors = colorManager.getTotalColors();
        int[] colorCodes = colorGraphRecursive(0, graph, totalColors, new int[graph.getTotalNodes()]);

        if (colorCodes[0] == -1) {
            throw new Exception("No valid coloring solution found!");
        }

        return colorManager.fetchColorsByIds(colorCodes);
    }

    private static int[] colorGraphRecursive(int nodeId, Graph graph, int totalColors, int[] colorCodes) {
        int totalNodes = graph.getTotalNodes();

        if (!isColoringValid(nodeId, colorCodes, graph)) {
            return fillArrayWith(totalNodes, -1);
        }

        if (nodeId + 1 == graph.getTotalNodes()) {
            return colorCodes;
        }

        for (int currentColor = 0; currentColor < totalColors; currentColor++) {
            int[] newColorCodes = Arrays.copyOf(colorCodes, colorCodes.length);
            newColorCodes[nodeId] = currentColor;

            int[] result = colorGraphRecursive(nodeId + 1, graph, totalColors, newColorCodes);
            if (result[0] != -1) {
                return result;
            }
        }

        return fillArrayWith(totalNodes, -1);
    }

    private static int[] fillArrayWith(int length, int value) {
        int[] array = new int[length];
        Arrays.fill(array, value);
        return array;
    }

    private static boolean isColoringValid(int node, int[] colorCodes, Graph graph) {
        for (int current = 0; current < node; current++) {
            if ((graph.hasConnection(node, current) || graph.hasConnection(current, node)) && colorCodes[node] == colorCodes[current]) {
                return false;
            }
        }
        return true;
    }
}
