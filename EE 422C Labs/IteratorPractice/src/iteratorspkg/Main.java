package iteratorspkg;

/**
 * Created by aliziyaan on 10/13/16.
 */
public class Main {
    public static void main(String[] args){
        MyLinkedList a = new MyLinkedList();
        a.add(9);
        a.add(8);
        a.add(10);

        System.out.println(a);

        MyListIterator it = a.iterator();

        while(true){
            System.out.println(it.next());
            it.remove();
            if(!it.hasNext()) break;
        }

        System.out.println(a);
    }
}
