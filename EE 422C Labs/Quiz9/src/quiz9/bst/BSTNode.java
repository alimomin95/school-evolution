/*
 * EE422C Quiz 9 submission by
 * Ali Ziyaan Momin
 * 16470
 * AZM259
 */

package quiz9.bst;

/**
 * There is no implementation needed in this class. Don't edit anything in this
 * class.
 * @param <T>
 */
public class BSTNode<T extends Comparable<T>> {

	T data;
	BSTNode<T> left;
	BSTNode<T> right;
	BSTNode<T> parent;

	public BSTNode() {
		super();
	}

	public BSTNode(T data, BSTNode<T> left, BSTNode<T> right) {
		super();
		parent = null;
		this.data = data;
		this.left = left;
		this.right = right;
	}

	public boolean isLeaf() {
		return left == null && right == null;
	}

	public String toString() {
		return data.toString();
	}

	/**
	 * @return the data
	 */
	public T getData() {
		return data;
	}

	/**
	 * @param data
	 *            the data to set
	 */
	public void setData(T data) {
		this.data = data;
	}

	/**
	 * @return the left
	 */
	public BSTNode<T> getLeft() {
		return left;
	}

	/**
	 * @param left
	 *            the left to set
	 */
	public void setLeft(BSTNode<T> left) {
		this.left = left;
	}

	/**
	 * @return the right
	 */
	public BSTNode<T> getRight() {
		return right;
	}

	/**
	 * @param right
	 *            the right to set
	 */
	public void setRight(BSTNode<T> right) {
		this.right = right;
	}

	public boolean hasLeftChild() {
		return !(left == null);
	}

}
