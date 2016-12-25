// SortTools.java
/*
 * EE422C Project 1 submission by
 * Ali Ziyaan Momin
 * AZM259
 * 16470
 * Fall 2016
 */

package assignment1;
public class SortTools {

    private static int giveMeIndex(int[] x, int n, int v){
        int ceiling = n-1;                              //top boundary in which to search
        int floor = 0;                                  //lower boundary in which to search

        while(floor <= ceiling){

            int mid = floor + (ceiling - floor) / 2;    //middle point between ceiling and floor

            if(v < x[mid]){
                ceiling = mid - 1;
            }

            else if(v > x[mid]){
                floor = mid + 1;
            }
        }

        return floor;
    }

    /**
     * This method tests to see if the given array is sorted.
     * @param x is the array
     * @param n is the size of the input to be checked
     * @return true if array is sorted
     */
    public static boolean isSorted(int[] x, int n) {

        if(x==null || x.length == 0 || n<=0 || n>x.length){
            return false;
        }

        int arrList = n;            //length of x
        int i = 0;                  //index for iteration
        int j = 1;                  //index for iteration

        while(i < arrList){
            while(j < arrList){
                if(x[i] > x[j]){
                    return false;
                }
                j++;
                break;
            }
            i++;
        }

        return true;
    }

    /**
     * This method tests to see if the given array has the element v in it.
     * @param x is the sorted array in non-decreasing order
     * @param n is the number of the input to be checked
     * @param v is the value element to be searched
     * @return index of the value v
     * @return -1 if v not contained within the array
     */
    public static int find(int x[], int n, int v) {
        int ceiling = n-1;                     //top boundary in which to search
        int floor = 0;                                  //lower boundary in which to search

        while(floor <= ceiling){

            int mid = floor + (ceiling - floor) / 2;    //middle point between ceiling and floor

            if(v < x[mid]){
                ceiling = mid - 1;
            }

            else if(v > x[mid]){
                floor = mid + 1;
            }

            else{
                return mid;
            }
        }

        return -1;
    }


    /**
     * This method inserts the element v in the copy of the array passed.
     * @param x is the sorted array in non-decreasing order
     * @param n is the number of the array elements
     * @param v is the value element to be inserted
     * @return new array with the element v in it
     */
    public static int[] insertGeneral(int x[], int n, int v){

        if(find(x,n,v) != -1){                  //uses the find method to check if value v is in the array passed
            int[] y = x.clone();                //creates a clone of array x into array y
            return y;                           //returns array y
        }

        int index = giveMeIndex(x, n, v);

        int[] z = new int[n+1];
        boolean added = false;

        for(int i = 0; i < n+1; i++){
            if(!added){
                if(i == index){
                    z[i] = v;
                    added = true;
                }
                else{
                    z[i] = x[i];
                }
            }
            else{
                z[i] = x[i-1];
            }
        }

        return z;
    }

    /**
     * This method inserts the element v in the array passed.
     * @param x is the sorted array in non-decreasing order
     * @param n is the number of the array elements
     * @param v is the value element to be inserted
     * @return n if the element v already exists in the array
     * @return n+1 if the element v is added to the array
     */
    public static int insertInPlace(int[] x, int n, int v){
        int length = n-1;

        if(find(x, n, v) != -1){
            return n;
        }

        int index = giveMeIndex(x, n, v);

        for(int i = length+1; i >= 0; i--){
            if(i == index){
                x[i] = v;
                return n+1;
            }
            else{
                x[i] = x[i-1];
            }
        }
        return -1;
    }

    /**
     * This method sorts an array in non-decreasing order.
     * @param x is the array
     * @param n is the number of the array elements
     * @return void
     */
    public static void insertSort(int[] x, int n){
        if(isSorted(x, n)){
            return;
        }

        for(int i = 1; i < n; i++){
            int temp = x[i];
            int j = i-1;
            while(j > -1 && x[j] > temp){
                x[j+1] = x[j];
                j--;
            }
            x[j+1] = temp;
        }
    }
}
