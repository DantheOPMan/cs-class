import java.util.Random;

public class Main{

    public static void main(String[] args) {

        BinaryTree<Integer> tree = new BinarySearchTree<Integer>();
        Random rand = new Random(1);
        int num = args.length == 1 ? Integer.parseInt(args[0]) : 11;
        long start, stop;

        System.out.println("insert");
        start = System.currentTimeMillis();
        for (int i = 0; i < num; ++i) {
            int n = rand.nextInt(num);
            tree.insert(n);
            System.out.print(n + ": ");
            for (Integer j : tree) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
        stop = System.currentTimeMillis();
        System.out.println(stop-start);

        // System.out.println("height: " + ((BinarySearchTree)tree).height());

        rand = new Random(1);
        System.out.println("search");
        start = System.currentTimeMillis();
        for (int i = 0; i < num; ++i) {
            int n = rand.nextInt(num);
            tree.search(n);
            System.out.println(n + (tree.search(n) ? " " : " not ") + "found");
        }
        System.out.println();
        for (int i = 0; i < num/2; ++i) {
            int n = rand.nextInt(num);
            tree.search(n);
            System.out.println(n + (tree.search(n) ? " " : " not ") + "found");
        }
        stop = System.currentTimeMillis();
        System.out.println(stop-start);

        // rand = new Random(1);
        System.out.println("remove");
        start = System.currentTimeMillis();
        for (int i = 0; i < num; ++i) {
            int n = rand.nextInt(num);
            tree.remove(n);
            System.out.print(n + ": ");
            for (Integer j : tree) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
        stop = System.currentTimeMillis();
        System.out.println(stop-start);

        System.out.println(tree.root == null);
    }
}