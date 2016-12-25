/*
 * This file is how you might test out your code.  Don't submit this, and don't
 * have a main method in SortTools.java.
 */
package assignment1;


import java.util.Arrays;

public class Main {
    public static void main(String [] args) {
        /*SortTools tools = new SortTools();

        int [] x = {1,1,3,4,5,6};
        if(!tools.isSorted(x,6)){
            System.out.println("false");
        }

        //int [] y = {0,1,1,1,1,5,6,7,8,9,10,11,12,13,13,0};
        //System.out.println(tools.find(y, y.length, 12));

        //System.out.println(Arrays.toString(tools.insertGeneral(y, y.length, 3)));

        //System.out.println(tools.insertInPlace(y, 15, 1));
        //System.out.println(Arrays.toString(y));

        //int [] z = {9,6,7,4,5,8,1,2,3,2};
        //tools.insertSort(z,z.length);
        //System.out.println(Arrays.toString(z));

        // call your test methods here*/

        SortToolsTest test = new SortToolsTest();

        test.testIsSorted();
        test.testFind();
        test.testInsertGeneral();
        test.testInsertInPlace();
        test.testInsertSort();

        System.out.println("Testing for isSorted method....");
        int[] a = { 1, 2, 3, 4, 5 };// sorted array, should return true;
        int[] b = { 1, 2, 3, 5, 4 };// semi sorted array, should return true for
        // first 3 elements, false otherwise.
        int[] c = { 5, 4, 3, 2, 1 };// not sorted, should return false;
        System.out.println("Sorted status:(should be true) " + SortTools.isSorted(a, 5)); // should
        // return
        // True
        System.out.println("Sorted status:(should be true) " + SortTools.isSorted(b, 3)); // should
        // return
        // true
        System.out.println("Sorted status:(should be false) " + SortTools.isSorted(b, 5)); // should
        // return
        // false
        System.out.println("Sorted status:(should be true)" + SortTools.isSorted(c, 1)); // Should
        // return
        // true
        System.out.println("Sorted status:(should be false)" + SortTools.isSorted(c, 5)); // Should
        // return
        // false
        System.out.println("End of testing.....\n");

        // tests for find();
        System.out.println("Testing for find method....");
        int[] aa = { 1, 2, 3, 4, 5 };
        System.out.println("The index is(0): " + SortTools.find(aa, 5, 1)); // look
        // for
        // value
        // =1;//should
        // be 0
        System.out.println("The index is(0): " + SortTools.find(aa, 1, 1)); // 0
        System.out.println("The index is(1): " + SortTools.find(aa, 5, 2));// 1
        System.out.println("The index is(1): " + SortTools.find(aa, 2, 2));// 1
        System.out.println("The index is(2): " + SortTools.find(aa, 5, 3));// 2
        System.out.println("The index is(2): " + SortTools.find(aa, 3, 3));// 2
        System.out.println("The index is(3): " + SortTools.find(aa, 5, 4));// 3
        System.out.println("The index is(3): " + SortTools.find(aa, 4, 4));// 3
        System.out.println("The index is(4): " + SortTools.find(aa, 5, 5));// 4
        System.out.println("The index is(4): " + SortTools.find(aa, 5, 5));// 4
        System.out.println("The index is(-1): " + SortTools.find(aa, 3, 5));// -1
        System.out.println("The index is(-1): " + SortTools.find(aa, 0, 4));// -1

        System.out.println("End of testing ......\n");
        // tests for insertGeneral();
        System.out.println("Testing for insertGeneral.....");

        int[] v = { 1 };
        int[] b1 = { 2, 3, 4, 5 };
        int[] b2 = { 1, 3, 4, 5 };
        int[] b3 = { 1, 2, 4, 5 };
        int[] b4 = { 1, 2, 3, 5 };
        int[] b5 = { 1, 2, 3, 4 };
        System.out.println("Add 1 at start " + Arrays.toString(SortTools.insertGeneral(b1, 4, 1)));// add
        // at
        // start
        System.out.println("Add 2 on second spot " + Arrays.toString(SortTools.insertGeneral(b2, 4, 2)));
        System.out.println("Add 3 in the middle " + Arrays.toString(SortTools.insertGeneral(b3, 4, 3)));// add
        // at
        // middle
        System.out.println("Add 4 in 4th spot " + Arrays.toString(SortTools.insertGeneral(b4, 4, 4)));
        System.out.println("Add 5 at the end " + Arrays.toString(SortTools.insertGeneral(b5, 4, 5)));// add
        // at
        // end

        System.out.println("End of testing.....\n");
        //
        // int[] xx = tools.insertGeneral(x1, 3, 1);
        // int[] xy = tools.insertGeneral(x2,9,5);
        // int[] b1xx = tools.insertGeneral(x3, 9, 10);
        // for (int i = 0; i < 4; i++) {
        // System.out.println(xx[i]);
        // }
        // for (int i = 0; i < 10; i++) {
        // System.out.println(xy[i]);
        // }
        // for (int i = 0; i < 10; i++) {
        // System.out.println(b1xx[i]);
        // }
        // call your test methods here

        System.out.println("Testing for insertInPlace method.....");
        int[] x = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x1 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x2 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x3 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x4 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x5 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x6 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x7 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x8 = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
        int[] x9 = { 1, 2, 3, 4, 5, 7, 8, 9, 0 };
        System.out.println("Making sure we get the right number of elements");
        System.out.println("should be 1: " + SortTools.insertInPlace(x, 0, 50));
        System.out.println("should be 2: " + SortTools.insertInPlace(x1, 1, 50));
        System.out.println("should be 3: " + SortTools.insertInPlace(x2, 2, 50));
        System.out.println("should be 4: " + SortTools.insertInPlace(x3, 3, 50));
        System.out.println("should be 5: " + SortTools.insertInPlace(x4, 4, 50));
        System.out.println("should be 6: " + SortTools.insertInPlace(x5, 5, 50));
        System.out.println("should be 7: " + SortTools.insertInPlace(x6, 6, 50));
        System.out.println("should be 8: " + SortTools.insertInPlace(x7, 7, 50));
        System.out.println("should be 9: " + SortTools.insertInPlace(x8, 8, 50));
        System.out.println("should be 9: " + SortTools.insertInPlace(x9, 8, 6));

        System.out.println(Arrays.toString(x));
        System.out.println(Arrays.toString(x1));
        System.out.println(Arrays.toString(x2));
        System.out.println(Arrays.toString(x3));
        System.out.println(Arrays.toString(x4));
        System.out.println(Arrays.toString(x5));
        System.out.println(Arrays.toString(x6));
        System.out.println(Arrays.toString(x7));
        System.out.println(Arrays.toString(x8));
        System.out.println(Arrays.toString(x9));
        System.out.println("End of testing.....\n");

        System.out.println("Testing for insertSort method....");
        int[] array = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array1 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array2 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array3 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array4 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array5 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array6 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array7 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array8 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };
        int[] array9 = { 3, 2, 1, 5, 9, 4, 6, 7, 8 };

        SortTools.insertSort(array, 0);
        System.out.println(Arrays.toString(array));
        SortTools.insertSort(array1, 1);
        System.out.println(Arrays.toString(array1));
        SortTools.insertSort(array2, 2);
        System.out.println(Arrays.toString(array2));
        SortTools.insertSort(array3, 3);
        System.out.println(Arrays.toString(array3));
        SortTools.insertSort(array4, 4);
        System.out.println(Arrays.toString(array4));
        SortTools.insertSort(array5, 5);
        System.out.println(Arrays.toString(array5));
        SortTools.insertSort(array6, 6);
        System.out.println(Arrays.toString(array6));
        SortTools.insertSort(array7, 7);
        System.out.println(Arrays.toString(array7));
        SortTools.insertSort(array8, 8);
        System.out.println(Arrays.toString(array8));
        SortTools.insertSort(array9, 9);
        System.out.println(Arrays.toString(array9));

        System.out.println("End of testing ......\n");

    }
}
