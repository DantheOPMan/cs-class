import java.util.Iterator;

public class SortedList<E extends Comparable<? super E>> extends List<E> {

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

    public void insert(E data) {
        Node<E> temp = new Node<E>(data);
        if (head == null || data.compareTo(head.data) < 0) {
            temp.next = head;
            head = temp;
        }else{
            _insert(head, temp);
        }
        
    } 
    private Node<E> _insert(Node<E> curr, Node<E> node ){
        if(curr.next ==null){
            curr.next = node;
            return curr;
        }
        if(node.data.compareTo(curr.next.data)<0){
            node.next = curr.next;
            curr.next = node;
            return curr;
        }
        return _insert(curr.next, node);
    }

    public void remove(E data) {
        Node<E> temp = new Node<E>(data);
        if (head != null && data.compareTo(head.data) == 0) {
            head = head.next;
        } else {
            _remove(head,temp);
        }
    }
    private Node<E> _remove(Node<E> curr, Node<E> node ){
        if(curr == null){
            return null;
        }
        if (node.data.compareTo(curr.next.data) == 0) {
            curr.next = curr.next.next;
            return curr;
        }
        return _remove(curr.next,node); 
    }

    public E retrieve(int index) {
        return _retrieve(head, index, 0);
    }

    private E _retrieve(Node<E> curr, int index, int count){
        if(curr == null){
            return null;
        }
        if(count == index){
            return curr.data;
        }
        return _retrieve(curr.next, index, count+=1);
    }

    public boolean search(E data) {
        return _search(head, new Node<E>(data));
    }
    private boolean _search(Node<E> curr, Node<E> val) {
        if(curr == null){
            return false;
        }
        if (val.data.compareTo(curr.data) == 0) {
            return true;
        }
        return _search(curr.next, val);
    }

}
