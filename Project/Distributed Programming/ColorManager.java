import java.util.HashMap;
import java.util.Map;

public class ColorManager {
    /*
    totalColors: int representing the total number of colors;
    colorMap: map with (key,value) pairs where key(int) is the identifier of the color and value(String) is the name of the color;
     */
    private int totalColors;
    private Map<Integer, String> colorMap;

    // Constructor
    public ColorManager(int total) {
        this.totalColors = total;

        colorMap = new HashMap<>();
        for (int id = 0; id < total; id++) {
            colorMap.put(id, "");
        }
    }

    // Method to add a new color
    public void insertColor(int id, String name) {
        colorMap.put(id, name);
    }

    // Method to retrieve a map of color IDs and names for a list of given IDs
    public Map<Integer, String> fetchColorsByIds(int[] ids) {
        Map<Integer, String> selectedColors = new HashMap<>();

        for (int i = 0; i < ids.length; i++) {
            String colorName = colorMap.get(ids[i]);
            selectedColors.put(i, colorName);
        }
        return selectedColors;
    }

    // Getters and Setters
    public int getTotalColors() {
        return totalColors;
    }

    public void setTotalColors(int totalColors) {
        this.totalColors = totalColors;
    }

    public Map<Integer, String> getColorMap() {
        return colorMap;
    }

    public void setColorMap(Map<Integer, String> colorMap) {
        this.colorMap = colorMap;
    }

    @Override
    public String toString() {
        return "ColorManager{" +
                "totalColors=" + totalColors +
                ", colorMap=" + colorMap +
                '}';
    }
}
