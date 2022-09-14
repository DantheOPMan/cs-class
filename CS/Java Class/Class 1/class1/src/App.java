public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");

    }
    public static <E extends Comparable<? super E>> int bsearch(E[] a, E key){
        return bsearch(a, key, 0, a.length-1);
    }

    private static <E extends Comparable<? super E>> int bsearch(E[] a, E key, int left, int right){

        int cmp, mid = (left + right) / 2;
        if(left <= right){
            if((cmp = key.compareTo(a[mid])) == 0){
                return mid;
            }else if(cmp < 0){
                return bsearch(a, key, left, mid-1);
            }else{
                return bsearch(a,key,mid+1,right);
            }
        }
        
        return -1;
    }

    public static <E extends Comparable<? super E>> int ssearch(E[] a, E key){
        
        //return ssearch(a,key,0);
        return 1;
    }
}
