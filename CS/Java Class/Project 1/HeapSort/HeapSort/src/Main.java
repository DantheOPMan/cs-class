import java.util.Random;

public class Main {
    public static void main(String[] args) {
        int num = args.length == 1 ? Integer.parseInt(args[0]) : 10000;
        Integer[] array = new Integer[num];
        Random rand;
        long start, stop;
        rand = new Random(1);
        for (int i = 0; i < array.length; ++i) {
            array[i] = rand.nextInt(num);
        }
        start = System.currentTimeMillis();
        Sorts.bubbleSort(array);
        stop = System.currentTimeMillis();
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                System.out.println("bubble fail");
                System.exit(0);
            }
        }
        System.out.println("bubble pass: " + (stop - start));
        rand = new Random(1);
        for (int i = 0; i < array.length; ++i) {
            array[i] = rand.nextInt(num);
        }
        start = System.currentTimeMillis();
        Sorts.insertSort(array);
        stop = System.currentTimeMillis();
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                System.out.println("insert fail");
                System.exit(0);
            }
        }
        System.out.println("insert pass: " + (stop - start));
        rand = new Random(1);
        for (int i = 0; i < array.length; ++i) {
            array[i] = rand.nextInt(num);
        }
        start = System.currentTimeMillis();
        Sorts.selectSort(array);
        stop = System.currentTimeMillis();
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                System.out.println("select fail");
                System.exit(0);
            }
        }
        System.out.println("select pass: " + (stop - start));
        rand = new Random(1);
        for (int i = 0; i < array.length; ++i) {
            array[i] = rand.nextInt(num);
        }
        start = System.currentTimeMillis();
        Sorts.mergeSort(array);
        stop = System.currentTimeMillis();
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                System.out.println("merge fail");
                System.exit(0);
            }
        }
        System.out.println("merge pass: " + (stop - start));
        rand = new Random(1);
        for (int i = 0; i < array.length; ++i) {
            array[i] = rand.nextInt(num);
        }
        start = System.currentTimeMillis();
        Sorts.quickSort(array);
        stop = System.currentTimeMillis();
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                System.out.println("quick fail");
                System.exit(0);
            }
        }
        System.out.println("quick pass: " + (stop - start));
        rand = new Random(1);
        for (int i = 0; i < array.length; ++i) {
            array[i] = rand.nextInt(num);
        }
        start = System.currentTimeMillis();
        Sorts.heapSort(array);
        stop = System.currentTimeMillis();
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                System.out.println("heap fail");
                System.exit(0);
            }
        }
        System.out.println("heap pass: " + (stop - start));

    }
}