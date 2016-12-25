package iteratorspkg;

import java.util.ConcurrentModificationException;

/**
 * Created by aliziyaan on 10/12/16.
 */
public class MyListIterator {
    int index;
    MyLinkedList list;
    boolean removeOk = false;


    public MyListIterator(MyLinkedList list){
        this.list = list;
    }

    public boolean hasNext(){
        return index < list.size();
    }

    public Integer next(){
        if(list.isModified()){
            throw new ConcurrentModificationException("List modified outside of the iterator");
        }
        Integer temp = list.get(index);
        index++;
        removeOk = true;
        return temp;
    }

    public void remove(){
        if(list.isModified()){
            throw new ConcurrentModificationException("List modified outside of the iterator");
        }
        if(!removeOk){
            throw new IllegalStateException("Remove can't be done before next");
        }
        list.itRemoveAt(index - 1);
        removeOk = false;
        index --;
    }
}
