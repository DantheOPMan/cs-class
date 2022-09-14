import java.util.Random;

public class Main {
    public static void main(String[] args) throws Exception {
        List<Integer> list = new SortedList<Integer>();
        Random rand = new Random(1);
        int num = args.length == 1 ? Integer.parseInt(args[0]) : 11;
        System.out.println("insert");
        for (int i = 0; i < num; ++i) {
            int n = rand.nextInt(num);
            System.out.print(n + ": ");
            list.insert(n);
            for (Integer j : list) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
        System.out.println("search");
        System.out.println(" 6: " + list.search(6));
        System.out.println("12: " + list.search(12));
        System.out.println("retrieve");
        System.out.println(" 5: " + list.retrieve(5));
        System.out.println("13: " + list.retrieve(13));
        System.out.println("remove");
        rand = new Random(1);
        for (int i = 0; i < num; ++i) {
            int n = rand.nextInt(num);
            System.out.print(n + ": ");
            list.remove(n);
            for (Integer j : list) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
    }
}
