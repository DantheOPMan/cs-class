public class App {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");

    }
    
}
class AStack <E> implements Stack<E>{
    private class Node<T>{
        private Node(T data){
            this.data = data;
        }
        private T data;
        private Node<T> next;
    }
    public E pop(){
        E temp = null;
        if(head != null){
            temp = head.data;
            head = head.next;
        }
        return null;
    }
    public void push(E Data){   
        Node<E> temp = new Node<E>(data);
        temp.next = head;
        head = temp; 
    }
    private Node<E>;
}
