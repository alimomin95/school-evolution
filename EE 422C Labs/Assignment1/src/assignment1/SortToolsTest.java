package assignment1;

import static org.junit.Assert.*;
import org.junit.Test;

public class SortToolsTest {
	
	int[] testArr = {1, 2, 5, 9, 100, 300};
	int[] emptyArr = new int[0];
	
	int[] unsortedArr = {300, 100, 9, 5, 2, 1};
	int[] sortedArr = {1, 2, 5, 9, 100, 300};
	
	@Test
	public void testIsSorted() {
		//does your code work?
		assertTrue(SortTools.isSorted(testArr, 6)); 
		
		//edge case n = 0
		assertFalse(SortTools.isSorted(testArr, 0));
		
		//edge case n > length
		assertFalse(SortTools.isSorted(testArr, 9)); 
		
		//edge case n < 0
		assertFalse(SortTools.isSorted(testArr, -1)); 
		
		//edge case empty array
		assertFalse(SortTools.isSorted(emptyArr, 0));
		//edge case empty array wrong n
		assertFalse(SortTools.isSorted(emptyArr, 1));

		System.out.println("testIsSorted Passed!");
	}

	@Test
	public void testFind() {
		//does your code return the correct index?
		assertTrue(SortTools.find(testArr, 6, 1) == 0);
		assertTrue(SortTools.find(testArr, 6, 2) == 1);
		assertTrue(SortTools.find(testArr, 6, 5) == 2);
		assertTrue(SortTools.find(testArr, 6, 9) == 3);
		assertTrue(SortTools.find(testArr, 6, 100) == 4);
		assertTrue(SortTools.find(testArr, 6, 300) == 5);
		
		//what if it isn't even there but you think it is?
		assertTrue(SortTools.find(testArr, 5, 300) == -1);
		assertTrue(SortTools.find(testArr, 4, 100) == -1);
		assertTrue(SortTools.find(testArr, 3, 9) == -1);
		assertTrue(SortTools.find(testArr, 2, 5) == -1);
		assertTrue(SortTools.find(testArr, 1, 2) == -1);
		assertTrue(SortTools.find(testArr, 0, 1) == -1);

		System.out.println("testFind Passed!");
	}

	@Test
	public void testInsertGeneral() {
		//before, between, after, and strange n
		assertArrayEquals(SortTools.insertGeneral(testArr, 6, 0), new int[]{0,1,2,5,9,100,300});
		assertArrayEquals(SortTools.insertGeneral(testArr, 6, 400), new int[]{1,2,5,9,100,300,400});
		assertArrayEquals(SortTools.insertGeneral(testArr, 6, 7), new int[]{1,2,5,7,9,100,300});
		assertArrayEquals(SortTools.insertGeneral(testArr, 6, 6), new int[]{1,2,5,6,9,100,300});
		assertArrayEquals(SortTools.insertGeneral(testArr, 6, 6), new int[]{1,2,5,6,9,100,300});
		assertArrayEquals(SortTools.insertGeneral(testArr, 5, 6), new int[]{1,2,5,6,9,100});
		assertArrayEquals(SortTools.insertGeneral(testArr, 4, 6), new int[]{1,2,5,6,9});
		assertArrayEquals(SortTools.insertGeneral(testArr, 3, 6), new int[]{1,2,5,6});
		assertArrayEquals(SortTools.insertGeneral(testArr, 2, 6), new int[]{1,2,6});
		assertArrayEquals(SortTools.insertGeneral(testArr, 1, 6), new int[]{1,6});
		assertArrayEquals(SortTools.insertGeneral(testArr, 0, 6), new int[]{6});

	}

	@Test
	public void testInsertInPlace() {
		SortTools.insertInPlace(testArr, 5, 1);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 2);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 5);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 9);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 100);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 300);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 1);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,300});
		
		SortTools.insertInPlace(testArr, 5, 200);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,200});
		
		SortTools.insertInPlace(testArr, 5, 150);
		assertArrayEquals(testArr, new int[]{1,2,5,9,100,150});
		
		SortTools.insertInPlace(testArr, 1, 3);
		assertArrayEquals(testArr, new int[]{1,3,5,9,100,150});
		
		SortTools.insertInPlace(testArr, 1, 3);
		assertArrayEquals(testArr, new int[]{1,3,5,9,100,150});
		
		SortTools.insertInPlace(testArr, 5, 0);
		assertArrayEquals(testArr, new int[]{0,1,3,5,9,100});
		
		SortTools.insertInPlace(testArr, 5, 4);
		assertArrayEquals(testArr, new int[]{0,1,3,4,5,9});
		
		SortTools.insertInPlace(testArr, 5, 10);
		assertArrayEquals(testArr, new int[]{0,1,3,4,5,10});
		
	}

	@Test
	public void testInsertSort() {
		//does it sort it?
		SortTools.insertSort(unsortedArr, 6);
		assertArrayEquals(unsortedArr, sortedArr);
		
		//does it corrupt sorted data?
		SortTools.insertSort(sortedArr, 6);
		assertArrayEquals(sortedArr, unsortedArr);
		
	}

}
