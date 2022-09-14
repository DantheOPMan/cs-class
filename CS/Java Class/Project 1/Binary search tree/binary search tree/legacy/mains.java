import java.util.Iterator;
import java.util.Random;
import java.util.Vector;

public class Mains {

    public static void mains(String[] args) {

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

abstract class BinaryTree<E> implements Iterable<E> {

    protected class Node<T> {

        protected Node(T data) {
            this.data = data;
        }

        protected T data;
        protected Node<T> left;
        protected Node<T> right;
    }

    public abstract void insert(E data);
    public abstract void remove(E data);
    public abstract boolean search(E data);

    protected Node<E> root;
}

class BinarySearchTree<E extends Comparable<? super E>> extends BinaryTree<E> {

    private Node<E> findIOP(Node<E> curr) {
        curr = curr.left;
        while (curr.right != null) {
            curr = curr.right;
        }
        return curr;
    }

    public int height() {
        return height(root);
    }

    private int height(Node<E> curr) {
        if (curr == null) {
            return 0;
        }
        int left = height(curr.left) + 1;
        int right = height(curr.right) + 1;
        return left > right ? left : right;
    }

    public void insert(E data) {
        Node<E> temp = new Node<E>(data);
        if (root == null) {
            root = temp;
        }
        else {
            Node<E> curr = root;
            while (true) {
                if (data.compareTo(curr.data) <= 0) {
                    if (curr.left == null) {
                        curr.left = temp;
                        break;
                    }
                    else {
                        curr = curr.left;
                    }
                }
                else {
                    if (curr.right == null) {
                        curr.right = temp;
                        break;
                    }
                    else {
                        curr = curr.right;
                    }
                }
            }
        }
    }

    public Iterator<E> iterator() {
        vector = new Vector<E>();
        traverse(root);
        return vector.iterator();
    }

    public void remove(E data) {
        if (root != null) {
            if (data.compareTo(root.data) == 0) {
                if (root.left == null || root.right == null) {
                    root = root.left != null ? root.left : root.right;
                }
                else {
                    Node<E> iop = findIOP(root);
                    E temp = iop.data;
                    iop.data = root.data;
                    root.data = temp;
                    if (root.left != iop) {
                        Node<E> curr = root.left;
                        while (curr.right != iop) {
                            curr = curr.right;
                        }
                        curr.right = iop.left;
                    }
                    else {
                        root.left = root.left.left;
                    }
                }
            }
            else {
                Node<E> curr = root;
                while (true) {
                    if (data.compareTo(curr.data) <= 0) {
                        if (curr.left == null) {
                            break;
                        }
                        else if (data.compareTo(curr.left.data) == 0) {
                            if (curr.left.left == null || curr.left.right == null) {
                                curr.left = curr.left.left != null ? curr.left.left : curr.left.right;
                            }
                            else {
                                Node<E> iop = findIOP(curr.left);
                                E temp = iop.data;
                                iop.data = curr.left.data;
                                curr.left.data = temp;
                                if (curr.left.left != iop) {
                                    curr = curr.left.left;
                                    while (curr.right != iop) {
                                        curr = curr.right;
                                    }
                                    curr.right = iop.left;
                                }
                                else {
                                    curr.left.left = curr.left.left.left;
                                }
                            }
                            break;
                        }
                        else {
                            curr = curr.left;
                        }
                    }
                    else {
                        if (curr.right == null) {
                            break;
                        }
                        else if (data.compareTo(curr.right.data) == 0) {
                            if (curr.right.left == null || curr.right.right == null) {
                                curr.right = curr.right.left != null ? curr.right.left : curr.right.right;
                            }
                            else {
                                Node<E> iop = findIOP(curr.right);
                                E temp = iop.data;
                                iop.data = curr.right.data;
                                curr.right.data = temp;
                                if (curr.right.left != iop) {
                                    curr = curr.right.left;
                                    while (curr.right != iop) {
                                        curr = curr.right;
                                    }
                                    curr.right = iop.left;
                                }
                                else {
                                    curr.right.left = curr.right.left.left;
                                }
                            }
                            break;
                        }
                        else {
                            curr = curr.right;
                        }
                    }
                }
            }
        }
    }

    public boolean search(E data) {
        Node<E> curr = root;
        int cmp;
        while (curr != null) {
            if ((cmp = data.compareTo(curr.data)) == 0) {
                return true;
            }
            else if (cmp < 0) {
                curr = curr.left;
            }
            else {
                curr = curr.right;
            }
        }
        return false;
    }

    private void traverse(Node<E> curr) {
        if (curr != null) {
            traverse(curr.left);
            vector.add(curr.data);
            traverse(curr.right);
        }
    }

    private Vector<E> vector;
}
