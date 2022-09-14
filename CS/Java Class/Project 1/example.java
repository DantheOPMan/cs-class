import java.util.Iterator;
import java.util.Random;

public class example{
    public static void main(String[] args) {
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

abstract class List<E> implements Iterable<E> {
    protected class Node<T> {
        protected Node(T data) {
            this.data = data;
        }

        protected T data;
        protected Node<T> next;
    }

    public abstract void insert(E data);

    public abstract void remove(E data);

    public abstract E retrieve(int index);

    public abstract boolean search(E data);

    protected Node<E> head;
}

class SortedList<E extends Comparable<? super E>> extends List<E> {

    public void insert(E data) {
        Node<E> temp = new Node<E>(data);
        if (head == null || data.compareTo(head.data) < 0) {
            temp.next = head;
            head = temp;
        } else {
            
            Node<E> curr = head;
            while (curr.next != null) {
                if (data.compareTo(curr.next.data) < 0) {
                    break;
                }
                curr = curr.next;
            }
            temp.next = curr.next;
            curr.next = temp;
        }
    }

    public Iterator<E> iterator() {
        return new Iterator<E>() {
            public boolean hasNext() {
                return curr != null;
            }

            public E next() {
                E temp = curr.data;
                curr = curr.next;
                return temp;
            }

            private Node<E> curr = head;
        };
    }

    public void remove(E data) {
        if (head != null && data.compareTo(head.data) == 0) {
            head = head.next;
        } else {
            for (Node<E> curr = head; curr.next != null; curr = curr.next) {
                if (data.compareTo(curr.next.data) == 0) {
                    curr.next = curr.next.next;
                    break;
                }
            }
        }
    }

    public E retrieve(int index) {
        int i = 0;
        for (Node<E> curr = head; i <= index && curr != null; ++i, curr = curr.next) {
            if (i == index) {
                return curr.data;
            }
        }
        return null;
    }

    public boolean search(E data) {
        for (Node<E> curr = head; curr != null; curr = curr.next) {
            if (data.compareTo(curr.data) == 0) {
                return true;
            }
        }
        return false;
    }
}