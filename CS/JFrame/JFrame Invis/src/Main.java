import javax.swing.JFrame;
import javax.swing.WindowConstants;
public class Main {
    public static void main(String[] args) throws Exception {
        JFrame image = new JFrame("image");
        image.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        System.out.println(image.getDefaultCloseOperation());
    }

}
