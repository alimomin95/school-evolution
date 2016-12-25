/* 
 * EE422C Quiz 9 submission by
 * Ali Ziyaan Momin
 * 16470
 * AZM259
 */

package quiz9.bst;

/**
 * <p>
 * In this quiz, you are asked to implement Binary Search Tree using iteration.
 * Recursion is not allowed for any methods in this quiz.
 * </p>
 * <p>
 * Replacing TODO with your implementation for add and find methods. Don't
 * change any other things, including package, class, or method declaration.
 * Your submission should not have any generic warnings.
 * </p>
 * <p>
 * remove() is not required, yet if you can finish remove() methods, we give you
 * 3 extra points.
 * </p>
 * <p>
 * Include your name in file header. Zip your quiz9 folder and name it as quiz9_
 * <EID>.zip.
 * </p>
 */
public class BSearchTree<E extends Comparable<E>> {

	private BSTNode<E> root;

	public BSearchTree() {
		this.root = null;
	}

	/**
	 * BST insert method
	 * 
	 * @param root
	 *            BST root node
	 * @param value
	 *            the inserted value, allow duplicate values.
	 * @return BST root node
	 */
	public BSTNode<E> add(E value) {
		// TODO Implement this method using iteration
        BSTNode<E> temp = this.root;
        BSTNode<E> parent = this.root;
        if(this.root == null){
            this.root = new BSTNode<E>(value, null, null);
            return root;
        }
        while(temp != null){
            if(temp.data.compareTo(value) >= 0){
                parent = temp;
                temp = temp.getLeft();
            }
            else{
                parent = temp;
                temp = temp.getRight();
            }
        }
        temp = new BSTNode<E>(value, null, null);
        if(parent.data.compareTo(temp.data) >= 0){
            parent.setLeft(temp);
        }
        else{
            parent.setRight(temp);
        }
		return root;
	}

	/**
	 * Find method in BST
	 * 
	 * @param root
	 *            BST root
	 * @param value
	 *            searched value
	 * @return true if the value is found in the BST
	 */
	public boolean find(E value) {
		// TODO implement this method using iteration
		BSTNode<E> temp = this.root;

        while(temp != null){
            if(temp.data.compareTo(value) > 0){
                temp = temp.getLeft();
            }
            else if(temp.data.compareTo(value) < 0){
                temp = temp.getRight();
            }
            else{
                return true;
            }
        }
        return false;
	}

	/**
	 * BST remove method
	 * 
	 * @param root
	 *            BST root node
	 * @param value
	 * @return tree root
	 */
	public BSTNode<E> remove(BSTNode<E> root, E value) {
		// TODO You don't need to implement this method. Yet you will get 3
		// extra points if you successfully implement it in iteration.
        BSTNode<E> temp = this.root;
        while(temp != null){
            if(temp.data.compareTo(value) > 0){
                temp = temp.getLeft();
            }
            else if(temp.data.compareTo(value) < 0){
                temp = temp.getLeft();
            }
            else{
                temp = null;
                break;
            }
        }
		return temp;
	}

	public BSTNode<E> getRoot() {
		return root;
	}
	
	
}
