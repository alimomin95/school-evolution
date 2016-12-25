package quiz2;

//TestSelectionSort.java
/*
 * EE422C Quiz 2 submission by
 * Ali Ziyaan Momin
 * AZM259
 * 16470
 * Fall 2016
 */

import static org.junit.Assert.*;
import org.junit.Test;

public class TestSelectionSort {
    int[] unsortedArr = {300, 100, 9, 5, 2, 1};
    int[] sortedArr = {1, 2, 5, 9, 100, 300};

    @Test
    public void testGeneralSort() {
        //does it sort it?
        SelectionSort.sort(unsortedArr);
        assertArrayEquals(unsortedArr, sortedArr);

        //does it corrupt sorted data?
        SelectionSort.sort(sortedArr);
        assertArrayEquals(sortedArr, unsortedArr);
    }

    int[] array = {300, 300, 200, 200};
    int[] sarray = {200, 200, 300, 300};

    @Test
    public void testDupSort() {
        //does it sort array with duplications?
        SelectionSort.sort(array);
        assertArrayEquals(array, sarray);

        //does it corrupt sorted data?
        SelectionSort.sort(sarray);
        assertArrayEquals(sarray, array);
    }
    
}
