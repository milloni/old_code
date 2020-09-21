public class TreeDictionary<K extends Comparable<K>, V> {
    private Node root;

    public TreeDictionary() {
        this.root = null;
    }

    public int size() {
        return nodeSize(this.root);
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    public V get(K key) {
        Node node = getNode(key);
        return (node == null) ? (null) : (node.val);
    }

    public void put(K key, V val) {
        Node node = this.root;
        if (node == null) {
            this.root = new Node(key, val);
            return;
        }

        Node newNode = new Node(key, val);
        while (node != null) {
            if (key.compareTo(node.key) == 0) {
                node.val = val;
                return;
            } else if (key.compareTo(node.key) < 0) {
                if (node.left == null) {
                    newNode.parent = node;
                    node.left = newNode;
                    updateTreeSize(node);
                    return;
                } else {
                    node = node.left;
                }
            } else { // key.compareTo(node.key) > 0
                if (node.right == null) {
                    newNode.parent = node;
                    node.right = newNode;
                    updateTreeSize(node);
                    return;
                } else {
                    node = node.right;
                }
            }
        }
    }

    public K min() {
        Node node = this.root;
        if (node == null) {
            throw new IllegalStateException("Tree is empty");
        }

        K result;
        do {
            result = node.key;
            node = node.left;
        } while (node != null);

        return result;
    }

    public K max() {
        Node node = this.root;
        if (node == null) {
            throw new IllegalStateException("Tree is empty");
        }

        K result;
        do {
            result = node.key;
            node = node.right;
        } while (node != null);

        return result;
    }

    public K predecessor(K key) {
        Node node = getNode(key);
        if (node == null) {
            throw new IllegalStateException("tree is empty");
        }

        if (node.left != null) {
            node = node.left;
            while (node.right != null) {
                node = node.right;
            }
            return node.key;
        } else if (node.parent != null) {
            while (node.parent != null) {
                node = node.parent;
                if (node.key.compareTo(key) < 0) {
                    return node.key;
                }
            }
        }

        // key is the minimum
        return null;
    }

    public K successor(K key) {
        Node node = getNode(key);
        if (node == null) {
            throw new IllegalStateException("tree is empty");
        }

        if (node.right != null) {
            node = node.right;
            while (node.left != null) {
                node = node.left;
            }
            return node.key;
        } else if (node.parent != null) {
            while (node.parent != null) {
                node = node.parent;
                if (node.key.compareTo(key) > 0) {
                    return node.key;
                }
            }
        }

        // key is the maximum
        return null;
    }

    public K select(int i) {
        if (i < 0 || i >= this.size()) {
            throw new IllegalArgumentException(
                "i has to be in range [0, size_of_tree)"
            );
        }

        Node node = this.root;
        if (node == null) {
            throw new IllegalStateException("Tree is empty");
        }

        int ns = nodeSize(node.left);
        while (true) {
            if (i == ns) {
                return node.key;
            } else if (i < ns) {
                node = node.left;
            } else { // i > ns
                node = node.right;
                i -= ns + 1;
            }

            assert node != null;
            assert i >= 0;
            assert i < this.size();

            ns = nodeSize(node.left);
        }
    }

    public int rank(K key) {
        Node node = getNode(key);
        if (node == null) {
            throw new IllegalArgumentException("key not in the tree");
        }

        int result = nodeSize(node.left);
        node = node.parent;
        while (node != null) {
            if (node.key.compareTo(key) < 0) {
                result += nodeSize(node.left) + 1;
            }
            node = node.parent;
        }

        return result;
    }

    public void delete(K key) {
        Node node = getNode(key);
        if (node == null) {
            throw new IllegalArgumentException("key not in the tree");
        }

        if (this.root.left == null && this.root.right == null) {
            assert this.root.key.equals(key);
            this.root = null;
            return;
        }

        if (node.left != null && node.right != null) {
            System.out.println("A");
            Node pred = node.left;
            while (pred.right != null) pred = pred.right;
            swapNodes(node, pred);
            node = pred;
        }

        if (node.left != null) {
            System.out.println("B");
            spliceOut(node, node.parent, node.left);
        } else if (node.right != null) {
            System.out.println("C");
            spliceOut(node, node.parent, node.right);
        } else { // no children
            spliceOut(node, node.parent, null);
        }
    }

    private void spliceOut(Node child, Node parent, Node newChild) {
        if (parent.left != null && parent.left.key.equals(child.key)) {
            parent.left = newChild;
        } else if (parent.right != null && parent.right.key.equals(child.key)) {
            parent.right = newChild;
        } else {
            throw new IllegalArgumentException(
                "First argument is not a child of the second argument"
            );
        }
    }

    /*private void updateParent(Node parent, Node child) {
        if (parent.left.key.equals(child.key)) {
            parent.left = 
        } else if (parent.left.key.equals(child.key)) {
            
        }
    }*/

    private void swapNodes(Node a, Node b) {
        K tkey = a.key;
        V tval = a.val;
        a.key = b.key;
        a.val = b.val;
        b.key = tkey;
        b.val = tval;
    }

    private int nodeSize(Node node) {
        return (node == null) ? (0) : (node.size);
    }

    private void updateTreeSize(Node node) {
        while (node != null) {
            node.size++;
            node = node.parent;
        }
    }

    private Node getNode(K key) {
        Node node = this.root;
        while (node != null) {
            if (key.compareTo(node.key) == 0) {
                return node;
            } else if (key.compareTo(node.key) < 0) {
                if (node.left == null) {
                    return null;
                } else {
                    node = node.left;
                }
            } else { // key.compareTo(node.key) > 0
                if (node.right == null) {
                    return null;
                } else {
                    node = node.right;
                }
            }
        }

        // Should never get here
        return null; 
    }

    private class Node {
        private Node parent;
        private Node left;
        private Node right;
        private int size;
        private K key;
        private V val;

        public Node() {
            this(null, null);
        }
        
        public Node(K key, V val) {
            this.parent = null;
            this.left = null;
            this.right = null;
            this.size = 1;
            this.key = key;
            this.val = val;
        }
    }

    private static void execTests() {
        TreeDictionary<String, Integer> dict = new TreeDictionary<>();
        assert dict.size() == 0;
        assert dict.isEmpty();
        dict.put("f", 9);
        assert dict.size() == 1;
        assert !dict.isEmpty();
        assert dict.get("f") == 9;
        assert dict.min().equals("f");
        assert dict.max().equals("f");
        dict.delete("f");
        assert dict.get("f") == null;
        assert dict.isEmpty();
        dict.put("f", 9);
        assert dict.get("f") == 9;
        dict.put("a", 11);
        assert dict.size() == 2;
        assert dict.get("f") == 9;
        assert dict.get("a") == 11;
        assert dict.min().equals("a");
        assert dict.max().equals("f");
        dict.put("g", 4);
        assert dict.size() == 3;
        assert dict.get("g") == 4;
        assert dict.get("a") == 11;
        assert dict.min().equals("a");
        assert dict.max().equals("g");
        dict.put("g", 20);
        assert dict.size() == 3;
        assert dict.get("g") == 20;
        assert dict.get("f") == 9;
        dict.put("o", 123);
        assert dict.size() == 4;
        assert dict.get("o") == 123;
        assert dict.get("a") == 11;
        assert dict.min().equals("a");
        assert dict.max().equals("o");
        dict.put("h", 1);
        assert dict.size() == 5;
        assert dict.get("h") == 1;
        assert dict.get("g") == 20;
        assert dict.min().equals("a");
        assert dict.max().equals("o");
        dict.put("t", 2);
        assert dict.size() == 6;
        assert dict.get("t") == 2;
        assert dict.get("f") == 9;
        assert dict.min().equals("a");
        assert dict.max().equals("t");
        dict.put("c", 3);
        assert dict.size() == 7;
        assert dict.get("c") == 3;
        assert dict.get("o") == 123;
        assert dict.min().equals("a");
        assert dict.max().equals("t");
        dict.put("b", 4);
        assert dict.size() == 8;
        assert dict.get("b") == 4;
        assert dict.min().equals("a");
        assert dict.max().equals("t");

        String[] sortedKeys = {"a", "b", "c", "f", "g", "h", "o", "t"};
        for (int i = 0; i < sortedKeys.length; i++) {
            assert dict.select(i).equals(sortedKeys[i]);
            assert dict.rank(sortedKeys[i]) == i;
        }

        assert dict.predecessor(sortedKeys[0]) == null;
        for (int i = 1; i < sortedKeys.length; i++) {
            assert dict.predecessor(sortedKeys[i]).equals(sortedKeys[i - 1]);
        }

        for (int i = 0; i < sortedKeys.length - 1; i++) {
            assert dict.successor(sortedKeys[i]).equals(sortedKeys[i + 1]);
        }
        assert dict.successor(sortedKeys[sortedKeys.length - 1]) == null;

        dict.delete("t");
        assert dict.get("t") == null;
        dict.delete("c");
        assert dict.get("c") == null;
    }
    
    public static void main(String[] args) {
        execTests();
    }
}

