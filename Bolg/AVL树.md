# AVL树

## 完全二叉树  
定义:complete binary tree is a binary tree in which every level of the tree 
is completely filled except the last level
除了最后一层外每个节点都是完全被填充的

## 满二叉树

定义:a binary tree T is full if each node is either a leaf or possesses exactly two child nodes
也就是每个节点有两个子节点或者该节点是某个叶子几点
## 注意
上述的完全二叉树和满二叉树可能有不同的版本,国外和国内的定义都不同。。。
所以我也不纠结了,反正二叉树就是那几种形态,介绍上面的那些主要是为了说明一下如果一棵二叉树每层都是满节点的(或者除了最后一层外其他都是满节点的)
那么在查询的时候效率就会大幅度提高

但是在我们在一棵二叉树中进行删除或者插入节点的时候会破坏二叉树的平衡性,所以我们需要调整二叉树使他重新达到平衡

## AVL树
定义:AVL tree is a binary search tree in which the difference of heights of left and right subtrees of any node is less than or equal to one
任何节点的左右子树的高度差<=1  WSF

AVL树
TL and TR are height balanced
hL - hR <= 1, where hL - hR are the heights of TL and TR

AVL树是一种二叉平衡树.传统的二叉树在某些情况下会造成某一条路径是
单链表的情况,此时为了保持二叉树的查询的高效,需要对其做一些节点的旋转

### 节点的定义  
```
@Data
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class AVLV2Node {
    private int balanceFactor;
    private AVLV2Node left;
    private AVLV2Node right;
    private int value;
    public AVLV2Node(int value){
        this.value=value;
    }
}
```

### 插入操作
* Step 1: First, insert a new element into the tree using BST's (Binary Search Tree) insertion logic.
使用二叉搜索树的插入逻辑插入一个节点
* Step 2: After inserting the elements you have to check the Balance Factor of each node.
检查每个节点的平衡因子
* Step 3: When the Balance Factor of every node will be found like 0 or 1 or -1 then the algorithm will proceed for the next operation.
当找到平衡因子(0,1,-1)时需要执行下一个操作
* Step 4: When the balance factor of any node comes other than the above three values then the tree is said to be imbalanced. 
Then perform the suitable Rotation to make it balanced and then the algorithm will proceed for the next operation
当任何一个平衡因子大于上面三个值时这棵树就是不平衡的,需要适当的旋转使得AVL树保持平衡并且这个算法会继续下一步  
### 删除操作
* Step 1: Firstly, find that node where k is stored
首先找到需要删除的节点
* Step 2: Secondly delete those contents of the node (Suppose the node is x)
然后删除这个节点的值
* Step 3: Claim: Deleting a node in an AVL tree can be reduced by deleting a leaf. There are three possible cases:
删除一个节点可以通过删除叶子节点来缩减,有三种情况
When x has no children then, delete x
当该节点没有子节点时,直接删除它
When x has one child, let x' becomes the child of x.
当有一个孩子节点的时候,让x的孩子成为x的孩子??
Notice: x' cannot have a child, since subtrees of T can differ in height by at most one :
then replace the contents of x with the contents of x'
然后x节点和x的孩子节点替换内容
then delete x' (a leaf)
然后删除x的孩子
Step 4:  When x has two children,
当x有两个孩子
then find x's successor z (which has no left child)
找到x的后继
then replace x's contents with z's contents, and

delete z
In all of the three cases, you will end up removing a leaf
在上面所有情况下,你需要删除该孩子节点

### Left Rotation


### AVL树节点的删除
* 不是真正的删除节点,而是将该节点的右边最小的值和当前节点替换,然后再递归删除那个最小的节点
* 所以最后需要处理的情况只是删除某个节点,该节点有一个节点或者就干脆是一个叶子节点
* 其他和插入节点一样,更新每个节点的高度并且根据平衡度适当旋转节点


# 红黑树
红黑树不是严格的平衡二叉树,AVL树是
## 红黑树的节点结构
left
right
value
height
color
### 查询

### 删除

### 插入

