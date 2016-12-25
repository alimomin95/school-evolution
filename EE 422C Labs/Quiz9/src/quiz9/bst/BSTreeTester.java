/*
 * EE422C Quiz 9 submission by
 * Ali Ziyaan Momin
 * 16470
 * AZM259
 */

package quiz9.bst;

import static org.junit.Assert.*;

import org.junit.Test;

public class BSTreeTester {

	private void print(BSTNode<Integer> root, int level) {
		if (root == null)
			return;
		if (root.isLeaf()) {
			for (int i = 0; i < level * 4; i++) {
				System.out.print(" ");
			}
			System.out.println(root);
		} else {
			print(root.right, level + 1);
			for (int i = 0; i < level * 4; i++) {
				System.out.print(" ");
			}
			System.out.println(root);
			print(root.left, level + 1);
		}
	}

	@Test
	public void test_add() {
		BSearchTree<Integer> intTree = new BSearchTree<Integer>();
		intTree.add(4);
		intTree.add(3);
		intTree.add(6);
		intTree.add(1);
		intTree.add(7);
		intTree.add(5);
		BSTNode<Integer> root = intTree.getRoot();
		print(root, 0);
		assertEquals(root.data, new Integer(4));
		assertEquals(root.left.data, new Integer(3));
		assertEquals(root.right.data, new Integer(6));
		assertEquals(root.left.left.data, new Integer(1));
		assertEquals(root.right.left.data, new Integer(5));
		assertEquals(root.right.right.data, new Integer(7));
	}

	@Test
	public void test_find() {
		BSearchTree<Integer> intTree = new BSearchTree<Integer>();
		intTree.add(4);
		intTree.add(3);
		intTree.add(6);
		intTree.add(1);
		intTree.add(7);
		intTree.add(5);
		BSTNode<Integer> root = intTree.getRoot();
		print(root, 0);
		assertTrue(intTree.find(3));
		assertTrue(intTree.find(1));
		assertTrue(intTree.find(7));
		assertFalse(intTree.find(8));
		assertFalse(intTree.find(0));

	}

}
