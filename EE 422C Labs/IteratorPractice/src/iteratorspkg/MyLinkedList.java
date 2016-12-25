package iteratorspkg;

/**
 * Created by aliziyaan on 10/12/16.
 */

public class MyLinkedList implements MyListInterface {

    private Node head;
    private int size;
    private boolean modified;

    static class Node {
        Node next;
        Node prev;
        Integer data;

        public Node (Integer i) {
            next = null;
            prev = null;
            data = i;
        }

        public Node () {
            this(0);
        }

        @Override
        public String toString () {
            return "" + data;
        }
    } // end of Node class

    public MyLinkedList () {
        head = new Node();
        size = 0;
    }

    @Override
    public void add(Integer value) {
        modified = true;
        Node n = head;
        while (n.next != null) {
            n = n.next;
        }
        n.next = new Node(value);
        n.next.prev = n;
        size++;

    }

    @Override
    public boolean remove(Integer val) {
        Node n = head;
        while (n != null && n.data != val ) {
            n = n.next;
        }
        if (n != null) { // found data
            n.prev.next = n.next;
            if (n.next != null) { // if not removing last element
                n.next.prev = n.prev;
            }
            size--;
            modified = true;
            return true;
        }
        return false;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Integer get(int pos) throws IndexOutOfBoundsException {
        Node n = head.next;
        int p  = 0;
        if (pos > size - 1) {
            throw new IndexOutOfBoundsException(
                    "Pos " + pos + " is greater than size " + size + ".");

        }
        while (n != null && p < pos) {
            n = n.next;
            p++;
        }
        return n.data;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public String toString () {
        String s = "[";
        String comma = "";
        Node n = head.next;
        while (n != null) {
            s += comma + n;
            comma = ", ";
            n = n.next;
        }
        s += "]";
        return s;
    }

    void itRemoveAt(int index) {
        Node n = head.next;
        int pos = 0;

        while (pos != index) {
            n = n.next;
            pos++;
        }
        // n is item to be removed

        if (n.next == null) {
            n.prev.next = null;
            n = null;
        } else {
            n.prev.next = n.next;
            n.next.prev = n.prev;
        }
        size--;
    }

    public MyListIterator iterator () {
        modified = false;
        return new MyListIterator(this);
    }

    boolean isModified()	 {
        return modified;
    }

    void setModified(boolean b)	 {
        this.modified = b;
    }

    public void removeAt(int index) {
        if (index >= size || index < 0)
            throw new IndexOutOfBoundsException();
        modified = true;
        itRemoveAt(index);
    }

}
