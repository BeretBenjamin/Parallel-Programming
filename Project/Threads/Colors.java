import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Colors {
    /*
    totalColors: represents the number of colors available
    colorMap: a map where the key is the color code (integer) and the value is the color name (string)
     */
    private int totalColors;
    private Map<Integer, String> colorMap;

    // Constructor
    public Colors(int totalColors) {
        this.totalColors = totalColors;
        this.colorMap = new HashMap<>();

        for (int code = 0; code < totalColors; code++) {
            colorMap.put(code, "");
        }
    }

    // Add a new color by its code and name
    public void addColor(int colorCode, String colorName) {
        colorMap.put(colorCode, colorName);
    }

    // Retrieve a map of colors for a list of color codes
    public Map<Integer, String> getColorsByCodes(List<Integer> colorCodes) {
        Map<Integer, String> resultMap = new HashMap<>();

        for (int index = 0; index < colorCodes.size(); index++) {
            String colorName = colorMap.get(colorCodes.get(index));
            resultMap.put(index, colorName);
        }

        return resultMap;
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
        return "Colors{" +
                "totalColors=" + totalColors +
                ", colorMap=" + colorMap +
                '}';
    }
}