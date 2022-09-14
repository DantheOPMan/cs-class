public class Main {
    public static void main(String[] args) {
        Integer[] array = {12, 23, 34, 45, 56, 67, 78, 89, 90};
        System.out.println(bsearch(array, 45));
        System.out.println(bsearch(array, 46));
        System.out.println(ssearch(array, 45));
        System.out.println(ssearch(array, 46));
    }

    public static <E extends Comparable<? super E>> int bsearch(E[] a, E key) {
        return bsearch(a, key, 0, a.length-1);
    }
    public static <E extends Comparable<? super E>> int bsearch(E[] a, E 
        key, int left, int right) {
        int cmp;
        if (left <= right) {
            int mid = (left+right) / 2;
            if ((cmp = key.compareTo(a[mid])) == 0) {
                return mid;
            }else if (cmp < 0) {
                return bsearch(a, key, left, mid-1);
            }else {
                return bsearch(a, key, mid+1, right);
            }
        }
        return -1;
    }
    public static <E extends Comparable<? super E>> int ssearch(E[] a, E key) {
        return ssearch(a, key, 0);
    }
    private static <E extends Comparable<? super E>> int ssearch(E[] a, E key, int index) {
        if (index < a.length) {
            if (key.compareTo(a[index]) == 0) {
                return index;
            }else {
            return ssearch(a, key, index+1);
            }
        }
        return -1;
    }
}